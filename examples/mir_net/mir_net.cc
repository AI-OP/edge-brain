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
#include "mir_net.h"

namespace mirnet {

MIRNet::MIRNet() { ; }

std::string MIRNet::GetModelName() { return model_name_; }

bool MIRNet::Init(const std::string model_path, const ModelType& model_type) {
  model_ = tflite::FlatBufferModel::BuildFromFile(model_path.c_str());
  CHECK(model_ != nullptr, "Model cannot be built.");

  tflite::ops::builtin::BuiltinOpResolver resolver;
  tflite::InterpreterBuilder builder(*model_, resolver);
  builder(&interpreter_);
  CHECK(this->interpreter_ != nullptr, "Interpreter is null.");

  interpreter_->AllocateTensors();

  input_tensor_index_ = interpreter_->inputs()[0];
  output_tensor_index_ = interpreter_->outputs()[0];

  return true;
}

bool MIRNet::Preprocess(const cv::Mat& image, cv::Mat& input_buffer,
                        cv::Size& output_size) {
  if (image.empty()) {
    printf("Error: input image is emtpy on Preprocess.");
    return false;
  }

  int net_height = interpreter_->tensor(input_tensor_index_)->dims->data[1];
  int net_width = interpreter_->tensor(input_tensor_index_)->dims->data[2];

  float k =
      std::min((float)net_width / image.cols, (float)net_height / image.rows);

  output_size = cv::Size(image.cols * k, image.rows * k);

  cv::Mat resized_image;
  cv::resize(image, resized_image, cv::Size(), k, k);
  cv::Mat buffer = cv::Mat::zeros(net_height, net_width, CV_8UC3);
  cv::Rect rect(0, 0, resized_image.cols, resized_image.rows);
  resized_image.copyTo(buffer(rect));
  buffer.convertTo(buffer, CV_32F, 1. / 255);
  buffer.copyTo(input_buffer);

  std::cout << "Info: MIRNet::Preprocess completed." << std::endl;

  return true;
}

bool MIRNet::RunInference(const cv::Mat& input_buffer, cv::Mat& output_buffer) {
  if (input_buffer.empty()) {
    printf("Error: input_buffer is empty.");
    return false;
  }

  assert(input_buffer.channels() == 3);
  //    interpreter_->ResizeInputTensor(input_tensor_index_,
  //            {1, input_buffer.rows, input_buffer.cols, 3});

  size_t buffer_size =
      sizeof(float) * input_buffer.rows * input_buffer.cols * 3;

  memcpy(interpreter_->typed_tensor<float>(input_tensor_index_),
         input_buffer.data, buffer_size);

  CHECK(kTfLiteOk == interpreter_->Invoke(), "Error: Inference invoke err.");

  const float* output_buffer_data =
      interpreter_->typed_tensor<float>(output_tensor_index_);

  output_buffer.release();
  output_buffer.create(input_buffer.rows, input_buffer.cols, CV_32FC3);
  memcpy(output_buffer.data, output_buffer_data, buffer_size);

  std::cout << "Info: MIRNet::RunInference completed." << std::endl;

  return true;
}

bool MIRNet::Postprocess(const cv::Mat& output_buffer, const cv::Size& size,
                         cv::Mat& output_image) {
  if (output_buffer.empty()) {
    printf("Error: output_buffer is empty on Postprocess.");
    return false;
  }

  output_buffer(cv::Rect(0, 0, size.width, size.height)).copyTo(output_image);
  output_image.convertTo(output_image, CV_8U, 255.);

  // output_buffer.convertTo(output_image, CV_8U, 255.);

  std::cout << "Info: MIRNet::Postprocess completed." << std::endl;

  return true;
}

bool MIRNet::EnhanceImage(const cv::Mat& image, cv::Mat& output_image) {
  cv::Mat input_buffer;
  cv::Size size;
  bool is_ok = Preprocess(image, input_buffer, size);
  if (!is_ok) {
    printf("Error: preprocessing got some errors.");
    assert(false);
    return false;
  }

  cv::Mat output_buffer;
  is_ok = RunInference(input_buffer, output_buffer);
  if (!is_ok) {
    printf("Error: runing inference got errors.");
    assert(false);
    return false;
  }

  is_ok = Postprocess(output_buffer, size, output_image);
  if (!is_ok) {
    printf("Error: post-processing got errors.");
    assert(false);
    return false;
  }

  return true;
}

}  // namespace mirnet
