"""
py-chiaki-ng: Python bindings for chiaki-ng PlayStation Remote Play

A Python library for automating PlayStation Remote Play sessions with computer vision
and controller input. Built on the actively maintained chiaki-ng C++ library.

Features:
- Headless PlayStation Remote Play automation
- Real-time video frame access for computer vision
- Programmatic controller input injection  
- Docker-compatible (no screen capture required)
- Support for PS4 and PS5 consoles

Usage:
    >>> from py_chiaki_ng import Session, ControllerState
    >>> session = Session(host='192.168.1.100')
    >>> session.start()
    >>> # Process video frames and send controller input
"""

__version__ = "0.1.0"
__author__ = "RaceCrewAI"
__email__ = "contact@racecrew.ai"
__license__ = "AGPL-3.0-only"

# Core imports will be added as modules are implemented
# from .session import Session
# from .controller import ControllerState  
# from .video import VideoFrame
# from .events import EventHandler

__all__ = [
    # Will be populated as modules are implemented
    # "Session",
    # "ControllerState", 
    # "VideoFrame",
    # "EventHandler",
]
