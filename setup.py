#!/usr/bin/env python3
"""
PlayStation Remote Play Automation Library
A Python library for automating PlayStation Remote Play with computer vision and controller input.

IMPORTANT: This library builds upon chiaki-ng (the actively maintained fork) rather than
the broken pyremoteplay library. It provides computer vision analysis and automated
controller input for PlayStation Remote Play sessions.
"""

from setuptools import setup, find_packages, Extension
from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11 import get_cmake_dir
import pybind11
import os
import subprocess

# Check if chiaki-ng submodule is available
chiaki_ng_path = "external/chiaki-ng"
if not os.path.exists(os.path.join(chiaki_ng_path, "lib")):
    raise RuntimeError(
        "chiaki-ng submodule not found. Please run:\n"
        "git submodule update --init --recursive"
    )

# Define the extension module
ext_modules = [
    Pybind11Extension(
        "py_chiaki_ng_core",
        sorted([
            "src/py_chiaki_ng.cpp",
            "src/session_binding.cpp", 
            "src/controller_binding.cpp",
            "src/video_binding.cpp",
            "src/events_binding.cpp",
        ]),
        include_dirs=[
            # Add pybind11 includes
            pybind11.get_include(),
            # Add chiaki-ng includes
            os.path.join(chiaki_ng_path, "lib", "include"),
            # System includes will be added by pkg-config
        ],
        define_macros=[
            ("VERSION_INFO", '"dev"'),
        ],
        cxx_std=17,
        # Libraries and link flags will be added by cmake or pkg-config
    ),
]

with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()

# Read requirements from pyproject.toml dependencies instead of requirements.txt
install_requires = [
    "pybind11>=2.10.0",
    "opencv-python>=4.8.0",
    "numpy>=1.21.0",
    "aiohttp>=3.8.0",
    "asyncio-throttle>=1.0.0",
    "loguru>=0.7.0",
    "pydantic>=2.0.0",
]

setup(
    name="py-chiaki-ng",
    version="0.1.0",
    author="RaceCrewAI",
    author_email="contact@racecrew.ai",
    description="Python bindings for chiaki-ng PlayStation Remote Play with computer vision and automation",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/RaceCrewAI/py-chiaki-ng",
    packages=find_packages(),
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
        "Topic :: Games/Entertainment",
        "Topic :: Software Development :: Libraries :: Python Modules",
        "Topic :: Scientific/Engineering :: Image Processing",
    ],
    python_requires=">=3.8",
    install_requires=install_requires,
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    extras_require={
        "dev": [
            "pytest",
            "black",
            "flake8",
            "mypy",
            "pytest-cov",
        ],
        "gui": [
            "PySide6",
        ]
    },
    entry_points={
        "console_scripts": [
            "py-chiaki-ng-demo=py_chiaki_ng.examples.demo:main",
        ],
    },
)
