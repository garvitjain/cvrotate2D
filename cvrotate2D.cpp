#include "cvrotate2D.hpp"

namespace cv {

void rotate2D(const cv::Mat & src, cv::Mat & dst, const double degrees)
{
    cv::Mat frame, frameRotated;

    int diagonal = (int)sqrt(src.cols * src.cols + src.rows * src.rows);
    int newWidth = diagonal;
    int newHeight = diagonal;

    int offsetX = (newWidth - src.cols) / 2;
    int offsetY = (newHeight - src.rows) / 2;
    cv::Mat targetMat(newWidth, newHeight, src.type(), cv::Scalar(0));
    cv::Point2f src_center(targetMat.cols / 2.0f, targetMat.rows / 2.0f);

    src.copyTo(frame);

    frame.copyTo(targetMat.rowRange(offsetY, offsetY +
                 frame.rows).colRange(offsetX, offsetX + frame.cols));
    cv::Mat rot_mat = cv::getRotationMatrix2D(src_center, degrees, 1.0);
    cv::warpAffine(targetMat, frameRotated, rot_mat, targetMat.size());

    cv::Rect bound_Rect(frame.cols, frame.rows, 0, 0);
    int x1 = offsetX;
    int x2 = offsetX + frame.cols;
    int x3 = offsetX;
    int x4 = offsetX + frame.cols;
    int y1 = offsetY;
    int y2 = offsetY;
    int y3 = offsetY + frame.rows;
    int y4 = offsetY + frame.rows;
    cv::Mat co_Ordinate = (cv::Mat_<double>(3, 4) << x1, x2, x3, x4,
                           y1, y2, y3, y4,
                           1,  1,  1,  1 );

    cv::Mat RotCo_Ordinate = rot_mat * co_Ordinate;

    for (int i = 0; i < 4; ++i) {
        if (RotCo_Ordinate.at<double>(0, i) < bound_Rect.x)
            bound_Rect.x = (int)RotCo_Ordinate.at<double>(0, i);
        if (RotCo_Ordinate.at<double>(1, i) < bound_Rect.y)
            bound_Rect.y = RotCo_Ordinate.at<double>(1, i);
    }

    for (int i = 0; i < 4; ++i) {
        if (RotCo_Ordinate.at<double>(0, i) > bound_Rect.width)
            bound_Rect.width = (int)RotCo_Ordinate.at<double>(0, i);
        if (RotCo_Ordinate.at<double>(1, i) > bound_Rect.height)
            bound_Rect.height = RotCo_Ordinate.at<double>(1, i);
    }

    bound_Rect.width = bound_Rect.width - bound_Rect.x;
    bound_Rect.height = bound_Rect.height - bound_Rect.y;

    if (bound_Rect.x < 0)
        bound_Rect.x = 0;
    if (bound_Rect.y < 0)
        bound_Rect.y = 0;
    if (bound_Rect.width > frameRotated.cols)
        bound_Rect.width = frameRotated.cols;
    if (bound_Rect.height > frameRotated.rows)
        bound_Rect.height = frameRotated.rows;

    cv::Mat ROI = frameRotated(bound_Rect);
    ROI.copyTo(dst);
}

}
