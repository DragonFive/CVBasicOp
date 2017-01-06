#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace cv;

int main(){
	Mat frame;
	Mat fgMaskMOG2;
	Mat roi;
	Ptr<BackgroundSubtractor> pMOG2;
	char keyboard = 0;
	char string[10];
	char name[10];
	double t = 0;
	double fps;
	__int16 threshold = 1000;

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	pMOG2 = createBackgroundSubtractorMOG2();
	VideoCapture cap("C:\\codes\\001.avi");
	if (!cap.isOpened()){
		exit(0);
	}

	//cvNamedWindow("fg", CV_WINDOW_NORMAL);
	//cvNamedWindow("mask", CV_WINDOW_NORMAL);

	/*int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);
	int resizePram = 2;
	resizeWindow("fg", width /resizePram, height /resizePram);
	resizeWindow("mask", width /resizePram, height /resizePram);*/

	while (keyboard != 'q'){
		if (!cap.read(frame)){
			exit(0);
		}

		t = (double)getTickCount();

		pMOG2->apply(frame, fgMaskMOG2);

		//blur(fgMaskMOG2, fgMaskMOG2, Size(3, 3));
		findContours(fgMaskMOG2.clone(), contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

		vector<vector<Point>> contours_poly(contours.size());
		vector<Rect> boundRect(contours.size());
		for (size_t i = 0; i < contours.size(); i++){
			boundRect[i] = boundingRect(Mat(contours[i]));
		}
		for (size_t i = 0; i < contours.size(); i++){
			if (boundRect[i].area() > threshold && boundRect[i].area() < frame.cols * frame.rows / 16){
				rectangle(frame, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 0, 0), 2, 8, 0);
				__int32 iname = i;
				sprintf(name, "%d.png", iname);
				std::string fullName("C:\\codes\\tmp\\");
				fullName += name;
				roi = frame(boundRect[i]);
				imwrite(fullName, roi);
			}

		}

		t = ((double)getTickCount() - t) / getTickFrequency();
		fps = 1.0 / t;
		sprintf(string, "%.2f", fps);
		std::string fpsString("Speed:");
		fpsString += string;

		putText(frame, fpsString, cv::Point(15, 15), FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255));

		imshow("fg", frame);
		imshow("mask", fgMaskMOG2);
		keyboard = (char)waitKey(33);
	}
	cap.release();

	return 0;
}