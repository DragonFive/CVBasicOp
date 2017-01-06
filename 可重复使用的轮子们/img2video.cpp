#include "mytools.h"

//参考资料 OpenCV入门系列（7）：读取摄像头，保存为视频文件 - TW-Freewind - 博客园
// http://www.cnblogs.com/9keyes/archive/2012/08/06/2625868.html


void testimg2video()
{
	// = "D:\\IP_CV_WorkSpace\\video\\20160328_birdimg\\birdImg"
	string birdPath;
	cout << "本程序可以用来将一个文件夹里的图像转化为视频\n请选择要处理的目录:";
	//getline(cin, birdPath);
	birdPath = get_direc_path();
	img2video(birdPath, 24, 720, 400);

}

//把文件夹中的图片转化为视频;
void img2video(string path, double rate, double width, double height)
{
	struct _finddata_t jpg_file;
	intptr_t hFile;
	//string path = "D:\\IP_CV_WorkSpace\\Img\\birdImg\\";
	VideoWriter writer;
	writer.open(path + "\\result.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate,
		Size(width, height));
	if (!writer.isOpened())
	{
		cerr << "Unable to write avi" << endl;
		exit(-1);
	}
	string testPath = path;
	int numOfTest = 408;
	char positiveImgName[256];
	//string path;
	if ((hFile = _findfirst((path + "\\*.jpg").c_str(), &jpg_file)) == -1L)
		printf("no *.jpg files in directory '%s'\n", path);
	else
	{

		//	init highgui
		cvAddSearchPath(path);
		string strPrefix;
		string strPostfix;

		//	open every *.jpg file
		do
		{

			strPostfix = "";
			strPrefix = path + "\\";
			strPrefix += jpg_file.name;
			printf("%s\n", jpg_file.name);
			//IplImage * image = cvLoadImage(strPrefix.c_str());
			Mat image = imread(strPrefix, 1);
			if (image.empty())
			{
				cout << "error to load image" << endl;
			}
			else
			{
				writer << image;
			}

		} while (_findnext(hFile, &jpg_file) == 0);

	}



}
void testVideo2img()
{
	string birdPath;
	cout << "本程序可以用来将一个文件夹里的视频转化为图片\n请选择要处理的目录:";
	//getline(cin, birdPath);
	video2img(get_path());
	
}
//把视频转化为每一帧的图片;
void video2img(string path)
{
	VideoCapture cap;
	cap.open(path);
	int endPos = path.find_last_of('\\');
	string imgPath(path.begin(), path.begin() + endPos + 1);
	char imgName[256];
	if (!cap.isOpened())
	{
		cerr << "unable to read avi" << endl;
		exit(-1);
	}
	int index_img = 0;
	while (true)
	{
		memset(imgName, 0, sizeof(imgName) / sizeof(char));
		sprintf(imgName, "%05d.jpg", index_img);
		
		Mat img;
		cap >> img;
		if (img.empty())
			break;
		imwrite(imgPath+imgName,img);
		index_img++;
		
	}
}

