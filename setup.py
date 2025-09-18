#!/usr/bin/env python3
"""
PlayStation Remote Play Automation Library
A Python library for automating PlayStation Remote Play with computer vision and controller input.

IMPORTANT: This library builds upon chiaki-ng (the actively maintained fork) rather than
the broken pyremoteplay library. It provides computer vision analysis and automated
controller input for PlayStation Remote Play sessions.
"""

from setuptools import setup, find_packages

with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()

with open("requirements.txt", "r", encoding="utf-8") as fh:
    requirements = [line.strip() for line in fh if line.strip() and not line.startswith("#")]

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
    install_requires=requirements,
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
