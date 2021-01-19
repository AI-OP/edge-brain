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

#ifndef IMAGE_CLASSIFIER_CC_IMAGE_CLASSIFIER_H_
#define IMAGE_CLASSIFIER_CC_IMAGE_CLASSIFIER_H_
#include "utils.h"

class ImageClassifier {
public:
    ImageClassifier() = default;
    ~ImageClassifier() = default;

public:
    virtual bool Init(std::string model_dir) = 0;
    virtual int GetModelInputSizeX() = 0;
    virtual int GetModelInputSizeY() = 0;
    virtual std::vector<std::pair<std::string, float>>
        classify(const cv::Mat& image) = 0;

public:
    virtual void SetThreads(int);
    virtual void SetDevice(Device);
};

#endif // IMAGE_CLASSIFIER_CC_IMAGE_CLASSIFIER_H_

