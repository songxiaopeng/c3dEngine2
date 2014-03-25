#ifndef CINDEXVBO_H_H
#define CINDEXVBO_H_H
class CindexVBO{
public:
	GLuint VertexGBuffer; 
	GLuint NormGBuffer; 
	GLuint TexCoordGBuffer;
	vector<GLuint*> indexArrayList;//索引数组列表,indexArrayList[i]存texrureList[i]对应的三角形子集
	vector<int> topList;//topList[i]为indexArrayList[i]的栈顶指针
	vector<GLuint> indexGBufferList;//索引显卡缓冲区列表
	GLenum mode;//形状
	CindexVBO(){
		VertexGBuffer = 0; 
		NormGBuffer = 0; 
		TexCoordGBuffer =0;
		mode=GL_TRIANGLES;
	}
	~CindexVBO(){
		//销毁vbo
		if(VertexGBuffer!=0)glDeleteBuffersARB(1,&VertexGBuffer);
		if(NormGBuffer!=0)glDeleteBuffersARB(1,&NormGBuffer);
		if(TexCoordGBuffer!=0)glDeleteBuffersARB(1,&TexCoordGBuffer);
		int nIndexGBuffer=(int)indexGBufferList.size();
		for(int i=0;i<nIndexGBuffer;i++){
			if(indexGBufferList[i]!=0)glDeleteBuffersARB(1,&indexGBufferList[i]);
		}
		
		//销毁indexArrayList
		{
			int nIndexArray=(int)indexArrayList.size();
			for(int i=0;i<nIndexArray;i++){
				if(indexArrayList[i]!=NULL)delete []indexArrayList[i];//注意前面加[]
			}
		}
	}

