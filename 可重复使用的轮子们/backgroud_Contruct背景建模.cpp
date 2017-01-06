#include <iostream>
#include <string>
#include "mytools.h"
#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "bgsegm.hpp"
#include <opencv2/video/background_segm.hpp>
#include "opencv2/video.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;
//using namespace cv::cuda;

void backgroudSubstract()
{
	Ptr<cv::bgsegm::BackgroundSubtractorGMG> bcgst = cv::bgsegm::createBackgroundSubtractorGMG();
	VideoCapture vdcp("D:\\IP_CV_WorkSpace\\video\\20160328_video\\5.38 MVI_0867.MOV");
	if (!vdcp.isOpened())
	{
		cout << "error in open video" << endl;
	}
	else
	{
		Mat frame;
		Mat mask;
		Mat bgImg;
		while (true)
		{
			vdcp >> frame;
			if (frame.empty())
			{//²¥·Å½áÊø;
				break;
			}
			bcgst->apply(frame, mask);
			bcgst->getBackgroundImage(bgImg);
			imshow("frame", frame);
			imshow("background", bgImg);
			imshow("mask", mask);
			int key = waitKey(40);
			if (27 == key)
				break;
			{

			}

		}
		vdcp.release();
		
	}
	return;
	
}