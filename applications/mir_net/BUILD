# Copyright 2021 The Edge Brain Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# =======================================================================
cc_binary(
    name = "demo_mir_net",
    srcs = "demo/main.cc",
    deps = [
       ":mir_net"
    ]
)

cc_library(
    name = "mir_net",
    srcs = glob(["mir_net/*.cc", "mir_net/*.h"]),
    deps = [
        "@org_tensorflow//tensorflow/lite:builtin_op_data",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
        "@org_tensorflow//tensorflow/lite:framework",
        "@org_tensorflow//tensorflow/lite:tflite_with_xnnpack",
        "@com_google_absl//absl/memory",
        "//third_party:opencv"
    ]
)
