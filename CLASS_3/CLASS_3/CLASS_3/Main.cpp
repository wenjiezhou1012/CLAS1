#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{

	double scale = 0.3;

	double i_minH = 0;
	double i_maxH = 20;

	double i_minS = 43;
	double i_maxS = 255;

	double i_minV = 55;
	double i_maxV = 255;

	Mat frame;
	Mat hsvMat;
	Mat detectMat;

	frame = imread("FUSE.jpg");

	Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
	Mat rFrame = Mat(ResImgSiz, frame.type());
	resize(frame, rFrame, ResImgSiz, INTER_LINEAR);
		
	cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);

	rFrame.copyTo(detectMat);

	cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

	imshow("whie: in the range", detectMat);
	imshow("frame", rFrame);

	waitKey(0);


}