"""
Basic tests for py-chiaki-ng package structure
"""

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
    assert py_chiaki_ng.__license__ == "AGPL-3.0-only"


def test_package_imports():
    """Test that package can be imported without errors"""
    # Basic import test - more specific imports will be added
    # as modules are implemented
    import py_chiaki_ng
    assert py_chiaki_ng is not None
