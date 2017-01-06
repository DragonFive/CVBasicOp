#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;


const char* keys =
{
	"{c |camera   |true    | use camera or not}"
	"{fn|file_name|tree.avi | movie file             }"
};

//this is a sample for foreground detection functions
int main(int argc, const char** argv)
{

	VideoCapture cap;
	bool update_bg_model = true;


	
	cap.open("D:\\IP_CV_WorkSpace\\video\\768x576.avi");
	if (!cap.isOpened())
	{
		printf("can not open camera or video file\n");
		return -1;
	}

	namedWindow("image", WINDOW_NORMAL);
	namedWindow("foreground mask", WINDOW_NORMAL);
	namedWindow("foreground image", WINDOW_NORMAL);
	namedWindow("mean background image", WINDOW_NORMAL);

	BackgroundSubtractorMOG2 bg_model;//(100, 3, 0.3, 5);

	Mat img, fgmask, fgimg;

	for (;;)
	{
		cap >> img;

		if (img.empty())
			break;

		//cvtColor(_img, img, COLOR_BGR2GRAY);

		if (fgimg.empty())
			fgimg.create(img.size(), img.type());

		//update the model
		bg_model(img, fgmask, update_bg_model ? -1 : 0);

		fgimg = Scalar::all(0);
		img.copyTo(fgimg, fgmask);

		Mat bgimg;
		bg_model.getBackgroundImage(bgimg);

		imshow("image", img);
		imshow("foreground mask", fgmask);
		imshow("foreground image", fgimg);
		if (!bgimg.empty())
			imshow("mean background image", bgimg);

		char k = (char)waitKey(30);
		if (k == 27) break;
		if (k == ' ')
		{
			update_bg_model = !update_bg_model;
			if (update_bg_model)
				printf("Background update is on\n");
			else
				printf("Background update is off\n");
		}
	}

	return 0;
}
