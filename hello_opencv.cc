#include <opencv2/opencv.hpp>

int main(int argc, char** arv) {

    const int kImageHeight = 240;
    const int kImageWidth = 320;

    cv::Mat image(kImageHeight, kImageWidth, CV_8UC3);

    image.setTo(cv::Scalar(0,255,0));

    cv::imwrite("hello_opencv.jpg", image);

    return 0;
}
