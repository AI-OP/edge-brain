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
    toolchain_identifier = "k8-toolchain",
    toolchain_config = ":k8_toolchain_config",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
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
    toolchain_identifier = "respi-toolchain",
    toolchain_config = ":respi_toolchain_config",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
)
