#ifndef _c3dSkinActor__
#define _c3dSkinActor__
#include<vector>
using namespace std;
#include "c3dActor.h"
#if (C3D_TARGET_PLATFORM == C3D_PLATFORM_WIN32)
#include <direct.h>
#endif
static char tCharBuffer[1024]={0};
static void fskipOneStr(FILE * fp){
	fscanf(fp,"%s",tCharBuffer);
}
class Cc3dAniFrame
{
protected:
	Cc3dMatrix4 m_vertexTransformMat;
	float m_time;
public:
	Cc3dAniFrame(){
		m_time=0;
	}
	virtual ~Cc3dAniFrame(){
	
	}

	Cc3dAniFrame(const Cc3dMatrix4&vertexTransformMat,float time){
		m_vertexTransformMat=vertexTransformMat;
		m_time=time;
	}

	void setVertexTransformMat(const Cc3dMatrix4&vertexTransformMat){m_vertexTransformMat=vertexTransformMat;}
	Cc3dMatrix4 getVertexTransformMat()const{return m_vertexTransformMat;}
	void setTime(float time){m_time=time;}
	float getTime()const{return m_time;}
};
class Cc3dAniLayer:public Cc3dObject
{
protected:
	vector<Cc3dAniFrame>  m_aniFrameList;
public:
	void addAniFrame(const Cc3dAniFrame&aniFrame){
		m_aniFrameList.push_back(aniFrame);
	}
	const Cc3dAniFrame&getAniFrameByIndex(int index){
		assert(index>=0&&index<(int)m_aniFrameList.size());
		return m_aniFrameList[index];
	}
	int getAniFrameCount()const {return (int)m_aniFrameList.size();}
	Cc3dAniFrame getAniFrameByTime(float time){
		assert(m_aniFrameList.empty()==false);
		assert(time>=m_aniFrameList[0].getTime());
		assert(time<=m_aniFrameList[(int)m_aniFrameList.size()-1].getTime());
		Cc3dAniFrame aniFrameFoe;
		Cc3dAniFrame aniFrameNxt;
		int nAniFrame=(int)m_aniFrameList.size();
		for(int i=0;i<nAniFrame;i++){
			const Cc3dAniFrame&aniFrame=m_aniFrameList[i];
			if(aniFrame.getTime()==time){
				return aniFrame;
			}else if(aniFrame.getTime()>time){
				assert(i-1>=0);
				aniFrameFoe=m_aniFrameList[i-1];
				aniFrameNxt=m_aniFrameList[i];
				//calculate interpolated aniFrame
				float timeFoe=aniFrameFoe.getTime();
				const Cc3dMatrix4&vertexTransformMatFoe=aniFrameFoe.getVertexTransformMat();
				float timeNxt=aniFrameNxt.getTime();
				const Cc3dMatrix4&vertexTransformMatNxt=aniFrameNxt.getVertexTransformMat();
				float weightFoe=(timeNxt-time)/(timeNxt-timeFoe);
				float weightNxt=(time-timeFoe)/(timeNxt-timeFoe);
				Cc3dMatrix4 vertexTransformMat=vertexTransformMatFoe*weightFoe+vertexTransformMatNxt*weightNxt;
				Cc3dAniFrame aniFrame(vertexTransformMat,time);
				return aniFrame;
			}
		}
		assert(false);
	}
	void doExport(string filePath){
#if (C3D_TARGET_PLATFORM == C3D_PLATFORM_WIN32)
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		//create a directory
		if (isFolderExist||_mkdir(folderFullPath.c_str()) == 0){//success
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dAniLayer.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"w");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}
			//------------------write file
			int nAniFrame=(int)m_aniFrameList.size();
			fprintf(fp,"m_aniFrameList.size %i\n",nAniFrame);
			for(int i=0;i<nAniFrame;i++){
				const Cc3dAniFrame&aniFrame=m_aniFrameList[i];
				fprintf(fp,"aniFrame\n");
				float time=aniFrame.getTime();
				fprintf(fp,"  m_time %f\n",time);
				const float *m=aniFrame.getVertexTransformMat().getArray();
				fprintf(fp,"  m_vertexTransformMat %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
					m[0],m[1],m[2],m[3],
					m[4],m[5],m[6],m[7],
					m[8],m[9],m[10],m[11],
					m[12],m[13],m[14],m[15]);
			}
			//--------------------------close file
			fclose(fp);
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
#endif
	}
	void doImport(string filePath){
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		if (isFolderExist){
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dAniLayer.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"r");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}

			//------------------read file
		//	cout<<"hi"<<endl;
			assert(m_aniFrameList.empty());
			int t_nAniFrame;
			fskipOneStr(fp);
			fscanf(fp,"%i",&t_nAniFrame);
			assert(string(tCharBuffer)=="m_aniFrameList.size");
			for(int i=0;i<t_nAniFrame;i++){
		//		cout<<"i="<<i<<endl;
				fskipOneStr(fp);
				assert(string(tCharBuffer)=="aniFrame");
				float time;
				fskipOneStr(fp);
				assert(string(tCharBuffer)=="m_time");
				fscanf(fp,"%f",&time);
				float m[16];
				fskipOneStr(fp);
				assert(string(tCharBuffer)=="m_vertexTransformMat");
				for(int j=0;j<16;j++){
					fscanf(fp,"%f",&m[j]);
				}
				Cc3dMatrix4 vertexTransformMat(m);
				Cc3dAniFrame aniFrame(vertexTransformMat,time);
				m_aniFrameList.push_back(aniFrame);

			}
		//	cout<<"ha"<<endl;
			//--------------------------close file
			fclose(fp);
			
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}

	}

};
class Cc3dSkinCluster:public Cc3dObject
{
protected:
	vector<int> m_vertexIndexList;
	vector<float> m_vertexWeightList;
	vector<Cc3dAniLayer*>  m_aniLayerList;
public:
	Cc3dSkinCluster(){
	
	}
	virtual~Cc3dSkinCluster(){
		for(int i=0;i<(int)m_aniLayerList.size();i++){
			Cc3dAniLayer*aniLayer=m_aniLayerList[i];
			if(aniLayer)aniLayer->release();
		}
	}
	void doExport(string filePath){
#if (C3D_TARGET_PLATFORM == C3D_PLATFORM_WIN32)
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		//create a directory
		if (isFolderExist||_mkdir(folderFullPath.c_str()) == 0){//success
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dSkinCluster.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"w");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}
			//------------------write file
			int nVertexIndex=(int)m_vertexIndexList.size();
			fprintf(fp,"m_vertexIndexList.size %i\n",nVertexIndex);
			for(int i=0;i<nVertexIndex;i++){
				fprintf(fp,"%i ",m_vertexIndexList[i]);
			}fprintf(fp,"\n");
			int nVertexWeight=(int)m_vertexWeightList.size();
			fprintf(fp,"m_vertexWeightList.size %i\n",nVertexWeight);
			for(int i=0;i<nVertexWeight;i++){
				fprintf(fp,"%f ",m_vertexWeightList[i]);
			}fprintf(fp,"\n");
			fprintf(fp,"m_aniLayerList.size %i",(int)m_aniLayerList.size());
			//--------------------------close file
			fclose(fp);
			//------------------m_aniLayerList
			int nAniLayer=(int)m_aniLayerList.size();
			for(int i=0;i<nAniLayer;i++){
				string numStr=numberToStr(i);
				m_aniLayerList[i]->doExport(folderPath+"/m_aniLayer_"+numStr);	
			}
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
#endif
		
	}
	void doImport(string filePath){
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		if (isFolderExist){
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dSkinCluster.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"r");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}

			//------------------read file
			assert(m_vertexIndexList.empty());
			int t_nVertexIndex;
			fskipOneStr(fp);
			fscanf(fp,"%i",&t_nVertexIndex);
			assert(string(tCharBuffer)=="m_vertexIndexList.size");
			for(int i=0;i<t_nVertexIndex;i++){
				int vertexIndex;
				fscanf(fp,"%i",&vertexIndex);
				m_vertexIndexList.push_back(vertexIndex);
			}
			assert(m_vertexWeightList.empty());
			int t_nVertexWeight;
			fskipOneStr(fp);
			fscanf(fp,"%i",&t_nVertexWeight);
			assert(string(tCharBuffer)=="m_vertexWeightList.size");
			for(int i=0;i<t_nVertexWeight;i++){
				float vertexWeight;
				fscanf(fp,"%f ",&vertexWeight);
				m_vertexWeightList.push_back(vertexWeight);
			}
			int t_nAniLayer;
			fskipOneStr(fp);
			fscanf(fp,"%i",&t_nAniLayer);
			assert(string(tCharBuffer)=="m_aniLayerList.size");

			//--------------------------close file
			fclose(fp);
			//------------------m_aniLayerList
			assert(m_aniLayerList.empty());
			for(int i=0;i<t_nAniLayer;i++){
				string numStr=numberToStr(i);
				Cc3dAniLayer*p=new Cc3dAniLayer();
				p->autorelease();
				this->addAniLayer(p);
				p->doImport(folderPath+"/m_aniLayer_"+numStr);	
			}
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
	}
	void addAniLayer(Cc3dAniLayer*aniLayer){
		m_aniLayerList.push_back(aniLayer);
		aniLayer->retain();
	}
	Cc3dAniLayer* getAniLayerByIndex(int index){
		assert(index>=0&&index<(int)m_aniLayerList.size());
		return m_aniLayerList[index];
		
	}
	int getAniLayerCount()const{return (int)m_aniLayerList.size();}
	void setVertexIndexList(int*vertexIndexArray,int len){
		m_vertexIndexList.clear();
		for(int i=0;i<len;i++){
			m_vertexIndexList.push_back(vertexIndexArray[i]);
		}
	}
	void setVertexWeightList(double*vertexWeightArray,int len){
		m_vertexWeightList.clear();
		for(int i=0;i<len;i++){
			m_vertexWeightList.push_back(vertexWeightArray[i]);
		}
	}
	int getVertexIndexAt(int index){
		assert(index>=0&&index<(int)m_vertexIndexList.size());
		return m_vertexIndexList[index];
	}
	float getVertexWeightAt(int index){
		assert(index>=0&&index<(int)m_vertexWeightList.size());
		return m_vertexWeightList[index];
	}
	int getVertexIndexCount()const{return (int)m_vertexIndexList.size();}
	int getVertexWeightCount()const{
		assert((int)m_vertexWeightList.size()==(int)m_vertexIndexList.size());
		return (int)m_vertexWeightList.size();
	
	}


};
class Cc3dSkin:public Cc3dObject
{
protected:
	int m_skinType;
	vector<Cc3dSkinCluster*> m_clusterList;
public:
	Cc3dSkin(){
		m_skinType=0;
	}
	virtual ~Cc3dSkin(){
		for(int i=0;i<(int)m_clusterList.size();i++){
			m_clusterList[i]->release();
		}
	}
	void doExport(string filePath){
#if (C3D_TARGET_PLATFORM == C3D_PLATFORM_WIN32)
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		//create a directory
		if (isFolderExist||_mkdir(folderFullPath.c_str()) == 0){//success
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dSkin.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"w");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}
			//------------------write file
			fprintf(fp,"m_skinType %i\n",m_skinType);
			fprintf(fp,"m_clusterList.size %i",(int)m_clusterList.size());
			//--------------------------close file
			fclose(fp);
			//------------------m_clusterList
			int nCluster=(int)m_clusterList.size();
			for(int i=0;i<nCluster;i++){
				string numStr=numberToStr(i);
				m_clusterList[i]->doExport(folderPath+"/m_skinCluster_"+numStr);	
			}
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
#endif
	}
	void doImport(string filePath){
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		if (isFolderExist){
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dSkin.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"r");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}

			//------------------read file

			fskipOneStr(fp);
			fscanf(fp,"%i",&m_skinType);
			assert(string(tCharBuffer)=="m_skinType");

			fskipOneStr(fp);
			int t_nCluster;
			fscanf(fp,"%i",&t_nCluster);
			assert(string(tCharBuffer)=="m_clusterList.size");

			//--------------------------close file
			fclose(fp);
			//------------------m_clusterList
			assert(m_clusterList.empty());
			for(int i=0;i<t_nCluster;i++){
				string numStr=numberToStr(i);
				Cc3dSkinCluster* cluster=new Cc3dSkinCluster();
				cluster->autorelease();
				addCluster(cluster);
				cluster->doImport(folderPath+"/m_skinCluster_"+numStr);	
			}
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
	}
	void setSkinType(int skinType){m_skinType=skinType;} 
	int getSkinType()const{return m_skinType;}
	void addCluster(Cc3dSkinCluster*cluster){
		m_clusterList.push_back(cluster);
		cluster->retain();
	}
	Cc3dSkinCluster* getClusterByIndex(int index){
		assert(index>=0&&index<(int)m_clusterList.size());
		return m_clusterList[index];
	}
	int getClusterCount(){
		return (int)m_clusterList.size();
	}

};
class _CmeshIDvID{
protected:
	int m_meshID;
	int m_vID;
public:
	_CmeshIDvID(){
		initMembers();
	}
	_CmeshIDvID(int meshID,int vID){
		init(meshID,vID);
	}
	virtual ~_CmeshIDvID(){
		
	}

