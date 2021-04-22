# Edge-Brain

In the past few years, we have gradually seen more and more smart terminal devices appearing in different corners of work and life, such as smart home appliances, mall customer service robots, unmanned logistics and distribution vehicles, smart surveillance, etc. They can bring everything to our lives. All kinds of convenience. Therefore, edge intelligence and AIoT have become an important direction for the development of many domestic and foreign companies. Edge intelligence is a cutting-edge technology based on embedded device application development. We need to deploy intelligent applications such as face recognition, object detection, and audio classification in some resource-stricken embedded devices, such as MCU and SOC. However, we have also seen that the actual embedded intelligent application development is facing some challenges in software and hardware ecological compatibility. For example, the on-board systems recommended by chip manufacturers are often customized, use different compilation tools, and most of them will not have a Python interpreter. Therefore, when we plan to deploy our own smart applications to embedded devices, we cannot avoid the cross-platform issue of AI inference frameworks. TensorFlow Lite uses C++ as the underlying basic implementation of the framework to naturally guarantee cross-platform extension characteristics, but due to its relatively cutting-edge technology, it mainly uses Python interfaces on embedded Linux devices. Some developers are not comfortable with it and think it is not easy Get started. To this end, we developed Edge Brain to facilitate developers to deploy TensorFlow Lite smart applications in a familiar cross-compilation method, and make their embedded applications smarter.

## Requirements Installation
1. Install Bazel refer to [Official Tutorial](https://docs.bazel.build/versions/master/install-ubuntu.html)
2. Use Docker to build ubuntu:18.04 environment (RECOMMENDED)
  ```bash
  docker build -t bazel-build-env:v0.01 .
  # build docker images which included all requirements for this repo
  docker run -it --rm -v /path/to/edge-brain:/mnt/code bazel-build-env:v0.01 bash
  # mount code to the container
  ```

## How to test examples
PS: All examples listed below have passed the test in ubuntu:18.04 docker environment. 

### Cross compile Hello-TFLite
1. Use official toolchain contained in Tensorflow Repo to cross compile tflite's minimal example (`minimal.cc`)
  ```bash
  bazel build --config elinux_armhf //examples/hello_world:hello_world --experimental_repo_remote_exec
  ```
2. Copy folders, `bazel-bin` and `models`, also tflite model files (in ./models) to Respi4b. After that place tflite model file and executable file `hello-tflite` in the same place to test.
  ```bash
  /Path/To/Bazel-bin/test-tflite ./test-model.tflite # Will return model architecture
  ```

### Cross compile Hello-OpenCV
1. Cross compile OpenCV with toolchain, then compile `hello-opencv.cc`
  ```bash
  bazel build --config elinux_armhf //examples/hello_opencv:hello-opencv --experimental_repo_remote_exec
  ```

2. Copy file to Respi4b

### Cross compile external repo [Image-Classifier](https://github.com/SunAriesCN/image-classifier) project

1. Cross compile project in external repo
  ```bash
  bazel build --config elinux_armhf //examples/image_benchmark:image_benchmark --experimental_repo_remote_exec
  ```

2. Copy file to Respi4b

### Cross compile [MIRNET](https://github.com/SunAriesCN/image-classifier) project

1. Cross compile project in external repo
  ```bash
  bazel build --config elinux_armhf //examples/mir_net:mir_net --experimental_repo_remote_exec # --verbose_failures
  ```

2. Copy file to Respi4b

## About Bazel
For we use Bazel to be our build and test tool, however some players still
unfamiliar with this tool. So we list some useful resources for beginners.

- [Bazel Official Guide to Bazel](https://docs.bazel.build/versions/master/guide.html)。
- [Bazel Official Examples](https://github.com/bazelbuild/examples)
- [Good Chinese Blog for Beginners](https://blog.csdn.net/elaine_bao/article/details/78668657)

## About Code style
We recommend referring to the `Google Style Guide`, which can be found here:
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)。
- [Google Python Style Guide](https://google.github.io/styleguide/pyguide.html)。
