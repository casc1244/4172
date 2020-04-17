#include <opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("D:\\360downloads\\13.png", 0);
	Mat dspMat = imread("D:\\360downloads\\13.png");
	Mat binaryMat;

	Mat inversedMat = 255 - srcMat;
	threshold(inversedMat, binaryMat, 150, 255, THRESH_OTSU);

	Mat element = getStructuringElement(MORPH_RECT, Size(13, 13));
	morphologyEx(binaryMat, binaryMat, MORPH_OPEN, element);

	vector<vector<Point>> contours;
	findContours(binaryMat, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	float rate[100];
	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rect = minAreaRect(contours[i]);
		Point2f vtx[4];
		rect.points(vtx);

		float Y = sqrt((vtx[0].y - vtx[1].y) * (vtx[0].y - vtx[1].y) + (vtx[0].x - vtx[1].x) * (vtx[0].x - vtx[1].x));
		float X = sqrt((vtx[1].y - vtx[2].y) * (vtx[1].y - vtx[2].y) + (vtx[1].x - vtx[2].x) * (vtx[1].x - vtx[2].x));
		rate[i] = X / Y;

		if ((rate[i] >= 0.95) and (rate[i] <= 1.1))
		{
			for (int j = 0; j <= 3; j++)
			{
				line(dspMat, vtx[j], vtx[(j + 1) % 4], Scalar(0, 255, 0), 1);
			}
		}
	}
	imshow("dspMat", dspMat);
	waitKey(0);
	return 0;
}