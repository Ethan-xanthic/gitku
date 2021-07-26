#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat src = imread("Lena.jpg"), dst(src.size(), src.type());
int contrast = 100, bright;

void on_change(int, void*)
{
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			for (int c = 0; c < 3; c++)
				dst.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((contrast * 0.01) * (src.at<Vec3b>(y, x)[c]) + bright);
	imshow("Ч��ͼ", dst);
}

int main()
{
	namedWindow("������");
	createTrackbar("�Աȶ�300", "������", &contrast, 300, on_change);
	createTrackbar("���� 200", "������", &bright, 200, on_change);
	on_change(contrast, 0);
	on_change(bright, 0);
	imshow("ԭͼ", src);
	waitKey();
	return 0;
}