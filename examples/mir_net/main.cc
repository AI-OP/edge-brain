/* Copyright 2021 Sun Aries. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
=======================================================================*/
#include <cstdio>

#include "examples/mir_net/mir_net.h"

namespace {
const std::string command =
    "{i |         | input image path}"
    "{m | models  | model path}"
    "{o | output.jpg | output image path}";
}

int main(int argc, char** argv) {
  cv::CommandLineParser parser(argc, argv, command);

  auto image_enhancer = absl::make_unique<mirnet::MIRNet>();

  if (nullptr == image_enhancer) {
    printf("Image Enhaner is null.\n");
    return -1;
  }

  CHECK(parser.has("m"), "Error: Has no model...");
  std::string model_dir = parser.get<std::string>("m");
  image_enhancer->Init(model_dir, mirnet::kInt8);

  CHECK(parser.has("i"), "Error: Has no image input.");

  std::string image_path = parser.get<std::string>("i");
  cv::Mat image = cv::imread(image_path);
  if (image.empty()) {
    printf("Error: Image(%s) is empty.\n", image_path.c_str());
    return -1;
  }

  cv::Mat enhanced_image;
  cv::TickMeter tick_meter;
  tick_meter.start();
  image_enhancer->EnhanceImage(image, enhanced_image);
  tick_meter.stop();

  printf("It's take %lf ms to enhance an image.", tick_meter.getTimeMilli());

  std::string output_image_path =
      parser.has("o") ? parser.get<std::string>("o") : "enhanced_image.jpg";

  cv::imwrite(output_image_path, enhanced_image);

  return 0;
}
