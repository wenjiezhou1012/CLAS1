#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("1.jpg");
	Mat srcMat0 = imread("1.jpg",0);

	Mat dstMat;
	Mat src2binary;//二值化数据
	srcMat0.copyTo(src2binary);

	int i, j;
	int height = srcMat.rows;
	int width = srcMat.cols;
	/*二值化*/
	threshold(srcMat0, src2binary, 170, 255, THRESH_BINARY);

	/*通过二值化后的图找三点*/
	cv::Point2f pts1[] = {
										cv::Point2f(0,0),
										cv::Point2f(0,0),
										cv::Point2f(0,0)
	};
	 cv::Point2f pts2[] = {
									cv::Point2f(0,0),
									cv::Point2f(width-1,0),
									cv::Point2f(0,height-1)
	};
	int cnt = 0;
	for (j = 0; j < height; j++)
	{
		uchar* data = src2binary.ptr<uchar>(j);
		for (i = 0; i < width; i++)
		{
			if (data[i] == 0)
			{
				cnt++;
				if (cnt == 1) 
				{ 
					pts1[0] = Point2f(i, j); 
					pts1[1] = Point2f(i, j);
					pts1[2] = Point2f(i, j);
				}
				if (i >= pts1[1].x) pts1[1].x = i, pts1[1].y = j;
				if (i <= pts1[2].x) pts1[2].x = i, pts1[2].y = j;
			}
		}
	}
	/*仿射变换*/
	const cv::Mat affine_matrix = cv::getAffineTransform(pts1, pts2);
	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	imshow("src", srcMat);
	imshow("src0", srcMat0);
	imshow("binary", src2binary);
	imshow("dst", dstMat);

	waitKey(0);

}