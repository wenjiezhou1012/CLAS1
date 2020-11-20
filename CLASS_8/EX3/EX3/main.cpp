#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat src_color = imread("1.jpg");
	double scale = 0.2;//缩小图片
	Size ResImgSiz = Size(src_color.cols*scale,src_color.rows*scale);
	Mat rsrc_color = Mat(ResImgSiz,src_color.type());
	resize(src_color,rsrc_color, ResImgSiz,INTER_LINEAR);
	/*在dstColor上绘图*/
	Mat dstColor = rsrc_color;
	/*在dst上存符合条件的灰度图用以筛选*/
	Mat dst = imread("1.jpg",0);
	Mat rdst = Mat(ResImgSiz, dst.type());
	resize(dst, rdst, ResImgSiz, INTER_LINEAR);
	/*获得同样尺寸的数据记录板*/
	threshold(rdst, rdst, 255, 255, THRESH_BINARY);
	/*将图片三通道分离*/
	std::vector<cv::Mat> channels;
	cv::split(rsrc_color, channels);
	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);

	for (int j = 0; j < rsrc_color.rows; j++)//使用合适的条件将瓶盖与背景分离
	{
		uchar* pdata_R = R.ptr<uchar>(j);
		uchar* pdata_G = G.ptr<uchar>(j);
		uchar* pdata_rdst = rdst.ptr<uchar>(j);
		for (int i = 0; i < rsrc_color.cols; i++)
		{
			uchar data_R = pdata_R[i];
			uchar data_G = pdata_G[i];
			if (data_R > 70 & data_G < 150)
			{
				pdata_rdst[i] = 255;
			}

		}
	}

	Mat size = getStructuringElement(MORPH_RECT, Size(6, 6));

	Mat rdstopen;
	morphologyEx(rdst, rdstopen, MORPH_OPEN, size);
	vector<vector<Point>> contours;
	findContours(rdstopen, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (int j = 0; j < contours.size(); j++)//选择符合条件的轮廓
	{
		RotatedRect rbox = minAreaRect(contours[j]);
		Point2f vtx[4];
		rbox.points(vtx);

		double X = (vtx[0].x - vtx[1].x)*(vtx[0].x - vtx[1].x) + (vtx[0].y - vtx[1].y)*(vtx[0].y - vtx[1].y);
		double Y = (vtx[1].x - vtx[2].x)*(vtx[1].x - vtx[2].x) + (vtx[1].y - vtx[2].y)*(vtx[1].y - vtx[2].y);
		double F = X / Y;
		double S = sqrt(X) * sqrt(Y);
		if (F > 0.81 & F < 1.21 & S > 100)
		{
			for (int i = 0; i < 4; i++)
			{
				cv::line(dstColor, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
			}
		}

	}

	imshow("dstColor",dstColor);
	waitKey(0);
}