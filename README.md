# py-chiaki-ng

Python bindings for [chiaki-ng](https://github.com/streetpea/chiaki-ng) - PlayStation Remote Play automation with computer vision and controller input.

[![PyPI version](https://badge.fury.io/py/py-chiaki-ng.svg)](https://badge.fury.io/py/py-chiaki-ng)
[![Python Support](https://img.shields.io/pypi/pyversions/py-chiaki-ng.svg)](https://pypi.org/project/py-chiaki-ng/)
[![License: AGPL v3](https://img.shields.io/badge/License-AGPL%20v3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)

## Overview

py-chiaki-ng enables programmatic automation of PlayStation Remote Play sessions through Python. Unlike screen capture approaches, this library provides direct access to the video stream and controller input at the protocol level, making it perfect for headless automation, computer vision applications, and Docker deployments.

### Key Features

- 🎮 **Direct Protocol Access**: Real-time video frames and controller input via chiaki-ng
- 🤖 **Computer Vision Ready**: OpenCV integration for automated gameplay analysis  
- 🐳 **Docker Compatible**: Headless operation without GUI dependencies
- 🎯 **Low Latency**: Direct memory access to video frames, no screen capture overhead
- 📡 **Network Based**: Works remotely over network, not limited to local machine
- 🔧 **Full Control**: Complete controller state manipulation (buttons, analog sticks, touchpad, motion)

### Supported Platforms

- PlayStation 4 (all firmware versions)
- PlayStation 5 (latest firmware supported via chiaki-ng)
- Linux, macOS, Windows
- Docker containers (headless)

## Installation

### From PyPI (Recommended)

```bash
pip install py-chiaki-ng
```

### From Source

```bash
git clone https://github.com/RaceCrewAI/py-chiaki-ng.git
cd py-chiaki-ng
pip install -e .
```

### Development Installation

```bash
git clone https://github.com/RaceCrewAI/py-chiaki-ng.git
cd py-chiaki-ng
pip install -e ".[dev]"
```

## Quick Start

```python
from py_chiaki_ng import Session, ControllerState
import cv2

# Connect to PlayStation
session = Session(
    host='192.168.1.100',  # Your PlayStation's IP
    # Registration key from PlayStation setup
)

# Start Remote Play session
session.start()

# Set up computer vision processing
def process_frame(frame):
    # Your computer vision logic here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # Detect game elements, make decisions...
    return should_press_x_button

# Set up controller automation
controller = ControllerState()

# Main automation loop
for frame in session.video_stream():
    if process_frame(frame):
        controller.cross = True  # Press X button
        session.send_controller_state(controller)
        controller.cross = False  # Release X button

session.stop()
```

## Use Cases

### Automated Gameplay

```python
# Automate repetitive tasks in games
def farm_currency():
    while session.is_connected():
        frame = session.get_latest_frame()
        
        if detect_enemy(frame):
            controller.cross = True  # Attack
        elif detect_loot(frame):
            controller.square = True  # Pick up
        
        session.send_controller_state(controller)
```

### Game Testing

```python
# Automated regression testing for game developers
def test_game_mechanics():
    test_cases = load_test_scenarios()
    
    for scenario in test_cases:
        session.navigate_to_test_area(scenario.location)
        result = session.execute_inputs(scenario.inputs)
        assert_expected_behavior(result, scenario.expected)
```

### AI Training

```python
# Collect training data for reinforcement learning
def collect_training_data():
    states = []
    actions = []
    rewards = []
    
    while collecting:
        state = session.get_game_state()
        action = expert_player.get_action(state)
        reward = session.execute_action(action)
        
        states.append(state)
        actions.append(action)
        rewards.append(reward)
```

## Docker Support

py-chiaki-ng is designed for headless operation in Docker containers:

```dockerfile
FROM python:3.11-slim

# Install system dependencies for chiaki-ng
RUN apt-get update && apt-get install -y \\
    cmake \\
    pkg-config \\
    libavcodec-dev \\
    libavformat-dev \\
    libswscale-dev \\
    && rm -rf /var/lib/apt/lists/*

# Install py-chiaki-ng
RUN pip install py-chiaki-ng

COPY your_automation_script.py /app/
WORKDIR /app

CMD ["python", "your_automation_script.py"]
```

## Architecture

py-chiaki-ng is built on top of the excellent [chiaki-ng](https://github.com/streetpea/chiaki-ng) C++ library:

```
┌─────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│   Your Python  │    │   py-chiaki-ng   │    │   chiaki-ng     │
│   Application   │◄──►│   (pybind11)     │◄──►│   (C++ Library) │
└─────────────────┘    └──────────────────┘    └─────────────────┘
                                ▲                         ▲
                                │                         │
                       ┌────────▼────────┐       ┌───────▼────────┐
                       │ Computer Vision │       │ PlayStation    │
                       │ (OpenCV)        │       │ Remote Play    │
                       └─────────────────┘       │ Protocol       │
                                                 └────────────────┘
```

## Why py-chiaki-ng?

### vs. Screen Capture Approaches
- ❌ Screen capture: High latency, requires GUI, breaks in Docker
- ✅ py-chiaki-ng: Direct video access, headless, Docker-ready

### vs. pyremoteplay  
- ❌ pyremoteplay: Broken since 2023, incompatible with modern firmware
- ✅ py-chiaki-ng: Based on actively maintained chiaki-ng, latest firmware support

### vs. Manual Automation
- ❌ Manual tools: Limited to local machine, GUI required
- ✅ py-chiaki-ng: Network-based, scriptable, perfect for CI/CD

## Documentation

- [API Reference](https://py-chiaki-ng.readthedocs.io/en/latest/api/)
- [Examples](https://github.com/RaceCrewAI/py-chiaki-ng/tree/main/examples)
- [Docker Guide](https://py-chiaki-ng.readthedocs.io/en/latest/docker/)
- [Computer Vision Integration](https://py-chiaki-ng.readthedocs.io/en/latest/cv/)

## Contributing

Contributions are welcome! Please see our [Contributing Guide](CONTRIBUTING.md).

### Development Setup

```bash
git clone https://github.com/RaceCrewAI/py-chiaki-ng.git
cd py-chiaki-ng
pip install -e ".[dev]"
pre-commit install
```

### Running Tests

```bash
pytest
pytest --cov=py_chiaki_ng  # With coverage
```

## License

This project is licensed under the AGPL-3.0 License - see the [LICENSE](LICENSE) file for details.

Built on [chiaki-ng](https://github.com/streetpea/chiaki-ng) by streetpea and the chiaki community.

## Support

- 🐛 [Bug Reports](https://github.com/RaceCrewAI/py-chiaki-ng/issues)
- 💡 [Feature Requests](https://github.com/RaceCrewAI/py-chiaki-ng/discussions)
- 📖 [Documentation](https://py-chiaki-ng.readthedocs.io/)
- 💬 [Discord Community](https://discord.gg/racecrew)

---

Made with ❤️ by [RaceCrewAI](https://github.com/RaceCrewAI)
