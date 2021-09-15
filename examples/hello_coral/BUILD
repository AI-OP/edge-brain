cc_binary(
    name = "hello_coral",
    srcs = ["hello_coral.cc"],
    deps = [
        "@libedgetpu//tflite/public:oss_edgetpu_direct_all",
        "@org_tensorflow//tensorflow/lite:builtin_op_data",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
        "@org_tensorflow//tensorflow/lite:framework",
    ],
)
