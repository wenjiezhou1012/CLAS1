#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
int main() {
	cv::Mat srcMat = imread("D:\\1.jpg");
	int height = srcMat.rows;
	int width = srcMat.cols;
	cv::Mat srcMat1 = imread("D:\\1.jpg", 0);
	cv::Mat srcMat2 = imread("D:\\1.jpg");
	cv::Mat srcMat3 = imread("D:\\1.jpg");
	/*第一题*/
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar average = (srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2]) / 3;
			srcMat.at<Vec3b>(j, i)[0] = average;
			srcMat.at<Vec3b>(j, i)[1] = average;
			srcMat.at<Vec3b>(j, i)[2] = average;
		}
	}
	imshow("src", srcMat);
	waitKey(0);
	/*第二题*/
	imshow("src", srcMat1);
	waitKey(0);
	/*第三题*/
	uchar threshold = 100;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar average = (srcMat2.at<Vec3b>(j, i)[0] + srcMat2.at<Vec3b>(j, i)[1] + srcMat2.at<Vec3b>(j, i)[2]) / 3;
			for (int k = 0; k < 2; k++)
			{
				if (average > threshold) average = 255;
				else if (average < threshold) average = 0;
				srcMat2.at<Vec3b>(j, i)[k] = average;
			}
		}
	}
	imshow("src", srcMat2);
	waitKey(0);
	/*第四题*/
	cv::Mat shallowMat;
	cv::Mat deepMat;

	shallowMat = srcMat3;
	imshow("src", shallowMat);
	waitKey(0);

	srcMat.copyTo(deepMat);
	imshow("src", deepMat);
	waitKey(0);
	return 0;
}