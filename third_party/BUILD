# Copyright 2021 The Edge Brain Authors, MediaPipe Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

licenses(["notice"])  # Apache License 2.0

load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")
load("//third_party:opencv_configs.bzl",
     "OPENCV_SO_VERSION",
     "OPENCV_MODULES",
     "OPENCV_THIRD_PARTY_DEPS",
     "OPENCV_SHARED_LIBS")


exports_files(["LICENSE"])

package(default_visibility = ["//visibility:public"])

alias(
    name = "opencv",
    actual = select({
        "//conditions:default": ":opencv_cmake",
    }),
    visibility = ["//visibility:public"],
)

OPENCV_DEPS_PATH = "$BUILD_TMPDIR/$INSTALL_PREFIX"
cmake_external(
    name = "opencv_cmake",
    # Values to be passed as -Dkey=value on the CMake command line;
    # here are serving to provide some CMake script configuration options
    cache_entries = {
        "CMAKE_BUILD_TYPE": "Release",
        # The module list is always sorted alphabetically so that we do not
        # cause a rebuild when changing the link order.
        "CMAKE_TOOLCHAIN_FILE": "$EXT_BUILD_ROOT/external/opencv/platforms/linux/arm-gnueabi.toolchain.cmake",
        "BUILD_LIST": ",".join(sorted(OPENCV_MODULES)),
        "BUILD_TESTS": "OFF",
        "BUILD_PERF_TESTS": "OFF",
        "BUILD_EXAMPLES": "OFF",
        "BUILD_SHARED_LIBS": "ON" if OPENCV_SHARED_LIBS else "OFF",
        "WITH_ITT": "OFF",
        "WITH_TIFF": "OFF",
        "WITH_JASPER": "OFF",
        "WITH_WEBP": "OFF",
#        "ENABLE_NEON": "TRUE",
        "BUILD_PNG": "ON",
        "BUILD_JPEG": "ON",
        "BUILD_ZLIB": "ON",
        #"WITH_OPENCL": "OFF",
        #"WITH_OPENCLAMDBLAS": "OFF",
        #"WITH_OPENCLAMDFFT": "OFF",
        #"OPENCV_FORCE_3RDPARTY_BUILD": "ON",

        # When building tests, by default Bazel builds them in dynamic mode.
        # See https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary.linkstatic
        # For example, when building //mediapipe/calculators/video:opencv_video_encoder_calculator_test,
        # the dependency //mediapipe/framework/formats:image_frame_opencv will
        # be built as a shared library, which depends on a cv::Mat constructor,
        # and expects it to be provided by the main exacutable. The main
        # executable depends on libimage_frame_opencv.so and links in
        # libopencv_core.a, which contains cv::Mat. However, if
        # libopencv_core.a marks its symbols as hidden, then cv::Mat is in
        # opencv_video_encoder_calculator_test but it is not exported, so
        # libimage_frame_opencv.so fails to find it.
        "OPENCV_SKIP_VISIBILITY_HIDDEN": "ON" if not OPENCV_SHARED_LIBS else "OFF",
        # The COPY actions in modules/python/python_loader.cmake have issues with symlinks.
        # In any case, we don't use this.
        "OPENCV_SKIP_PYTHON_LOADER": "ON",
        # Need to set this too, for the same reason.
        "BUILD_opencv_python": "OFF",
        # Ccache causes issues in some of our CI setups. It's not clear that
        # ccache would be able to work across sandboxed Bazel builds, either.
        # In any case, Bazel does its own caching of the rule's outputs.
        "ENABLE_CCACHE": "OFF",
    },

    make_commands = ["make -j4", "make install"] + \
		    ["cp {}/lib/opencv4/3rdparty/*.a  {}/lib/".format(OPENCV_DEPS_PATH, OPENCV_DEPS_PATH)] + \
		    ["cp -rf {}/include/opencv4/opencv2 {}/include/".format(OPENCV_DEPS_PATH, OPENCV_DEPS_PATH)],

    lib_source = "@opencv//:all",
    linkopts = [] if OPENCV_SHARED_LIBS else [
        # When using static libraries, the binary that eventually depends on the
        # libraries also needs to link in their dependencies, which therefore
        # have to be listed here.
        # This list depends on which dependencies CMake finds when it configures
        # the build, and so depends on what is installed on the local system.
        # After building, the linkopts for the current setup can be extracted
        # from lib/pkgconfig/opencv.pc in bazel-out
        "-ldl",
        "-lm",
        "-lpthread",
        "-lrt",
    ],
    shared_libraries = select({
        "@bazel_tools//src/conditions:darwin": ["libopencv_%s.%s.dylib" % (module, OPENCV_SO_VERSION) for module in OPENCV_MODULES],
        # Only the shared objects listed here will be linked in the directory
        # that Bazel adds to the RUNPATH of dependent executables. You cannot
        # list both the versioned and unversioned name of the .so, and the
        # versioned name is the one that the executables actually reference.
        "//conditions:default": ["libopencv_%s.so.%s" % (module, OPENCV_SO_VERSION) for module in OPENCV_MODULES],
    }) if OPENCV_SHARED_LIBS else None,
    static_libraries = ["libopencv_%s.a" % module for module in OPENCV_MODULES]
      + [module for module in OPENCV_THIRD_PARTY_DEPS] if not OPENCV_SHARED_LIBS else None,

    alwayslink=True,
)

