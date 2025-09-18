"""
Computer Vision Example for py-chiaki-ng

This example demonstrates how to use py-chiaki-ng with OpenCV for
automated gameplay based on computer vision analysis.
"""

import sys
import time
import asyncio
from typing import Optional

try:
    import cv2
    import numpy as np
    CV2_AVAILABLE = True
except ImportError:
    CV2_AVAILABLE = False


class GameplayAutomator:
    """
    Example class showing how to combine py-chiaki-ng with computer vision
    for automated PlayStation gameplay.
    """
    
    def __init__(self, host: str, regist_key: str):
        self.host = host
        self.regist_key = regist_key
        self.session = None
        self.controller = None
        self.running = False
        self.latest_frame = None
        
    def initialize(self):
        """Initialize the Remote Play session"""
        try:
            from py_chiaki_ng import Session, ControllerState
            
            self.session = Session()
            self.controller = ControllerState()
            
            # Set up session callbacks
            self.session.set_video_callback(self._on_video_frame)
            self.session.set_event_callback(self._on_event)
            
            # Initialize connection
            if not self.session.initialize(self.host, self.regist_key):
                raise RuntimeError("Failed to initialize session")
                
            print(f"✅ Session initialized for {self.host}")
            return True
            
        except ImportError:
            print("❌ py-chiaki-ng bindings not available")
            return False
        except Exception as e:
            print(f"❌ Initialization failed: {e}")
            return False
    
    def _on_video_frame(self, frame_data, size, frames_lost, frame_recovered):
        """Callback for video frames from PlayStation"""
        try:
            if not CV2_AVAILABLE:
                return True  # Accept frame but can't process
                
            # Convert frame data to numpy array for OpenCV
            # Note: This is simplified - real implementation would need
            # proper H.264 decoding via FFmpeg
            frame_array = np.frombuffer(frame_data, dtype=np.uint8)
            
            # Store latest frame for processing
            self.latest_frame = frame_array
            
            # Process frame in background to avoid blocking
            asyncio.create_task(self._process_frame_async(frame_array))
            
            return True  # Accept the frame
            
        except Exception as e:
            print(f"❌ Error processing video frame: {e}")
            return False
    
    def _on_event(self, event_type, event_data):
        """Callback for session events"""
        from py_chiaki_ng import EventType, QuitReason
        
        if event_type == EventType.CONNECTED:
            print("🔗 Connected to PlayStation")
            
        elif event_type == EventType.QUIT:
            reason = event_data.get('reason', 'unknown')
            print(f"🔌 Session ended: {reason}")
            self.running = False
            
        else:
            print(f"📡 Event: {event_type}")
    
    async def _process_frame_async(self, frame_data):
        """Asynchronously process video frame for computer vision"""
        try:
            if not CV2_AVAILABLE:
                return
                
            # Placeholder for computer vision processing
            # In a real implementation, you would:
            # 1. Decode H.264 frame to RGB/BGR
            # 2. Analyze game state (health bars, enemies, items, etc.)
            # 3. Make decisions based on analysis
            # 4. Send appropriate controller inputs
            
            # Example: Detect if we should press X button
            should_press_x = await self._analyze_game_state(frame_data)
            
            if should_press_x:
                await self._press_button('cross')
                
        except Exception as e:
            print(f"❌ Error in frame processing: {e}")
    
    async def _analyze_game_state(self, frame_data) -> bool:
        """
        Analyze game state from video frame.
        Returns True if X button should be pressed.
        """
        # Placeholder for actual computer vision logic
        # Real implementation might:
        # - Detect enemies using object detection
        # - Find UI elements with template matching  
        # - Analyze health/mana bars with color analysis
        # - Detect collectible items
        # - Navigate menus with text recognition
        
        # For demo, randomly decide to press X
        import random
        return random.random() < 0.1  # 10% chance
    
    async def _press_button(self, button_name: str, duration: float = 0.1):
        """Press a controller button for specified duration"""
        if not self.controller or not self.session:
            return
            
        try:
            # Press button
            setattr(self.controller, button_name, True)
            self.session.send_controller_state(self.controller)
            
            # Wait
            await asyncio.sleep(duration)
            
            # Release button
            setattr(self.controller, button_name, False) 
            self.session.send_controller_state(self.controller)
            
            print(f"🎮 Pressed {button_name} button")
            
        except Exception as e:
            print(f"❌ Error pressing button: {e}")
    
    def start(self):
        """Start the automation session"""
        if not self.session:
            print("❌ Session not initialized")
            return False
            
        try:
            if not self.session.start():
                print("❌ Failed to start session")
                return False
                
            print("🚀 Automation started")
            self.running = True
            return True
            
        except Exception as e:
            print(f"❌ Error starting session: {e}")
            return False
    
    def stop(self):
        """Stop the automation session"""
        self.running = False
        
        if self.session:
            try:
                self.session.stop()
                print("⏹️  Session stopped")
            except Exception as e:
                print(f"❌ Error stopping session: {e}")
    
    async def run_automation_loop(self):
        """Main automation loop"""
        print("🔄 Starting automation loop...")
        
        while self.running:
            try:
                # Main automation logic would go here
                # For now, just wait and let callbacks handle everything
                await asyncio.sleep(1.0)
                
            except KeyboardInterrupt:
                print("\n⏹️  Stopping automation...")
                break
            except Exception as e:
                print(f"❌ Error in automation loop: {e}")
                break
        
        self.stop()


def main():
    """Main function demonstrating computer vision automation"""
    print("🤖 py-chiaki-ng Computer Vision Automation Example")
    print("=" * 55)
    
    if not CV2_AVAILABLE:
        print("⚠️  OpenCV not available - computer vision features disabled")
        print("💡 Install with: pip install opencv-python")
    
    # Example configuration (replace with your values)
    host = "192.168.1.100"  # Your PlayStation IP
    regist_key = "0" * 16   # Your registration key (16 bytes)
    
    print(f"🎯 Target PlayStation: {host}")
    print("💡 This is a demo - replace with your actual PlayStation IP and registration key")
    print("\n🔧 Setting up automation...")
    
    try:
        # Create and initialize automator
        automator = GameplayAutomator(host, regist_key)
        
        if not automator.initialize():
            print("❌ Failed to initialize automator")
            return 1
        
        # Note: In a real scenario, you would actually start the session
        # automator.start()
        # asyncio.run(automator.run_automation_loop())
        
        print("✅ Automator initialized successfully!")
        print("\n📝 To actually run automation:")
        print("   1. Update host and regist_key with your PlayStation details")
        print("   2. Uncomment the automation.start() and run_automation_loop() calls")
        print("   3. Implement your computer vision logic in _analyze_game_state()")
        print("   4. Add proper H.264 video decoding")
        
    except Exception as e:
        print(f"❌ Error in demo: {e}")
        return 1
    
    return 0


if __name__ == "__main__":
    sys.exit(main())
