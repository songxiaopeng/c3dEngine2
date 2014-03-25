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
	float v[4];//坐标
	float u[2];//贴图坐标
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
	int index_IDtri;//指明本IDLine属于第几个IDtri
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
	float norm[4];//当vlist中的顶点坐标发生变化norm需更新
	bool added;//为避免重复加入而作的标记
	GLuint texture;//纹理
	bool noSV;//不生成阴影体
	int textureIndex_inMeshTextureList;//纹理索引（在mesh.textureList中的索引）
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
	void getVertex(int index,const vector<Cvertex>&vlist,float v[4]){//获得index号顶点坐标,由v带回
		veccopy(vlist[vID[index]].v,v);
	}
	void getVertex(const vector<Cvertex>&vlist,float p0[4],float p1[4],float p2[4]){//获得全部三个顶点的坐标
		veccopy(vlist[vID[0]].v,p0);
		veccopy(vlist[vID[1]].v,p1);
		veccopy(vlist[vID[2]].v,p2);
	}

	void print(const vector<Cvertex>&vlist){//打印顶点坐标
		const float *p0=vlist[vID[0]].v;
		const float *p1=vlist[vID[1]].v;
		const float *p2=vlist[vID[2]].v;
		cout<<p0[X]<<" "<<p0[Y]<<" "<<p0[Z]<<endl;
		cout<<p1[X]<<" "<<p1[Y]<<" "<<p1[Z]<<endl;
		cout<<p2[X]<<" "<<p2[Y]<<" "<<p2[Z]<<endl;
	}
	void showWire(vector<Cvertex>&vlist){//画线框
		float *p0=vlist[vID[0]].v;
		float *p1=vlist[vID[1]].v;
		float *p2=vlist[vID[2]].v;
		//画三角面p0p1p2
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
class Cplane//用点法式描述
{
public:
	float p[4];
	float norm[4];
	void makePlane(float _p[4],float _norm[4])
	//由点法构造平面，_norm确保为单位向量
	{
		veccopy(_p,p);
		veccopy(_norm,norm);
	}

};
#endif