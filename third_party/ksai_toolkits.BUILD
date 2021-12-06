cc_binary(
    name = "test_ocr",
    srcs = ["test/test_ocr.cpp"],
    includes = ['include'],
    deps = [
        ":ksai_toolkits",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "ksai_toolkits",
    
    srcs = glob([
        "src/OCR/*.cpp", 
        "src/base/*.cpp", 
        "src/OCR/*.h", 
        "src/base/*.h",
        "include/*.h",
    ]),
    
    hdrs = glob([
        "include/*.h",
        "src/OCR/*.h", 
        "src/base/*.h",
    ]),

    includes = ["include","src"],
    
    deps = [
        "@org_tensorflow//tensorflow/lite:builtin_op_data",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
        "@org_tensorflow//tensorflow/lite:framework",
        "@org_tensorflow//tensorflow/lite:tflite_with_xnnpack",
        "@com_google_absl//absl/memory",
        "@//third_party:opencv",
    ],
    
    visibility = ["//visibility:public"],
)
