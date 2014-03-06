// Compile with: g++ test.cpp cvrotate2D.cpp -lopencv_core -lopencv_highgui -lopencv_imgproc

#include "cvrotate2D.hpp"

int main()
{
    const double degrees = 45;

    cv::Mat src = cv::imread("image.png", CV_LOAD_IMAGE_UNCHANGED);
    cv::Mat dst;

    cv::rotate2D(src, dst, degrees);

    cv::imwrite("rotated.png", dst);

    return 0;
}
