#include "paint.h"

void onPaint(HDC hDC){

	//获得视口大小
	GLint viewport[4];//4个元素依次为viewX,viewY,width,height
	glGetIntegerv(GL_VIEWPORT,viewport);
	float width=viewport[2];
	float height=viewport[3];


	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);//切换到投影模式
    glPushMatrix();//保存状态
    glLoadIdentity();//归一化
	//设置视锥
	float nearface=0.5;
	float farface=10000.0;//远截面
    gluPerspective(70,//视角
		(float)width/height, //窗口横纵比
		nearface,//近截面
		farface);//远截面(为了能够显示大尺度空间，此值必须设得足够大)
	//--------------------------------对 模型-视图 堆栈的操作----
	glMatrixMode(GL_MODELVIEW);//切换到 模型-视图 模式
	glLoadIdentity();//归一化
	//设置视图矩阵
	{
		gluLookAt(0,800,1500,//相机位置
			0,800,0,//关注点
			0,1,0);//相机向上方向
	//	gluLookAt(0,5000,6000,//相机位置
	//		0,0,0,//关注点
	//		0,1,0);//相机向上方向
	}
	float _light_pos[4]={1000,5000,1000,0};
	glLightfv(GL_LIGHT0,GL_POSITION,_light_pos);
	modelx2.show();
	////////////////////////////// swap buffers ///////////////////
	SwapBuffers(hDC);
}
