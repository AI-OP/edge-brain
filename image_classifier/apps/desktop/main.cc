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

#include <opencv2/opencv.hpp>
#include "absl/memory/memory.h"

#include "image_classifier/cc/utils.h"
#include "image_classifier/cc/image_classify_service.h"

namespace {
    const std::string command = 
        "{c | 0       | Camera device}"
        "{i |         | image path}"
        "{m | models  | model folder}";
}
 
void DrawResult(const std::vector<std::pair<std::string, float>>& result,
        cv::Mat& debug_image) {
    // Put text here....
    
    int text_org_y = 0;
    for(int i = 0 ; i < 5; i++) {
        std::stringstream display_info;
        display_info << "Top"<<i+1<<" is "<< result[i].first 
            << " with score "<< result[i].second<<" ";

        const std::string text = display_info.str();
        const int font_face = cv::FONT_HERSHEY_COMPLEX;
        const double font_scale = 0.7;
        const int thickness = 2;
    
        int baseline = 0;
        cv::Size text_size = cv::getTextSize(text, font_face,
                font_scale, thickness, &baseline);

        // center the text
        text_org_y += text_size.height + baseline;
        cv::Point text_org(0, text_org_y);

        putText(debug_image, text, text_org, font_face, font_scale,  
                CV_RGB(255,255,0), thickness, cv::LINE_8, false);


    }

}

int main(int argc, char** argv) {

    cv::CommandLineParser parser(argc, argv, command);

    CHECK(parser.has("m"), "Has no model...");

    auto image_classify_service = absl::make_unique<ImageClassifyService>();
    std::string model_dir = parser.get<std::string>("m");
    image_classify_service->Init(model_dir, Model::kFloatMobileNet, Device::kCPU, 2); 

    if(parser.has("i")) {

        std::string image_path = parser.get<std::string>("i"); 
        cv::Mat image = cv::imread(image_path);
        CHECK(!image.empty(), "Image cannot be read.");

        std::vector<uchar> rgb_image_buffer;
        cv::imencode(".bmp", image, rgb_image_buffer);
        std::vector<std::pair<std::string, float>> result = 
            image_classify_service -> RecognizeImage(rgb_image_buffer);

        CHECK(!result.empty(), "Results should not be empty!");
        std::cout<<"Top1 is "<< result[0].first << " with score "<< result[0].second <<std::endl;

        DrawResult(result, image); 
        cv::imshow("Debug Image Show", image);
        cv::waitKey();

        return 0;
    }

    CHECK(parser.has("c"), "Has no camera device input..."); 

    int device = parser.get<int>("c");

    cv::VideoCapture capture;
    CHECK(capture.open(device), "Can not open devices");

    cv::Mat frame;
    for(;;) { 
        capture >> frame;
        CHECK(!frame.empty(), "Frame is empty has no data.");

        std::vector<uchar> rgb_image_buffer;
        cv::imencode(".bmp", frame, rgb_image_buffer);
        std::vector<std::pair<std::string, float>> result = image_classify_service -> RecognizeImage(rgb_image_buffer);

        DrawResult(result, frame); 

        cv::imshow("Debug Image Show", frame);
        char key = cv::waitKey(10);
        if(key == 'q')
            break;
    }

    return 0;
}