	int getMeshID()const{return m_meshID;}
	int getvID()const{return m_vID;}
	void init(int meshID,int vID){
		m_meshID=meshID;
		m_vID=vID;
	}
protected:
	void initMembers(){
		m_meshID=-1;
		m_vID=-1;
	}

};
class Cc3dSkinSubMeshData:public Cc3dSubMeshData
{
public:
	void doExport(string filePath){
#if (C3D_TARGET_PLATFORM == C3D_PLATFORM_WIN32)
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		//create a directory
		if (isFolderExist||_mkdir(folderFullPath.c_str()) == 0){//success
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dSkinSubMeshData.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"w");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}
			//------------------write file	
			int nv=(int)vlist.size();
			fprintf(fp,"m_vlist.size %i\n",nv);
			for(int i=0;i<nv;i++){
				const Cc3dVertex&vertex=vlist[i];
				fprintf(fp,"vertex\n",i);
				const Cc3dVector4&pos=vertex.getPos();
				const Cc3dVector2&texCoord=vertex.getTexCoord();
				const Cc3dVector4&norm=vertex.getNorm();
				const Cc3dVector4&color=vertex.getColor();
				fprintf(fp,"  pos %f %f %f\n",pos.x(),pos.y(),pos.z());
				fprintf(fp,"  texCoord %f %f\n",texCoord.x(),texCoord.y());
				fprintf(fp,"  norm %f %f %f\n",norm.x(),norm.y(),norm.z());
				fprintf(fp,"  color %f %f %f %f\n",color.x(),color.y(),color.z(),color.w());
			}
			int nIDtri=(int)IDtriList.size();
			fprintf(fp,"m_IDtriList.size %i\n",nIDtri);
			for(int i=0;i<nIDtri;i++){
				const Cc3dIDTriangle&IDtri=IDtriList[i];
				fprintf(fp,"IDtri %i %i %i\n",IDtri.vID[0],IDtri.vID[1],IDtri.vID[2]);
			}

