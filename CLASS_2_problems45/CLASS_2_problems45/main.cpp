#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	float histogram[3][256] = {0};
	cv::Mat src_color = imread("2.jpg");
	int height = src_color.rows;
	int width = src_color.cols;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			for (int k = 0; k < 256; k++)
			{
				if (src_color.at<Vec3b>(j, i)[0] == k)
				{
					histogram[0][k] += 1;
				}
				if (src_color.at<Vec3b>(j, i)[1] == k)
				{
					histogram[1][k] += 1;
				}
				if (src_color.at<Vec3b>(j, i)[2] == k)
				{
					histogram[2][k] += 1;
				}
			}
		}
	}

	float pixel_total = height * width;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			histogram[i][j] = histogram[i][j] / pixel_total;
		}
	}

	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j < 255; j++)
		{
			printf("%.5f ", histogram[i][j]);
		}
		printf("\n");
	}
	waitKey(0);

	cv::Mat histogram_picture =imread("blank.png");
	cv::Point pt1, pt2, pt3,pt4,pt5;
	pt1.x = 10;
	pt1.y = 10;
	pt2.x = 10;
	pt2.y = 610;
	pt3.x = 510;
	pt3.y = 610;
	pt4.x = 10;
	pt4.y = 610;
	line( histogram_picture, pt1, pt2, CV_RGB(0, 0, 0), 1, 8, 0);
	line( histogram_picture, pt2, pt3, CV_RGB(0, 0, 0), 1, 8, 0);
	for (int i = 0; i < 255; i++)
	{
		pt4.x += 1;
		pt4.y = 610;
		pt5.x = pt4.x;
		pt5.y = pt4.y - ceil(histogram[0][i] * 10000);
		line( histogram_picture, pt4, pt5, CV_RGB(0, 0, 255), 1, 8, 0);
	}

	pt1.x = 550;
	pt1.y = 10;
	pt2.x = 550;
	pt2.y = 610;
	pt3.x = 1050;
	pt3.y = 610;
	pt4.x = 550;
	pt4.y = 610;
	line(histogram_picture, pt1, pt2, CV_RGB(0, 0, 0), 1, 8, 0);
	line(histogram_picture, pt2, pt3, CV_RGB(0, 0, 0), 1, 8, 0);
	for (int i = 0; i < 255; i++)
	{
		pt4.x += 1;
		pt4.y = 610;
		pt5.x = pt4.x;
		pt5.y = pt4.y - ceil(histogram[1][i] * 10000);
		line(histogram_picture, pt4, pt5, CV_RGB(0, 255, 0), 1, 8, 0);
	}

	pt1.x = 1100;
	pt1.y = 10;
	pt2.x = 1100;
	pt2.y = 610;
	pt3.x = 1600;
	pt3.y = 610;
	pt4.x = 1100;
	pt4.y = 610;
	line(histogram_picture, pt1, pt2, CV_RGB(0, 0, 0), 1, 8, 0);
	line(histogram_picture, pt2, pt3, CV_RGB(0, 0, 0), 1, 8, 0);
	for (int i = 0; i < 255; i++)
	{
		pt4.x += 1;
		pt4.y = 610;
		pt5.x = pt4.x;
		pt5.y = pt4.y - ceil(histogram[2][i] * 10000);
		line(histogram_picture, pt4, pt5, CV_RGB(255, 0, 0), 1, 8, 0);
	}
	cv::imshow("histogram", histogram_picture);
	waitKey(0);
	return 0;
}