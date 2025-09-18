/**
 * controller_binding.cpp - Controller state Python bindings
 * 
 * This file contains the Python bindings for ChiakiControllerState and
 * controller input functionality.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <chiaki/controller.h>

namespace py = pybind11;

void init_controller_binding(py::module& m) {
    // Controller touch structure
    py::class_<ChiakiControllerTouch>(m, "ControllerTouch")
        .def(py::init<>())
        .def_readwrite("x", &ChiakiControllerTouch::x)
        .def_readwrite("y", &ChiakiControllerTouch::y)
        .def_readwrite("id", &ChiakiControllerTouch::id);
    
    // Main controller state
    py::class_<ChiakiControllerState>(m, "ControllerState")
        .def(py::init<>())
        .def_readwrite("buttons", &ChiakiControllerState::buttons)
        .def_readwrite("l2_state", &ChiakiControllerState::l2_state)
        .def_readwrite("r2_state", &ChiakiControllerState::r2_state)
        .def_readwrite("left_x", &ChiakiControllerState::left_x)
        .def_readwrite("left_y", &ChiakiControllerState::left_y)
        .def_readwrite("right_x", &ChiakiControllerState::right_x)
        .def_readwrite("right_y", &ChiakiControllerState::right_y)
        .def_readwrite("gyro_x", &ChiakiControllerState::gyro_x)
        .def_readwrite("gyro_y", &ChiakiControllerState::gyro_y)
        .def_readwrite("gyro_z", &ChiakiControllerState::gyro_z)
        .def_readwrite("accel_x", &ChiakiControllerState::accel_x)
        .def_readwrite("accel_y", &ChiakiControllerState::accel_y)
        .def_readwrite("accel_z", &ChiakiControllerState::accel_z)
        .def_readwrite("orient_x", &ChiakiControllerState::orient_x)
        .def_readwrite("orient_y", &ChiakiControllerState::orient_y)
        .def_readwrite("orient_z", &ChiakiControllerState::orient_z)
        .def_readwrite("orient_w", &ChiakiControllerState::orient_w)
        .def("set_idle", [](ChiakiControllerState& self) {
            chiaki_controller_state_set_idle(&self);
        }, "Reset controller to idle state")
        .def("start_touch", [](ChiakiControllerState& self, uint16_t x, uint16_t y) {
            return chiaki_controller_state_start_touch(&self, x, y);
        }, "Start a touch at the given coordinates")
        .def("stop_touch", [](ChiakiControllerState& self, uint8_t id) {
            chiaki_controller_state_stop_touch(&self, id);
        }, "Stop a touch with the given ID")
        .def("set_touch_pos", [](ChiakiControllerState& self, uint8_t id, uint16_t x, uint16_t y) {
            chiaki_controller_state_set_touch_pos(&self, id, x, y);
        }, "Set touch position for the given touch ID")
        // Convenience properties for common buttons
        .def_property("cross", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_CROSS) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_CROSS;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_CROSS;
                }
            })
        .def_property("circle", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_MOON) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_MOON;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_MOON;
                }
            })
        .def_property("square", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_BOX) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_BOX;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_BOX;
                }
            })
        .def_property("triangle", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_PYRAMID) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_PYRAMID;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_PYRAMID;
                }
            })
        .def_property("l1", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_L1) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_L1;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_L1;
                }
            })
        .def_property("r1", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_R1) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_R1;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_R1;
                }
            })
        .def_property("options", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_OPTIONS) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_OPTIONS;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_OPTIONS;
                }
            })
        .def_property("share", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_SHARE) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_SHARE;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_SHARE;
                }
            })
        .def_property("ps", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_PS) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_PS;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_PS;
                }
            })
        .def_property("touchpad", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_TOUCHPAD) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_TOUCHPAD;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_TOUCHPAD;
                }
            })
        // D-pad properties
        .def_property("dpad_left", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_DPAD_LEFT) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_DPAD_LEFT;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_DPAD_LEFT;
                }
            })
        .def_property("dpad_right", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_DPAD_RIGHT) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_DPAD_RIGHT;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_DPAD_RIGHT;
                }
            })
        .def_property("dpad_up", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_DPAD_UP) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_DPAD_UP;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_DPAD_UP;
                }
            })
        .def_property("dpad_down", 
            [](const ChiakiControllerState& self) { 
                return (self.buttons & CHIAKI_CONTROLLER_BUTTON_DPAD_DOWN) != 0; 
            },
            [](ChiakiControllerState& self, bool pressed) {
                if (pressed) {
                    self.buttons |= CHIAKI_CONTROLLER_BUTTON_DPAD_DOWN;
                } else {
                    self.buttons &= ~CHIAKI_CONTROLLER_BUTTON_DPAD_DOWN;
                }
            });

    // Controller button enum
    py::enum_<ChiakiControllerButton>(m, "ControllerButton")
        .value("CROSS", CHIAKI_CONTROLLER_BUTTON_CROSS)
        .value("MOON", CHIAKI_CONTROLLER_BUTTON_MOON)
        .value("BOX", CHIAKI_CONTROLLER_BUTTON_BOX) 
        .value("PYRAMID", CHIAKI_CONTROLLER_BUTTON_PYRAMID)
        .value("DPAD_LEFT", CHIAKI_CONTROLLER_BUTTON_DPAD_LEFT)
        .value("DPAD_RIGHT", CHIAKI_CONTROLLER_BUTTON_DPAD_RIGHT)
        .value("DPAD_UP", CHIAKI_CONTROLLER_BUTTON_DPAD_UP)
        .value("DPAD_DOWN", CHIAKI_CONTROLLER_BUTTON_DPAD_DOWN)
        .value("L1", CHIAKI_CONTROLLER_BUTTON_L1)
        .value("R1", CHIAKI_CONTROLLER_BUTTON_R1)
        .value("L3", CHIAKI_CONTROLLER_BUTTON_L3)
        .value("R3", CHIAKI_CONTROLLER_BUTTON_R3)
        .value("OPTIONS", CHIAKI_CONTROLLER_BUTTON_OPTIONS)
        .value("SHARE", CHIAKI_CONTROLLER_BUTTON_SHARE)
        .value("TOUCHPAD", CHIAKI_CONTROLLER_BUTTON_TOUCHPAD)
        .value("PS", CHIAKI_CONTROLLER_BUTTON_PS)
        .export_values();
}
