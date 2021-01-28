# Bazel-Crosstools-Compiler
Simple examples of using bazel to cross compile AI applicaions for armv7hf devices.

## Requirements Installation
1. Install Bazel refer to [Official Tutorial](https://docs.bazel.build/versions/master/install-ubuntu.html)
2. MacOS installation environment required for cross compilation (NOT RECOMMENDED) 
  ```bash
  sudo apt-get install clang libc6-armel-cross libc6-dev-armel-cross binutils-arm-linux-gnueabihf libncurses5-dev build-essential bison flex libssl-dev bc
  ```
3. Use Docker to build ubuntu:18.04 environment (RECOMMENDED)
  ```bash
  docker build -t bazel-build-env:v0.01 .
  # build docker images which included all requirements for this repo
  docker run -it --rm -v /path/to/bazel-crosstools-compiler:/mnt/code bazel-build-env:v0.01 bash
  # mount code to the container
  ```

## How to test examples
PS: All examples listed below have passed the test in ubuntu:18.04 docker environment. 

### Hello World
1. Cross compile `hello-world.cc` locally
  ```bash
  bazel build --config rpi hello # just test for custom toolchain, recommended use elinux_armhf toolchain
  ```

2. Copy the folder named `bazel-bin` to Respi4b, then execute the `hello` file.

### Hello-TFLite
1. Use official toolchain contained in Tensorflow Repo to cross compile tflite's minimal example (`minimal.cc`)
  ```bash
  bazel build --config elinux_armhf hello-tflite
  ```
2. Copy folders, `bazel-bin` and `files`, also tflite model files (in ./files) to Respi4b. After that place tflite model file and executable file `hello-tflite` in the same place to test.
  ```bash
  /Path/To/Bazel-bin/test-tflite ./test-model.tflite # Will return model architecture
  ```

### Hello-OpenCV
1. Cross compile OpenCV with toolchain, then compile `hello-opencv.cc`
  ```bash
  bazel build --config elinux_armhf hello-opencv
  ```

2. Copy file to Respi4b

### Hello-TFLite-Opencv
1. Cross compile OpenCV and also compile TFLite sample application, `hello-tflite-opencv.cc`
  ```bash
  bazel build --config elinux_armhf hello-tflite-opencv
  ```

2. Copy file to Respi4b
