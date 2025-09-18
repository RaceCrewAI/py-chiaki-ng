/**
 * py_chiaki_ng.cpp - Main Python binding module
 * 
 * This file contains the main pybind11 module definition that exposes
 * chiaki-ng functionality to Python.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/functional.h>

// Chiaki headers
#include <chiaki/session.h>
#include <chiaki/controller.h>
#include <chiaki/log.h>
#include <chiaki/thread.h>

// Binding declarations
void init_session_binding(pybind11::module& m);
void init_controller_binding(pybind11::module& m);
void init_video_binding(pybind11::module& m);
void init_events_binding(pybind11::module& m);

namespace py = pybind11;

PYBIND11_MODULE(py_chiaki_ng_core, m) {
    m.doc() = "Python bindings for chiaki-ng PlayStation Remote Play";
    
    // Version info
    m.attr("__version__") = "0.1.0";
    
    // Initialize all binding modules
    init_session_binding(m);
    init_controller_binding(m);
    init_video_binding(m);
    init_events_binding(m);
    
    // Basic enums and constants
    py::enum_<ChiakiErrorCode>(m, "ErrorCode")
        .value("SUCCESS", CHIAKI_ERR_SUCCESS)
        .value("UNKNOWN", CHIAKI_ERR_UNKNOWN)
        .value("PARSE_ADDR", CHIAKI_ERR_PARSE_ADDR)
        .value("THREAD", CHIAKI_ERR_THREAD)
        .value("MEMORY", CHIAKI_ERR_MEMORY)
        .value("OVERFLOW", CHIAKI_ERR_OVERFLOW)
        .value("NETWORK", CHIAKI_ERR_NETWORK)
        .value("CONNECTION_REFUSED", CHIAKI_ERR_CONNECTION_REFUSED)
        .value("HOST_DOWN", CHIAKI_ERR_HOST_DOWN)
        .value("HOST_UNREACH", CHIAKI_ERR_HOST_UNREACH)
        .value("DISCONNECTED", CHIAKI_ERR_DISCONNECTED)
        .value("INVALID_DATA", CHIAKI_ERR_INVALID_DATA)
        .value("BUF_TOO_SMALL", CHIAKI_ERR_BUF_TOO_SMALL)
        .value("MUTEX", CHIAKI_ERR_MUTEX)
        .value("COND", CHIAKI_ERR_COND)
        .value("TIMEOUT", CHIAKI_ERR_TIMEOUT)
        .value("CANCELED", CHIAKI_ERR_CANCELED)
        .value("INVALID_RESPONSE", CHIAKI_ERR_INVALID_RESPONSE)
        .value("INVALID_MAC", CHIAKI_ERR_INVALID_MAC)
        .value("VERSION_MISMATCH", CHIAKI_ERR_VERSION_MISMATCH)
        .export_values();
        
    py::enum_<ChiakiTarget>(m, "Target")
        .value("PS4_UNKNOWN", CHIAKI_TARGET_PS4_UNKNOWN)
        .value("PS4_9", CHIAKI_TARGET_PS4_9)
        .value("PS4_10", CHIAKI_TARGET_PS4_10)
        .value("PS5_UNKNOWN", CHIAKI_TARGET_PS5_UNKNOWN)
        .value("PS5_1", CHIAKI_TARGET_PS5_1)
        .export_values();
        
    py::enum_<ChiakiCodec>(m, "Codec")
        .value("H264", CHIAKI_CODEC_H264)
        .value("H265", CHIAKI_CODEC_H265)
        .export_values();
}
