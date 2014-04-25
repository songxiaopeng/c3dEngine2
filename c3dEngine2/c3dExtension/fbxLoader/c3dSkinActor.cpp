#include "c3dSkinActor.h"

void Cc3dAniLayer::doExport(string filePath,bool valueOnly){
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
		fprintKey(fp,valueOnly,"m_aniFrameList.size");fprintf(fp," %i\n",nAniFrame);
		for(int i=0;i<nAniFrame;i++){
			const Cc3dAniFrame&aniFrame=m_aniFrameList[i];
			fprintKey(fp,valueOnly,"aniFrame\n");
			float time=aniFrame.getTime();
			fprintKey(fp,valueOnly,"  m_time");fprintf(fp," %f\n",time);
			const float *m=aniFrame.getVertexTransformMat().getArray();
			fprintKey(fp,valueOnly,"  m_vertexTransformMat");fprintf(fp," %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
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
void Cc3dAniLayer::doImport(string filePath,bool valueOnly){
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
		fskipOneStr(fp,valueOnly);
		fscanf(fp,"%i",&t_nAniFrame);
		if(!valueOnly)assert(string(tCharBuffer)=="m_aniFrameList.size");
		for(int i=0;i<t_nAniFrame;i++){
			//		cout<<"i="<<i<<endl;
			fskipOneStr(fp,valueOnly);
			if(!valueOnly)assert(string(tCharBuffer)=="aniFrame");
			float time;
			fskipOneStr(fp,valueOnly);
			if(!valueOnly)assert(string(tCharBuffer)=="m_time");
			fscanf(fp,"%f",&time);
			float m[16];
			fskipOneStr(fp,valueOnly);
			if(!valueOnly)assert(string(tCharBuffer)=="m_vertexTransformMat");
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
void Cc3dSkinCluster::doExport(string filePath,bool valueOnly){
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
		fprintKey(fp,valueOnly,"m_vertexIndexList.size");fprintf(fp," %i\n",nVertexIndex);
		for(int i=0;i<nVertexIndex;i++){
			fprintf(fp,"%i ",m_vertexIndexList[i]);
		}fprintf(fp,"\n");
		int nVertexWeight=(int)m_vertexWeightList.size();
		fprintKey(fp,valueOnly,"m_vertexWeightList.size");fprintf(fp," %i\n",nVertexWeight);
		for(int i=0;i<nVertexWeight;i++){
			fprintf(fp,"%f ",m_vertexWeightList[i]);
		}fprintf(fp,"\n");
		fprintKey(fp,valueOnly,"m_aniLayerList.size");fprintf(fp," %i",(int)m_aniLayerList.size());
		//--------------------------close file
		fclose(fp);
		//------------------m_aniLayerList
		int nAniLayer=(int)m_aniLayerList.size();
		for(int i=0;i<nAniLayer;i++){
			string numStr=numberToStr(i);
			m_aniLayerList[i]->doExport(folderPath+"/m_aniLayer_"+numStr,valueOnly);	
		}
	}else{
		cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
		assert(false);
	}
#endif

}
void Cc3dSkinCluster::doImport(string filePath,bool valueOnly){
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
		fskipOneStr(fp,valueOnly);
		fscanf(fp,"%i",&t_nVertexIndex);
		if(!valueOnly)assert(string(tCharBuffer)=="m_vertexIndexList.size");
		for(int i=0;i<t_nVertexIndex;i++){
			int vertexIndex;
			fscanf(fp,"%i",&vertexIndex);
			m_vertexIndexList.push_back(vertexIndex);
		}
		assert(m_vertexWeightList.empty());
		int t_nVertexWeight;
		fskipOneStr(fp,valueOnly);
		fscanf(fp,"%i",&t_nVertexWeight);
		if(!valueOnly)assert(string(tCharBuffer)=="m_vertexWeightList.size");
		for(int i=0;i<t_nVertexWeight;i++){
			float vertexWeight;
			fscanf(fp,"%f ",&vertexWeight);
			m_vertexWeightList.push_back(vertexWeight);
		}
		int t_nAniLayer;
		fskipOneStr(fp,valueOnly);
		fscanf(fp,"%i",&t_nAniLayer);
		if(!valueOnly)assert(string(tCharBuffer)=="m_aniLayerList.size");

		//--------------------------close file
		fclose(fp);
		//------------------m_aniLayerList
		assert(m_aniLayerList.empty());
		for(int i=0;i<t_nAniLayer;i++){
			string numStr=numberToStr(i);
			Cc3dAniLayer*p=new Cc3dAniLayer();
			p->autorelease();
			this->addAniLayer(p);
			p->doImport(folderPath+"/m_aniLayer_"+numStr,valueOnly);	
		}
	}else{
		cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
		assert(false);
	}
}

void Cc3dSkin::doExport(string filePath,bool valueOnly){
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
		fprintKey(fp,valueOnly,"m_skinType");fprintf(fp," %i\n",m_skinType);
		fprintKey(fp,valueOnly,"m_clusterList.size");fprintf(fp," %i",(int)m_clusterList.size());
		//--------------------------close file
		fclose(fp);
		//------------------m_clusterList
		int nCluster=(int)m_clusterList.size();
		for(int i=0;i<nCluster;i++){
			string numStr=numberToStr(i);
			m_clusterList[i]->doExport(folderPath+"/m_skinCluster_"+numStr,valueOnly);	
		}
	}else{
		cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
		assert(false);
	}
#endif
}
void Cc3dSkin::doImport(string filePath,bool valueOnly){
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

		fskipOneStr(fp,valueOnly);
		fscanf(fp,"%i",&m_skinType);
		if(!valueOnly)assert(string(tCharBuffer)=="m_skinType");

		fskipOneStr(fp,valueOnly);
		int t_nCluster;
		fscanf(fp,"%i",&t_nCluster);
		if(!valueOnly)assert(string(tCharBuffer)=="m_clusterList.size");

		//--------------------------close file
		fclose(fp);
		//------------------m_clusterList
		assert(m_clusterList.empty());
		for(int i=0;i<t_nCluster;i++){
			string numStr=numberToStr(i);
			Cc3dSkinCluster* cluster=new Cc3dSkinCluster();
			cluster->autorelease();
			addCluster(cluster);
			cluster->doImport(folderPath+"/m_skinCluster_"+numStr,valueOnly);	
		}
	}else{
		cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
		assert(false);
	}
}
void Cc3dSkinSubMeshData::doExport(string filePath,bool valueOnly){
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
		fprintKey(fp,valueOnly,"m_vlist.size");fprintf(fp," %i\n",nv);
		for(int i=0;i<nv;i++){
			const Cc3dVertex&vertex=vlist[i];
			fprintKey(fp,valueOnly,"vertex\n");
			const Cc3dVector4&pos=vertex.getPos();
			const Cc3dVector2&texCoord=vertex.getTexCoord();
			const Cc3dVector4&norm=vertex.getNorm();
			const Cc3dVector4&color=vertex.getColor();
			fprintKey(fp,valueOnly,"  pos");fprintf(fp," %f %f %f\n",pos.x(),pos.y(),pos.z());
			fprintKey(fp,valueOnly,"  texCoord");fprintf(fp," %f %f\n",texCoord.x(),texCoord.y());
			fprintKey(fp,valueOnly,"  norm");fprintf(fp," %f %f %f\n",norm.x(),norm.y(),norm.z());
			fprintKey(fp,valueOnly,"  color");fprintf(fp," %f %f %f %f\n",color.x(),color.y(),color.z(),color.w());
		}
		int nIDtri=(int)IDtriList.size();
		fprintKey(fp,valueOnly,"m_IDtriList.size");fprintf(fp," %i\n",nIDtri);
		for(int i=0;i<nIDtri;i++){
			const Cc3dIDTriangle&IDtri=IDtriList[i];
			fprintKey(fp,valueOnly,"IDtri");fprintf(fp," %i %i %i\n",IDtri.vID[0],IDtri.vID[1],IDtri.vID[2]);
		}

		//--------------------------close file
		fclose(fp);
	}else{
		cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
	}
#endif
}
void Cc3dSkinSubMeshData::doImport(string filePath,bool valueOnly){
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
		fskipOneStr(fp,valueOnly);
		if(!valueOnly)assert(string(tCharBuffer)=="m_vlist.size");
		fscanf(fp,"%i",&t_nv);
		for(int i=0;i<t_nv;i++){
			fskipOneStr(fp,valueOnly);
			if(!valueOnly)assert(string(tCharBuffer)=="vertex");
			Cc3dVector4 pos;
			Cc3dVector2 texCoord;
			Cc3dVector4 norm;
			Cc3dVector4 color;
			float posx,posy,posz;
			float s,t;
			float normx,normy,normz;
			float r,g,b,a;
			fskipOneStr(fp,valueOnly);
			fscanf(fp,"%f",&posx);
			fscanf(fp,"%f",&posy);
			fscanf(fp,"%f",&posz);
			fskipOneStr(fp,valueOnly);
			fscanf(fp,"%f",&s);
			fscanf(fp,"%f",&t);
			fskipOneStr(fp,valueOnly);
			fscanf(fp,"%f",&normx);
			fscanf(fp,"%f",&normy);
			fscanf(fp,"%f",&normz);
			fskipOneStr(fp,valueOnly);
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
		fskipOneStr(fp,valueOnly);
		if(!valueOnly)assert(string(tCharBuffer)=="m_IDtriList.size");
		fscanf(fp,"%i",&t_nIDtri);
		for(int i=0;i<t_nIDtri;i++){
			fskipOneStr(fp,valueOnly);
			if(!valueOnly)assert(string(tCharBuffer)=="IDtri");
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


void Cc3dSkinSubMesh::doExport(string filePath,bool valueOnly){
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
		fprintKey(fp,valueOnly,"texFilePath");fprintf(fp," %s\n",texFilePath.c_str());
		Cc3dVector4 ambient=this->getMaterial()->getAmbient();
		Cc3dVector4 diffuse=this->getMaterial()->getDiffuse();
		Cc3dVector4 specular=this->getMaterial()->getSpecular();
		float shininess=this->getMaterial()->getShininess();

		fprintKey(fp,valueOnly,"ambient");fprintf(fp," %f %f %f %f\n",ambient.x(),ambient.y(),ambient.z(),ambient.w());
		fprintKey(fp,valueOnly,"diffuse");fprintf(fp," %f %f %f %f\n",diffuse.x(),diffuse.y(),diffuse.z(),diffuse.w());
		fprintKey(fp,valueOnly,"specular");fprintf(fp," %f %f %f %f\n",specular.x(),specular.y(),specular.z(),specular.w());
		fprintKey(fp,valueOnly,"shininess");fprintf(fp," %f\n",shininess);

		//--------------------------close file
		fclose(fp);
		//-----------------m_subMeshData_backup
		m_subMeshData_backup->doExport(folderPath+"/m_subMeshData_backup",valueOnly);
	}else{
		cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
		assert(false);
	}
#endif
}
void Cc3dSkinSubMesh::doImport(string filePath,bool valueOnly){
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
		fskipOneStr(fp,valueOnly);
		if(!valueOnly)assert(string(tCharBuffer)=="texFilePath");
		char t_texFilePath[1024];
		fscanf(fp,"%s",t_texFilePath);
		string texFilePath=string(t_texFilePath);
		Cc3dTexture*texture=Cc3dTextureCache::sharedTextureCache()->addImage(texFilePath.c_str());
		this->setTexture(texture);

		Cc3dVector4 ambient;
		Cc3dVector4 diffuse;
		Cc3dVector4 specular;
		float shininess;

		fskipOneStr(fp,valueOnly);
		if(!valueOnly)assert(string(tCharBuffer)=="ambient");
		ambient=fscanVector4(fp);

		fskipOneStr(fp,valueOnly);
		if(!valueOnly)assert(string(tCharBuffer)=="diffuse");
		diffuse=fscanVector4(fp);

		fskipOneStr(fp,valueOnly);
		if(!valueOnly)assert(string(tCharBuffer)=="specular");
		specular=fscanVector4(fp);

		fskipOneStr(fp,valueOnly);
		if(!valueOnly)assert(string(tCharBuffer)=="shininess");
		fscanf(fp,"%f",&shininess);

		Cc3dMaterial*material=new Cc3dMaterial();
		material->autorelease();
		material->setAmbient(ambient);
		material->setDiffuse(diffuse);
		material->setSpecular(specular);
		material->setShininess(shininess);
		this->setMaterial(material);

		//--------------------------close file
		fclose(fp);
		//------------------m_subMeshData_backup
		assert(m_subMeshData_backup==NULL);
		m_subMeshData_backup=new Cc3dSkinSubMeshData();
		m_subMeshData_backup->autorelease();
		m_subMeshData_backup->retain();
		m_subMeshData_backup->doImport(folderPath+"/m_subMeshData_backup",valueOnly);
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


void Cc3dSkinMesh::doExport(string filePath,bool valueOnly){
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
		fprintKey(fp,valueOnly,"m_skinSubMesh.size");fprintf(fp," %i\n",this->getSubMeshCount());
		fprintKey(fp,valueOnly,"m_vertexDupList.size");fprintf(fp," %i\n",(int)m_vertexDupList.size());
		int nVertexDup=(int)m_vertexDupList.size();
		for(int i=0;i<nVertexDup;i++){
			int nMeshIDvID=(int)m_vertexDupList[i].size();
			fprintKey(fp,valueOnly,"nMeshIDvID");fprintf(fp," %i\n",nMeshIDvID);
			for(int j=0;j<nMeshIDvID;j++){
				const _CmeshIDvID&meshIDvID=m_vertexDupList[i][j];
				fprintKey(fp,valueOnly,"  meshIDvID");fprintf(fp," %i %i\n",meshIDvID.getMeshID(),meshIDvID.getvID());
			}
		}
		//RTmat and Scale
		Cc3dMatrix4 RTmat=this->getTransform()->getRTmat();
		const float *m=RTmat.getArray();
		fprintKey(fp,valueOnly,"RTmat");fprintf(fp," %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
			m[0],m[1],m[2],m[3],
			m[4],m[5],m[6],m[7],
			m[8],m[9],m[10],m[11],
			m[12],m[13],m[14],m[15]);
		float scaleX,scaleY,scaleZ;
		scaleX=this->getTransform()->getScaleX();
		scaleY=this->getTransform()->getScaleY();
		scaleZ=this->getTransform()->getScaleZ();
		fprintKey(fp,valueOnly,"scale");fprintf(fp," %f %f %f",scaleX,scaleY,scaleZ);
		//--------------------------close file
		fclose(fp);
		//------------------m_skin
		m_skin->doExport(folderPath+"/m_skin",valueOnly);
		//------------------skinSubMeshes
		int nSkinSubMesh=this->getSubMeshCount();
		for(int i=0;i<nSkinSubMesh;i++){
			Cc3dSkinSubMesh*skinSubMesh=(Cc3dSkinSubMesh*)this->getSubMeshByIndex(i);
			string numStr=numberToStr(i);
			skinSubMesh->doExport(folderPath+"/m_skinSubMesh_"+numStr,valueOnly);
		}

	}else{
		cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
		assert(false);
	}
#endif
}
void Cc3dSkinMesh::doImport(string filePath,bool valueOnly){
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

		fskipOneStr(fp,valueOnly);
		int t_nSkinSubMesh;
		fscanf(fp,"%i",&t_nSkinSubMesh);
		if(!valueOnly)assert(string(tCharBuffer)=="m_skinSubMesh.size");

		fskipOneStr(fp,valueOnly);
		int t_nVertexDup;
		fscanf(fp,"%i",&t_nVertexDup);
		if(!valueOnly)assert(string(tCharBuffer)=="m_vertexDupList.size");
		//m_vertexDupList
		assert(m_vertexDupList.empty());
		for(int i=0;i<t_nVertexDup;i++){
			vector<_CmeshIDvID> meshIDvIDList;
			int t_nMeshIDvID;
			fskipOneStr(fp,valueOnly);
			fscanf(fp,"%i",&t_nMeshIDvID);
			if(!valueOnly)assert(string(tCharBuffer)=="nMeshIDvID");
			for(int j=0;j<t_nMeshIDvID;j++){
				_CmeshIDvID meshIDvID;
				int meshID,vID;
				fskipOneStr(fp,valueOnly);
				fscanf(fp,"%i",&meshID);
				fscanf(fp,"%i",&vID);
				if(!valueOnly)assert(string(tCharBuffer)=="meshIDvID");
				meshIDvID.init(meshID,vID);
				meshIDvIDList.push_back(meshIDvID);
			}
			m_vertexDupList.push_back(meshIDvIDList);
		}
		//RTmat and Scale
		float m[16];
		fskipOneStr(fp,valueOnly);
		if(!valueOnly)assert(string(tCharBuffer)=="RTmat");
		for(int j=0;j<16;j++){
			fscanf(fp,"%f",&m[j]);
		}
		Cc3dMatrix4 RTmat(m);
		float scaleX,scaleY,scaleZ;
		fskipOneStr(fp,valueOnly);
		if(!valueOnly)assert(string(tCharBuffer)=="scale");
		fscanf(fp,"%f",&scaleX);
		fscanf(fp,"%f",&scaleY);
		fscanf(fp,"%f",&scaleZ);
		Cc3dTransform*transform=new Cc3dTransform();
        transform->autorelease();
		transform->init(RTmat,scaleX,scaleY,scaleZ);
		this->setTransform(transform);
		//--------------------------close file
		fclose(fp);
		//------------------m_skin
		Cc3dSkin*skin=new Cc3dSkin();
		skin->autorelease();
		setSkin(skin);
		skin->doImport(folderPath+"/m_skin",valueOnly);
		//------------------skinSubMeshes
		assert(this->getSubMeshCount()==0);
		for(int i=0;i<t_nSkinSubMesh;i++){
			string numStr=numberToStr(i);
			Cc3dSkinSubMesh*p=new Cc3dSkinSubMesh();
			p->autorelease();
			this->addSubMesh(p);
			p->doImport(folderPath+"/m_skinSubMesh_"+numStr,valueOnly);
		}
	}else{
		cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
		assert(false);
	}
}
void Cc3dAniLayerInfo::doExport(string filePath,bool valueOnly){
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
			fprintKey(fp,valueOnly,"m_interval");fprintf(fp," %f\n",m_interval);
			fprintKey(fp,valueOnly,"m_startTime");fprintf(fp," %f\n",m_startTime);
			fprintKey(fp,valueOnly,"m_endTime");fprintf(fp," %f\n",m_endTime);
		}
		//--------------------------close file
		fclose(fp);
	}else{
		cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
		assert(false);
	}
