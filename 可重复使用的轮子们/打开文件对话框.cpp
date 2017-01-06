#include "mytools.h"

string get_direc_path()
{
	HINSTANCE hInstance;  //HINSTANCE需要包含windows.h
	typedef int  (Fun)(string &);  //定义函数原型
	Fun* pFun;  //声明函数指针

	//返回由LoadLibrary加载的动态链接库的实例句柄
	hInstance = LoadLibrary(L"getPath");

	//找到DLL中ShowTime函数的地址，函数名调用
	//pFun=(Fun*)GetProcAddress(hInstance,"ShowTime"); 

	//使用数字序号方式，可明显加快函数的调用
	pFun = (Fun*)GetProcAddress(hInstance, (LPCSTR)2);

	string  path;
	path.reserve(1024);
	int size = (*pFun)(path); //调用函数 
	cout << path  << endl;

	FreeLibrary(hInstance);  //释放调用的DLL资源

	return path;
}


string get_path()
{
	HINSTANCE hInstance;  //HINSTANCE需要包含windows.h
	typedef int  (Fun)(string &);  //定义函数原型
	Fun* pFun;  //声明函数指针

	//返回由LoadLibrary加载的动态链接库的实例句柄
	hInstance = LoadLibrary(L"getPath");

	//找到DLL中ShowTime函数的地址，函数名调用
	//pFun=(Fun*)GetProcAddress(hInstance,"ShowTime"); 

	//使用数字序号方式，可明显加快函数的调用
	pFun = (Fun*)GetProcAddress(hInstance, (LPCSTR)1);

	string  path;
	path.reserve(1024);
	int size = (*pFun)(path); //调用函数 
	//cout << path << size << endl;

	FreeLibrary(hInstance);  //释放调用的DLL资源

	return path;
}