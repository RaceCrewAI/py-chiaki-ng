/**
 * session_binding.cpp - Session management Python bindings
 * 
 * This file contains the Python bindings for ChiakiSession and related
 * connection management functionality.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <chiaki/session.h>
#include <chiaki/log.h>
#include <memory>
#include <functional>

namespace py = pybind11;

// Logger wrapper to redirect chiaki logs to Python
class PythonLogger {
public:
    PythonLogger(std::function<void(const std::string&, int)> callback) 
        : python_callback(callback) {
        chiaki_log_init(&log, CHIAKI_LOG_ALL, log_callback, this);
    }
    
    ~PythonLogger() {
        chiaki_log_fini(&log);
    }
    
    ChiakiLog* get_log() { return &log; }

private:
    ChiakiLog log;
    std::function<void(const std::string&, int)> python_callback;
    
    static void log_callback(ChiakiLogLevel level, const char* msg, void* user) {
        auto* logger = static_cast<PythonLogger*>(user);
        if (logger->python_callback) {
            logger->python_callback(std::string(msg), static_cast<int>(level));
        }
    }
};

// Session wrapper class
class SessionWrapper {
public:
    SessionWrapper() : logger(nullptr) {
        // Initialize with default logger for now
        logger = std::make_unique<PythonLogger>([](const std::string& msg, int level) {
            // Default: print to stdout (can be overridden)
            printf("[ChiakiLog:%d] %s\n", level, msg.c_str());
        });
    }
    
    ~SessionWrapper() {
        if (session_initialized) {
            stop();
            chiaki_session_fini(&session);
        }
    }
    
    bool initialize(const std::string& host, const std::string& regist_key) {
        if (session_initialized) {
            return false; // Already initialized
        }
        
        // Set up connect info
        memset(&connect_info, 0, sizeof(connect_info));
        connect_info.host = host.c_str();
        connect_info.ps5 = true; // Default to PS5, can be made configurable
        
        // Copy registration key
        if (regist_key.length() >= CHIAKI_SESSION_AUTH_SIZE) {
            memcpy(connect_info.regist_key, regist_key.c_str(), CHIAKI_SESSION_AUTH_SIZE);
        } else {
            // Pad with zeros if key is shorter
            memcpy(connect_info.regist_key, regist_key.c_str(), regist_key.length());
            memset(connect_info.regist_key + regist_key.length(), 0, 
                   CHIAKI_SESSION_AUTH_SIZE - regist_key.length());
        }
        
        // Set default video profile
        chiaki_connect_video_profile_preset(&connect_info.video_profile, 
                                           CHIAKI_VIDEO_RESOLUTION_PRESET_1080p,
                                           CHIAKI_VIDEO_FPS_PRESET_60);
        
        // Initialize session
        ChiakiErrorCode err = chiaki_session_init(&session, &connect_info, logger->get_log());
        if (err != CHIAKI_ERR_SUCCESS) {
            return false;
        }
        
        session_initialized = true;
        return true;
    }
    
    bool start() {
        if (!session_initialized) {
            return false;
        }
        
        ChiakiErrorCode err = chiaki_session_start(&session);
        return err == CHIAKI_ERR_SUCCESS;
    }
    
    bool stop() {
        if (!session_initialized) {
            return false;
        }
        
        ChiakiErrorCode err = chiaki_session_stop(&session);
        return err == CHIAKI_ERR_SUCCESS;
    }
    
    bool join() {
        if (!session_initialized) {
            return false;
        }
        
        ChiakiErrorCode err = chiaki_session_join(&session);
        return err == CHIAKI_ERR_SUCCESS;
    }
    
    void set_video_callback(std::function<bool(py::bytes, size_t, int32_t, bool)> callback) {
        video_callback = callback;
        chiaki_session_set_video_sample_cb(&session, video_sample_callback, this);
    }
    
    void set_event_callback(std::function<void(int, py::dict)> callback) {
        event_callback = callback;
        chiaki_session_set_event_cb(&session, event_callback_wrapper, this);
    }
    
    bool send_controller_state(const ChiakiControllerState& state) {
        if (!session_initialized) {
            return false;
        }
        
        ChiakiErrorCode err = chiaki_session_set_controller_state(&session, 
                                                                const_cast<ChiakiControllerState*>(&state));
        return err == CHIAKI_ERR_SUCCESS;
    }

private:
    ChiakiSession session;
    ChiakiConnectInfo connect_info;
    std::unique_ptr<PythonLogger> logger;
    bool session_initialized = false;
    
    std::function<bool(py::bytes, size_t, int32_t, bool)> video_callback;
    std::function<void(int, py::dict)> event_callback;
    
    static bool video_sample_callback(uint8_t* buf, size_t buf_size, int32_t frames_lost, 
                                     bool frame_recovered, void* user) {
        auto* wrapper = static_cast<SessionWrapper*>(user);
        if (wrapper->video_callback) {
            py::bytes data(reinterpret_cast<char*>(buf), buf_size);
            return wrapper->video_callback(data, buf_size, frames_lost, frame_recovered);
        }
        return true; // Default: accept all frames
    }
    
    static void event_callback_wrapper(ChiakiEvent* event, void* user) {
        auto* wrapper = static_cast<SessionWrapper*>(user);
        if (wrapper->event_callback) {
            py::dict event_data;
            event_data["type"] = static_cast<int>(event->type);
            
            // Add type-specific data
            switch (event->type) {
                case CHIAKI_EVENT_QUIT:
                    event_data["reason"] = static_cast<int>(event->quit.reason);
                    if (event->quit.reason_str) {
                        event_data["reason_str"] = std::string(event->quit.reason_str);
                    }
                    break;
                default:
                    // Add more event types as needed
                    break;
            }
            
            wrapper->event_callback(static_cast<int>(event->type), event_data);
        }
    }
};

void init_session_binding(py::module& m) {
    // Connect info structure
    py::class_<ChiakiConnectVideoProfile>(m, "VideoProfile")
        .def(py::init<>())
        .def_readwrite("width", &ChiakiConnectVideoProfile::width)
        .def_readwrite("height", &ChiakiConnectVideoProfile::height)
        .def_readwrite("max_fps", &ChiakiConnectVideoProfile::max_fps)
        .def_readwrite("bitrate", &ChiakiConnectVideoProfile::bitrate);
    
    // Session wrapper
    py::class_<SessionWrapper>(m, "Session")
        .def(py::init<>())
        .def("initialize", &SessionWrapper::initialize,
             "Initialize session with host and registration key",
             py::arg("host"), py::arg("regist_key"))
        .def("start", &SessionWrapper::start,
             "Start the Remote Play session")
        .def("stop", &SessionWrapper::stop,
             "Stop the Remote Play session")
        .def("join", &SessionWrapper::join,
             "Wait for session to complete")
        .def("set_video_callback", &SessionWrapper::set_video_callback,
             "Set callback for video frame data")
        .def("set_event_callback", &SessionWrapper::set_event_callback,
             "Set callback for session events")
        .def("send_controller_state", &SessionWrapper::send_controller_state,
             "Send controller input to PlayStation");
    
    // Video resolution presets
    py::enum_<ChiakiVideoResolutionPreset>(m, "VideoResolutionPreset")
        .value("PRESET_360p", CHIAKI_VIDEO_RESOLUTION_PRESET_360p)
        .value("PRESET_540p", CHIAKI_VIDEO_RESOLUTION_PRESET_540p) 
        .value("PRESET_720p", CHIAKI_VIDEO_RESOLUTION_PRESET_720p)
        .value("PRESET_1080p", CHIAKI_VIDEO_RESOLUTION_PRESET_1080p)
        .export_values();
        
    // Video FPS presets
    py::enum_<ChiakiVideoFPSPreset>(m, "VideoFPSPreset")
        .value("PRESET_30", CHIAKI_VIDEO_FPS_PRESET_30)
        .value("PRESET_60", CHIAKI_VIDEO_FPS_PRESET_60)
        .export_values();
}
