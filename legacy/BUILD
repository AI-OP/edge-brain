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

cc_binary(
    name = "hello",
    srcs = ["hello-world.cc"]
)

cc_binary(
    name = "hello-tflite",
    srcs = ["hello-tflite.cc"],
    deps = [
        "@org_tensorflow//tensorflow/lite:builtin_op_data",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
        "@org_tensorflow//tensorflow/lite:framework",
    ],
)

cc_binary(
    name = "hello-opencv",
    srcs = ["hello-opencv.cc"],
    deps = [
        "//third_party:opencv",
    ],
    linkstatic=True,
)

cc_binary(
    name = "hello-tflite-opencv",
    srcs = ["hello-tflite-opencv.cc"],
    deps = [
        "@org_tensorflow//tensorflow/lite:builtin_op_data",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
        "@org_tensorflow//tensorflow/lite:framework",
	"//third_party:opencv",
    ],
    linkstatic=True,
)
