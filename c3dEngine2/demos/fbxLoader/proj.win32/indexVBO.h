#ifndef CINDEXVBO_H_H
#define CINDEXVBO_H_H
class CindexVBO{
public:
	GLuint VertexGBuffer; 
	GLuint NormGBuffer; 
	GLuint TexCoordGBuffer;
	vector<GLuint*> indexArrayList;//���������б�,indexArrayList[i]��texrureList[i]��Ӧ���������Ӽ�
	vector<int> topList;//topList[i]ΪindexArrayList[i]��ջ��ָ��
	vector<GLuint> indexGBufferList;//�����Կ��������б�
	GLenum mode;//��״
	CindexVBO(){
		VertexGBuffer = 0; 
		NormGBuffer = 0; 
		TexCoordGBuffer =0;
		mode=GL_TRIANGLES;
	}
	~CindexVBO(){
		//����vbo
		if(VertexGBuffer!=0)glDeleteBuffersARB(1,&VertexGBuffer);
		if(NormGBuffer!=0)glDeleteBuffersARB(1,&NormGBuffer);
		if(TexCoordGBuffer!=0)glDeleteBuffersARB(1,&TexCoordGBuffer);
		int nIndexGBuffer=(int)indexGBufferList.size();
		for(int i=0;i<nIndexGBuffer;i++){
			if(indexGBufferList[i]!=0)glDeleteBuffersARB(1,&indexGBufferList[i]);
		}
		
		//����indexArrayList
		{
			int nIndexArray=(int)indexArrayList.size();
			for(int i=0;i<nIndexArray;i++){
				if(indexArrayList[i]!=NULL)delete []indexArrayList[i];//ע��ǰ���[]
			}
		}
	}

	void bind_arrayGbuffers(){
		//����
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VertexGBuffer ); 
		glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );//ָ������󶨵��Ƕ��㣬��ָ�������ʽ
		//����
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NormGBuffer );//ָ������󶨵��Ƿ��ߣ���ָ�����߸�ʽ
		glNormalPointer( GL_FLOAT, 0, (char *) NULL ); 
		//uv
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, TexCoordGBuffer );//ָ������󶨵����������꣬��ָ����������ĸ�ʽ
		glTexCoordPointer(2,GL_FLOAT, 0, (char *) NULL ); 

	}
	void submitIndexArrayList_and_showIndexGBufferList(const vector<GLuint>&textureList){
		int nIndexArray=(int)indexArrayList.size();
		for(int i=0;i<nIndexArray;i++){
			if(topList[i]!=0){
				glBindTexture(GL_TEXTURE_2D,textureList[i]);//������
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, indexGBufferList[i]);//����
				glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*topList[i], indexArrayList[i], GL_STREAM_DRAW_ARB );
				glDrawElements(mode, topList[i], GL_UNSIGNED_INT, 0);//�ڶ�������Ϊ��������������������
			}
		}
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);//�������
		glBindTexture(GL_TEXTURE_2D,0);
		
	}
	void unbind_arrayGBuffers(){
		glBindBufferARB(GL_ARRAY_BUFFER, 0); 
	}
	void setTopListElmToZero(){
		int nIndexArray=(int)indexArrayList.size();
		for(int i=0;i<nIndexArray;i++){
			topList[i]=0;//ջָ�����
			
		}
	}
	void fillIndexArrayList(const vector<CIDTriangle*>&pVisibleIDtriList){
		//���indexArrayList
		int nIDtri=(int)pVisibleIDtriList.size();
		for(int i=0;i<nIDtri;i++){
			CIDTriangle&IDtri=*pVisibleIDtriList[i];
			//��IDtri.textureIndex_inMeshTextureList��k
			//�ͽ�IDtri��������������浽indexArrayList[k]��
			int k=IDtri.textureIndex_inMeshTextureList;
			indexArrayList[k][topList[k]++]=IDtri.vID[0];
			indexArrayList[k][topList[k]++]=IDtri.vID[1];
			indexArrayList[k][topList[k]++]=IDtri.vID[2];
		}//�õ�indexArrayList
	}
	void allocateIndexArrayListAndTopList(const vector<GLuint>&texIDtriCountList){
		//����texIDtriCountList����
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
	void submitVertexs(vector<Cvertex>&vlist,vector<CIDTriangle>&IDtriList){//��mesh�ж��������ύ���Կ�,������mesh������ִ��
		vector<float> vertexArray;//�Ƶ㻺������
		vector<float> uvArray;//uv��������
		vector<float> normArray;//���򻺳�����
		//------------------------������������
		//�������㻺�����飬���򻺳������uv��������
		
		//��������������
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
		//-------------------����vbo
		//��������vbo
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, VertexGBuffer);
		if((int)vertexArray.size()>0){
			glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(float)*(int)vertexArray.size(), &vertexArray[0], GL_STATIC_DRAW_ARB ); 
		}
		glBindBufferARB(GL_ARRAY_BUFFER, 0);//��󶨣�ʹ����������ʽ�Ļ滭����Ӱ�죩
		//��ʱ����vbo�ѽ������������������ύ�Կ�������ʹvertexArray�����޸�Ҳ��Ӱ�졣
		//��������vbo
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, NormGBuffer);
		if((int)normArray.size()>0){
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(float)*(int)normArray.size(), &normArray[0], GL_STATIC_DRAW_ARB ); 
		}
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		//����uv��vbo
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