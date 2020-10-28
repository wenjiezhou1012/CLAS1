#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	double scale = 0.3;
	Mat picture = imread("1.jpg");
	Size Respicture = Size(picture.cols*scale, picture.rows*scale);
	Mat rpicture = Mat(Respicture, picture.type());
	resize(picture, rpicture, Respicture, INTER_LINEAR);

	Mat dst;
	Size ksize = Size(9, 9);
	blur(rpicture,dst,ksize,Point(-1,-1));//均值滤波
	imshow("p", rpicture);
	imshow("p1", dst);
	
	Mat dst2;
	GaussianBlur(rpicture, dst2, ksize, 3, 3);//高斯滤波
	imshow("p2", dst2);
	
	waitKey(0);
}