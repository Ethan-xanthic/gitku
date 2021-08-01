#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

Mat src = imread("indoor.jpg"), hsv, hsvtemp, labtemp;
Mat rgb(src.size(), src.type()), lab(src.size(), src.type());
Mat img1, img2, img3;
Mat temp = getStructuringElement(MORPH_RECT, Size(3, 3));
int hmin = 0, hmax = 180, smin = 0, smax = 255, vmin = 0, vmax = 255;
int rmin = 0, rmax = 255, gmin = 0, gmax = 255, bmin = 0, bmax = 255;
int lmin = 0, lmax = 255, amin = 0, amax = 255, blmin = 0, blmax = 255;

void hsv_change(int, void*)
{
	inRange(hsvtemp, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), hsv);
	erode(hsv, img1, temp);
	erode(img1, img1, temp);
	imshow("HSV", img1);
}

void rgb_change(int, void*)
{
	for (int i = 0; i < src.rows; ++i)
	{
		for (int j = 0; j < src.cols; ++j)
		{
			if (src.at<Vec3b>(i, j)[2] > rmin && src.at<Vec3b>(i, j)[2]<rmax && src.at<Vec3b>(i, j)[1]>gmin && src.at<Vec3b>(i, j)[1] < gmax && src.at<Vec3b>(i, j)[0]>bmin && src.at<Vec3b>(i, j)[0] < bmax)
			{
				rgb.at<Vec3b>(i, j)[0] = 255;
				rgb.at<Vec3b>(i, j)[1] = 255;
				rgb.at<Vec3b>(i, j)[2] = 255;
			}
			else
			{
				rgb.at<Vec3b>(i, j)[0] = 0;
				rgb.at<Vec3b>(i, j)[1] = 0;
				rgb.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}
	erode(rgb, img2, temp);
	erode(img2, img2, temp);
	imshow("RGB", img2);
}

void lab_change(int, void*)
{
	for (int i = 0; i < src.rows; ++i)
	{
		for (int j = 0; j < src.cols; ++j)
		{
			if (labtemp.at<Vec3b>(i, j)[0] > lmin && labtemp.at<Vec3b>(i, j)[0]<lmax && labtemp.at<Vec3b>(i, j)[1]>amin && labtemp.at<Vec3b>(i, j)[1] < amax && labtemp.at<Vec3b>(i, j)[2]>blmin && labtemp.at<Vec3b>(i, j)[2] < blmax)
			{
				lab.at<Vec3b>(i, j)[0] = 255;
				lab.at<Vec3b>(i, j)[1] = 255;
				lab.at<Vec3b>(i, j)[2] = 255;
			}
			else
			{
				lab.at<Vec3b>(i, j)[0] = 0;
				lab.at<Vec3b>(i, j)[1] = 0;
				lab.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}
	erode(lab, img3, temp);
	imshow("LAB", img3);
}

int main()
{	
	imshow("ԭͼ", src);	

	cvtColor(src, hsvtemp, COLOR_BGR2HSV);
	namedWindow("HSV������");
	createTrackbar("hmin", "HSV������", &hmin, 180, hsv_change);
	createTrackbar("hmax", "HSV������", &hmax, 180, hsv_change);
	createTrackbar("smin", "HSV������", &smin, 255, hsv_change);
	createTrackbar("smax", "HSV������", &smax, 255, hsv_change);
	createTrackbar("vmin", "HSV������", &vmin, 255, hsv_change);
	createTrackbar("vmax", "HSV������", &vmax, 255, hsv_change);
	hsv_change(0, 0);

	namedWindow("RGB������");
	createTrackbar("rmin", "RGB������", &rmin, 255, rgb_change);
	createTrackbar("rmax", "RGB������", &rmax, 255, rgb_change);
	createTrackbar("gmin", "RGB������", &gmin, 255, rgb_change);
	createTrackbar("gmax", "RGB������", &gmax, 255, rgb_change);
	createTrackbar("bmin", "RGB������", &bmin, 255, rgb_change);
	createTrackbar("bmax", "RGB������", &bmax, 255, rgb_change);
	rgb_change(0, 0);

	cvtColor(src, labtemp, COLOR_BGR2Lab);
	namedWindow("LAB������");
	createTrackbar("lmin", "LAB������", &lmin, 255, lab_change);
	createTrackbar("lmax", "LAB������", &lmax, 255, lab_change);
	createTrackbar("amin", "LAB������", &amin, 255, lab_change);
	createTrackbar("amax", "LAB������", &amax, 255, lab_change);
	createTrackbar("blmin", "LAB������", &blmin, 255, lab_change);
	createTrackbar("blmax", "LAB������", &blmax, 255, lab_change);
	lab_change(0, 0);

	waitKey();
	return 0;
}