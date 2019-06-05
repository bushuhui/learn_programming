#include <iostream>
#include <opencv2/opencv.hpp>
int main()
{
    cv::Mat image = cv::imread("../timg.jpeg");
    if (!image.empty()) {
        cv::imshow("image", image);
        cv::waitKey(-1);
    } else {
        std::cout << "Can not get image." << std::endl;
    }

    return 0;
}
