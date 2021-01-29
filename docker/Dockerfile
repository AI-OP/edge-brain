From ubuntu:18.04
RUN apt update -y \
      && apt install -y curl gnupg git vim python python3 python3-distutils python3-pip g++ unzip zip openjdk-11-jdk wget cmake make -y \
      && pip3 install numpy \
      && wget https://github.com/bazelbuild/bazel/releases/download/3.7.2/bazel-3.7.2-installer-linux-x86_64.sh \
      && chmod +x ./bazel-3.7.2-installer-linux-x86_64.sh \
      && ./bazel-3.7.2-installer-linux-x86_64.sh --user \
      && echo 'export PATH=$PATH:$HOME/bin' >> ~/.bashrc \
      && apt-get purge -y --auto-remove \
      && rm -rf bazel-3.7.2-installer-linux-x86_64.sh
