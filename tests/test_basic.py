"""
Basic tests for py-chiaki-ng package structure
"""

import pytest
import py_chiaki_ng


def test_package_version():
    """Test that package version is accessible"""
    assert hasattr(py_chiaki_ng, "__version__")
    assert py_chiaki_ng.__version__ == "0.1.0"


def test_package_metadata():
    """Test that package metadata is accessible"""
    assert hasattr(py_chiaki_ng, "__author__")
    assert hasattr(py_chiaki_ng, "__email__")
    assert hasattr(py_chiaki_ng, "__license__")
    
    assert py_chiaki_ng.__author__ == "RaceCrewAI"
    assert py_chiaki_ng.__email__ == "contact@racecrew.ai"
    assert py_chiaki_ng.__license__ == "MIT"


def test_package_imports():
    """Test that package can be imported without errors"""
    # Basic import test - more specific imports will be added
    # as modules are implemented
    import py_chiaki_ng
    assert py_chiaki_ng is not None


@pytest.mark.skipif(
    not hasattr(py_chiaki_ng, 'Session') or 
    (hasattr(py_chiaki_ng.Session, '__init__') and 
     'ImportError' in str(py_chiaki_ng.Session.__init__.__doc__ or '')),
    reason="C++ bindings not built"
)
def test_core_classes_available():
    """Test that core C++ binding classes are available"""
    # Only run if C++ bindings are built
    assert hasattr(py_chiaki_ng, 'Session')
    assert hasattr(py_chiaki_ng, 'ControllerState')
    assert hasattr(py_chiaki_ng, 'VideoFrame')
    
    # Test basic instantiation
    session = py_chiaki_ng.Session()
    controller = py_chiaki_ng.ControllerState()
    
    assert session is not None
    assert controller is not None


@pytest.mark.skipif(
    not hasattr(py_chiaki_ng, 'Session') or 
    (hasattr(py_chiaki_ng.Session, '__init__') and 
     'ImportError' in str(py_chiaki_ng.Session.__init__.__doc__ or '')),
    reason="C++ bindings not built"
)
def test_controller_state_basic():
    """Test basic controller state functionality"""
    controller = py_chiaki_ng.ControllerState()
    
    # Test button properties
    controller.cross = True
    assert controller.cross == True
    
    controller.cross = False
    assert controller.cross == False
    
    # Test analog stick values
    controller.left_x = 12000
    controller.left_y = -8000
    assert controller.left_x == 12000
    assert controller.left_y == -8000
    
    # Test idle state
    controller.set_idle()
    assert controller.cross == False
