
#include "mytools.h"

void getFiles(string path, vector<string>& files)
{
	//文件句柄
	intptr_t   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("/").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
//int main()
//{
//	string path = "D:/IP_CV_WorkSpace/Img/ResIlu_pre2";
//	string pathSave = "D:/IP_CV_WorkSpace/img/posBoatForHog";
//	vector<string> files;
//	getFiles(path, files);
//	for (int i = 0; i < files.size(); i++)
//	{
//		Mat img = imread(files[i]);
//
//		//Size dsize = Size(287, 90);
//		//Mat image2 = Mat(dsize, CV_32S);
//		//resize(img, image2, dsize);
//		char pictureName[10];
//		sprintf(pictureName, "%d.jpg", i);
//
//		string filename = pathSave + "/" + pictureName;
//		imwrite(filename, img);
//	}
//	return 0;
//}