#endif
}
void Cc3dAniLayerInfo::doImport(string filePath,bool valueOnly){

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

		fskipOneStr(fp,valueOnly);
		fscanf(fp,"%f",&m_interval);
		if(!valueOnly)assert(string(tCharBuffer)=="m_interval");

		fskipOneStr(fp,valueOnly);
		fscanf(fp,"%f",&m_startTime);
		if(!valueOnly)assert(string(tCharBuffer)=="m_startTime");

		fskipOneStr(fp,valueOnly);
		fscanf(fp,"%f",&m_endTime);
		if(!valueOnly)assert(string(tCharBuffer)=="m_endTime");


		m_curTime=0;

		//--------------------------close file
		fclose(fp);
	}else{
		cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
		assert(false);
	}

}
void Cc3dSkinActor::doExport(string filePath,bool valueOnly){
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
			if(valueOnly){
				fprintf(fp,"%s","valueOnly\n");
			}else{
				fprintf(fp,"%s","notValueOnly\n");
		
			}
		
			fprintKey(fp,valueOnly,"m_aniLayerIndex");
			fprintf(fp," %i\n",m_aniLayerIndex);
			fprintKey(fp,valueOnly,"m_interval");fprintf(fp," %f\n",m_interval);
			fprintKey(fp,valueOnly,"m_aniLayerInfoList.size");fprintf(fp," %i\n",(int)m_aniLayerInfoList.size());
			fprintKey(fp,valueOnly,"m_skinMeshList.size");fprintf(fp," %i\n",(int)this->getMeshCount());
		}
		//--------------------------close file
		fclose(fp);
		//------------------m_aniLayerInfoList
		int nAniLayerInfo=(int)m_aniLayerInfoList.size();
		for(int i=0;i<nAniLayerInfo;i++){
			string numStr=numberToStr(i);
			m_aniLayerInfoList[i]->doExport(folderPath+"/m_aniLayerInfo_"+numStr,valueOnly);
		}
		//------------------skinMeshes
		int meshCount=this->getMeshCount();
		for(int i=0;i<meshCount;i++){
			string numStr=numberToStr(i);
			Cc3dSkinMesh*mesh=(Cc3dSkinMesh*)this->getMeshByIndex(i);
			mesh->doExport(folderPath+"/m_skinMesh_"+numStr,valueOnly);
		}
	}else{
		cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
		assert(false);
	}
