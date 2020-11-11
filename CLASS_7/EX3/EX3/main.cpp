
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat dstMat;
	Mat srcMat = imread("2.jpg", 1);
	if (srcMat.empty()) return -1;

	Mat canny;
	Canny(srcMat, canny, 50, 150, 3);
	std::vector<cv::Vec4i> lines;
	HoughLinesP(canny, lines, 1, CV_PI / 180, 45,10,30);
	imshow("P1", canny);

	std::vector<cv::Vec4i>::iterator it = lines.begin();
	for (; it != lines.end(); ++it) {
		cv::Point pt1, pt2;
		pt1.x = (*it)[0];
		pt1.y = (*it)[1];
		pt2.x = (*it)[2];
		pt2.y = (*it)[3];
		cv::line(srcMat, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
	}

	imshow("P", srcMat);
	waitKey(0);
}