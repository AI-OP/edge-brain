// Copyright 2020 Sun Aries.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <iostream>
#include <queue>
#include <string>
#include <fstream>

#include "classifier_float_mobilenet.h"

bool ClassifierFloatMobileNet::LoadLabelsFile(std::string label_path) {
    std::ifstream label_file(label_path);
    if(!label_file) {
        printf("%s cannot be opened.\n", label_path.c_str());
        return false;
    }

    std::string line;

    while(getline(label_file, line)) {
        labels_.emplace_back(line);
    }

    return !labels_.empty();
}

bool ClassifierFloatMobileNet::Init(std::string model_dir) {

    // Load labels file
    std::string label_path = model_dir+"/labels.txt";
    labels_.clear();
    CHECK(LoadLabelsFile(label_path), "Error load labels file.");

    // Set model path
    std::string model_path = model_dir+"/mobilenet_v1_1.0_224.tflite";
    std::cout<<model_path<<std::endl;

    // Load model
    model_ = tflite::FlatBufferModel::BuildFromFile(model_path.c_str());
    CHECK(model_ != nullptr, "Model cannot be built.");

    // Build the interpreter
    tflite::ops::builtin::BuiltinOpResolver resolver;
    tflite::InterpreterBuilder builder(*model_, resolver);
    builder(&interpreter_);
    CHECK(this->interpreter_ != nullptr, "Interpreter is null.");

    input_tensor_index_ = interpreter_ -> inputs()[0];
    output_tensor_index_ = interpreter_ -> outputs()[0];

    CHECK(kTfLiteOk == interpreter_ -> AllocateTensors(), "Can not allocate tensors.");

//    tflite::PrintInterpreterState(interpreter_.get());
    return true;
}

int ClassifierFloatMobileNet::GetModelInputSizeX() {
    return interpreter_ -> tensor(input_tensor_index_) -> dims -> data[2];
}

int ClassifierFloatMobileNet::GetModelInputSizeY() {
    return interpreter_ -> tensor(input_tensor_index_) -> dims -> data[1];
}

void ClassifierFloatMobileNet::SetThreads(int threads) {
    interpreter_->SetNumThreads(threads);
}

void ClassifierFloatMobileNet::SetDevice(Device device) {
    ;
}

std::vector<std::pair<std::string, float>>
ClassifierFloatMobileNet::classify(const cv::Mat& image) {

    if(image.empty())
        return {};

    // Input shape: {1, height, width, 3}
    const int kNetworkInputWidth = interpreter_ -> tensor(input_tensor_index_) -> dims -> data[2];
    const int kNetworkInputHeight = interpreter_ -> tensor(input_tensor_index_) -> dims -> data[1];
    const int kNetworkInputChannels = interpreter_ -> tensor(input_tensor_index_) -> dims -> data[3];
    const cv::Size input_size(kNetworkInputWidth, kNetworkInputHeight);

    cv::Mat input_image;
    cv::resize(image, input_image, input_size);
    cv::cvtColor(input_image, input_image, cv::COLOR_BGR2RGB);

    const float kImageMean = 127.5f;
    const float kImageStd = 127.5f;
    input_image.convertTo(input_image, CV_32F, 1. / kImageStd, - kImageMean / kImageStd);
    float* input_tensor_buffer = interpreter_ -> typed_tensor<float>(input_tensor_index_);
    int buffer_size = sizeof(float)*kNetworkInputWidth*kNetworkInputHeight*kNetworkInputChannels;
    memcpy((uchar*)(input_tensor_buffer), input_image.data, buffer_size);

    // Runing inference.
    CHECK(kTfLiteOk == interpreter_->Invoke(), "Inference invoke error.");

    // Output shape: {1, NUM_CLASSES}
    const float* output = interpreter_->typed_tensor<float>(output_tensor_index_);
    const int kNumClasses = interpreter_->tensor(output_tensor_index_)->dims->data[1];

    auto compare =
        [](std::pair<std::string, float> a, std::pair<std::string, float> b){
            return a.second < b.second;
        };

    std::priority_queue< std::pair<std::string,float>,
        std::vector<std::pair<std::string, float>>,
        decltype(compare) > pq(compare);

    for(int i = 0 ; i < kNumClasses; i ++) {
       pq.push(std::make_pair(labels_[i], output[i]));
    }

    std::vector<std::pair<std::string, float>> label_prob;
    for(int i = 0; i < kNumClasses; i ++) {
        label_prob.emplace_back(pq.top());
        pq.pop();
    }

    return label_prob;
}


