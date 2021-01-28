# Bazel-Crosstools-Compiler
根据 bazel 官网 crosstools 改编的使用 bazel 交叉编译 AI 小程序使其能在 armv7hf 硬件上使用的简单实例。

## 依赖项安装：
1. 根据[官网的指南](https://docs.bazel.build/versions/master/install-ubuntu.html)安装 bazel
2. MacOS 安装交叉编译需要的环境 (不推荐)
  ```bash
  sudo apt-get install clang libc6-armel-cross libc6-dev-armel-cross binutils-arm-linux-gnueabihf libncurses5-dev build-essential bison flex libssl-dev bc
  ```
3. 使用 Docker 构建 ubuntu:18.04 环境(推荐)
  ```bash
  docker build -t bazel-build-env:v0.01 .
  # 将构建一个含有本项目依赖环境的 docker images
  docker run -it --rm -v /path/to/bazel-crosstools-compiler:/mnt/code bazel-build-env:v0.01 bash
  # 把代码挂载到容器 /mnt/code 目录下，并交互式运行 bash
  ```

## 使用测试方法
注意事项为当前项目的所有环境均在 ubuntu:18.04 docker 环境下测试通过。

### Hello World
1. 本机编译 hello world 程序
  ```bash
  bazel build --config rpi hello # 仅为测试案例，建议使用 elinux_armhf 来配置
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

### Hello-OpenCV
1. 交叉编译 OpenCV 并编译 hello-opencv.cc
  ```bash
  bazel build --config elinux_armhf hello-opencv
  ```

2. 拷贝文件至树莓派

### Hello-TFLite-Opencv
1. 交叉编译 OpenCV 并编译含有 TFLite 的样例程序 hello-tflite-opencv.cc
  ```bash
  bazel build --config elinux_armhf hello-tflite-opencv
  ```

2. 拷贝文件至树莓派
