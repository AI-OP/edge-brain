# Note: passing both BUILD_SHARED_LIBS=ON and BUILD_STATIC_LIBS=ON to cmake
# still only builds the shared libraries, so we have to choose one or the
# other. We build shared libraries by default, but this variable can be used
# to switch to static libraries.
OPENCV_SHARED_LIBS = False

OPENCV_TAG = "3.4.10"
OPENCV_SO_VERSION = "3.4" # OPENCV_SO_VERSION need to match OPENCV_TAG

# Note: this determines the order in which the libraries are passed to the
# linker, so if library A depends on library B, library B must come _after_.
# Hence core is at the bottom.
OPENCV_MODULES = [
    "calib3d",
    "features2d",
    "highgui",
    "video",
    "videoio",
    "imgcodecs",
    "imgproc",
    "core",
]

OPENCV_THIRD_PARTY_DEPS = [
    "liblibjpeg-turbo.a",
    "liblibpng.a",
    "liblibprotobuf.a",
    "libquirc.a",
    "libtegra_hal.a",
    "libzlib.a",
]
