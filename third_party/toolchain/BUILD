# Copyright 2021 Duan-JM

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

package(default_visibility = ["//visibility:public"])

load(":cc_toolchain_config.bzl", "cc_toolchain_config")
load(":cc_respi_toolchain_config.bzl", "cc_respi_toolchain_config")

filegroup(name = "empty")

cc_toolchain_suite(
    name = "clang_suite",
    toolchains = {
        "k8": ":k8_toolchain",
    },
)

cc_toolchain_config(name = "k8_toolchain_config")

cc_toolchain(
    name = "k8_toolchain",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
    toolchain_config = ":k8_toolchain_config",
    toolchain_identifier = "k8-toolchain",
)

# armv7hf config
cc_toolchain_suite(
    name = "respi_clang_suite",
    toolchains = {
        "armhf": ":respi_toolchain",
    },
)

cc_respi_toolchain_config(name = "respi_toolchain_config")

cc_toolchain(
    name = "respi_toolchain",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
    toolchain_config = ":respi_toolchain_config",
    toolchain_identifier = "respi-toolchain",
)
