#include "mainWindowGlobal.h"
//global var
bool isTouching;
long tf=0,t=0,dt=0;//tf�ϴν���idle,t���ν���idle,dt�������ϴν���idleʱ����--abc
float captionHeight=0;//�������߶�--abc
float frameBoarder=0;//���ڱ߿���--abc
 
//win32 global var
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application