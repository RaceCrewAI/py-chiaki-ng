/**
 * video_binding.cpp - Video processing Python bindings
 * 
 * This file contains the Python bindings for video frame processing
 * and computer vision integration.
 */

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <chiaki/video.h>
#include <chiaki/ffmpegdecoder.h>

namespace py = pybind11;

// Video frame wrapper for easy Python/OpenCV integration
class VideoFrame {
public:
    VideoFrame(uint8_t* data, size_t size, int width, int height) 
        : width_(width), height_(height), size_(size) {
        // Copy the data
        data_.resize(size);
        memcpy(data_.data(), data, size);
    }
    
    py::array_t<uint8_t> to_numpy() {
        // Return as numpy array that can be used with OpenCV
        return py::array_t<uint8_t>(
            {height_, width_, 3}, // shape (H, W, C) for BGR
            {sizeof(uint8_t) * width_ * 3, sizeof(uint8_t) * 3, sizeof(uint8_t)}, // strides
            data_.data()
        );
    }
    
    py::bytes get_raw_data() {
        return py::bytes(reinterpret_cast<char*>(data_.data()), size_);
    }
    
    int width() const { return width_; }
    int height() const { return height_; }
    size_t size() const { return size_; }

private:
    std::vector<uint8_t> data_;
    int width_;
    int height_;
    size_t size_;
};

// Video profile helper functions
py::dict get_video_profile_info(const ChiakiVideoProfile& profile) {
    py::dict info;
    info["width"] = profile.width;
    info["height"] = profile.height;
    info["header_size"] = profile.header_sz;
    return info;
}

void init_video_binding(py::module& m) {
    // Video profile
    py::class_<ChiakiVideoProfile>(m, "VideoProfile")
        .def(py::init<>())
        .def_readwrite("width", &ChiakiVideoProfile::width)
        .def_readwrite("height", &ChiakiVideoProfile::height)
        .def_readonly("header_size", &ChiakiVideoProfile::header_sz)
        .def("get_info", &get_video_profile_info, "Get video profile information as dict");
    
    // Video frame wrapper
    py::class_<VideoFrame>(m, "VideoFrame")
        .def_property_readonly("width", &VideoFrame::width)
        .def_property_readonly("height", &VideoFrame::height)
        .def_property_readonly("size", &VideoFrame::size)
        .def("to_numpy", &VideoFrame::to_numpy, "Convert to numpy array for OpenCV")
        .def("get_raw_data", &VideoFrame::get_raw_data, "Get raw frame data as bytes");
    
    // Video buffer padding constant
    m.attr("VIDEO_BUFFER_PADDING_SIZE") = CHIAKI_VIDEO_BUFFER_PADDING_SIZE;
    
    // Helper functions for video processing
    m.def("create_video_frame", [](py::bytes data, int width, int height) {
        std::string str_data = data;
        return VideoFrame(reinterpret_cast<uint8_t*>(const_cast<char*>(str_data.data())), 
                         str_data.size(), width, height);
    }, "Create VideoFrame from raw bytes", py::arg("data"), py::arg("width"), py::arg("height"));
}
