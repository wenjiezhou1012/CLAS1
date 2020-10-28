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
	
	medianBlur( rpicture ,dst,15);
	imshow("p",rpicture);
	imshow("p1",dst);
	waitKey(0);
}