#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
int main()
{
	Mat input;
	Mat output1;
	Mat output2;
	Mat output3;
	Mat output4;
	input = imread("1.jpg",0);
	Mat size = getStructuringElement(MORPH_RECT,Size(3,3));

	morphologyEx(input, output1, 0, size);//��ʴ
	morphologyEx(input, output2, 1, size);//����
	morphologyEx(input, output3, 2, size);//������
	morphologyEx(input, output4, 3, size);//������
	/*��ʾ�����������ͼ*/
	imshow("window", input);
	imshow("windows1", output1);
	imshow("windows2", output2);
	imshow("windows3", output3);
	imshow("windows4", output4);

	waitKey(0);
	return 0;
}