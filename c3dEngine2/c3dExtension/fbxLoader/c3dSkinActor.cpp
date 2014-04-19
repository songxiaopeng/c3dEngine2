#include "c3dSkinActor.h"


	void Cc3dAniLayer::doExport(string filePath){
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
	void Cc3dAniLayer::doImport(string filePath){
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
	void Cc3dSkinCluster::doExport(string filePath){
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
	void Cc3dSkinCluster::doImport(string filePath){
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

	void Cc3dSkin::doExport(string filePath){
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
	void Cc3dSkin::doImport(string filePath){
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
	void Cc3dSkinSubMeshData::doExport(string filePath){
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
	void Cc3dSkinSubMeshData::doImport(string filePath){
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


	void Cc3dSkinSubMesh::doExport(string filePath){
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
	void Cc3dSkinSubMesh::doImport(string filePath){
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


	void Cc3dSkinMesh::doExport(string filePath){
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
	void Cc3dSkinMesh::doImport(string filePath){
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
	void Cc3dAniLayerInfo::doExport(string filePath){
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
	void Cc3dAniLayerInfo::doImport(string filePath){
        
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
	void Cc3dSkinActor::doExport(string filePath){
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