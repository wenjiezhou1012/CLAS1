#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat dstMat;
	Mat srcMat = imread("1.jpg", 1);
	if (srcMat.empty()) return -1;
	float angle = -10.0, scale = 1;

	cv::Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, scale);
	//获取外接四边形
	cv::Rect bbox = cv::RotatedRect(center,srcMat.size(),angle).boundingRect();
	//调整仿射矩阵参数
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	//仿射变换
	warpAffine(srcMat, dstMat, rot,bbox.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);

	waitKey(0);
	return 0;
}