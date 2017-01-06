#ifndef MyTools
#define MyTools


// for filelisting
#include <stdio.h>
#include <io.h>
// for fileoutput
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>
//#include "cv.h"
//#include "cvaux.h"
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>//feature2d 模块. 2D特征框架；
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include "highgui.h"
//#include <ml.h>
#include <windows.h>
#include"tinyxml.h"
#include "tinystr.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;
using namespace cv;
using namespace cv::ml;
#pragma comment( lib, "vfw32.lib" )
#pragma comment( lib, "comctl32.lib" )


//参考资料一个解决方案中有两个项目，一个项目调用另一个项目中的函数 - 大白菜 - 51CTO技术博客
// http://dreamylights.blog.51cto.com/1163218/1299828


//把目录中的图像转化为视频;
void testimg2video();
void img2video(string path, double rate, double width, double height);

//把视频转化为每一帧的图片;
void testVideo2img();
void video2img(string path);
//进行canny边缘检测
void CannyThreshold(int, void*);
int testCanny();

//获取目录下的文件名;
void getFiles(string path, vector<string>& files);
//选择文件目录
string get_path();
//选择文件夹目录
string get_direc_path();


void backgroudSubstract();

//对图像进行腐蚀膨胀;
int mophology_imgprocess(Mat &imgToProcess, int &iterls);



#endif