# Bazel-Crosstools-Compiler
根据 bazel 官网 crosstools 改编的使用 bazel 交叉编译 armv7hf 的简单实例。

## 依赖项安装：
1. 根据[官网的指南](https://docs.bazel.build/versions/master/install-ubuntu.html)安装 bazel
2. 安装交叉编译需要的环境
  ```bash
  sudo apt-get install clang libc6-armel-cross libc6-dev-armel-cross binutils-arm-linux-gnueabihf libncurses5-dev build-essential bison flex libssl-dev bc
  ```

## 使用测试方法
### Hello World
1. 本机编译 hello world 程序
  ```bash
  bazel build --config rpi hello
  ```

2. 拷贝 `bazel-bin` 目录到树莓派之后运行其中的可执行文件 `hello`

### Hello-TFLite
1. 使用 Tensorflow 中的交叉编译 toolchain 编译 minimal.cc
  ```bash
  bazel build --config elinux_armhf hello-tflite
  ```
2. 拷贝 `bazel-bin` 和 `files` 目录中的 tflite 模型到树莓派后，将 tflite
   模型和可执行文件 `hello-tflite` 放在一起进行测试。
  ```
  /Path/To/Bazel-bin/test-tflite ./test-model.tflite # 返回模型的结构
  ```

