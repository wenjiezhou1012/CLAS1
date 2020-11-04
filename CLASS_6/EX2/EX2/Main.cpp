#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat dstMat;
	Mat srcMat = imread("1.jpg",1);
	if (srcMat.empty()) return -1;

	float angle = -45.0, scale = 1;

	Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
	const cv::Mat affine_matrix = getRotationMatrix2D(center, angle, scale);
	warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	imshow("src",srcMat);
	imshow("dst", dstMat);

	waitKey(0);
	return 0;
}