			//--------------------------close file
			fclose(fp);
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
		}
#endif
	}
	void doImport(string filePath){
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		if (isFolderExist){
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dSkinSubMeshData.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"r");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}

			//------------------read file
			//vlist
			assert(vlist.empty());
			int t_nv;
			fskipOneStr(fp);
			assert(string(tCharBuffer)=="m_vlist.size");
			fscanf(fp,"%i",&t_nv);
			for(int i=0;i<t_nv;i++){
				fskipOneStr(fp);
				assert(string(tCharBuffer)=="vertex");
				Cc3dVector4 pos;
				Cc3dVector2 texCoord;
				Cc3dVector4 norm;
				Cc3dVector4 color;
				float posx,posy,posz;
				float s,t;
				float normx,normy,normz;
				float r,g,b,a;
				fskipOneStr(fp);
				fscanf(fp,"%f",&posx);
				fscanf(fp,"%f",&posy);
				fscanf(fp,"%f",&posz);
				fskipOneStr(fp);
				fscanf(fp,"%f",&s);
				fscanf(fp,"%f",&t);
				fskipOneStr(fp);
				fscanf(fp,"%f",&normx);
				fscanf(fp,"%f",&normy);
				fscanf(fp,"%f",&normz);
				fskipOneStr(fp);
				fscanf(fp,"%f",&r);
				fscanf(fp,"%f",&g);
				fscanf(fp,"%f",&b);
				fscanf(fp,"%f",&a);
				pos.init(posx,posy,posz,1);
				texCoord.init(s,t);
				norm.init(normx,normy,normz,0);
				color.init(r,g,b,a);
				Cc3dVertex vertex(pos,texCoord,norm,color);
				vlist.push_back(vertex);
			}
			assert(IDtriList.empty());
			int t_nIDtri;
			fskipOneStr(fp);
			assert(string(tCharBuffer)=="m_IDtriList.size");
			fscanf(fp,"%i",&t_nIDtri);
			for(int i=0;i<t_nIDtri;i++){
				fskipOneStr(fp);
				assert(string(tCharBuffer)=="IDtri");
				int vID0,vID1,vID2;
				fscanf(fp,"%i",&vID0);
				fscanf(fp,"%i",&vID1);
				fscanf(fp,"%i",&vID2);
				Cc3dIDTriangle IDtri(vID0,vID1,vID2);
				IDtriList.push_back(IDtri);

			}

			//--------------------------close file
			fclose(fp);
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
	}
};
class Cc3dSkinSubMesh:public Cc3dSubMesh
{
protected:
	Cc3dSkinSubMeshData*m_subMeshData_backup;
public:
	Cc3dSkinSubMesh(){
		m_subMeshData_backup=NULL;
	}
	virtual ~Cc3dSkinSubMesh(){
		if(m_subMeshData_backup)m_subMeshData_backup->release();
	}
	void doExport(string filePath){
#if (C3D_TARGET_PLATFORM == C3D_PLATFORM_WIN32)
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		//create a directory
		if (isFolderExist||_mkdir(folderFullPath.c_str()) == 0){//success
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dSkinSubMesh.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"w");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}
			//------------------write file
			string texFilePath=this->getTexture()->getFilePath();
			fprintf(fp,"texFilePath %s\n",texFilePath.c_str());
			//--------------------------close file
			fclose(fp);
			//-----------------m_subMeshData_backup
			m_subMeshData_backup->doExport(folderPath+"/m_subMeshData_backup");
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
#endif
	}
	void doImport(string filePath){
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		if (isFolderExist){
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dSkinSubMesh.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"r");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}

			//------------------read file
			fskipOneStr(fp);
			assert(string(tCharBuffer)=="texFilePath");
			char t_texFilePath[1024];
			fscanf(fp,"%s",t_texFilePath);
			string texFilePath=string(t_texFilePath);
			Cc3dTexture*texture=Cc3dTextureCache::sharedTextureCache()->addImage(texFilePath.c_str());
			this->setTexture(texture);
			//--------------------------close file
			fclose(fp);
			//------------------m_subMeshData_backup
			assert(m_subMeshData_backup==NULL);
			m_subMeshData_backup=new Cc3dSkinSubMeshData();
			m_subMeshData_backup->autorelease();
			m_subMeshData_backup->retain();
			m_subMeshData_backup->doImport(folderPath+"/m_subMeshData_backup");
			//------------------m_subMeshData
			Cc3dSkinSubMeshData* subMeshData=new Cc3dSkinSubMeshData();
			subMeshData->autorelease();
			this->setMeshData(subMeshData);
			*subMeshData=*m_subMeshData_backup;
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
	}
	void backupSubMeshData(){//call after m_subMeshData has established
		m_subMeshData_backup=new Cc3dSkinSubMeshData();
		m_subMeshData_backup->autorelease();
		m_subMeshData_backup->retain();
		//copy m_subMeshData
		*m_subMeshData_backup=*(Cc3dSkinSubMeshData*)m_subMeshData;
	}
	Cc3dVertex getBackupVertexByIndex(int index){
		return m_subMeshData_backup->getVertexByIndex(index); 
	}

};