#endif
}
void Cc3dSkinActor::doImport(string filePath){
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
		bool valueOnly;

		char t_str[1024];
		fscanf(fp,"%s",t_str);
		string str=t_str;
		if(str=="valueOnly"){
			valueOnly=true;
		}else if(str=="notValueOnly"){
			valueOnly=false;
		}else{
			assert(false);
		}
		cout<<"valueOnly:"<<valueOnly<<endl;

		fskipOneStr(fp,valueOnly);
		fscanf(fp,"%i",&m_aniLayerIndex);

		fskipOneStr(fp,valueOnly);
		fscanf(fp,"%f",&m_interval);

		fskipOneStr(fp,valueOnly);
		int t_nAniLayerInfo;
		fscanf(fp,"%i",&t_nAniLayerInfo);

		fskipOneStr(fp,valueOnly);
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
			p->doImport(folderPath+"/m_aniLayerInfo_"+numStr,valueOnly);
		}
		//------------------skinMeshes
		assert(this->getMeshCount()==0);
		for(int i=0;i<t_nSkinMesh;i++){
			string numStr=numberToStr(i);
			Cc3dSkinMesh*p=new Cc3dSkinMesh();
			p->autorelease();
			this->addMesh(p);
			p->doImport(folderPath+"/m_skinMesh_"+numStr,valueOnly);
		}
	}else{
		cout<<string("")+"warning: create path: "+folderFullPath+ " failed!"<<endl;
		assert(false);
	}

}