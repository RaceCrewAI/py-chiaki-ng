#!/bin/bash
# build.sh - Build script for py-chiaki-ng
#
# This script handles the complex build process including:
# 1. Checking system dependencies
# 2. Building chiaki-ng C++ library
# 3. Compiling Python bindings

set -e  # Exit on any error

echo "🔨 Building py-chiaki-ng..."

# Check for required system dependencies
check_dependency() {
    if ! command -v "$1" &> /dev/null; then
        echo "❌ Required dependency '$1' not found"
        echo "💡 Please install it using your system package manager"
        exit 1
    fi
}

echo "📦 Checking system dependencies..."
check_dependency cmake
check_dependency pkg-config

# Check for required libraries
check_pkg_config() {
    if ! pkg-config --exists "$1"; then
        echo "❌ Required library '$1' not found"
        echo "💡 Please install development packages for $1"
        exit 1
    fi
}

echo "📚 Checking required libraries..."
check_pkg_config libavcodec
check_pkg_config libavformat
check_pkg_config libavutil
check_pkg_config libswscale

# Initialize submodules if needed
if [ ! -f "external/chiaki-ng/CMakeLists.txt" ]; then
    echo "📥 Initializing chiaki-ng submodule..."
    git submodule update --init --recursive
fi

# Create build directory
BUILD_DIR="cmake_build"
echo "🏗️  Creating build directory: $BUILD_DIR"
mkdir -p "$BUILD_DIR"

# Run CMake configuration
echo "⚙️  Configuring with CMake..."
cd "$BUILD_DIR"
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCHIAKI_ENABLE_CLI=OFF \
    -DCHIAKI_ENABLE_GUI=OFF \
    -DCHIAKI_ENABLE_ANDROID=OFF

# Build the project
echo "🔧 Building C++ library..."
cmake --build . --config Release -j$(nproc)

cd ..

# Now build the Python package
echo "🐍 Building Python package..."
python setup.py build_ext --inplace

echo "✅ Build completed successfully!"
echo ""
echo "🚀 You can now install the package with:"
echo "   pip install -e ."
echo ""
echo "🧪 Or run tests with:"  
echo "   python -m pytest tests/"
