#include <iostream>

#include "imgproc/imgproc.hpp"
#include "ml.h"
#include "core/core.hpp"
#include "highgui/highgui.hpp"
#include "opencv2/tracking.hpp"

using namespace cv;
using namespace std;
//²Î¿¼´úÂë¼òÊé http://www.jianshu.com/p/e5d41cab8057
int main()
{
	Rect2d roi;
	Mat frame;
	Ptr<Tracker> tracker = Tracker::create("MEDIANFLOW");
	VideoCapture cap("result_161.avi");
	double fps = cap.get(CAP_PROP_FPS);
	double hgh = cap.get(CAP_PROP_FRAME_HEIGHT);
	double wgh = cap.get(CAP_PROP_FRAME_WIDTH);
	VideoWriter writer("result148.avi", CV_FOURCC('D', 'I', 'V', 'X'), fps, Size(wgh,hgh));
	cap >> frame;
	roi = Rect2d(610, 88, 13, 17);
	tracker->init(frame, roi);
	for (;;)
	{
		cap >> frame;
		if (frame.empty())
		{
			continue;
		}
		
		tracker->update(frame, roi);
		rectangle(frame, roi, Scalar(255, 0, 0), 2, 1);
		writer << frame;
		imshow("tracker", frame);
		if (waitKey(127) == 'q')
		{
			cap.release();
			writer.release();
			break;
		}
	}
	cap.release();
	//writer.release();
	return 0;
}