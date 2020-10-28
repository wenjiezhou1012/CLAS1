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

	Mat dx;
	Mat dy;
	Sobel(rpicture, dx, CV_16SC1, 1, 0, 5);
	Sobel(rpicture, dy, CV_16SC1, 0, 1, 5);

	imshow("p1", dx);
	imshow("p2", dy);
	waitKey(0);
}