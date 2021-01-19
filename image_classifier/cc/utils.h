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

#ifndef IMAGE_CLASSIFIER_CC_UTILS_H_
#define IMAGE_CLASSIFIER_CC_UTILS_H_

#include <cstdio>
#include <vector>
#include <string>

#include "opencv2/opencv.hpp"
#include "absl/memory/memory.h"

#define CHECK(condition, error_info) \
    if(!(condition)) { \
        printf("%s\n", error_info);\
        exit(-1); \
    }\

// Todo:
// Find more easy way to print our content
#define LOG_INFO(content) \
    std::cout<<content<<std::endl;

enum class Device{
    kCPU = 0,
    kNNAPI = 1,
    kGPU = 2,
};

typedef std::vector<uchar> Bytes;

#endif //IMAGE_CLASSIFIER_CC_UTILS_H_ 
