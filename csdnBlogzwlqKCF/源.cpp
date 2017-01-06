//安装配置好opencv3.1
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
using namespace cv;


//测试数据来源:https://github.com/opencv/opencv_extra/tree/master/testdata/cv/tracking
int main(){
	// declares all required variables
	//! [vars]
	Rect2d roi;
	Mat frame;
	//! [vars]

	// create a tracker object
	//! create这个函数的参数也可以是-   "MIL" -- TrackerMIL
	//! -   "BOOSTING" -- TrackerBoosting ,还可以是　"TLD"，"MEDIANFLOW"
	Ptr<Tracker> tracker = Tracker::create("MIL");
	//! [create]

	// set input video
	//! [setvideo]
	std::string video = "768x576_clip(1).avi";
	VideoCapture cap(video);
	//! [setvideo]
	cout<<cap.get(CAP_PROP_FPS)<<endl;
	cout << cap.get(CAP_PROP_FRAME_HEIGHT) << endl;
	cout << cap.get(CAP_PROP_FRAME_WIDTH) << endl;
	//fstream in("gt.txt");
	//Rect2d roiT;
	// get bounding box
	//! [getframe]
	cap >> frame;
	//double leftX, leftY, height, width;
	//char ch;
	////getline(in,ch);
	////cout << ch;
	//in >> leftX >> ch >> leftY >> ch >> width >> ch >> height;
	//roiT = Rect2d(leftX, leftY, width, height);
	//cout << leftX << "," << leftY << "," << width << "," <<height<< "\n";

	//! [getframe]
	//! [selectroi]选择目标ｒｏｉ以ＧＵＩ的形式
	roi = selectROI("tracker", frame);
	//! [selectroi]
	
	//quit if ROI was not selected
	if (roi.width == 0 || roi.height == 0)
		return 0;

	// initialize the tracker
	//! [init]
	tracker->init(frame, roi);
	//! [init]

	// perform the tracking process
	printf("Start the tracking process\n");
	for (;;){
		// get frame from the video
		cap >> frame;

		// stop the program if no more images
		if (frame.rows == 0 || frame.cols == 0)
			break;

		// update the tracking result
		//! [update]
		tracker->update(frame, roi);
		//! [update]


		//in >> leftX >> leftY >> width >> height;
		//roiT = Rect2d(leftX, leftY, width, height);
		//! [visualization]
		// draw the tracked object
		rectangle(frame, roi, Scalar(255, 0, 0), 2, 1);
		// show image with the tracked object
		imshow("tracker", frame);
		//! [visualization]
		//quit on ESC button
		if (waitKey(127) == 27)
			break;
	}

	return 0;
}