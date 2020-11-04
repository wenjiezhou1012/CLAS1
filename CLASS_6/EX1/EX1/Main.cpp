#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat image=imread("1.jpg");
	Mat edges;
	Canny(image,edges,50,150,3);
	imshow("P1", edges);
	waitKey(0);
	return 0;
}
