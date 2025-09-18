"""
Demo script for py-chiaki-ng

This script demonstrates basic usage of the PlayStation Remote Play automation library.
"""

import sys
import time

def main():
    """Main demo function showing basic py-chiaki-ng usage"""
    print("🎮 py-chiaki-ng Demo")
    print("=" * 50)
    
    try:
        # Import the main library
        from py_chiaki_ng import Session, ControllerState, ErrorCode
        
        print("✅ C++ bindings loaded successfully!")
        print(f"📦 Available classes: Session, ControllerState")
        print(f"📡 Available error codes: {list(ErrorCode.__members__.keys())[:5]}...")
        
        # Demo 1: Create session and controller
        print("\n🔧 Demo 1: Creating session and controller objects")
        session = Session()
        controller = ControllerState()
        
        print("✅ Session created")
        print("✅ Controller state created")
        
        # Demo 2: Show controller state manipulation
        print("\n🎯 Demo 2: Controller state manipulation")
        controller.set_idle()
        print("🎮 Controller set to idle state")
        
        # Test button properties
        controller.cross = True
        print(f"❌ Cross button pressed: {controller.cross}")
        
        controller.cross = False
        controller.triangle = True
        print(f"🔺 Triangle button pressed: {controller.triangle}")
        
        # Test analog sticks
        controller.left_x = 12000  # Range is typically -32768 to 32767
        controller.left_y = -8000
        print(f"🕹️  Left stick: ({controller.left_x}, {controller.left_y})")
        
        # Demo 3: Connection example (without actually connecting)
        print("\n📡 Demo 3: Connection setup example")
        print("💡 To actually connect to a PlayStation:")
        print("   session.initialize(host='192.168.1.100', regist_key='your_registration_key')")
        print("   session.start()")
        print("   # Set up video and event callbacks")
        print("   # Send controller input with session.send_controller_state(controller)")
        print("   session.stop()")
        
        print("\n✅ Demo completed successfully!")
        
    except ImportError as e:
        print(f"❌ C++ bindings not available: {e}")
        print("\n🔧 To build the bindings:")
        print("   1. Install system dependencies (cmake, pkg-config, ffmpeg-dev)")
        print("   2. Run: ./build.sh")
        print("   3. Run: pip install -e .")
        print("   4. Try the demo again")
        return 1
        
    except Exception as e:
        print(f"❌ Error during demo: {e}")
        return 1
        
    return 0

if __name__ == "__main__":
    sys.exit(main())
