#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

static void help()
{
	printf("\nDo background segmentation, especially demonstrating the use of cvUpdateBGStatModel().\n"
		"Learns the background at the start and then segments.\n"
		"Learning is togged by the space key. Will read from file or camera\n"
		"Usage: \n"
		"			./bgfg_segm [--camera]=<use camera, if this key is present>, [--file_name]=<path to movie file> \n\n");
}

const char* keys =
{
	"{c  camera   |         | use camera or not}"
	"{m  method   |mog2     | method (knn or mog2) }"
	"{s  smooth   |         | smooth the mask }"
	"{fn file_name|../data/tree.avi | movie file        }"
};

void ErodeDilate(Mat src, Mat dst,int n)//ÅòÕÍ¸¯Ê´;
{
	int element_shape = MORPH_RECT;
	int an = n > 0 ? n : -n;
	Mat element = getStructuringElement(element_shape, Size(an * 2 + 1, an * 2 + 1), Point(an, an));
	if (n < 0)
		erode(src, dst, element);
	else
		dilate(src, dst, element);
}

//this is a sample for foreground detection functions
int t_main(int argc, const char** argv)
{
	bool smoothMask = true;
	string file = "D:\\IP_CV_WorkSpace\\video\\768x576.avi";
	string method = "mog2";
	VideoCapture cap;
	bool update_bg_model = true;

	cap.open(file.c_str());

	if (!cap.isOpened())
	{
		printf("can not open camera or video file\n");
		return -1;
	}

	namedWindow("image", WINDOW_NORMAL);
	namedWindow("foreground mask", WINDOW_NORMAL);
	namedWindow("foreground image", WINDOW_NORMAL);
	namedWindow("mean background image", WINDOW_NORMAL);

	Ptr<BackgroundSubtractor> bg_model = method == "knn" ?
		createBackgroundSubtractorKNN().dynamicCast<BackgroundSubtractor>() :
		createBackgroundSubtractorMOG2().dynamicCast<BackgroundSubtractor>();

	Mat img0, img, fgmask, fgimg;

	for (;;)
	{
		cap >> img0;

		if (img0.empty())
			break;

		resize(img0, img, Size(640, 640 * img0.rows / img0.cols), INTER_LINEAR);

		if (fgimg.empty())
			fgimg.create(img.size(), img.type());

		//update the model
		bg_model->apply(img, fgmask, update_bg_model ? -1 : 0);
		if (smoothMask)
		{
			GaussianBlur(fgmask, fgmask, Size(11, 11), 3.5, 3.5);
			threshold(fgmask, fgmask, 10, 255, THRESH_BINARY);
		}

		fgimg = Scalar::all(0);
		ErodeDilate(fgimg, fgimg, -10);
		ErodeDilate(fgimg, fgimg, 5);
		img.copyTo(fgimg, fgmask);

		Mat bgimg;
		bg_model->getBackgroundImage(bgimg);

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