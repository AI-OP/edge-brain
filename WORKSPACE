# Copyright 2021 Duan-JM, Sun Aries

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("//third_party:opencv_configs.bzl", "OPENCV_TAG")

# Configure rules_foreign_cc for OpenCV CMakse used in `third_party/BUILD`
http_archive(
    name = "rules_cc",
    strip_prefix = "rules_cc-main",
    urls = ["https://github.com/bazelbuild/rules_cc/archive/main.zip"],
)

http_archive(
   name = "rules_foreign_cc",
   strip_prefix = "rules_foreign_cc-0.1.0",
   url = "https://github.com/bazelbuild/rules_foreign_cc/archive/0.1.0.zip",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()
ALL_CONTENT = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

# Custom other third party applications into repo as examples.
# 
# By the way, I world like to debug other application projects compilation with 
# following codes. Your can uncomment them to customize your apps.
# 
# local_repository(
#    name = "image_classifier",
#    path = "/root/workspace/image-classifier",
# )
#

# Custom Image Classifier applications by our team.
http_archive(
   name = "image_classifier",
   strip_prefix = "image-classifier-master",
   url = "https://github.com/SunAriesCN/image-classifier/archive/master.zip",
)

# KSAI toolkits 
http_archive(
    name = "ksai_third_party",
    strip_prefix = "3rdparty",
    url = "https://sdk.ai.wpscdn.cn/KSAI/KSAI-Toolkits/3rdparty.zip",
    build_file = "@//third_party:ksai_third_party.BUILD",
)

new_git_repository(
   name = "ksai_toolkits",
   remote = "https://github.com/kingsoft-wps/KSAI-Toolkits.git",
   tag = "release_2021.10",
   build_file = "@//third_party:ksai_toolkits.BUILD",
   patch_args = [
     "-p1",
   ],
   patches=[
     "@//third_party:ksai_toolkits_commit_5ad9406fe036ba60dbc190c823715bebdfa269d9.patch",

   ],
)

# OpenCV
new_git_repository(
    name = "opencv",
    build_file_content = ALL_CONTENT,
    remote = "https://github.com/opencv/opencv.git",
    tag = OPENCV_TAG
)

# Needed by TensorFlow
http_archive(
    name = "io_bazel_rules_closure",
    sha256 = "e0a111000aeed2051f29fcc7a3f83be3ad8c6c93c186e64beb1ad313f0c7f9f9",
    strip_prefix = "rules_closure-cf1e44edb908e9616030cc83d085989b8e6cd6df",
    urls = [
        # "http://mirror.tensorflow.org/github.com/bazelbuild/rules_closure/archive/cf1e44edb908e9616030cc83d085989b8e6cd6df.tar.gz",
        "https://github.com/bazelbuild/rules_closure/archive/cf1e44edb908e9616030cc83d085989b8e6cd6df.tar.gz",  # 2019-04-04
    ],
)

git_repository(
    name = "org_tensorflow",
    remote = "https://github.com/tensorflow/tensorflow.git",
    tag = "v2.4.0" # v2.4.1
)

load("@org_tensorflow//tensorflow:workspace.bzl", "tf_workspace")
tf_workspace(tf_repo_name = "org_tensorflow")

# ABSL cpp library
git_repository(
    name = "com_goolge_absl",
    remote = "https://github.com/abseil/abseil-cpp",
    commit = "6f9d96a1f41439ac172ee2ef7ccd8edf0e5d068c",
)


# Configure libedgetpu and downstream libraries (TF and Crosstool).
http_archive(
  name = "libedgetpu",
  sha256 = "14d5527a943a25bc648c28a9961f954f70ba4d79c0a9ca5ae226e1831d72fe80",
  strip_prefix = "libedgetpu-3164995622300286ef2bb14d7fdc2792dae045b7",
  urls = [
    "https://github.com/google-coral/libedgetpu/archive/3164995622300286ef2bb14d7fdc2792dae045b7.tar.gz"
  ],
)

load("@libedgetpu//:workspace.bzl", "libedgetpu_dependencies")
libedgetpu_dependencies()

load("@coral_crosstool//:configure.bzl", "cc_crosstool")
cc_crosstool(name = "crosstool")

