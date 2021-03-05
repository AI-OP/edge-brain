# Edge Brain

这几年我们逐渐看到越来越多的智能终端设备出现在工作生活的不同角落，如智能家电、商城客服机器人、物流配送无人小车、智能监控等等，它们可以为我们生活带来各种各样的便利。因此，边缘智能与 AIoT 已成为不少国内外企业发展的一个重要方向。边缘智能是一项以嵌入式设备应用开发为基础的前沿技术，我们需要在一些资源紧张的嵌入式设备，如 MCU、SOC，部署如人脸识别、物体检测、音频分类等智能应用。然而，我们又看到现实的嵌入式智能应用开发面正临着一些软硬件生态兼容方面的挑战。例如，芯片厂商提供推荐的板载系统往往是定制的，使用不同的编译工具，而且大多不会有 Python 解释器。所以，当我们打算将自己的智能应用部署到嵌入式设备时，我们绕不开 AI 推理框架跨平台的问题。TensorFlow Lite 应用 C++ 作为框架底层的基础实现可以天然保证跨平台扩展特性，但由于它的这项技术的比较前沿，在嵌入式 Linux 设备上以 Python 接口为主，有些开发者不太适应，认为不易上手。为此，我们开发 Edge Brain 方便开发者以其熟悉的交叉编译方式部署 TensorFlow Lite  智能应用，让他们的嵌入式应用走向智能化。

## 依赖项安装
1. 根据[官网的指南](https://docs.bazel.build/versions/master/install-ubuntu.html)安装 bazel
2. MacOS 安装交叉编译需要的环境 (不推荐)
  ```bash
  sudo apt-get install clang libc6-armel-cross libc6-dev-armel-cross binutils-arm-linux-gnueabihf libncurses5-dev build-essential bison flex libssl-dev bc
  ```
3. 使用 Docker 构建 ubuntu:18.04 环境(推荐)
  ```bash
  docker build -t bazel-build-env:v0.01 .
  # 将构建一个含有本项目依赖环境的 docker images
  docker run -it --rm -v /path/to/edge-brain:/mnt/code bazel-build-env:v0.01 bash
  # 把代码挂载到容器 /mnt/code 目录下，并交互式运行 bash
  ```

## 使用测试方法
注意事项为当前项目的所有环境均在 ubuntu:18.04 docker 环境下测试通过。

### 测试交叉编译 Hello TFLite
1. 使用 Tensorflow 中的交叉编译 toolchain 编译 minimal.cc
  ```bash
  bazel build --config elinux_armhf //examples/hello_world:hello_world --experimental_repo_remote_exec
  ```
2. 拷贝 `bazel-bin` 和 `models` 目录中的 tflite 模型到树莓派后，将 tflite
   模型和可执行文件 `hello-tflite` 放在一起进行测试。
  ```
  /Path/To/Bazel-bin/test-tflite ./test-model.tflite # 返回模型的结构
  ```

### 测试交叉编译 Hello OpenCV
1. 交叉编译 OpenCV 并编译 hello-opencv.cc
  ```bash
  bazel build --config elinux_armhf //examples/hello_opencv:hello-opencv --experimental_repo_remote_exec
  ```

2. 拷贝文件至树莓派

### 测试交叉编译第三方仓库中 [Image Classifier](https://github.com/SunAriesCN/image-classifier) 样例
1. 交叉编译第三方 Repo 中对应项目
  ```bash
  bazel build --config elinux_armhf //examples/image_benchmark:image_benchmark --experimental_repo_remote_exec
  ```

2. 拷贝文件至树莓派

### 测试交叉编译 [MIRNet](https://github.com/SunAriesCN/image-classifier) 样例
1. 交叉编译第三方 Repo 中对应项目
  ```bash
  bazel build --config elinux_armhf //examples/mir_net:mir_net --experimental_repo_remote_exec # --verbose_failures
  ```

2. 拷贝文件至树莓派
