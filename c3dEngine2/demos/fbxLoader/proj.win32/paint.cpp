#include "paint.h"

void onPaint(HDC hDC){

	//����ӿڴ�С
	GLint viewport[4];//4��Ԫ������ΪviewX,viewY,width,height
	glGetIntegerv(GL_VIEWPORT,viewport);
	float width=viewport[2];
	float height=viewport[3];


	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);//�л���ͶӰģʽ
    glPushMatrix();//����״̬
    glLoadIdentity();//��һ��
	//������׶
	float nearface=0.5;
	float farface=10000.0;//Զ����
    gluPerspective(70,//�ӽ�
		(float)width/height, //���ں��ݱ�
		nearface,//������
		farface);//Զ����(Ϊ���ܹ���ʾ��߶ȿռ䣬��ֵ��������㹻��)
	//--------------------------------�� ģ��-��ͼ ��ջ�Ĳ���----
	glMatrixMode(GL_MODELVIEW);//�л��� ģ��-��ͼ ģʽ
	glLoadIdentity();//��һ��
	//������ͼ����
	{
		gluLookAt(0,800,1500,//���λ��
			0,800,0,//��ע��
			0,1,0);//������Ϸ���
	//	gluLookAt(0,5000,6000,//���λ��
	//		0,0,0,//��ע��
	//		0,1,0);//������Ϸ���
	}
	float _light_pos[4]={1000,5000,1000,0};
	glLightfv(GL_LIGHT0,GL_POSITION,_light_pos);
	modelx2.show();
	////////////////////////////// swap buffers ///////////////////
	SwapBuffers(hDC);
}
