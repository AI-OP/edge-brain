# Copyright 2021 Duan-JM

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

From ubuntu:18.04
RUN apt update -y \
      && apt install -y curl gnupg git vim python python3 python3-distutils python3-pip g++ unzip zip openjdk-11-jdk wget cmake make -y \
       crossbuild-essential-armhf \
       crossbuild-essential-arm64 \
       libusb-1.0-0-dev \
       libusb-1.0-0-dev:arm64 \
       libusb-1.0-0-dev:armhf \
       libglib2.0-dev \
       libglib2.0-dev:armhf \
       libglib2.0-dev:arm64 \ 
      && pip3 install numpy \
      && wget https://github.com/bazelbuild/bazelisk/releases/download/v1.7.5/bazelisk-linux-amd64 \
      && chmod +x bazelisk-linux-amd64 \
      && mv bazelisk-linux-amd64 /usr/bin/bazel \
      && echo 'export PATH=$PATH:$HOME/bin' >> ~/.bashrc \
      && apt-get purge -y --auto-remove \