class Cc3dSkinMesh:public Cc3dMesh
{
protected:
	void* m_fbxMeshPtr;//this pointer only used for loading fbx data from fbx
	Cc3dSkin*m_skin;
	vector<vector<_CmeshIDvID> > m_vertexDupList;//m_vertexDupList[meshVID] is duplicated to {(meshID,vID),(meshID,vID),...}
public:
	Cc3dSkinMesh(){
		m_fbxMeshPtr=NULL;
		m_skin=NULL;
	}
	virtual ~Cc3dSkinMesh(){
		if(m_skin)m_skin->release();
	}
	void doExport(string filePath){
#if (C3D_TARGET_PLATFORM == C3D_PLATFORM_WIN32)
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		//create a directory
		if (isFolderExist||_mkdir(folderFullPath.c_str()) == 0){//success
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dSkinMesh.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"w");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}
			//------------------write file
			fprintf(fp,"m_skinSubMesh.size %i\n",this->getSubMeshCount());
			fprintf(fp,"m_vertexDupList.size %i\n",(int)m_vertexDupList.size());
			int nVertexDup=(int)m_vertexDupList.size();
			for(int i=0;i<nVertexDup;i++){
				int nMeshIDvID=(int)m_vertexDupList[i].size();
				fprintf(fp,"nMeshIDvID %i\n",nMeshIDvID);
				for(int j=0;j<nMeshIDvID;j++){
					const _CmeshIDvID&meshIDvID=m_vertexDupList[i][j];
					fprintf(fp,"  meshIDvID %i %i\n",meshIDvID.getMeshID(),meshIDvID.getvID());
				}
			}
			//RTmat and Scale
			Cc3dMatrix4 RTmat=this->getTransform().getRTmat();
			const float *m=RTmat.getArray();
			fprintf(fp,"RTmat %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
						m[0],m[1],m[2],m[3],
						m[4],m[5],m[6],m[7],
						m[8],m[9],m[10],m[11],
						m[12],m[13],m[14],m[15]);
			float scaleX,scaleY,scaleZ;
			scaleX=this->getTransform().getScaleX();
			scaleY=this->getTransform().getScaleY();
			scaleZ=this->getTransform().getScaleZ();
			fprintf(fp,"scale %f %f %f",scaleX,scaleY,scaleZ);
			//--------------------------close file
			fclose(fp);
			//------------------m_skin
			m_skin->doExport(folderPath+"/m_skin");
			//------------------skinSubMeshes
			int nSkinSubMesh=this->getSubMeshCount();
			for(int i=0;i<nSkinSubMesh;i++){
				Cc3dSkinSubMesh*skinSubMesh=(Cc3dSkinSubMesh*)this->getSubMeshByIndex(i);
				string numStr=numberToStr(i);
				skinSubMesh->doExport(folderPath+"/m_skinSubMesh_"+numStr);
			}
			
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
#endif
	}
	void doImport(string filePath){
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		if (isFolderExist){
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dSkinMesh.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"r");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}
			//------------------read file

			fskipOneStr(fp);
			int t_nSkinSubMesh;
			fscanf(fp,"%i",&t_nSkinSubMesh);
			assert(string(tCharBuffer)=="m_skinSubMesh.size");

			fskipOneStr(fp);
			int t_nVertexDup;
			fscanf(fp,"%i",&t_nVertexDup);
			assert(string(tCharBuffer)=="m_vertexDupList.size");
			//m_vertexDupList
			assert(m_vertexDupList.empty());
			for(int i=0;i<t_nVertexDup;i++){
				vector<_CmeshIDvID> meshIDvIDList;
				int t_nMeshIDvID;
				fskipOneStr(fp);
				fscanf(fp,"%i",&t_nMeshIDvID);
				assert(string(tCharBuffer)=="nMeshIDvID");
				for(int j=0;j<t_nMeshIDvID;j++){
					_CmeshIDvID meshIDvID;
					int meshID,vID;
					fskipOneStr(fp);
					fscanf(fp,"%i",&meshID);
					fscanf(fp,"%i",&vID);
					assert(string(tCharBuffer)=="meshIDvID");
					meshIDvID.init(meshID,vID);
					meshIDvIDList.push_back(meshIDvID);
				}
				m_vertexDupList.push_back(meshIDvIDList);
			}
			//RTmat and Scale
			float m[16];
			fskipOneStr(fp);
			assert(string(tCharBuffer)=="RTmat");
			for(int j=0;j<16;j++){
				fscanf(fp,"%f",&m[j]);
			}
			Cc3dMatrix4 RTmat(m);
			float scaleX,scaleY,scaleZ;
			fskipOneStr(fp);
			assert(string(tCharBuffer)=="scale");
			fscanf(fp,"%f",&scaleX);
			fscanf(fp,"%f",&scaleY);
			fscanf(fp,"%f",&scaleZ);
			Cc3dTransform transform;
			transform.init(RTmat,scaleX,scaleY,scaleZ);
			this->setTransform(transform);
			//--------------------------close file
			fclose(fp);
			//------------------m_skin
			Cc3dSkin*skin=new Cc3dSkin();
			skin->autorelease();
			setSkin(skin);
			skin->doImport(folderPath+"/m_skin");
			//------------------skinSubMeshes
			assert(this->getSubMeshCount()==0);
			for(int i=0;i<t_nSkinSubMesh;i++){
				string numStr=numberToStr(i);
				Cc3dSkinSubMesh*p=new Cc3dSkinSubMesh();
				p->autorelease();
				p->init();
				this->addSubMesh(p);
				p->doImport(folderPath+"/m_skinSubMesh_"+numStr);
			}
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
	}
	void setFbxMeshPtr(void*fbxMeshPtr){m_fbxMeshPtr=fbxMeshPtr;}
	void* getFbxMeshPtr(){return m_fbxMeshPtr;}

	void deform(int aniLayerIndex,float time){
		int meshVertexCount = (int)m_vertexDupList.size();

		vector<Cc3dMatrix4> deformationList;//deformation of each vertex
		deformationList.resize(meshVertexCount);
		for(int i=0;i<(int)deformationList.size();i++)deformationList[i]=zeroMat();
		vector<float> weightList;//weight of each vertex
		weightList.resize(meshVertexCount);
		for(int i=0;i<(int)weightList.size();i++)weightList[i]=0;

		// For all skins and all clusters, accumulate their deformation and weight
		// on each vertices and store them in deformationList and weightList.
		if(m_skin){
			int clusterCount = m_skin->getClusterCount();
			for ( int clusterIndex=0; clusterIndex<clusterCount; ++clusterIndex)
			{
				Cc3dSkinCluster*cluster=m_skin->getClusterByIndex(clusterIndex);

				int aniLayerCount=cluster->getAniLayerCount();
				assert(aniLayerIndex<aniLayerCount);
				Cc3dAniLayer*aniLayer=cluster->getAniLayerByIndex(aniLayerIndex);
				int aniFrameCount=aniLayer->getAniFrameCount();
				const Cc3dAniFrame&aniFrame=aniLayer->getAniFrameByTime(time);
				Cc3dMatrix4 vertexTransformMat=aniFrame.getVertexTransformMat();
				float time=aniFrame.getTime();
				int clusterVertexIndexCount=cluster->getVertexIndexCount();

				for (int k = 0; k < clusterVertexIndexCount; ++k) 
				{             
					int meshVID = cluster->getVertexIndexAt(k);

					// Sometimes, the mesh can have less points than at the time of the skinning
					// because a smooth operator was active when skinning but has been deactivated during export.
					if (meshVID >= meshVertexCount)
						continue;

					float weight = cluster->getVertexWeightAt(k);

					if (weight == 0.0)continue;

					// Compute the influence of the link on the vertex.
					Cc3dMatrix4 influenceMat = vertexTransformMat*weight;
					{
						// Add to the sum of the deformations on the vertex.
						deformationList[meshVID]=deformationList[meshVID]+influenceMat;

						// Add to the sum of weights to either normalize or complete the vertex.
						weightList[meshVID]+=weight;
					}
				}

			}	
			//Actually deform each vertices here by information stored in deformationList and weightList
			for (int i = 0; i < meshVertexCount; i++) 
			{
				const int meshVID=i;
				vector<_CmeshIDvID> vertexDup=m_vertexDupList[meshVID];
				int nDup=(int)vertexDup.size();
				if(nDup==0)continue;
				//deform vertexes in vertexDup
				for(int j=0;j<nDup;j++){
					int meshID = vertexDup[j].getMeshID();
					int vID = vertexDup[j].getvID();
					Cc3dVertex newVertex=((Cc3dSkinSubMesh*)this->getSubMeshByIndex(meshID))->getBackupVertexByIndex(vID);//deform result
					// Deform vertex
					if (weightList[meshVID] != 0.0) 
					{
						//deform pos
						if(j==0){
							newVertex.setPos(deformationList[meshVID]*newVertex.getPos());
						}else{
							//same as vertexDup[0]
							int meshID0=vertexDup[0].getMeshID();
							int vID0=vertexDup[0].getvID();
							newVertex.setPos(this->getSubMeshByIndex(meshID0)->getVertexByIndex(vID0).getPos());
						}
						//deform norm
						newVertex.setNorm(deformationList[meshVID]*newVertex.getNorm());

					}
					// replace vertexDup[j] with newVertex
					this->getSubMeshByIndex(meshID)->setVertexByIndex(vID,newVertex);
				}

			}
		}
	}
	void setSkin(Cc3dSkin*skin){
		if(m_skin==NULL){
			m_skin=skin;
			m_skin->retain();
		}else{
			m_skin->release();
			m_skin=skin;
			m_skin->retain();
		}
	}
	Cc3dSkin*getSkin(){return m_skin;}
	void setVertexDupList(const vector<vector<_CmeshIDvID> >&vertexDupList){
		m_vertexDupList=vertexDupList;
	}
	vector<_CmeshIDvID> getVertexDupByIndex(int index){
		assert(index>=0&&index<(int)m_vertexDupList.size());
		return m_vertexDupList[index];
	}
	
};
class Cc3dAniLayerInfo:public Cc3dObject
{
protected:
	//all time is second
	float m_interval;
	float m_startTime;
	float m_endTime;
	float m_curTime;
public:
	Cc3dAniLayerInfo(){
		m_interval=0;
		m_startTime=0;
		m_endTime=0;
		m_curTime=0;
	}
	void doExport(string filePath){
#if (C3D_TARGET_PLATFORM == C3D_PLATFORM_WIN32)
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		//create a directory
		if (isFolderExist||_mkdir(folderFullPath.c_str()) == 0){//success
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dAniLayerInfo.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"w");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}
			//------------------write file
			{
				fprintf(fp,"m_interval %f\n",m_interval);
				fprintf(fp,"m_startTime %f\n",m_startTime);
				fprintf(fp,"m_endTime %f\n",m_endTime);
				fprintf(fp,"m_curTime %f\n",m_curTime);
			}
			//--------------------------close file
			fclose(fp);
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
#endif
	}
	void doImport(string filePath){
        
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		if (isFolderExist){
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dAniLayerInfo.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"r");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}

			//------------------read file

			fskipOneStr(fp);
			fscanf(fp,"%f",&m_interval);
			assert(string(tCharBuffer)=="m_interval");

			fskipOneStr(fp);
			fscanf(fp,"%f",&m_startTime);
			assert(string(tCharBuffer)=="m_startTime");

			fskipOneStr(fp);
			fscanf(fp,"%f",&m_endTime);
			assert(string(tCharBuffer)=="m_endTime");

			fskipOneStr(fp);
			fscanf(fp,"%f",&m_curTime);
			assert(string(tCharBuffer)=="m_curTime");

			//--------------------------close file
			fclose(fp);
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
	  
	}
	void setInterval(float interval){m_interval=interval;}
	void setStartTime(float startTime){m_startTime=startTime;}
	void setEndTime(float endTime){m_endTime=endTime;}
	void setCurTime(float curTime){m_curTime=curTime;}
	float getInterval()const{return m_interval;}
	float getStartTime()const{return m_startTime;}
	float getEndTime()const{return m_endTime;}
	float getCurTime()const{return m_curTime;}
	void progress(float dt){
		if((m_endTime>m_startTime)==false)return;
		m_curTime+=dt;
		if(m_curTime>m_endTime)m_curTime-=(m_endTime-m_startTime);//wrap
	}


};
class Cc3dSkinActor:public Cc3dActor
{
protected:
	int m_aniLayerIndex;
	float m_interval;
	vector<Cc3dAniLayerInfo*> m_aniLayerInfoList;
public:
	Cc3dSkinActor(){
		m_interval=1.0/60;
		m_aniLayerIndex=0;
	}
	virtual ~Cc3dSkinActor(){
		for(int i=0;i<(int)m_aniLayerInfoList.size();i++){
			Cc3dAniLayerInfo*aniLayerInfo=m_aniLayerInfoList[i];
			if(aniLayerInfo)aniLayerInfo->release();
		}
	}
	void doExport(string filePath){
#if (C3D_TARGET_PLATFORM == C3D_PLATFORM_WIN32)
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		//create a directory
		if (isFolderExist||_mkdir(folderFullPath.c_str()) == 0){//success
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dSkinActor.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"w");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}
			//------------------write file
			{
				fprintf(fp,"m_aniLayerIndex %i\n",m_aniLayerIndex);
				fprintf(fp,"m_interval %f\n",m_interval);
				fprintf(fp,"m_aniLayerInfoList.size %i\n",(int)m_aniLayerInfoList.size());
				fprintf(fp,"m_skinMeshList.size %i\n",(int)this->getMeshCount());
			}
			//--------------------------close file
			fclose(fp);
			//------------------m_aniLayerInfoList
			int nAniLayerInfo=(int)m_aniLayerInfoList.size();
			for(int i=0;i<nAniLayerInfo;i++){
				string numStr=numberToStr(i);
				m_aniLayerInfoList[i]->doExport(folderPath+"/m_aniLayerInfo_"+numStr);
			}
			//------------------skinMeshes
			int meshCount=this->getMeshCount();
			for(int i=0;i<meshCount;i++){
				string numStr=numberToStr(i);
				Cc3dSkinMesh*mesh=(Cc3dSkinMesh*)this->getMeshByIndex(i);
				mesh->doExport(folderPath+"/m_skinMesh_"+numStr);
			}
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
#endif
	}
	void doImport(string filePath){
		//--------------use filePath as folder path
		const string folderPath=filePath;
		//-----------------------------------------
		bool isFolderExist=Cc3dFileUtils::sharedFileUtils()->getIsFileOrClipExist(folderPath);
		string folderFullPath=Cc3dFileUtils::sharedFileUtils()->getFullPath(folderPath);
		if (isFolderExist){
			//------------------full path of file
			string fileFullPath=folderFullPath+"/Cc3dSkinActor.txt";
			//open file
			FILE  *fp=NULL;
			fp=fopen(fileFullPath.c_str(),"r");//override write
			if(fp==NULL){
				cout<<"Open "<<fileFullPath<<" failed!"<<endl;
				assert(false);
			}

			//------------------read file
		
			fskipOneStr(fp);
			fscanf(fp,"%i",&m_aniLayerIndex);

			fskipOneStr(fp);
			fscanf(fp,"%f",&m_interval);

			fskipOneStr(fp);
			int t_nAniLayerInfo;
			fscanf(fp,"%i",&t_nAniLayerInfo);

			fskipOneStr(fp);
			int t_nSkinMesh;
			fscanf(fp,"%i",&t_nSkinMesh);

			//--------------------------close file
			fclose(fp);
			//------------------m_aniLayerInfoList
			assert(m_aniLayerInfoList.empty());
			for(int i=0;i<t_nAniLayerInfo;i++){
				string numStr=numberToStr(i);
				Cc3dAniLayerInfo*p=new Cc3dAniLayerInfo();
				p->autorelease();
				this->addAniLayerInfo(p);
				p->doImport(folderPath+"/m_aniLayerInfo_"+numStr);
			}
			//------------------skinMeshes
			assert(this->getMeshCount()==0);
			for(int i=0;i<t_nSkinMesh;i++){
				string numStr=numberToStr(i);
				Cc3dSkinMesh*p=new Cc3dSkinMesh();
				p->autorelease();
				p->init();
				this->addMesh(p);
				p->doImport(folderPath+"/m_skinMesh_"+numStr);
			}
		}else{
			cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
            assert(false);
		}
	  
	}
	void addAniLayerInfo(Cc3dAniLayerInfo*aniLayerInfo){
		m_aniLayerInfoList.push_back(aniLayerInfo);
		aniLayerInfo->retain();
	}
	Cc3dAniLayerInfo*getAniLayerInfoByIndex(int index){
		assert(index>=0&&index<(int)m_aniLayerInfoList.size());
		return m_aniLayerInfoList[index];
	}
	void update(float dt){
	//	cout<<"dt:"<<dt<<endl;
		if((int)m_aniLayerInfoList.size()==0)return;
		//update current aniLayerInfo
		Cc3dAniLayerInfo*curAniLayerInfo=m_aniLayerInfoList[m_aniLayerIndex];
		curAniLayerInfo->progress(dt);
		//calculate animation frame index
		float time = curAniLayerInfo->getCurTime();
		//deform
		deform(m_aniLayerIndex,time);
		this->submitVertex(GL_DYNAMIC_DRAW);//only need to submitVertex (actually only pos and norm)

	}
	void setAniLayerIndex(int aniLayerIndex){m_aniLayerIndex=aniLayerIndex;}
	int getAniLayerIndex()const{return m_aniLayerIndex;}
	void setInterval(float interval){m_interval=interval;}
	float getInterval()const{return m_interval;}
	Cc3dSkinMesh* findSkinMeshByFbxMeshPtr(void*fbxMeshPtr){
		int meshCount=this->getMeshCount();
		for(int i=0;i<meshCount;i++){
			Cc3dSkinMesh*mesh=(Cc3dSkinMesh*)this->getMeshByIndex(i);
			if(mesh->getFbxMeshPtr()==fbxMeshPtr){
				return mesh;
			}
		}
		return NULL;
	
	}
	void deform(int aniLayerIndex,float time){
		int nMeshCount=this->getMeshCount();
		for(int i=0;i<nMeshCount;i++){
			((Cc3dSkinMesh*)this->getMeshByIndex(i))->deform(aniLayerIndex,time);
		}
	}

};
#endif