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

