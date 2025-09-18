# PlayStation Remote Play Automation Library - Copilot Instructions

## Project Overview

This project is a Python library for automating PlayStation Remote Play sessions with computer vision and controller input. It builds upon **chiaki-ng** (the actively maintained C++ fork) rather than the broken pyremoteplay library. The library enables headless automation of PS4/PS5 gameplay through video feed analysis and programmatic controller input.

**Critical Context**: This is a Docker-compatible automation library that CANNOT use screen capture approaches. All video processing must be done through the PlayStation Remote Play protocol directly.

## Project Architecture

- **Language**: Python 3.8+ with C++ bindings to chiaki-ng
- **Core Dependencies**: OpenCV (computer vision), FFmpeg (video processing), pybind11 (C++ bindings)
- **Target Environment**: Docker containers (headless, no GUI/screen capture)
- **Protocol**: PlayStation Remote Play protocol via chiaki-ng C++ library

## Key Implementation Details

**ALWAYS check `implementation_details.md` first** - this file contains:
- Current project state and progress milestones
- Technical decisions and rationale
- Known working vs broken libraries (pyremoteplay is BROKEN)
- Architecture options and their feasibility analysis
- Docker compatibility requirements

## Project Structure

```
/home/jon/git/ai/
├── setup.py                 # Python package configuration
├── requirements.txt         # Python dependencies
├── implementation_details.md # CRITICAL: Current state and milestones
├── .github/
│   └── copilot-instructions.md
├── ps_remote_automation/    # Main Python package (when created)
├── bindings/               # C++ binding code (when created)
└── examples/               # Demo and test scripts (when created)
```

## Build and Development Instructions

**Setup Commands**:
```bash
# Install Python dependencies
pip install -r requirements.txt

# Install development dependencies
pip install -e ".[dev]"

# Install GUI dependencies (optional)
pip install -e ".[gui]"
```

**Testing**:
```bash
# Run tests
pytest

# Run with coverage
pytest --cov=ps_remote_automation
```

**Code Quality**:
```bash
# Format code
black ps_remote_automation/

# Lint code
flake8 ps_remote_automation/

# Type checking
mypy ps_remote_automation/
```

## Critical Technical Constraints

1. **Docker Compatibility**: Must work in headless containers - no screen capture
2. **Protocol Dependency**: Must use chiaki-ng (working) not pyremoteplay (broken since 2023)
3. **Memory Constraints**: This agent has limited memory - always reference `implementation_details.md` for context
4. **C++ Integration**: Requires Python bindings to chiaki-ng's C++ API

## Current Development Phase

**Check `implementation_details.md` for current milestone status**

The project is in architecture planning phase. Key decisions needed:
- C++ binding implementation approach
- Video frame extraction method
- Controller input injection mechanism
- Computer vision integration strategy

## Coding Standards

- Use type hints for all functions and classes
- Follow PEP 8 style guidelines (enforced by black)
- Document all public APIs with docstrings
- Use async/await for I/O operations where appropriate
- Prefer composition over inheritance
- Use dependency injection for testability

## Important Notes for Future Agent Sessions

1. **Always read `implementation_details.md` first** - contains critical context
2. **Check milestone status** before making changes
3. **Remember Docker constraints** - no GUI/screen capture approaches
4. **Validate chiaki-ng compatibility** - it's the only working solution
5. **Test in headless environment** - GUI dependencies break Docker deployment
6. **Update milestones** when completing major tasks

## External Dependencies

- **chiaki-ng**: Active C++ PlayStation Remote Play client (GitHub: streetpea/chiaki-ng)
- **OpenCV**: Computer vision processing
- **FFmpeg**: Video decoding and processing
- **pybind11**: C++ to Python binding generation
- **numpy**: Numerical operations for video frames

Trust these instructions and only search for additional information if something is incomplete or found to be incorrect.
