#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	/*第一题*/
	cv::Mat src_color = imread("2.jpg");
	std::vector<cv::Mat> channels;
	cv::split(src_color, channels);
	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);
	cv::imshow("red", R);
	cv::imshow("blue", B);
	cv::imshow("green", G);
	cv::imshow("original Mat",src_color);
	waitKey(0);

	/*第二题*/
	VideoCapture cap;
	cap.open("2.MP4");
	if (!cap.isOpened())
	{
		std::cout << "不能打开视频文件" << std::endl;
		return-1;
	}

	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << fps << std::endl;
	while (1)
	{
		cv::Mat frame;
		bool rSucess = cap.read(frame);
		if (!rSucess)
		{
			std::cout << "不能从视频文件中读取帧" << std::endl;
			break;
		}
		else
		{
			cv::imshow("frame", frame);
		}
		waitKey(30);
	}
	waitKey(0);

	/*第三题*/
	cv::Point pt;
	cv::Mat blank = imread("blank.png");
	pt.x = 10;
	pt.y = 10;
	circle(blank, pt, 5, CV_RGB(255, 0, 0), 1, 8, 0);

	cv::Point pt1, pt2;
	pt1.x = 10;
	pt1.y = 20;
	pt2.x = 20;
	pt2.y = 20;
	line(blank, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);

	cv::Rect rect;
	rect.x = 10;
	rect.y = 40;
	rect.width = 15;
	rect.height = 15;
	rectangle(blank, rect, CV_RGB(255, 0, 0), 1, 8, 0);
	cv::imshow("draw", blank);
	waitKey(0);
	return 0;
}