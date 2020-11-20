#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <math.h>

using namespace cv;
using namespace std;

int main()
{
	Mat dstMat = imread("2.jpg");
	Mat srcMat = imread("1.jpg", 0);
	Mat srcColor = imread("1.jpg");
	Mat binary;

	Mat srcMatover = 255 - srcMat;
	threshold(srcMatover, binary, 120, 255, THRESH_BINARY);
	Mat size = getStructuringElement(MORPH_RECT, Size(15, 15));

	Mat binaryopen;
	morphologyEx(binary, binaryopen, MORPH_OPEN, size);
	
	vector<vector<Point>> contours;
	findContours(binaryopen, contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++)
	{
		drawContours(dstMat, contours, i, Scalar(0, 255, 255), 1, 8);
	}

	for (int j = 0; j < contours.size(); j++)
	{	
		RotatedRect rbox = minAreaRect(contours[j]);
		Point2f vtx[4];
		rbox.points(vtx);

		double X = (vtx[0].x - vtx[1].x)*(vtx[0].x - vtx[1].x) + (vtx[0].y - vtx[1].y)*(vtx[0].y - vtx[1].y);
		double Y = (vtx[1].x - vtx[2].x)*(vtx[1].x - vtx[2].x) + (vtx[1].y - vtx[2].y)*(vtx[1].y - vtx[2].y);
		double F = X / Y;
		double R = (sqrt(X) + sqrt(Y) ) / 4;
		cout << X;
		printf("\n");
		double X1 = sqrt(X);
		cout << X1;
		printf("\n");
		if (F > 0.81 & F < 1.21)
		{
			for (int i = 0; i < 4; i++)
			{
				cv::line(srcColor, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
			}
			circle(srcColor,rbox.center,R,CV_RGB(255,255,0),-1,8,0);
		}
		
	}

	imshow("src",srcMat);
	imshow("srcMatover", srcMatover);
	imshow("binary",binary);
	imshow("binaryopen", binaryopen);
	imshow("dst",dstMat);
	imshow("srcColor",srcColor);

	waitKey(0);
}
