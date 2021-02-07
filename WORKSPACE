load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("//third_party:opencv_configs.bzl", "OPENCV_TAG")

# Configure rules_foreign_cc for OpenCV CMakse used in `third_party/BUILD`
http_archive(
    name = "rules_cc",
    strip_prefix = "rules_cc-master",
    urls = ["https://github.com/bazelbuild/rules_cc/archive/master.zip"],
)

http_archive(
   name = "rules_foreign_cc",
   strip_prefix = "rules_foreign_cc-master",
   url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()

ALL_CONTENT = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""
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
        "http://mirror.tensorflow.org/github.com/bazelbuild/rules_closure/archive/cf1e44edb908e9616030cc83d085989b8e6cd6df.tar.gz",
        "https://github.com/bazelbuild/rules_closure/archive/cf1e44edb908e9616030cc83d085989b8e6cd6df.tar.gz",  # 2019-04-04
    ],
)

git_repository(
    name = "org_tensorflow",
    remote = "https://github.com/tensorflow/tensorflow.git",
    tag = "v2.4.0"
)

load("@org_tensorflow//tensorflow:workspace.bzl", "tf_workspace")
tf_workspace(tf_repo_name = "org_tensorflow")

# Custom other thirdparty applications into repo as examples.
git_repository(
    name = "image-classifier",
    remote = "https://github.com/SunAriesCN/image-classifier.git",
    commit= "72d80543f1887375abb565988c12af1960fd311f",
)

# ABSL cpp library 
git_repository(
    name = "com_goolge_absl",
    remote = "https://github.com/abseil/abseil-cpp",
    commit = "6f9d96a1f41439ac172ee2ef7ccd8edf0e5d068c",
)

