#ifndef _MYH_H
#define _MYH_H
#pragma warning (disable:4183)
#pragma warning (disable:4786)
#pragma warning (disable:4804)
#pragma warning (disable:4800)
#include<string>
#include<vector>
#include<iostream> 
#include <fstream>
using namespace std;

#include <Tchar.h>//_T()函数在此头文件
#include <windows.h>

#include <math.h>
#include <time.h>
#include <float.h>//_isnan函数在此头文件中
//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <gl\gl.h>
#include "glext.h"
#pragma comment (lib,"glaux.lib")



//分量
const int X=0;
const int Y=1;
const int Z=2;
const int W=3;
const int ALPHA=3;
//常数
const float pi=3.1415926;
const float halfpi=pi/2;
const float piDiv180=pi/180;
const float inf=100000000000;




#endif