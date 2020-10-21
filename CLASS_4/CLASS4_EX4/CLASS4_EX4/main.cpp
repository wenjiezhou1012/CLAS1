#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("3.jpg", 0);
	Mat binaryzation;
	/*二值化*/
	threshold(src, binaryzation, 100, 255, THRESH_OTSU);
	binaryzation = 255 - binaryzation;
	imshow("windows1", binaryzation);
	/*膨胀*/
	Mat size_erode = getStructuringElement(MORPH_RECT, Size(10, 10));
	Mat output_erode;
	morphologyEx(binaryzation, output_erode, 1, size_erode);
	imshow("windows2", output_erode);
	/*腐蚀*/
	Mat size_dilate = getStructuringElement(MORPH_ELLIPSE, Size(12, 12));
	Mat output_dilate;
	morphologyEx(output_erode, output_dilate, 0, size_dilate);
	imshow("windows3", output_dilate);
	/*连通域计数*/
	Mat open = output_dilate;
	Mat labels;
	Mat stats;
	Mat centroids;
	int connect = connectedComponentsWithStats(open, labels, stats, centroids);
	/*将数字显示在状态栏*/
	cout << connect - 1;
	waitKey(0);

	return 0;
}