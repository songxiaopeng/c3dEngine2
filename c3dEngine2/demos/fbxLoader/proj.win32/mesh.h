
#ifndef CMESH_H_H
#define CMESH_H_H
#include "classes.h"
#include "indexVBO.h"
class Cmesh{
public:
	string descriptionStr;//描述字符串
	vector<Cvertex> vlist;//顶点列表
	vector<CIDTriangle> IDtriList;//索引三角形列表
	vector<GLuint> textureList;//纹理列表（只有那些真正被某个三角面使用的纹理才会被收录进来，由textureList的生成算法可以保证这点）
	vector<GLuint> texIDtriCountList;//texIDtriCountList[i]为textureList[i]对应的三角面数
	vector<string> texPathList;//纹理路径列表
	//index vbo
	CindexVBO indexVBO;
	//
	Cmesh(){

		
	}
	
	~Cmesh(){
		
	}
	void calTextureInfo(){
		makeTextureListAndCalIndexInTextureListForEachIDtri();//建立mesh.textureList
		makeTexIDtriCountList();//建立mesh.texIDtriCountList
	}
	void copy(const Cmesh&mesh){//拷贝
		*this=mesh;
	}
	
	void merge(const Cmesh&mesh){//将mesh合并到本网格
		//-------------------------------
		//预留空间
		this->vlist.reserve((int)this->vlist.size()+(int)mesh.vlist.size());
		this->IDtriList.reserve((int)this->IDtriList.size()+(int)mesh.IDtriList.size());
		//-------------------------------
		//只合并vlist和IDtriList
		//求本网格合并前顶点数nv_this_old
		int nv_this_old=(int)vlist.size();
		//将mesh.vlist接到vlist上
		{
			int nv=(int)mesh.vlist.size();
			for(int i=0;i<nv;i++){
				vlist.push_back(mesh.vlist[i]);
			}
		}
		//将mesh.IDtriList接到IDtriList上
		{
			int nIDtri=(int)mesh.IDtriList.size();
			for(int i=0;i<nIDtri;i++){
				CIDTriangle IDtri=mesh.IDtriList[i];//拷贝mesh中当前三角形(注意是拷贝而非引用)
				//对此三角形的各顶点号作偏移
				IDtri.vID[0]+=nv_this_old;
				IDtri.vID[1]+=nv_this_old;
				IDtri.vID[2]+=nv_this_old;
				//将IDtri加入到this
				IDtriList.push_back(IDtri);
			}
		}
	
	}

	

	void makeTextureListAndCalIndexInTextureListForEachIDtri()
	//生成textureList，并计算各三角形在textureList上的索引号
	//只有真正被某个三角面使用的纹理才会被收录到textureList，其它多余的不会被收录
	{
		//遍历所有三角形，每个三角形都去textureList中寻找自己的位置
		//如果找到就将此位置存到此三角形的textureIndex_InMeshTextureList中
		//如果找不到就将textureList新增一个元素，然后再将此三角形的textureIndex_InMeshTextueList中存入此位置
		int nIDtri=(int)IDtriList.size();
		for(int i=0;i<nIDtri;i++){
			CIDTriangle&IDtri=IDtriList[i];
			//找IDtri在textureList上的位置
			bool found=false;//是否找到
			int J=-1;//IDtri在textureList上的索引
			int nTexture=(int)textureList.size();
			for(int j=0;j<nTexture;j++){
				if(IDtri.texture==textureList[j]){
					found=true;
					J=j;
					break;
				}
			}//得到found
			if(found){//找到
				//将J保存到IDtri.textureIndex_inMeshTextureList
				IDtri.textureIndex_inMeshTextureList=J;
			}else{//没找到
				//textureList新增一个元素，用此元素作为IDtri的位置
				textureList.push_back(IDtri.texture);
				IDtri.textureIndex_inMeshTextureList=(int)textureList.size()-1;
			}
		}
	}
	
	void makeTexIDtriCountList(){
		int nTex=(int)textureList.size();
		for(int i=0;i<nTex;i++){
			GLuint texture=textureList[i];
			//统计纹理为texture的三角面共有多少个
			int count=0;
			int nIDtri=(int)IDtriList.size();
			for(int j=0;j<nIDtri;j++){
				if(IDtriList[j].texture==texture)count++;
			}//得到count
			//将count存入texIDtriCountList
			texIDtriCountList.push_back(count);
		}//得到texIDtriCountList
		
	}
	void clear(){
		vlist.clear();
		IDtriList.clear();
	}
	
	void calNorm_IDtriList(){//为IDtriList中各三角形计算法向量
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
	void setLastUV(float u,float v){//为当前最后一个顶点指定uv坐标
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
