#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <direct.h>
#include <vector>
#include <new>
#include <bitset>
#include <windows.h>
#include <math.h>
#include <glut.h>
#include <freeglut.h>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


#define M_PI 3.1415926536
#define MIN(a,b)  ((a) > (b) ? (b) : (a))
#define MAX(a,b)  ((a) < (b) ? (b) : (a))

#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifdef _DEBUG
//Debugモードの場合
#pragma comment(lib,"opencv_core249d.lib")
#pragma comment(lib,"opencv_imgproc249d.lib")
#pragma comment(lib,"opencv_highgui249d.lib")
//#pragma comment(lib,"opencv_objdetect249d.lib")
//#pragma comment(lib,"opencv_contrib249d.lib")
//#pragma comment(lib,"opencv_features2d249d.lib")
//#pragma comment(lib,"opencv_flann249d.lib")
//#pragma comment(lib,"opencv_gpu249d.lib")
//#pragma comment(lib,"opencv_haartraining_engined.lib")
//#pragma comment(lib,"opencv_legacy249d.lib")
//#pragma comment(lib,"opencv_ts249d.lib")
//#pragma comment(lib,"opencv_video249d.lib")
#else
//Releaseモードの場合
#pragma comment(lib,"opencv_core249.lib")
#pragma comment(lib,"opencv_imgproc249.lib")
#pragma comment(lib,"opencv_highgui249.lib")
//#pragma comment(lib,"opencv_objdetect249.lib")
//#pragma comment(lib,"opencv_contrib249.lib")
//#pragma comment(lib,"opencv_features2d249.lib")
//#pragma comment(lib,"opencv_flann249.lib")
//#pragma comment(lib,"opencv_gpu249.lib")
//#pragma comment(lib,"opencv_haartraining_engined.lib")
//#pragma comment(lib,"opencv_legacy249.lib")
//#pragma comment(lib,"opencv_ts249.lib")
//#pragma comment(lib,"opencv_video249.lib")
#endif


using namespace cv;

//マクロ定義
#define PIXEL(p,x,y)    ((unsigned char *)p->imageData)[p->widthStep*(y)+(x)]
#define PIXEL_R(p,x,y)  ((unsigned char *)p->imageData)[p->widthStep*(y)+(x)*3+2]
#define PIXEL_G(p,x,y)  ((unsigned char *)p->imageData)[p->widthStep*(y)+(x)*3+1]
#define PIXEL_B(p,x,y)  ((unsigned char *)p->imageData)[p->widthStep*(y)+(x)*3]

#define PIX(p,x,y)	(unsigned char)p.data[y*p.cols+x]
#define PIX_R(p,x,y)	(unsigned char)p.data[y * p.step + x * p.elemSize() + 2]
#define PIX_G(p,x,y)	(unsigned char)p.data[y * p.step + x * p.elemSize() + 1]
#define PIX_B(p,x,y)	(unsigned char)p.data[y * p.step + x * p.elemSize() + 0]

//順番に注意しようね
#include"EnumLib.h"
#include"PixelData.h"
#include"CellManage.h"
#include"BoardManage.h"
#include"Node.h"
#include"TreeStructure.h"
#include"PlayerManage.h"
#include"ComPlayer.h"
#include"GameManage.h"




