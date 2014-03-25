
#ifndef CMESH_H_H
#define CMESH_H_H
#include "classes.h"
#include "indexVBO.h"
class Cmesh{
public:
	string descriptionStr;//�����ַ���
	vector<Cvertex> vlist;//�����б�
	vector<CIDTriangle> IDtriList;//�����������б�
	vector<GLuint> textureList;//�����б�ֻ����Щ������ĳ��������ʹ�õ�����Żᱻ��¼��������textureList�������㷨���Ա�֤��㣩
	vector<GLuint> texIDtriCountList;//texIDtriCountList[i]ΪtextureList[i]��Ӧ����������
	vector<string> texPathList;//����·���б�
	//index vbo
	CindexVBO indexVBO;
	//
	Cmesh(){

		
	}
	
	~Cmesh(){
		
	}
	void calTextureInfo(){
		makeTextureListAndCalIndexInTextureListForEachIDtri();//����mesh.textureList
		makeTexIDtriCountList();//����mesh.texIDtriCountList
	}
	void copy(const Cmesh&mesh){//����
		*this=mesh;
	}
	
	void merge(const Cmesh&mesh){//��mesh�ϲ���������
		//-------------------------------
		//Ԥ���ռ�
		this->vlist.reserve((int)this->vlist.size()+(int)mesh.vlist.size());
		this->IDtriList.reserve((int)this->IDtriList.size()+(int)mesh.IDtriList.size());
		//-------------------------------
		//ֻ�ϲ�vlist��IDtriList
		//������ϲ�ǰ������nv_this_old
		int nv_this_old=(int)vlist.size();
		//��mesh.vlist�ӵ�vlist��
		{
			int nv=(int)mesh.vlist.size();
			for(int i=0;i<nv;i++){
				vlist.push_back(mesh.vlist[i]);
			}
		}
		//��mesh.IDtriList�ӵ�IDtriList��
		{
			int nIDtri=(int)mesh.IDtriList.size();
			for(int i=0;i<nIDtri;i++){
				CIDTriangle IDtri=mesh.IDtriList[i];//����mesh�е�ǰ������(ע���ǿ�����������)
				//�Դ������εĸ��������ƫ��
				IDtri.vID[0]+=nv_this_old;
				IDtri.vID[1]+=nv_this_old;
				IDtri.vID[2]+=nv_this_old;
				//��IDtri���뵽this
				IDtriList.push_back(IDtri);
			}
		}
	
	}

	

	void makeTextureListAndCalIndexInTextureListForEachIDtri()
	//����textureList�����������������textureList�ϵ�������
	//ֻ��������ĳ��������ʹ�õ�����Żᱻ��¼��textureList����������Ĳ��ᱻ��¼
	{
		//�������������Σ�ÿ�������ζ�ȥtextureList��Ѱ���Լ���λ��
		//����ҵ��ͽ���λ�ô浽�������ε�textureIndex_InMeshTextureList��
		//����Ҳ����ͽ�textureList����һ��Ԫ�أ�Ȼ���ٽ��������ε�textureIndex_InMeshTextueList�д����λ��
		int nIDtri=(int)IDtriList.size();
		for(int i=0;i<nIDtri;i++){
			CIDTriangle&IDtri=IDtriList[i];
			//��IDtri��textureList�ϵ�λ��
			bool found=false;//�Ƿ��ҵ�
			int J=-1;//IDtri��textureList�ϵ�����
			int nTexture=(int)textureList.size();
			for(int j=0;j<nTexture;j++){
				if(IDtri.texture==textureList[j]){
					found=true;
					J=j;
					break;
				}
			}//�õ�found
			if(found){//�ҵ�
				//��J���浽IDtri.textureIndex_inMeshTextureList
				IDtri.textureIndex_inMeshTextureList=J;
			}else{//û�ҵ�
				//textureList����һ��Ԫ�أ��ô�Ԫ����ΪIDtri��λ��
				textureList.push_back(IDtri.texture);
				IDtri.textureIndex_inMeshTextureList=(int)textureList.size()-1;
			}
		}
	}
	
	void makeTexIDtriCountList(){
		int nTex=(int)textureList.size();
		for(int i=0;i<nTex;i++){
			GLuint texture=textureList[i];
			//ͳ������Ϊtexture�������湲�ж��ٸ�
			int count=0;
			int nIDtri=(int)IDtriList.size();
			for(int j=0;j<nIDtri;j++){
				if(IDtriList[j].texture==texture)count++;
			}//�õ�count
			//��count����texIDtriCountList
			texIDtriCountList.push_back(count);
		}//�õ�texIDtriCountList
		
	}
	void clear(){
		vlist.clear();
		IDtriList.clear();
	}
	
	void calNorm_IDtriList(){//ΪIDtriList�и������μ��㷨����
		int nvID=(int)IDtriList.size();
		for(int i=0;i<nvID;i++){
			CIDTriangle&IDtri=IDtriList[i];
			float*v0=vlist[IDtri.vID[0]].v;
			float*v1=vlist[IDtri.vID[1]].v;
			float*v2=vlist[IDtri.vID[2]].v;
			float vec1[4],vec2[4];
			float norm[4];
			sub((float(&)[4])(*v1),(float(&)[4])(*v0),vec1);
			sub((float(&)[4])(*v2),(float(&)[4])(*v0),vec2);
			cross(vec1,vec2,norm);
			normalize(norm);
			veccopy(norm,IDtri.norm);

		}
	}

	void addvert(float x,float y,float z){
		Cvertex vertex;
		init4(vertex.v,x,y,z,1);
		vlist.push_back(vertex);
	}
	void setLastUV(float u,float v){//Ϊ��ǰ���һ������ָ��uv����
		init2(vlist[(int)vlist.size()-1].u ,u,v);
	}
	void addtri(int ID0,int ID1,int ID2){
		CIDTriangle IDtri;
		IDtri.setvID(ID0,ID1,ID2);
		IDtriList.push_back(IDtri);
	}
	int getLastvID(){
		return (int)vlist.size()-1;
	}
	void setNormForLastIDtri(float nx,float ny,float nz){
		float*norm=IDtriList[(int)IDtriList.size()-1].norm;
		init4(norm,nx,ny,nz,0);
	}
	void setTextureForLastIDtri(GLuint _texture){
		IDtriList[(int)IDtriList.size()-1].texture=_texture;
	
	}
	
	void show_immediate(){
		glBegin(GL_TRIANGLES);
		int n=(int)IDtriList.size();
		for(int i=0;i<n;i++){
			glNormal3fv(IDtriList[i].norm);
			//
			glTexCoord2fv(vlist[IDtriList[i].vID[0]].u);
			glVertex3fv(vlist[IDtriList[i].vID[0]].v);
			
			glTexCoord2fv(vlist[IDtriList[i].vID[1]].u);
			glVertex3fv(vlist[IDtriList[i].vID[1]].v);
			

			glTexCoord2fv(vlist[IDtriList[i].vID[2]].u);
			glVertex3fv(vlist[IDtriList[i].vID[2]].v);
			
			
		}
		glEnd();
	}
	
	
};
#endif
