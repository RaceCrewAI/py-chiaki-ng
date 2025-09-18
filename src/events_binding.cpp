/**
 * events_binding.cpp - Event handling Python bindings
 * 
 * This file contains the Python bindings for ChiakiEvent and
 * event handling functionality.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <chiaki/session.h>

namespace py = pybind11;

void init_events_binding(py::module& m) {
    // Event types
    py::enum_<ChiakiEventType>(m, "EventType")
        .value("CONNECTED", CHIAKI_EVENT_CONNECTED)
        .value("LOGIN_PIN_REQUEST", CHIAKI_EVENT_LOGIN_PIN_REQUEST)
        .value("HOLEPUNCH", CHIAKI_EVENT_HOLEPUNCH)
        .value("REGIST", CHIAKI_EVENT_REGIST)
        .value("NICKNAME_RECEIVED", CHIAKI_EVENT_NICKNAME_RECEIVED)
        .value("KEYBOARD_OPEN", CHIAKI_EVENT_KEYBOARD_OPEN)
        .value("KEYBOARD_TEXT_CHANGE", CHIAKI_EVENT_KEYBOARD_TEXT_CHANGE)
        .value("KEYBOARD_REMOTE_CLOSE", CHIAKI_EVENT_KEYBOARD_REMOTE_CLOSE)
        .value("RUMBLE", CHIAKI_EVENT_RUMBLE)
        .value("QUIT", CHIAKI_EVENT_QUIT)
        .value("TRIGGER_EFFECTS", CHIAKI_EVENT_TRIGGER_EFFECTS)
        .value("MOTION_RESET", CHIAKI_EVENT_MOTION_RESET)
        .value("LED_COLOR", CHIAKI_EVENT_LED_COLOR)
        .value("PLAYER_INDEX", CHIAKI_EVENT_PLAYER_INDEX)
        .value("HAPTIC_INTENSITY", CHIAKI_EVENT_HAPTIC_INTENSITY)
        .value("TRIGGER_INTENSITY", CHIAKI_EVENT_TRIGGER_INTENSITY)
        .export_values();
    
    // Quit reasons
    py::enum_<ChiakiQuitReason>(m, "QuitReason")
        .value("NONE", CHIAKI_QUIT_REASON_NONE)
        .value("STOPPED", CHIAKI_QUIT_REASON_STOPPED)
        .value("SESSION_REQUEST_UNKNOWN", CHIAKI_QUIT_REASON_SESSION_REQUEST_UNKNOWN)
        .value("SESSION_REQUEST_CONNECTION_REFUSED", CHIAKI_QUIT_REASON_SESSION_REQUEST_CONNECTION_REFUSED)
        .value("SESSION_REQUEST_RP_IN_USE", CHIAKI_QUIT_REASON_SESSION_REQUEST_RP_IN_USE)
        .value("SESSION_REQUEST_RP_CRASH", CHIAKI_QUIT_REASON_SESSION_REQUEST_RP_CRASH)
        .value("SESSION_REQUEST_RP_VERSION_MISMATCH", CHIAKI_QUIT_REASON_SESSION_REQUEST_RP_VERSION_MISMATCH)
        .value("CTRL_UNKNOWN", CHIAKI_QUIT_REASON_CTRL_UNKNOWN)
        .value("CTRL_CONNECT_FAILED", CHIAKI_QUIT_REASON_CTRL_CONNECT_FAILED)
        .value("CTRL_CONNECTION_REFUSED", CHIAKI_QUIT_REASON_CTRL_CONNECTION_REFUSED)
        .value("STREAM_CONNECTION_UNKNOWN", CHIAKI_QUIT_REASON_STREAM_CONNECTION_UNKNOWN)
        .value("STREAM_CONNECTION_REMOTE_DISCONNECTED", CHIAKI_QUIT_REASON_STREAM_CONNECTION_REMOTE_DISCONNECTED)
        .value("STREAM_CONNECTION_REMOTE_SHUTDOWN", CHIAKI_QUIT_REASON_STREAM_CONNECTION_REMOTE_SHUTDOWN)
        .value("PSN_REGIST_FAILED", CHIAKI_QUIT_REASON_PSN_REGIST_FAILED)
        .export_values();
    
    // Utility functions
    m.def("quit_reason_string", [](ChiakiQuitReason reason) {
        const char* str = chiaki_quit_reason_string(reason);
        return str ? std::string(str) : std::string("Unknown");
    }, "Get human-readable string for quit reason");
    
    m.def("quit_reason_is_error", [](ChiakiQuitReason reason) {
        return chiaki_quit_reason_is_error(reason);
    }, "Check if quit reason indicates an error");
}
