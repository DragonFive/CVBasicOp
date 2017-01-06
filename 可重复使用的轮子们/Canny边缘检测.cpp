// Canny边缘检测.cpp : 定义控制台应用程序的入口点。
//

#include "mytools.h"

/// 全局变量

Mat src, src_gray;
Mat dst, detected_edges;

//int edgeThresh = 1;
int lowThreshold=1;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";

/**
* @函数 CannyThreshold
* @简介： trackbar 交互回调 - Canny阈值输入比例1:3
*/
void CannyThreshold(int, void*)
{
	/// 使用 3x3内核降噪
	blur(src_gray, detected_edges, Size(3, 3));

	/// 运行Canny算子
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
	//第一个参数是原图像，第二个参数是输出图像，支持本地计算,第三个参数是低阈值，第四个参数是高阈值，第五个参数是内部sobel算子使用的内核大小。
	/// 使用 Canny算子输出边缘作为掩码显示原图像
	dst = Scalar::all(0);
	//把dst填充为黑色
	src.copyTo(dst, detected_edges);
	//第一个参数为输出图像，第二个参数为掩码；即把第二个图像中非0的部分在src中的像素复制给dst;

	imshow(window_name, dst);
}


/** @函数 main */
int testCanny()
{
	/// 装载图像
	src = imread("E:\\资料\\onedrive\\code\\test\\image\\lena.png",1);

	if (!src.data)
	{
		return -1;
	}

	/// 创建与src同类型和大小的矩阵(dst)
	dst.create(src.size(), src.type());

	/// 原图像转换为灰度图像
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// 创建显示窗口
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	/// 创建trackbar
	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

	/// 显示图像
	CannyThreshold(0, 0);

	/// 等待用户反应
	waitKey(0);

	return 0;
}
