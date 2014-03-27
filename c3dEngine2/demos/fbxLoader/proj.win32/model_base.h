
#ifndef CMODEL_H_H    
#define CMODEL_H_H
#include "mesh.h"
#include "mathEx.h"
class Cmodel{
public:
	//
	Cmesh*pmesh;//模型指针
	vector<Cmesh*> pmeshList;//模型指针列表
	GLuint displist;//显示列表句柄
	GLuint texture;//纹理句柄

	//变换
	float RMmat[16];//旋转-平移矩阵
	float Zmat[16];//缩放矩阵
	//连接
	Cmodel*pf;//父亲指针
	vector<Cmodel*>p;//孩子指针数组
	//材质
	float material_specular[4];
	float material_shininess[1];
	float material_emission[4];
	float color[4];//颜色，代替diffuse and ambient
	//其它
	bool visible;//是否可见
	bool bshowBB;//是否显示包围球
	float Rc;//包围球半径(注意，是世界空间中的量)
	int rotcount;//旋转次数计数

	Cmodel(){
		
		pmesh=NULL;
		init4(color,1,1,1,1);
		init4(material_specular,0,0,0,1);
		material_shininess[0]=0;
		init4(material_emission,0.15,0.15,0.15,1);
		rotcount=0;
		visible=true;
		bshowBB=false;
		Rc=0;
		pf=NULL;
		makeE(RMmat);
		makeE(Zmat);
		//opengl和openal中句柄0均表示无效
		displist=0;
		texture=0;
	}

	virtual ~Cmodel(){
	
		//pmeshList和pmesh不能在此处析构，因为一个mesh可以挂到多个模型上
		
		//texture可以被多个模型共用，所以不在此处析构（由textureManager负责）

		//displist也可以被多个模型共用，所以也不在此处析构

	}
	void getPosInFather(float v[4]){//获得在父坐标系中的位置
		//x=RMmat[12]
		//y=RMmat[13]
		//z=RMmat[14]
		init4(v,RMmat[12],RMmat[13],RMmat[14],1);
	}
	void getDirInFather(float v[4]){//获得在父坐标系中的朝向（即将局部坐标系中的(0,0,-1,0)变到父坐标系）
		init4(v,-RMmat[8],-RMmat[9],-RMmat[10],0);
	}
	void setPosInFather(float x,float y,float z){//设定自身在父坐标系中的位置
		RMmat[12]=x;
		RMmat[13]=y;
		RMmat[14]=z;
	}
	void addchild(Cmodel*_p){
		p.push_back(_p);
		_p->pf=this;
	}
	bool ridchild(Cmodel*_p){//将孩子指针中指向*_p者删除
		//去找要删除的元素
		int index=-1;
		int n=(int)p.size();
		for(int i=0;i<n;i++){
			if(_p==p[i]){
				index=i;
				break;
			}
		}//得到index
		if(index==-1){//没找到
			return false;
		}else{//找到
			//用p的最后一个元素替换p[index]，然后删除p的最后一个元素
			p[index]=p[n-1];
			p.pop_back();
			return true;
		}
	}
	void movloc(float dx,float dy,float dz){//相对于局部坐标系移动局部坐标（即dx,dy,dz为局部坐标系中的量）
		// RMmat    *   Mmat     =    RMmat'     
		// a d g x     1 0 0 dx     a d g x+adx+ddy+gdz 
		// b e h y  *  0 1 0 dy  =  b e h y+bdx+edy+hdz
		// c f i z     0 0 1 dz     c f i z+cdx+fdy+idz
		// 0 0 0 1     0 0 0  1     0 0 0 1
		RMmat[12]+=RMmat[0]*dx+RMmat[4]*dy+RMmat[8]*dz;
		RMmat[13]+=RMmat[1]*dx+RMmat[5]*dy+RMmat[9]*dz;
		RMmat[14]+=RMmat[2]*dx+RMmat[6]*dy+RMmat[10]*dz;

	}
	void movloc_010(float dy){//沿自身y轴移动自身局部坐标系
		//可以按movloc(0,dy,0)内部公式退化来理解，也可以从物理意义上来理解如下：
		//(RMmat[4],RMmat[5],RMmat[6])恰为局部坐标系Y轴在世界空间内的单位方向向量，所以如下即可实现移动
		RMmat[12]+=RMmat[4]*dy;
		RMmat[13]+=RMmat[5]*dy;
		RMmat[14]+=RMmat[6]*dy;

	}
	void movloc_100(float dx){//沿自身x轴移动自身局部坐标系
		RMmat[12]+=RMmat[0]*dx;
		RMmat[13]+=RMmat[1]*dx;
		RMmat[14]+=RMmat[2]*dx;

	}
	void movloc_001(float dz){//沿自身z轴移动自身局部坐标系
		RMmat[12]+=RMmat[8]*dz;
		RMmat[13]+=RMmat[9]*dz;
		RMmat[14]+=RMmat[10]*dz;

	}
	void movloc_101(float dx,float dz){//在xz平面上相对于局部坐标系移动局部坐标
		//除了从退化的角度来理解外，直接从物理意义上理解也很容易：
		//(RMmat[0],RMmat[1],RMmat[2])是局部坐标系x轴在世界空间内的单位方向向量
		//(RMmat[8],RMmat[9],RMmat[10])是局部坐标系z轴在世界空间内的单位方向向量
		//所以实现移动按下式即可
		RMmat[12]+=RMmat[0]*dx+RMmat[8]*dz;
		RMmat[13]+=RMmat[1]*dx+RMmat[9]*dz;
		RMmat[14]+=RMmat[2]*dx+RMmat[10]*dz;

	}
	void zoomloc(float kx,float ky,float kz){//相对于自身缩放局部坐标系，不影响Zmat0
		Zmat[0]*=kx;
		Zmat[5]*=ky;
		Zmat[10]*=kz;
	}
	
	void movloc_inFather(float dx,float dy,float dz){//在父坐标系中移动局部坐标系(即dx,dy,dz为父坐标系中的量)
		//  Mmat    *   RMmat   =   RMmat'
		// 1 0 0 dx    a d g x     a d g x+dx
		// 0 1 0 dy *  b e h y  =  b e h y+dy
		// 0 0 1 dz    c f i z     c f i z+dz
		// 0 0 0 1     0 0 0 1     0 0 0 1
		RMmat[12]+=dx;
		RMmat[13]+=dy;
		RMmat[14]+=dz;

		
		
	}
	
	void setColor(float r,float g,float b,float a){
		init4(color,r,g,b,a);
	
	}
	void virtual show(){
	}


};


#endif
