
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

float O_Distance(float* a, float* b, int n);
int calHOG(Mat src, float* hist, int nAngle, int cellSize);


int main()
{
	Mat srcMat = imread("1.jpg");
	Mat test1Mat = imread("2.jpg");
	Mat test2Mat = imread("3.jpg");

	int cellSize = 16;
	int nAngle = 8;		//�Ƕ�����

	int nX = srcMat.cols / cellSize;
	int nY = srcMat.rows / cellSize;
	int bins = nX * nY * nAngle;

	float* src_hist = new float[bins];		//��̬�����ڴ�
	memset(src_hist, 0, sizeof(float) * bins);
	float* test1_hist = new float[bins];
	memset(test1_hist, 0, sizeof(float) * bins);
	float* test2_hist = new float[bins];
	memset(test2_hist, 0, sizeof(float) * bins);

	int reCode = 0;
	reCode = calHOG(srcMat, src_hist, nAngle, cellSize);
	reCode = calHOG(test1Mat, test1_hist, nAngle, cellSize);
	reCode = calHOG(test2Mat, test2_hist, nAngle, cellSize);
	if (reCode != 0)
	{
		return -1;
	}

	//����ֱ��ͼ����
	float distance1 = O_Distance(src_hist, test1_hist, bins);
	float distance2 = O_Distance(src_hist, test2_hist, bins);

	cout << "����һ��ŷ����þ���Ϊ:" << distance1 << endl;
	cout << "���Զ���ŷ����þ���Ϊ:" << distance2 << endl;

	if (distance1 > distance2)
		cout << "�ڶ���ͼ���ӽ�ԭͼ" << endl;
	else
		cout << "��һ��ͼ���ӽ�ԭͼ" << endl;

	delete[] src_hist;		//�ͷ��ڴ�
	delete[] test1_hist;
	delete[] test2_hist;
	return 0;
}

int calHOG(Mat src, float* hist, int nAngle, int cellSize)
{
	Mat gx, gy;
	Mat mag, angle;
	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);
	Rect roi;
	roi.height = cellSize;
	roi.width = cellSize;
	int nX = src.cols / cellSize;
	int nY = src.rows / cellSize;
	for (int i = 0; i < nY; i++)
	{
		for (int j = 0; j < nX; j++)
		{
			Mat roiMat;
			Mat roiMag;
			Mat roiAgl;
			roi.x = j * cellSize;
			roi.y = i * cellSize;
			//��ֵͼ��
			roiMat = src(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);
			//��ǰcell��һ��Ԫ���������е�λ��
			int head = (i *nX + j)*nAngle;
			for (int n = 0; n < roiMat.rows; n++)
			{
				for (int m = 0; m < roiMat.cols; m++)
				{
					hist[head + (int)roiAgl.at<float>(n, m) / (360 / nAngle)] += roiMag.at<float>(n, m);
				}
			}
		}
	}
	return 0;
}



float O_Distance(float* a, float* b, int n)
{
	float distance = 0;
	for (int i = 0; i < n; i++)
	{
		distance += pow((a[i] - b[i]), 2);
	}
	distance = sqrt(distance);
	return distance;
}