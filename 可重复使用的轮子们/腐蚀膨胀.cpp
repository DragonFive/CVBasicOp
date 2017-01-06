#include "mytools.h"
//#define NOOPENCLOSE 1
//#define WriteVideo 1



static void help()
{
	printf("\nShow off image morphology: erosion, dialation, open and close\n"
		"Call:\n   morphology2 [image]\n"
		"This program also shows use of rect, ellipse and cross kernels\n\n");
	printf("Hot keys: \n"
		"\tESC - quit the program\n"
		"\tr - use rectangle structuring element\n"
		"\te - use elliptic structuring element\n"
		"\tc - use cross-shaped structuring element\n"
		"\tSPACE - loop through all the options\n");
}
static Mat  src, dst;
int element_shape = MORPH_RECT;
//the address of variable which receives trackbar position update
static int max_iters = 10;
static int open_close_pos = 0;
static int erode_dilate_pos = 0;
// callback function for open/close trackbar

#ifndef NOOPENCLOSE
static void OpenClose(int, void*)//开闭运算;
{
	int n = open_close_pos - max_iters;//这个max_iters相当于中间值;
	int an = n > 0 ? n : -n; //取距离中线的距离;
	Mat element = getStructuringElement(element_shape, Size(an * 2 + 1, an * 2 + 1), Point(an, an));//生成一个结构化元素;
	if (n < 0)
		morphologyEx(src, dst, MORPH_OPEN, element);
	else
		morphologyEx(src, dst, MORPH_CLOSE, element);
#ifndef WriteVideo
	imshow("Open/Close", dst);
#endif
}
#else 
// callback function for erode/dilate trackbar
static void ErodeDilate(int, void*)//膨胀腐蚀;
{
	int n = erode_dilate_pos - max_iters;
	int an = n > 0 ? n : -n;
	Mat element = getStructuringElement(element_shape, Size(an * 2 + 1, an * 2 + 1), Point(an, an));
	if (n < 0)
		erode(src, dst, element);
	else
		dilate(src, dst, element);
#ifndef WriteVideo
	imshow("Erode/Dilate", dst);
#endif
}
#endif
int mophology_imgprocess(Mat &imgToProcess,int &iterls)
{
	//cv::CommandLineParser parser(argc, argv, "{help h||}{ @image | ../data/baboon.jpg | }");
	//if (parser.has("help"))
	//{
	//	help();
	//	return 0;
	//}
	//std::string filename = parser.get<std::string>("@image");
	imgToProcess.copyTo(src);

	if (src.empty())
	{
		help();
		return -1;
	}
	//create windows for output images

	open_close_pos = erode_dilate_pos = max_iters;
	//int cv::createTrackbar(const String & 	trackbarname,   //trackbar的名字
	//	const String & 	winname,								//trackbar父窗口的名字
	//	int * 	value,											// slider 的位置;
	//	int 	count,											// slider的value的最大值;
	//	TrackbarCallback 	onChange = 0,						//回调函数,void Foo(int  trackbar position ,void*);
	//	void * 	userdata = 0									//回调函数的第二个参数;
	//	)
#ifdef WriteVideo
	
#ifndef NOOPENCLOSE
	open_close_pos = 4;
	OpenClose(open_close_pos, 0);
#else
	erode_dilate_pos = 4;
	ErodeDilate(erode_dilate_pos, 0);
#endif
	dst.copyTo(imgToProcess);
#else

#ifndef NOOPENCLOSE
	namedWindow("Open/Close", 1);
	createTrackbar("iterations", "Open/Close", &open_close_pos, max_iters * 2 + 1, OpenClose);
#else
	namedWindow("Erode/Dilate", 1);
	createTrackbar("iterations", "Erode/Dilate", &erode_dilate_pos, max_iters * 2 + 1, ErodeDilate);
#endif
	


	for (;;)
	{
		int c;
#ifndef NOOPENCLOSE
		OpenClose(open_close_pos, 0);

#else
		ErodeDilate(erode_dilate_pos, 0);
#endif
		c = waitKey(0);
		if ((char)c == 27)
		{
			dst.copyTo(imgToProcess);
			break;
		}
		if ((char)c == 'p')
			break;
		if ((char)c == 'e')
			element_shape = MORPH_ELLIPSE;
		else if ((char)c == 'r')
			element_shape = MORPH_RECT;
		else if ((char)c == 'c')
			element_shape = MORPH_CROSS;
		else if ((char)c == ' ')
			element_shape = (element_shape + 1) % 3;
	}
	
#endif
	iterls = erode_dilate_pos;
	return 0;
}