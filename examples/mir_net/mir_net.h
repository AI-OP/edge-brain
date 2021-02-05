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
#ifndef MIR_NET_H_
#define MIR_NET_H_

#include <cstdio>
#include <opencv2/opencv.hpp>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/optional_debug_tools.h"

#define TFLITE_CHECK(x)                                      \
  if (!(x)) {                                                \
    fprintf(stderr, "Error at %s:%d\n", __FILE__, __LINE__); \
    exit(1);                                                 \
  }

namespace mirnet {

enum ModelType {
    kDynamicRange,
    kInt8,
    kFloat16,
};

class MIRNet {
 public:
  virtual bool Init(const std::string model_dir, const ModelType& model_type);
  virtual bool EnhanceImage(const cv::Mat& image, cv::Mat& output_image); 

  virtual std::string GetModelName();

 protected:
  virtual bool Preprocess(const cv::Mat& image, cv::Mat& input_buffer);
  virtual bool RunInference(const cv::Mat& input_buffer, cv::Mat& output_buffer);
  virtual bool Postprocess(const cv::Mat& output_buffer, cv::Mat& output_image);

 protected:
  std::unique_ptr<tflite::Interpreter> interpreter_;
  std::unique_ptr<tflite::FlatBufferModel> model_;

  std::string model_name_;

 public:
  MIRNet();
  ~MIRNet() = default;
};

} //mirnet

#endif //MIR_NET_H_
