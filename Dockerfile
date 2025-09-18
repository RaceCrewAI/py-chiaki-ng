# Dockerfile for py-chiaki-ng development and testing
FROM python:3.11-slim

# Install system dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    build-essential \
    pkg-config \
    git \
    libavcodec-dev \
    libavformat-dev \
    libavutil-dev \
    libswscale-dev \
    libssl-dev \
    libprotobuf-dev \
    protobuf-compiler \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy requirements and install Python dependencies
COPY pyproject.toml setup.py ./
RUN pip install --upgrade pip

# Copy source code
COPY . .

# Initialize submodules and build
RUN git submodule update --init --recursive
RUN chmod +x build.sh
RUN ./build.sh

# Install the package
RUN pip install -e .

# Set environment variables
ENV PYTHONPATH=/app
ENV PYTHONUNBUFFERED=1

# Default command
CMD ["python", "-m", "py_chiaki_ng.examples.demo"]
