
#ifndef CMODEL_H_H    
#define CMODEL_H_H
#include "mesh.h"
#include "mathEx.h"
class Cmodel{
public:
	//
	Cmesh*pmesh;//ģ��ָ��
	vector<Cmesh*> pmeshList;//ģ��ָ���б�
	GLuint displist;//��ʾ�б���
	GLuint texture;//������

	//�任
	float RMmat[16];//��ת-ƽ�ƾ���
	float Zmat[16];//���ž���
	//����
	Cmodel*pf;//����ָ��
	vector<Cmodel*>p;//����ָ������
	//����
	float material_specular[4];
	float material_shininess[1];
	float material_emission[4];
	float color[4];//��ɫ������diffuse and ambient
	//����
	bool visible;//�Ƿ�ɼ�
	bool bshowBB;//�Ƿ���ʾ��Χ��
	float Rc;//��Χ��뾶(ע�⣬������ռ��е���)
	int rotcount;//��ת��������

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
		//opengl��openal�о��0����ʾ��Ч
		displist=0;
		texture=0;
	}

	virtual ~Cmodel(){
	
		//pmeshList��pmesh�����ڴ˴���������Ϊһ��mesh���Թҵ����ģ����
		
		//texture���Ա����ģ�͹��ã����Բ��ڴ˴���������textureManager����

		//displistҲ���Ա����ģ�͹��ã�����Ҳ���ڴ˴�����

	}
	void getPosInFather(float v[4]){//����ڸ�����ϵ�е�λ��
		//x=RMmat[12]
		//y=RMmat[13]
		//z=RMmat[14]
		init4(v,RMmat[12],RMmat[13],RMmat[14],1);
	}
	void getDirInFather(float v[4]){//����ڸ�����ϵ�еĳ��򣨼����ֲ�����ϵ�е�(0,0,-1,0)�䵽������ϵ��
		init4(v,-RMmat[8],-RMmat[9],-RMmat[10],0);
	}
	void setPosInFather(float x,float y,float z){//�趨�����ڸ�����ϵ�е�λ��
		RMmat[12]=x;
		RMmat[13]=y;
		RMmat[14]=z;
	}
	void addchild(Cmodel*_p){
		p.push_back(_p);
		_p->pf=this;
	}
	bool ridchild(Cmodel*_p){//������ָ����ָ��*_p��ɾ��
		//ȥ��Ҫɾ����Ԫ��
		int index=-1;
		int n=(int)p.size();
		for(int i=0;i<n;i++){
			if(_p==p[i]){
				index=i;
				break;
			}
		}//�õ�index
		if(index==-1){//û�ҵ�
			return false;
		}else{//�ҵ�
			//��p�����һ��Ԫ���滻p[index]��Ȼ��ɾ��p�����һ��Ԫ��
			p[index]=p[n-1];
			p.pop_back();
			return true;
		}
	}
	void movloc(float dx,float dy,float dz){//����ھֲ�����ϵ�ƶ��ֲ����꣨��dx,dy,dzΪ�ֲ�����ϵ�е�����
		// RMmat    *   Mmat     =    RMmat'     
		// a d g x     1 0 0 dx     a d g x+adx+ddy+gdz 
		// b e h y  *  0 1 0 dy  =  b e h y+bdx+edy+hdz
		// c f i z     0 0 1 dz     c f i z+cdx+fdy+idz
		// 0 0 0 1     0 0 0  1     0 0 0 1
		RMmat[12]+=RMmat[0]*dx+RMmat[4]*dy+RMmat[8]*dz;
		RMmat[13]+=RMmat[1]*dx+RMmat[5]*dy+RMmat[9]*dz;
		RMmat[14]+=RMmat[2]*dx+RMmat[6]*dy+RMmat[10]*dz;

	}
	void movloc_010(float dy){//������y���ƶ�����ֲ�����ϵ
		//���԰�movloc(0,dy,0)�ڲ���ʽ�˻�����⣬Ҳ���Դ�������������������£�
		//(RMmat[4],RMmat[5],RMmat[6])ǡΪ�ֲ�����ϵY��������ռ��ڵĵ�λ�����������������¼���ʵ���ƶ�
		RMmat[12]+=RMmat[4]*dy;
		RMmat[13]+=RMmat[5]*dy;
		RMmat[14]+=RMmat[6]*dy;

	}
	void movloc_100(float dx){//������x���ƶ�����ֲ�����ϵ
		RMmat[12]+=RMmat[0]*dx;
		RMmat[13]+=RMmat[1]*dx;
		RMmat[14]+=RMmat[2]*dx;

	}
	void movloc_001(float dz){//������z���ƶ�����ֲ�����ϵ
		RMmat[12]+=RMmat[8]*dz;
		RMmat[13]+=RMmat[9]*dz;
		RMmat[14]+=RMmat[10]*dz;

	}
	void movloc_101(float dx,float dz){//��xzƽ��������ھֲ�����ϵ�ƶ��ֲ�����
		//���˴��˻��ĽǶ�������⣬ֱ�Ӵ��������������Ҳ�����ף�
		//(RMmat[0],RMmat[1],RMmat[2])�Ǿֲ�����ϵx��������ռ��ڵĵ�λ��������
		//(RMmat[8],RMmat[9],RMmat[10])�Ǿֲ�����ϵz��������ռ��ڵĵ�λ��������
		//����ʵ���ƶ�����ʽ����
		RMmat[12]+=RMmat[0]*dx+RMmat[8]*dz;
		RMmat[13]+=RMmat[1]*dx+RMmat[9]*dz;
		RMmat[14]+=RMmat[2]*dx+RMmat[10]*dz;

	}
	void zoomloc(float kx,float ky,float kz){//������������žֲ�����ϵ����Ӱ��Zmat0
		Zmat[0]*=kx;
		Zmat[5]*=ky;
		Zmat[10]*=kz;
	}
	
	void movloc_inFather(float dx,float dy,float dz){//�ڸ�����ϵ���ƶ��ֲ�����ϵ(��dx,dy,dzΪ������ϵ�е���)
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
