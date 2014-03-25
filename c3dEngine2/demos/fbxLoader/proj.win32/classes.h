#include "mathEx.h"
#ifndef CRGBA_H_H
#define CRGBA_H_H
class Crgba{
public:
	float R;
	float G;
	float B;
	float A;
	Crgba(){
		R=1;
		G=1;
		B=1;
		A=1;
	}
	void init(float r,float g,float b,float a=1){
		R=r;
		G=g;
		B=b;
		A=a;
	}
};
#endif
#ifndef CV4_H_H
#define CV4_H_H
class Cv4{
public:
	float v[4];
};
#endif
#ifndef CVERTEX_H_H
#define CVERTEX_H_H
class Cvertex
{
public:
	float v[4];//����
	float u[2];//��ͼ����
	Cvertex(){
	}
};
#endif
#ifndef CTRI_H_H
#define CTRI_H_H
class Ctri{
public:
	float p[3][4];
	void makeTri(float p0[4],float p1[4],float p2[4]){
		veccopy(p0,p[0]);
		veccopy(p1,p[1]);
		veccopy(p2,p[2]);
	}
};
#endif
#ifndef CRECT_H_H
#define CRECT_H_H
class Crect{
public:
	float p[4][4];
	void makeRect(const float p0[4],const float p1[4],const float p2[4],const float p3[4]){
		veccopy(p0,p[0]);
		veccopy(p1,p[1]);
		veccopy(p2,p[2]);
		veccopy(p3,p[3]);
	}
		
};
#endif
#ifndef CIDLINE_H_H
#define CIDLINE_H_H
class CIDLine{
public:
	int vID[2];
	int index_IDtri;//ָ����IDLine���ڵڼ���IDtri
	CIDLine(){
		index_IDtri=-1;
	}
	void setvID(int ID0,int ID1){
		vID[0]=ID0;
		vID[1]=ID1;
	}

};
#endif


#ifndef CIDEDGE_H_H
#define CIDEDGE_H_H
class CIDedge{
public:
	int vID[2];
	void setvID(int ID0,int ID1){
		vID[0]=ID0;
		vID[1]=ID1;
	}

};
#endif
#ifndef CIDTRIANGLE_H_H
#define CIDTRIANGLE_H_H
class CIDTriangle{
public:
	int vID[3];
	float norm[4];//��vlist�еĶ������귢���仯norm�����
	bool added;//Ϊ�����ظ���������ı��
	GLuint texture;//����
	bool noSV;//��������Ӱ��
	int textureIndex_inMeshTextureList;//������������mesh.textureList�е�������
	CIDTriangle(){
		texture=0;
		added=false;
		noSV=false;
	}
	
	void setvID(int ID0,int ID1,int ID2){
		vID[0]=ID0;
		vID[1]=ID1;
		vID[2]=ID2;
	
	}
	void getVertex(int index,const vector<Cvertex>&vlist,float v[4]){//���index�Ŷ�������,��v����
		veccopy(vlist[vID[index]].v,v);
	}
	void getVertex(const vector<Cvertex>&vlist,float p0[4],float p1[4],float p2[4]){//���ȫ���������������
		veccopy(vlist[vID[0]].v,p0);
		veccopy(vlist[vID[1]].v,p1);
		veccopy(vlist[vID[2]].v,p2);
	}

	void print(const vector<Cvertex>&vlist){//��ӡ��������
		const float *p0=vlist[vID[0]].v;
		const float *p1=vlist[vID[1]].v;
		const float *p2=vlist[vID[2]].v;
		cout<<p0[X]<<" "<<p0[Y]<<" "<<p0[Z]<<endl;
		cout<<p1[X]<<" "<<p1[Y]<<" "<<p1[Z]<<endl;
		cout<<p2[X]<<" "<<p2[Y]<<" "<<p2[Z]<<endl;
	}
	void showWire(vector<Cvertex>&vlist){//���߿�
		float *p0=vlist[vID[0]].v;
		float *p1=vlist[vID[1]].v;
		float *p2=vlist[vID[2]].v;
		//��������p0p1p2
		glBegin(GL_LINES);
		glVertex3fv(p0);
		glVertex3fv(p1);
		glVertex3fv(p1);
		glVertex3fv(p2);
		glVertex3fv(p2);
		glVertex3fv(p0);
		glEnd();

	}


	
};
#endif

#ifndef CPLANE_H_H
#define CPLANE_H_H
class Cplane//�õ㷨ʽ����
{
public:
	float p[4];
	float norm[4];
	void makePlane(float _p[4],float _norm[4])
	//�ɵ㷨����ƽ�棬_normȷ��Ϊ��λ����
	{
		veccopy(_p,p);
		veccopy(_norm,norm);
	}

};
#endif