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
    >>> session = Session()
    >>> session.initialize(host='192.168.1.100', regist_key='your_key')
    >>> session.start()
    >>> # Process video frames and send controller input
"""

__version__ = "0.1.0"
__author__ = "RaceCrewAI"
__email__ = "contact@racecrew.ai"
__license__ = "MIT"

# Import core C++ bindings
try:
    from py_chiaki_ng_core import (
        # Core classes
        Session,
        ControllerState,
        VideoFrame,
        VideoProfile,
        
        # Enums
        ErrorCode,
        Target,
        Codec,
        EventType,
        QuitReason,
        ControllerButton,
        VideoResolutionPreset,
        VideoFPSPreset,
        
        # Utility functions
        quit_reason_string,
        quit_reason_is_error,
        create_video_frame,
        
        # Constants
        VIDEO_BUFFER_PADDING_SIZE,
    )
except ImportError as e:
    # If C++ bindings aren't built yet, provide helpful error message
    import sys
    print(f"❌ C++ bindings not available: {e}", file=sys.stderr)
    print("💡 Please build the C++ extension first:", file=sys.stderr)
    print("   ./build.sh", file=sys.stderr)
    print("   pip install -e .", file=sys.stderr)
    
    # Define placeholder classes for development
    class Session:
        def __init__(self): 
            raise ImportError("C++ bindings not built. Run ./build.sh first.")
    
    class ControllerState:
        def __init__(self): 
            raise ImportError("C++ bindings not built. Run ./build.sh first.")
    
    class VideoFrame:
        def __init__(self): 
            raise ImportError("C++ bindings not built. Run ./build.sh first.")

__all__ = [
    # Core classes
    "Session",
    "ControllerState", 
    "VideoFrame",
    "VideoProfile",
    
    # Enums
    "ErrorCode",
    "Target", 
    "Codec",
    "EventType",
    "QuitReason",
    "ControllerButton",
    "VideoResolutionPreset",
    "VideoFPSPreset",
    
    # Utility functions
    "quit_reason_string",
    "quit_reason_is_error", 
    "create_video_frame",
]