	void bind_arrayGbuffers(){
		//顶点
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VertexGBuffer ); 
		glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );//指明上面绑定的是顶点，并指明顶点格式
		//法向
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NormGBuffer );//指明上面绑定的是法线，并指明法线格式
		glNormalPointer( GL_FLOAT, 0, (char *) NULL ); 
		//uv
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, TexCoordGBuffer );//指明上面绑定的是纹理坐标，并指明纹理坐标的格式
		glTexCoordPointer(2,GL_FLOAT, 0, (char *) NULL ); 

	}
	void submitIndexArrayList_and_showIndexGBufferList(const vector<GLuint>&textureList){
		int nIndexArray=(int)indexArrayList.size();
		for(int i=0;i<nIndexArray;i++){
			if(topList[i]!=0){
				glBindTexture(GL_TEXTURE_2D,textureList[i]);//绑定纹理
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, indexGBufferList[i]);//索引
				glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*topList[i], indexArrayList[i], GL_STREAM_DRAW_ARB );
				glDrawElements(mode, topList[i], GL_UNSIGNED_INT, 0);//第二个参数为顶点数（即索引个数）
			}
		}
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);//索引解绑定
		glBindTexture(GL_TEXTURE_2D,0);
		
	}
	void unbind_arrayGBuffers(){
		glBindBufferARB(GL_ARRAY_BUFFER, 0); 
	}
	void setTopListElmToZero(){
		int nIndexArray=(int)indexArrayList.size();
		for(int i=0;i<nIndexArray;i++){
			topList[i]=0;//栈指针归零
			
		}
	}
	void fillIndexArrayList(const vector<CIDTriangle*>&pVisibleIDtriList){
		//填充indexArrayList
		int nIDtri=(int)pVisibleIDtriList.size();
		for(int i=0;i<nIDtri;i++){
			CIDTriangle&IDtri=*pVisibleIDtriList[i];
			//看IDtri.textureIndex_inMeshTextureList是k
			//就将IDtri三个顶点的索引存到indexArrayList[k]中
			int k=IDtri.textureIndex_inMeshTextureList;
			indexArrayList[k][topList[k]++]=IDtri.vID[0];
			indexArrayList[k][topList[k]++]=IDtri.vID[1];
			indexArrayList[k][topList[k]++]=IDtri.vID[2];
		}//得到indexArrayList
	}
	void allocateIndexArrayListAndTopList(const vector<GLuint>&texIDtriCountList){
		//根据texIDtriCountList来开
		//indexArrayList
		int nTex=(int)texIDtriCountList.size();
		indexArrayList.resize(nTex);
		for(int i=0;i<nTex;i++){
			if(texIDtriCountList[i]!=0){
				indexArrayList[i]=new GLuint[texIDtriCountList[i]*3];
			}else{
				indexArrayList[i]=NULL;
			}
		}
		//topList
		topList.resize(nTex);
		for(int i=0;i<nTex;i++){
			topList[i]=0;
		}


	}
	void makeVBO(vector<Cvertex>&vlist,vector<CIDTriangle>&IDtriList,const vector<GLuint>&textureList,const vector<GLuint>&texIDtriCountList,GLenum _mode){
		makeIndexGBufferList(textureList);
		genGBuffers();
		submitVertexs(vlist,IDtriList);
		allocateIndexArrayListAndTopList(texIDtriCountList);
		mode=_mode;
	}
	void genGBuffers(){
		glGenBuffersARB(1,&VertexGBuffer);
		glGenBuffersARB(1,&NormGBuffer);
		glGenBuffersARB(1,&TexCoordGBuffer);
		int nIndexGBuffer=(int)indexGBufferList.size();
		for(int i=0;i<nIndexGBuffer;i++){
			glGenBuffersARB(1, &indexGBufferList[i]);
		}
	}
	void submitVertexs(vector<Cvertex>&vlist,vector<CIDTriangle>&IDtriList){//将mesh中顶点数据提交到显卡,必须在mesh建立后执行
		vector<float> vertexArray;//制点缓冲数组
		vector<float> uvArray;//uv缓冲数组
		vector<float> normArray;//法向缓冲数组
		//------------------------制作缓冲数组
		//制作顶点缓冲数组，法向缓冲数组和uv缓冲数组
		
		//制作各缓冲数组
		int vertexCount=vlist.size();
		int IDtriCount=vertexCount/3;
		if(IDtriCount!=(int)IDtriList.size()){
			cout<<"IDtriCount!=IDtriList.size()!"<<endl;
			system("pause");
			exit(0);
		}
		for(int i=0;i<IDtriCount;i++){
			CIDTriangle&IDtri=IDtriList[i];
			for(int j=0;j<3;j++){
				float*v=vlist[IDtri.vID[j]].v;
				float*norm=IDtri.norm;
				float*u=vlist[IDtri.vID[j]].u;
				//vertexArray
				vertexArray.push_back(v[X]);
				vertexArray.push_back(v[Y]);
				vertexArray.push_back(v[Z]);
				//normArray
				normArray.push_back(norm[X]);
				normArray.push_back(norm[Y]);
				normArray.push_back(norm[Z]);
				//uvArray
				uvArray.push_back(u[0]);
				uvArray.push_back(u[1]);
			}
		
		}
		//-------------------制作vbo
		//制作顶点vbo
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, VertexGBuffer);
		if((int)vertexArray.size()>0){
			glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(float)*(int)vertexArray.size(), &vertexArray[0], GL_STATIC_DRAW_ARB ); 
		}
		glBindBufferARB(GL_ARRAY_BUFFER, 0);//解绑定（使后面其它形式的绘画不受影响）
		//此时顶点vbo已建立（即顶点数据已提交显卡），即使vertexArray内容修改也不影响。
		//制作法向vbo
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, NormGBuffer);
		if((int)normArray.size()>0){
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(float)*(int)normArray.size(), &normArray[0], GL_STATIC_DRAW_ARB ); 
		}
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		//制作uv的vbo
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, TexCoordGBuffer);
		if((int)uvArray.size()>0){
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(float)*(int)uvArray.size(), &uvArray[0], GL_STATIC_DRAW_ARB ); 
		}
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	}
	void makeIndexGBufferList(const vector<GLuint>&textureList){
		indexGBufferList.resize((int)textureList.size());
	}
	
};
#endif