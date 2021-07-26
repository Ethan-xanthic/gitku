#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat src = imread("3号战车.jpg"), temp;
Mat dst1(src.size(), src.type(), Scalar(0)), dst2(src.size(), src.type(), Scalar(0));
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;
RNG rng(12345);

int main()
{
	imshow("战车", src);
	cvtColor(src, temp, COLOR_BGR2GRAY);
	blur(temp, temp, Size(3, 3));
	Canny(temp, temp, 80, 160, 3);
	findContours(temp, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst1, contours, i, color, 1, 8, hierarchy, 0, Point());
	}
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		vector<vector<Point>> hull(contours.size());
		convexHull(Mat(contours[i]), hull[i], false);
		drawContours(dst2, contours, i, color, 1, 8, hierarchy, 0, Point());
		drawContours(dst2, hull, i, color, 2, 8, hierarchy, 0, Point());
	}
	imshow("不带凸包", dst1);
	imshow("带凸包", dst2);
	waitKey();
	return 0;
}