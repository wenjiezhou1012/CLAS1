#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("1.jpg",0);
	Mat src = imread("1.jpg");
	Mat Binarization;
	Mat labels;
	Mat stats;
	Mat centroids;
	/*二值化*/
	threshold(srcMat, Binarization, 80, 255, THRESH_BINARY);
	/*连通域标记*/
	int connect =connectedComponentsWithStats(Binarization,labels, stats, centroids);
	/*外接四边形绘制*/
	for (int i = 1; i<connect ; i++)
	{
		cv::Rect rect;
		rect.x = stats.at<int>(i, 0);
		rect.y = stats.at<int>(i, 1);
		rect.width = stats.at<int>(i, 2);
		rect.height= stats.at<int>(i, 3);
	
		rectangle(src, rect, CV_RGB(255, 0, 0), 1, 8, 0);
	}
	imshow("result1", src);
	/*连通域数量减去背景后输出至状态栏*/
	cout << connect-1;

	waitKey(0);
	return 0;
}