#include "fbxmodel.h"

	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//��ʼ��
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Cmodelfbx::Init_and_load(char* _fbxFileName){
		fbxFileName=_fbxFileName;
		cout<<"����\"";
		cout<<fbxFileName;
		cout<<"\":";
		//����fbx����
		InitializeSdkObjects(lSdkManager,lScene);
		LoadScene(lSdkManager,lScene,fbxFileName);
		cout<<"���!"<<endl;
	}
	void Cmodelfbx::InitializeSdkObjects(FbxManager*& pSdkManager, FbxScene*& pScene)
	{
		// The first thing to do is to create the FBX SDK manager which is the 
		// object allocator for almost all the classes in the SDK.
		pSdkManager = FbxManager::Create();
		if( !pSdkManager )
		{
			FBXSDK_printf("Unable to create the FBX SDK manager\n");
			system("pause");
			exit(0);
		}
		else
		{
//ϵͳ�Դ����			FBXSDK_printf("FBX SDK version %s\n\n", pSdkManager->GetVersion());
		}

		// create an IOSettings object
		FbxIOSettings * ios = FbxIOSettings::Create(pSdkManager, IOSROOT );
		pSdkManager->SetIOSettings(ios);

		// Load plugins from the executable directory
		FbxString lPath = FbxGetApplicationDirectory();
		pSdkManager->LoadPluginsDirectory(lPath.Buffer());

		// Create the entity that will hold the scene.
		pScene = FbxScene::Create(pSdkManager,"");
	}

	bool Cmodelfbx::LoadScene(FbxManager* pSdkManager, FbxDocument* pScene,char* pFilename)
	{
#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(pSdkManager->GetIOSettings()))
#endif

		int lFileMajor, lFileMinor, lFileRevision;
		int lSDKMajor,  lSDKMinor,  lSDKRevision;
		//int lFileFormat = -1;
		int i, lAnimStackCount;
		bool lStatus;
		char lPassword[1024];

		// Get the file version number generate by the FBX SDK.
		FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

		// Create an importer.
		FbxImporter* lImporter = FbxImporter::Create(pSdkManager,"");

		// Initialize the importer by providing a filename.
		const bool lImportStatus = lImporter->Initialize(pFilename, -1, pSdkManager->GetIOSettings());
		lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

		if( !lImportStatus )
		{
//ϵͳ�Դ����			FBXSDK_printf("Call to FbxImporter::Initialize() failed.\n");
//ϵͳ�Դ����			FBXSDK_printf("Error returned: %s\n\n", lImporter->GetLastErrorString());

			if (lImporter->GetLastErrorID() == FbxIOBase::eFileVersionNotSupportedYet ||
				lImporter->GetLastErrorID() == FbxIOBase::eFileVersionNotSupportedAnymore)
			{
//ϵͳ�Դ����				FBXSDK_printf("FBX version number for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
//ϵͳ�Դ����				FBXSDK_printf("FBX version number for file %s is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
			}

			return false;
		}



//ϵͳ�Դ����		FBXSDK_printf("FBX version number for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

		if (lImporter->IsFBX())
		{
//ϵͳ�Դ����			FBXSDK_printf("FBX version number for file %s is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);

			// From this point, it is possible to access animation stack information without
			// the expense of loading the entire file.

//ϵͳ�Դ����			FBXSDK_printf("Animation Stack Information\n");

			lAnimStackCount = lImporter->GetAnimStackCount();

//ϵͳ�Դ����			FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
//ϵͳ�Դ����			FBXSDK_printf("    Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
//ϵͳ�Դ����			FBXSDK_printf("\n");

			for(i = 0; i < lAnimStackCount; i++)
			{
				FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

//ϵͳ�Դ����				FBXSDK_printf("    Animation Stack %d\n", i);
//ϵͳ�Դ����				FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
//ϵͳ�Դ����				FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

				// Change the value of the import name if the animation stack should be imported 
				// under a different name.
//ϵͳ�Դ����				FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

				// Set the value of the import state to false if the animation stack should be not
				// be imported. 
//ϵͳ�Դ����				FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
//ϵͳ�Դ����				FBXSDK_printf("\n");
			}

			// Set the import states. By default, the import states are always set to 
			// true. The code below shows how to change these states.
			IOS_REF.SetBoolProp(IMP_FBX_MATERIAL,        true);
			IOS_REF.SetBoolProp(IMP_FBX_TEXTURE,         true);
			IOS_REF.SetBoolProp(IMP_FBX_LINK,            true);
			IOS_REF.SetBoolProp(IMP_FBX_SHAPE,           true);
			IOS_REF.SetBoolProp(IMP_FBX_GOBO,            true);
			IOS_REF.SetBoolProp(IMP_FBX_ANIMATION,       true);
			IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
		}

		// Import the scene.
		lStatus = lImporter->Import(pScene);

		if(lStatus == false && lImporter->GetLastErrorID() == FbxIOBase::ePasswordError)
		{
			FBXSDK_printf("Please enter password: ");

			lPassword[0] = '\0';

			FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
				scanf("%s", lPassword);
			FBXSDK_CRT_SECURE_NO_WARNING_END

				FbxString lString(lPassword);

			IOS_REF.SetStringProp(IMP_FBX_PASSWORD,      lString);
			IOS_REF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

			lStatus = lImporter->Import(pScene);

			if(lStatus == false && lImporter->GetLastErrorID() == FbxIOBase::ePasswordError)
			{
				FBXSDK_printf("\nPassword is wrong, import aborted.\n");
			}
		}

		// Destroy the importer.
		lImporter->Destroy();

		return lStatus;
	}

	void Cmodelfbx::DestroySdkObjects(FbxManager* &pSdkManager)//һ��Ҫ��ָ������ã���Ϊ��Ҫ��ָ����NULL
	{
		// Delete the FBX SDK manager. All the objects that have been allocated 
		// using the FBX SDK manager and that haven't been explicitly destroyed 
		// are automatically destroyed at the same time.
		if (pSdkManager) pSdkManager->Destroy();
		pSdkManager = NULL;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Ԥ����
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Cmodelfbx::triangulate_loadTextures_preprocess(){
		cout<<"----------------------------fbxFileName:"<<fbxFileName<<endl;
        TriangulateRecursive(lScene->GetRootNode());// Convert mesh, NURBS and patch into triangle mesh
		loadTextures(fbxFileName);
	/*	//get smoothInfo
		{
			//set me true to compute smoothing info from normals
			bool lComputeFromNormals = true;//false;
			//set me true to convert hard/soft edges info to smoothing groups info
			bool lConvertToSmoothingGroup = true;//false;
			//get smoothing info, if there're mesh in the scene
			GetSmoothing(lSdkManager, lScene->GetRootNode(), lComputeFromNormals, lConvertToSmoothingGroup);
		
		}*/
		makeSubMeshSetForEachNode(lScene->GetRootNode(),userDataIndex_idSubMeshSet);
		makeOtherUserForEachNode(lScene->GetRootNode(),userDataIndex_UV,userDataIndex_Norm);
		
	

	}
	void Cmodelfbx::makeSubMeshSetForThisNode(FbxNode* pNode,int userDataIndex){
		cout<<"nodeName:"<<pNode->GetName()<<endl;
		FbxMesh*lMesh=pNode->GetMesh();
		if(!lMesh){
			cout<<"error: lMesh==NULL!"<<endl;
			return;
		}
		Cc3dMesh*mesh=new Cc3dMesh();
		mesh->autorelease();
		//��mesh��ӵ�lMesh�ڵ�
		lMesh->SetUserDataPtr(userDataIndex,mesh);
		//����mesh
		//ÿ�����ʶ�Ӧһ��subMesh
		{
			
			//��ò���������
			FbxLayerElementArrayTemplate<int>* lMaterialIndice = NULL;
			{
				if (lMesh->GetElementMaterial())
				{
					lMaterialIndice = &lMesh->GetElementMaterial()->GetIndexArray();
				}
			}
			if(!lMaterialIndice){
				cout<<"error: lMaterialIndice==NULL!"<<endl;
				return;
			}
			//��ò�����������
			const int MaterialIndiceCount=lMaterialIndice->GetCount();
			if(MaterialIndiceCount==0){
				cout<<"error: MaterialIndiceCount==0 !"<<endl;
				return;
			}
	
			//-------------------------------�ж�uvӳ��ģʽ�����lUVName
			const char * lUVName = NULL;
			FbxStringList lUVNames;//������ܷŵ��������������ȥ����Ϊ����lUVName��Ҫָ��lUVNames[0]��
			//���lUVNames������������������棬���Ž���ʱlUVName�����������lUVName�ɿ�����
			{
				//�Ƿ���uv
				bool mHasUV = lMesh->GetElementUVCount() > 0;
				if(mHasUV==false){
					cout<<"û��uv!"<<endl;
					return;
				}else{
					//uvӳ��ģʽ
					const FbxGeometryElementUV * lUVElement = lMesh->GetElementUV(0);
					FbxGeometryElement::EMappingMode lUVMappingMode=lUVElement->GetMappingMode();
					if(lUVMappingMode!=FbxGeometryElement::eByPolygonVertex){
						cout<<"error:uvӳ��ģʽ����eByPolygonVertex��Ŀǰ�в�֧������ģʽ!"<<endl;
						system("pause");
						exit(0);
						return;
					}else{
						//���uvSet����
						lMesh->GetUVSetNames(lUVNames);
						if (lUVNames.GetCount())
						{
							lUVName = lUVNames[0];
						}else{
							cout<<"lUVName==NULL!"<<endl;
							return;
						}
					}	
				}
			}//�õ�lUVName
			//cout<<"lUVName:"<<lUVName<<endl;
			//---------------------�ж�normӳ��ģʽ
			bool mHasNormal = lMesh->GetElementNormalCount() > 0;
			if (mHasNormal)
			{
				FbxGeometryElement::EMappingMode lNormalMappingMode = lMesh->GetElementNormal(0)->GetMappingMode();
				if (lNormalMappingMode == FbxGeometryElement::eNone)
				{
					cout<<"error:û�з�������!"<<endl;
					system("pause");
					exit(0);
				}
				if (mHasNormal && lNormalMappingMode != FbxGeometryElement::eByPolygonVertex)
				{
					cout<<"error:normӳ��ģʽ����eByPolygonVertex��Ŀǰ�в�֧������ģʽ!"<<endl;
					system("pause");
					exit(0);
				}
			}
			//-------------
			//������������ֵ
			int maxMaterialIndex=-1;
			for(int i=0;i<MaterialIndiceCount;i++){
				int curMaterialIndex=lMaterialIndice->GetAt(i);
				if(curMaterialIndex>maxMaterialIndex){
					maxMaterialIndex=curMaterialIndex;
				}
			}//�õ�maxMaterialIndex
			if(maxMaterialIndex==-1){
				cout<<"error: maxMaterialIndex==-1"<<endl;
				return;
			}
			//����subMesh�б�ÿ����������һ��subMesh��
			vector<Cc3dSubMesh*> subMeshList;
			for(int i=0;i<MaterialIndiceCount;i++){
				Cc3dSubMesh*subMesh=new Cc3dSubMesh();
				subMesh->autorelease();
				subMesh->init();
				subMeshList.push_back(subMesh);
			}
			//Ϊ��subMesh�������
			for(int i=0;i<MaterialIndiceCount;i++){
				int lMaterialIndex=lMaterialIndice->GetAt(i);
				Cc3dTexture* texture=NULL;
				const FbxSurfaceMaterial * lMaterial = pNode->GetMaterial(lMaterialIndex);
				const char * pPropertyName=FbxSurfaceMaterial::sDiffuse;
				const FbxProperty lProperty = lMaterial->FindProperty(pPropertyName);
				if (lProperty.IsValid())
				{
					const int lTextureCount = lProperty.GetSrcObjectCount(FbxFileTexture::ClassId);
					if (lTextureCount)
					{
						const FbxFileTexture* lTexture = lProperty.GetSrcObject(FBX_TYPE(FbxFileTexture), 0);
						if (lTexture && lTexture->GetUserDataPtr(userDataIndex_texture))
						{
							texture = (static_cast<Cc3dTexture *>(lTexture->GetUserDataPtr(userDataIndex_texture)));
						}
					}
				}//got texture
				assert(texture);
				subMeshList[i]->setTexture(texture);
			}
			//�����������,��䵽subMesh
			const int triangleCount = lMesh->GetPolygonCount();
			for (int i = 0; i < triangleCount; i++)
			{
				//��ǰ����κţ�i
				Cc3dSubMesh*subMesh=subMeshList[i];
				//----���uv
				FbxVector2 uv0;
				FbxVector2 uv1;
				FbxVector2 uv2;
				lMesh->GetPolygonVertexUV(i, 0, lUVName, uv0);
				lMesh->GetPolygonVertexUV(i, 1, lUVName, uv1);
				lMesh->GetPolygonVertexUV(i, 2, lUVName, uv2);
				//----��÷�����
				FbxVector4 norm0;
				FbxVector4 norm1;
				FbxVector4 norm2;
				lMesh->GetPolygonVertexNormal(i, 0, norm0);
				lMesh->GetPolygonVertexNormal(i, 1, norm1);
				lMesh->GetPolygonVertexNormal(i, 2, norm2);
				norm0[3]=0;
				norm1[3]=0;
				norm2[3]=0;
				//----����
				FbxVector4 pos0=lMesh->GetControlPoints()[lMesh->GetPolygonVertex(i,0)];
				FbxVector4 pos1=lMesh->GetControlPoints()[lMesh->GetPolygonVertex(i,1)];
				FbxVector4 pos2=lMesh->GetControlPoints()[lMesh->GetPolygonVertex(i,2)];
				pos0[3]=1;
				pos1[3]=1;
				pos2[3]=1;
				//----��uv,norm,pos�ϳɶ���
				Cc3dVertex vertex0(Cc3dVector4(pos0[0],pos0[1],pos0[2],pos0[3]),Cc3dVector2(uv0[0],uv0[1]),Cc3dVector4(norm0[0],norm0[1],norm0[2],norm0[3]));
				Cc3dVertex vertex1(Cc3dVector4(pos1[0],pos1[1],pos1[2],pos1[3]),Cc3dVector2(uv1[0],uv1[1]),Cc3dVector4(norm1[0],norm1[1],norm1[2],norm1[3]));
				Cc3dVertex vertex2(Cc3dVector4(pos2[0],pos2[1],pos2[2],pos2[3]),Cc3dVector2(uv2[0],uv2[1]),Cc3dVector4(norm2[0],norm2[1],norm2[2],norm2[3]));
				//----addIDtri first
				int ID0=subMesh->getSubMeshData()->vlist.size();
				int ID1=subMesh->getSubMeshData()->vlist.size()+1;
				int ID2=subMesh->getSubMeshData()->vlist.size()+2;
				subMesh->addIDtri(Cc3dIDTriangle(ID0,ID1,ID2));
				//----addVertex second (must after addIDtri)
				subMesh->addVertex(vertex0);
				subMesh->addVertex(vertex1);
				subMesh->addVertex(vertex2);
			}
			//��subMeshList������mesh��ӵ�mesh
			int nSubMesh=(int)subMeshList.size();
			for(int i=0;i<nSubMesh;i++){
				mesh->addSubMesh(subMeshList[i]);
			}
		}
		//��mesh��ӵ�this
		this->addMesh(mesh);
	

		

	}
	void Cmodelfbx::makeSubMeshSetForEachNode(FbxNode* pNode,int userDataIndex)
	{
		FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();
		if (lNodeAttribute//�����Խڵ�
			&&lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh//�����Խڵ�Ϊ������ΪeMesh
			)//ΪpNode��������idSubMeshSet
		{	
			makeSubMeshSetForThisNode(pNode,userDataIndex);
		}
		const int lChildCount = pNode->GetChildCount();
		for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
		{
			makeSubMeshSetForEachNode(pNode->GetChild(lChildIndex),userDataIndex);
		}
	}
	bool Cmodelfbx::getHasDeformer(FbxMesh*lMesh){
		//	// If it has some deformer connection, update the vertices position
		//	const bool lHasVertexCache = lMesh->GetDeformerCount(FbxDeformer::eVertexCache) &&
		//		(static_cast<FbxVertexCacheDeformer*>(lMesh->GetDeformer(0, FbxDeformer::eVertexCache)))->IsActive();
		//	const bool lHasShape = lMesh->GetShapeCount() > 0;
		const bool lHasSkin = lMesh->GetDeformerCount(FbxDeformer::eSkin) > 0;
		//	const bool lHasDeformation = lHasVertexCache || lHasShape || lHasSkin;
		return lHasSkin;
	}

	void Cmodelfbx::makeOtherUserForThisNode(FbxNode* pNode,int userDataIndex_uv,int userDataIndex_norm){
		//���mesh
		FbxMesh*lMesh=pNode->GetMesh();
		if(!lMesh){
			cout<<"error: lMesh==NULL!"<<endl;
			return;
		}
		//��ö���θ���
		const int triangleCount = lMesh->GetPolygonCount();
		//��ö������
		const int lVertexCount = lMesh->GetControlPointsCount();
		//ΪpUVs��pNorms���ٿռ�
		float*pUVs=new float[triangleCount*3*2];//(pUVs[6*i],pUVs[6*i+1])Ϊi�������ε�һ�������uv����
									   	  //(pUVs[6*i+2],pUVs[6*i+3])Ϊi�������εڶ��������uv����
										  //(pUVs[6*i+4],pUVs[6*i+5])Ϊi�������ε����������uv����
		FbxVector4*pNorms=new FbxVector4[triangleCount*3];//pNorms[3*i]Ϊi�������ε�һ�������norm
															//pNorms[3*i+1]Ϊi�������εڶ��������norm
															//pNorms[3*i+2]Ϊi�������ε����������norm
		//ΪclusterCount,hasSkin���ٿռ�
		int*pClusterCount=new int;
		bool*pHasSkin=new bool;
		//ΪlVertexArray��lNormalArray��lClusterDeformation��lClusterWeight���ٿռ�
		FbxVector4* lVertexArray= NULL;
		FbxVector4* lNormalArray= NULL;
		FbxAMatrix* lClusterDeformation=NULL;
		double* lClusterWeight=NULL;
		//���ٿռ�
		{
			if (lVertexCount == 0){
				//��ָ�������ΪNULL
			}else{//lVertexCount!=0
				//��������Ƥʱ�����ɣ�Ϊ���ǲ��ƻ�ԭ���ݣ��������ֱ����ԭʼ���ݵ����ã�
				if(getHasDeformer(lMesh)){
					lVertexArray = new FbxVector4[lVertexCount];
					lNormalArray = new FbxVector4[3*triangleCount];
					lClusterDeformation = new FbxAMatrix[lVertexCount];
					lClusterWeight = new double[lVertexCount];
				}
			}
		}

		//��ӵ�lMesh�ڵ�
		lMesh->SetUserDataPtr(userDataIndex_uv,pUVs);
		lMesh->SetUserDataPtr(userDataIndex_norm,pNorms);
		lMesh->SetUserDataPtr(userDataIndex_clusterCount,pClusterCount);
		lMesh->SetUserDataPtr(userDataIndex_hasSkin,pHasSkin);
		lMesh->SetUserDataPtr(userDataIndex_Vertex_deformed,lVertexArray);
		lMesh->SetUserDataPtr(userDataIndex_Normal_deformed,lNormalArray);
		lMesh->SetUserDataPtr(userDataIndex_clusterDeformation,lClusterDeformation);
		lMesh->SetUserDataPtr(userDataIndex_clusterWeight,lClusterWeight);
		//���pCLusterCount
		{
			//we need to get the number of clusters
			const int lSkinCount = lMesh->GetDeformerCount(FbxDeformer::eSkin);
			int lClusterCount = 0;
			for (int lSkinIndex = 0; lSkinIndex < lSkinCount; ++lSkinIndex)
			{
				lClusterCount += ((FbxSkin *)(lMesh->GetDeformer(lSkinIndex, FbxDeformer::eSkin)))->GetClusterCount();
			}//�õ�lClusterCount
			*pClusterCount=lClusterCount;
		}
		//���pHasSkin
		{
			*pHasSkin=getHasDeformer(lMesh);//�˴����Ͻ�
		}
		//���pUVs��pNorms
		{
			//-------------------------------�ж�uvӳ��ģʽ�����lUVName
			const char * lUVName = NULL;
			FbxStringList lUVNames;//������ܷŵ��������������ȥ����Ϊ����lUVName��Ҫָ��lUVNames[0]��
			//���lUVNames������������������棬���Ž���ʱlUVName�����������lUVName�ɿ�����
			{
				//�Ƿ���uv
				bool mHasUV = lMesh->GetElementUVCount() > 0;
				if(mHasUV==false){
					cout<<"û��uv!"<<endl;
					return;
				}else{
					//uvӳ��ģʽ
					const FbxGeometryElementUV * lUVElement = lMesh->GetElementUV(0);
					FbxGeometryElement::EMappingMode lUVMappingMode=lUVElement->GetMappingMode();
					if(lUVMappingMode!=FbxGeometryElement::eByPolygonVertex){
						cout<<"error:uvӳ��ģʽ����eByPolygonVertex��Ŀǰ�в�֧������ģʽ!"<<endl;
						system("pause");
						exit(0);
						return;
					}else{
						//���uvSet����
						lMesh->GetUVSetNames(lUVNames);
						if (lUVNames.GetCount())
						{
							lUVName = lUVNames[0];
						}else{
							cout<<"lUVName==NULL!"<<endl;
							return;
						}
					}	
				}
			}//�õ�lUVName
			//cout<<"lUVName:"<<lUVName<<endl;
			//---------------------���pUVs
			FbxVector2 lCurrentUV;//��ʱuv
			const int triangleCount = lMesh->GetPolygonCount();
			for (int i = 0; i < triangleCount; i++)
			{
				//----���pUVs
				lMesh->GetPolygonVertexUV(i, 0, lUVName, lCurrentUV);
				pUVs[6*i]=static_cast<float>(lCurrentUV[0]);
				pUVs[6*i+1]=static_cast<float>(lCurrentUV[1]);
			
				lMesh->GetPolygonVertexUV(i, 1, lUVName, lCurrentUV);
				pUVs[6*i+2]=static_cast<float>(lCurrentUV[0]);
				pUVs[6*i+3]=static_cast<float>(lCurrentUV[1]);
				
				lMesh->GetPolygonVertexUV(i, 2, lUVName, lCurrentUV);
				pUVs[6*i+4]=static_cast<float>(lCurrentUV[0]);
				pUVs[6*i+5]=static_cast<float>(lCurrentUV[1]);
			}
			//---------------------�ж�normӳ��ģʽ
			bool mHasNormal = lMesh->GetElementNormalCount() > 0;
			if (mHasNormal)
			{
				FbxGeometryElement::EMappingMode lNormalMappingMode = lMesh->GetElementNormal(0)->GetMappingMode();
				if (lNormalMappingMode == FbxGeometryElement::eNone)
				{
					cout<<"error:û�з�������!"<<endl;
					system("pause");
					exit(0);
				}
				if (mHasNormal && lNormalMappingMode != FbxGeometryElement::eByPolygonVertex)
				{
					cout<<"error:normӳ��ģʽ����eByPolygonVertex��Ŀǰ�в�֧������ģʽ!"<<endl;
					system("pause");
					exit(0);
				}
			}
			//---------------------�󶥵㷨����(���pNorms)
	//		memset(pNorms, 0, triangleCount*3 * sizeof(FbxVector4));//����ȫ����ʼ��Ϊ0
			for (int i = 0; i < triangleCount; i++)
			{
				FbxVector4 norm0;
				FbxVector4 norm1;
				FbxVector4 norm2;
				lMesh->GetPolygonVertexNormal(i, 0, norm0);
				lMesh->GetPolygonVertexNormal(i, 1, norm1);
				lMesh->GetPolygonVertexNormal(i, 2, norm2);
				pNorms[3*i]=norm0;
				pNorms[3*i+1]=norm1;
				pNorms[3*i+2]=norm2;
			}

		}
	}

	//get mesh smoothing info
//set pCompute true to compute smoothing from normals by default 
//set pConvertToSmoothingGroup true to convert hard/soft edge info to smoothing group info by default
void Cmodelfbx::GetSmoothing(FbxManager* pSdkManager, FbxNode* pNode, bool pCompute, bool pConvertToSmoothingGroup)
{
    if(!pNode || !pSdkManager)
        return;

    //get mesh
    FbxMesh* lMesh = pNode->GetMesh();
    if(lMesh)
    {
        //print mesh node name
        FBXSDK_printf("current mesh node: %s\n", pNode->GetName());

        //if there's no smoothing info in fbx file, but you still want to get smoothing info.
        //please compute smoothing info from normals.
        //Another case to recompute smoothing info from normals is:
        //If users edit normals manually in 3ds Max or Maya and export the scene to FBX with smoothing info,
        //The smoothing info may NOT match with normals.
        //the mesh called "fbx_customNormals" in Normals.fbx is the case. All edges are hard, but normals actually represent the "soft" looking.
        //Generally, the normals in fbx file holds the smoothing result you'd like to get.
        //If you want to get correct smoothing info(smoothing group or hard/soft edges) which match with normals,
        //please drop the original smoothing info of fbx file, and recompute smoothing info from normals.
        //if you want to get soft/hard edge info, please call FbxGeometryConverter::ComputeEdgeSmoothingFromNormals().
        //if you want to get smoothing group info, please get soft/hard edge info first by ComputeEdgeSmoothingFromNormals() 
        //And then call FbxGeometryConverter::ComputePolygonSmoothingFromEdgeSmoothing().
        if(pCompute)
        {
            FbxGeometryConverter lGeometryConverter(pSdkManager);
            lGeometryConverter.ComputeEdgeSmoothingFromNormals(lMesh);
            //convert soft/hard edge info to smoothing group info
            if(pConvertToSmoothingGroup)
                lGeometryConverter.ComputePolygonSmoothingFromEdgeSmoothing(lMesh);
        }

        //if there is smoothing groups info in your fbx file, but you want to get hard/soft edges info
        //please use following code:
        //FbxGeometryConverter lGeometryConverter(lSdkManager);
        //lGeometryConverter.ComputeEdgeSmoothingFromPolygonSmoothing(lMesh);

        //get smoothing info
        FbxGeometryElementSmoothing* lSmoothingElement = lMesh->GetElementSmoothing();
        if(lSmoothingElement)
        {
		//	system("pause");
            //mapping mode is by edge. The mesh usually come from Maya, because Maya can set hard/soft edges.
            //we can get smoothing info(which edges are soft, which edges are hard) by retrieving each edge. 
            if( lSmoothingElement->GetMappingMode() == FbxGeometryElement::eByEdge )
            {
                //Let's get smoothing of each edge, since the mapping mode of smoothing element is by edge
                for(int lEdgeIndex = 0; lEdgeIndex < lMesh->GetMeshEdgeCount(); lEdgeIndex++)
                {
                    int lSmoothingIndex = 0;
                    //reference mode is direct, the smoothing index is same as edge index.
                    //get smoothing by the index of edge
                    if( lSmoothingElement->GetReferenceMode() == FbxGeometryElement::eDirect )
                        lSmoothingIndex = lEdgeIndex;

                    //reference mode is index-to-direct, get smoothing by the index-to-direct
                    if(lSmoothingElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                        lSmoothingIndex = lSmoothingElement->GetIndexArray().GetAt(lEdgeIndex);

                    //Got smoothing of each vertex.
                    int lSmoothingFlag = lSmoothingElement->GetDirectArray().GetAt(lSmoothingIndex);
              //      FBXSDK_printf("hard/soft value for edge[%d]: %d \n", lEdgeIndex, lSmoothingFlag);
                    //add your custom code here, to output smoothing or get them into a list, such as KArrayTemplate<int>
                    //. . .
                }//end for lEdgeIndex
            }//end eByEdge
            //mapping mode is by polygon. The mesh usually come from 3ds Max, because 3ds Max can set smoothing groups for polygon.
            //we can get smoothing info(smoothing group ID for each polygon) by retrieving each polygon. 
            else if(lSmoothingElement->GetMappingMode() == FbxGeometryElement::eByPolygon)
            {
                //Let's get smoothing of each polygon, since the mapping mode of smoothing element is by polygon.
                for(int lPolygonIndex = 0; lPolygonIndex < lMesh->GetPolygonCount(); lPolygonIndex++)
                {
                    int lSmoothingIndex = 0;
                    //reference mode is direct, the smoothing index is same as polygon index.
                    if( lSmoothingElement->GetReferenceMode() == FbxGeometryElement::eDirect )
                        lSmoothingIndex = lPolygonIndex;

                    //reference mode is index-to-direct, get smoothing by the index-to-direct
                    if(lSmoothingElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                        lSmoothingIndex = lSmoothingElement->GetIndexArray().GetAt(lPolygonIndex);

                    //Got smoothing of each polygon.
                    int lSmoothingFlag = lSmoothingElement->GetDirectArray().GetAt(lSmoothingIndex);
                    FBXSDK_printf("smoothing group ID for polygon[%d]: %d \n", lPolygonIndex, lSmoothingFlag);
                    //add your custom code here, to output normals or get them into a list, such as KArrayTemplate<int>
                    //. . .

                }//end for lPolygonIndex //PolygonCount

            }//end eByPolygonVertex
        }//end if lSmoothingElement
    }//end if lMesh

    //recursively traverse each node in the scene
    int i, lCount = pNode->GetChildCount();
    for (i = 0; i < lCount; i++)
    {
        GetSmoothing(pSdkManager, pNode->GetChild(i), pCompute, pConvertToSmoothingGroup);
    }
}

	void Cmodelfbx::makeOtherUserForEachNode(FbxNode* pNode,int userDataIndex_uv,int userDataIndex_norm){
		FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();
		if (lNodeAttribute//�����Խڵ�
			&&lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh//�����Խڵ�Ϊ������ΪeMesh
			)//ΪpNode��������idSubMeshSet
		{	
			makeOtherUserForThisNode(pNode,userDataIndex_uv,userDataIndex_norm);
		}
		const int lChildCount = pNode->GetChildCount();
		for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
		{
			makeOtherUserForEachNode(pNode->GetChild(lChildIndex),userDataIndex_uv,userDataIndex_norm);
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���userData
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Cmodelfbx::destroyAllUserData_and_manager(){
		destroyAllUserData();//ɾ���û��Զ�������
		DestroySdkObjects(lSdkManager);//ɾ��manager
	}
	void Cmodelfbx::destroyAllUserData(){
		//����û����������������������
		{
			const int lTextureCount = lScene->GetTextureCount();
			for (int lTextureIndex = 0; lTextureIndex < lTextureCount; ++lTextureIndex)
			{
				FbxTexture * lTexture = lScene->GetTexture(lTextureIndex);
				FbxFileTexture * lFileTexture = FbxCast<FbxFileTexture>(lTexture);
				if (lFileTexture && lFileTexture->GetUserDataPtr(userDataIndex_texture))
				{
					GLuint* texture =(static_cast<GLuint *>(lFileTexture->GetUserDataPtr(userDataIndex_texture)));
					delete texture;
				}
			}
		}
		//����ݹ��û�����
		clearUserDataRecursive(lScene->GetRootNode());
	}
	
	void Cmodelfbx::clearUserDataRecursive(FbxNode* pNode)
	{
		FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();
		if (lNodeAttribute//�����Խڵ�
			&&lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh//�����Խڵ�Ϊ������ΪeMesh
			)
		{	
			FbxMesh*lMesh=pNode->GetMesh();
			//����UV
			float*pUVs=(static_cast<float*>(lMesh->GetUserDataPtr(userDataIndex_UV)));
			if(pUVs!=NULL)delete []pUVs;
			//����Norm
			FbxVector4*pNorms=(static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Norm)));
			if(pNorms!=NULL)delete []pNorms;
			//����Vertex_deformed
			FbxVector4* lVertexArray=(static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Vertex_deformed)));
			if(lVertexArray!=NULL)delete []lVertexArray;
			//����Norm_deformed
			FbxVector4* lNormalArray=(static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Normal_deformed)));
			if(lNormalArray!=NULL)delete []lNormalArray;
			//����clusterDeformation
			FbxAMatrix*lClusterDeformation=(static_cast<FbxAMatrix*>(lMesh->GetUserDataPtr(userDataIndex_clusterDeformation)));
			if(lClusterDeformation!=NULL)delete []lClusterDeformation;
			//����clusterWeight
			double*lClusterWeight=(static_cast<double*>(lMesh->GetUserDataPtr(userDataIndex_clusterWeight)));
			if(lClusterWeight!=NULL)delete []lClusterWeight;
			//����clusterCount
			int*pClusterCount=(static_cast<int*>(lMesh->GetUserDataPtr(userDataIndex_clusterCount)));
			if(pClusterCount!=NULL)delete pClusterCount;
			//����hasSkin
			bool*pHasSkin=(static_cast<bool*>(lMesh->GetUserDataPtr(userDataIndex_hasSkin)));
			if(pHasSkin!=NULL)delete pHasSkin;
			//��������cluster���û�����
			FbxMesh* pMesh = pNode->GetMesh();
			{
				int lSkinCount = pMesh->GetDeformerCount(FbxDeformer::eSkin);
				for ( int lSkinIndex=0; lSkinIndex<lSkinCount; ++lSkinIndex)
				{
					FbxSkin * lSkinDeformer = (FbxSkin *)pMesh->GetDeformer(lSkinIndex, FbxDeformer::eSkin);

					int lClusterCount = lSkinDeformer->GetClusterCount();
					for ( int lClusterIndex=0; lClusterIndex<lClusterCount; ++lClusterIndex)
					{
						FbxCluster* pCluster = lSkinDeformer->GetCluster(lClusterIndex);
						FbxAMatrix *plClusterRelativeInitPosition=(static_cast<FbxAMatrix*>(pCluster->GetUserDataPtr(userDataIndex_clusterRelativeInitPosition)));
						if(plClusterRelativeInitPosition!=NULL)delete plClusterRelativeInitPosition;
						
					}
				}
			}
		}
		const int lChildCount = pNode->GetChildCount();
		for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
		{
			clearUserDataRecursive(pNode->GetChild(lChildIndex));
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//����
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Cmodelfbx::setTime(int t_MilliSecond){
		Time.SetMilliSeconds(t_MilliSecond);
	}
	void Cmodelfbx::selectAnimation(int iAnimationStack){
		FbxArray<FbxString*> mAnimStackNameArray;
		lScene->FillAnimStackNameArray(mAnimStackNameArray);
		const int lAnimStackCount = mAnimStackNameArray.GetCount();
		if(iAnimationStack<0||iAnimationStack>=lAnimStackCount){
			cout<<"error: ��Ч��iAnimationStackֵ!"<<endl;
			//����mAnimStackNameArray
			FbxArrayDelete(mAnimStackNameArray);
			return;
		}
		// select the base layer from the animation stack
		lCurrentAnimationStack = lScene->FindMember(FBX_TYPE(FbxAnimStack), mAnimStackNameArray[iAnimationStack]->Buffer());
		if (lCurrentAnimationStack == NULL)
		{
			// this is a problem. The anim stack should be found in the scene!
			cout<<"erorr: δ����AnimationStack!"<<endl;
			//����mAnimStackNameArray
			FbxArrayDelete(mAnimStackNameArray);
			return;
		}
		//���õ�ǰAnimationStackΪlCurrentAnimationStack
		lScene->GetEvaluator()->SetContext(lCurrentAnimationStack);
		//����˶�������ֹʱ��
		{
			FbxTime mStart,mStop;//��ֹʱ�䣨��ʱʹ�ã�
			FbxTakeInfo* lCurrentTakeInfo = lScene->GetTakeInfo(*(mAnimStackNameArray[iAnimationStack]));
			if (lCurrentTakeInfo)
			{
				mStart = lCurrentTakeInfo->mLocalTimeSpan.GetStart();
				mStop = lCurrentTakeInfo->mLocalTimeSpan.GetStop();
		//		cout<<"mStart:"<<mStart.GetMilliSeconds()<<endl;
		//		cout<<"mStop:"<<mStop.GetMilliSeconds()<<endl;


			}else{
				cout<<"û�еõ�CurrentTakeInfo"<<endl;
			}
			if(lCurrentTakeInfo==NULL//û�õ�lCurrentTakeInfo
				||mStart.GetMilliSeconds()<0//������lCurrentTakeInfo�еõ���StartΪ��ֵ
				)
			{
				// Take the time line value
				FbxTimeSpan lTimeLineTimeSpan;
				lScene->GetGlobalSettings().GetTimelineDefaultTimeSpan(lTimeLineTimeSpan);

				mStart = lTimeLineTimeSpan.GetStart();
				mStop  = lTimeLineTimeSpan.GetStop();
			}//�õ�mStart��mStop
			StartTime=mStart;
			StopTime=mStop;
		}
	//	cout<<"StartTime:"<<StartTime.GetMilliSeconds()<<endl;
	//	cout<<"StopTime:"<<StopTime.GetMilliSeconds()<<endl;
	//	cout<<"StartTime:"<<StartTime.GetSecondDouble()<<endl;
	//	cout<<"StopTime:"<<StopTime.GetSecondDouble()<<endl;
		//��Time��Ϊ��StartTimeһ��
		Time=StartTime;
		//����mAnimStackNameArray
		FbxArrayDelete(mAnimStackNameArray);

	}
	void Cmodelfbx::animationAdvance_rollback(int dms){//����ǰ��dms���룬����������Ⱦ��ƻ�
		FbxTime dTime;
		dTime.SetMilliSeconds(dms);
		Time+=dTime;
		if(Time>StopTime){
			Time=StartTime;
		}	
	}
	
	void Cmodelfbx::drawSkin(FbxNode*pNode,FbxVector4*lVertexArray,FbxVector4*lNormalArray){
	/*	if(lVertexArray==NULL)return;

		FbxMesh*lMesh=pNode->GetMesh();
		
		//����subMesh
		CidSubMeshSet*pIdSubMeshSet=(static_cast<CidSubMeshSet*>(lMesh->GetUserDataPtr(userDataIndex_idSubMeshSet)));
		float*pUVs=(static_cast<float*>(lMesh->GetUserDataPtr(userDataIndex_UV)));
		const int nidSubMesh=(int)pIdSubMeshSet->idSubMeshList.size();
		for(int i=0;i<nidSubMesh;i++){
			CidSubMesh&idSubMesh=pIdSubMeshSet->idSubMeshList[i];
			//��idSubMesh
			//������
			glBindTexture(GL_TEXTURE_2D,idSubMesh.texture);
			glBegin(GL_TRIANGLES);
			//����������
			int j=0;
			int jMul3=0;
			int nTriangle=(int)idSubMesh.polygenIndexList.size();
			for(;j<nTriangle;j++){
				const int triangleIndex=idSubMesh.polygenIndexList[j];
				//��triangleIndex��������
				//���������
				const int ID0=idSubMesh.vIDList[jMul3++];
				const int ID1=idSubMesh.vIDList[jMul3++];
				const int ID2=idSubMesh.vIDList[jMul3++];
				//��uv
				const float *u0=pUVs+triangleIndex*6;//��pUVs+triangleIndex*6
				const float *u1=u0+2;
				const float *u2=u0+4;
				//��
				glNormal3dv((double*)lNormalArray[triangleIndex*3]);
				glTexCoord2fv(u0);glVertex3dv((double*)lVertexArray[ID0]);
				glNormal3dv((double*)lNormalArray[triangleIndex*3+1]);
				glTexCoord2fv(u1);glVertex3dv((double*)lVertexArray[ID1]);
				glNormal3dv((double*)lNormalArray[triangleIndex*3+2]);
				glTexCoord2fv(u2);glVertex3dv((double*)lVertexArray[ID2]);
				
			}
			glEnd();


		}
		*/

	}
	
	void Cmodelfbx::loadTextures(const char * pFbxFileName)
	//���������ļ���·����lScene��ȡ����
	//Ȼ��ͨ��textureManager�ύ��GPU�������Դ������浽textureManager
	{
		 // Load the textures into GPU, only for file texture now
        const int lTextureCount = lScene->GetTextureCount();
        for (int lTextureIndex = 0; lTextureIndex < lTextureCount; ++lTextureIndex)
        {
            FbxTexture * lTexture = lScene->GetTexture(lTextureIndex);
            FbxFileTexture * lFileTexture = FbxCast<FbxFileTexture>(lTexture);//ֻ��ת��һ�����ͣ���ʵlFileTexture����lTexture
            if (lFileTexture && !lFileTexture->GetUserDataPtr())
            {
                // Try to load the texture from absolute path
				const char* tfilename=lFileTexture->GetFileName();
                string filename =tfilename; 
				//����׺����Ϊ.bmp
				int len=(int)filename.size();
				int iDot=-1;
				for(int i=len-1;i>=0;i--){
					if(filename[i]=='.'){
						iDot=i;
						break;
					}
				}
				if(iDot==-1){//û�ҵ�'.'
					cout<<"��Ч���ļ���!"<<endl;
			//		return;
				}else{//�ҵ�'.'
					filename=filename.substr(0,iDot);
					filename+=".bmp";
				}//��׺���Ѹ�Ϊ.bmp
				//��ǰ���·������ɾ����ֻʣ���ļ���
				{
					//�����һ��\��/
					int iBar=-1;
					int len=(int)filename.size();
					for(int i=len-1;i>=0;i--){
						if(filename[i]=='\\'||filename[i]=='/'){
							iBar=i;
							break;
						}
					}
					if(iBar==-1){//û�ҵ�\��/
						//˵��û�У����ھ��Ƿ���Ҫ���
					}else{//�ҵ�\��/
						//��\��/����ǰ����ַ���ȥ��
						filename=filename.substr(iBar+1,len-(iBar+1));
					}
				
				}
				//����Լ�Ŀ¼��·����
				{

					string pathPerfix="data\\model_fbx\\";
					//��fbxFileName����ȡ���һ���ļ���(����Ҫ��.fbxȥ��)���浽tstr
					string tstr=fbxFileName;
					{
						//�����һ��\��/
						int iBar=-1;
						int len=(int)tstr.size();
						for(int i=len-1;i>=0;i--){
							if(tstr[i]=='\\'||tstr[i]=='/'){
								iBar=i;
								break;
							}
						}
						if(iBar==-1){//û�ҵ�\��/
							//˵��û�У����ھ��Ƿ���Ҫ���
						}else{//�ҵ�\��/
							//��\��/����ǰ����ַ���ȥ��
							tstr=tstr.substr(iBar+1,len-(iBar+1));
						}
						//��tstr������ĸ��ַ�(һ����.fbx)ȥ��
						tstr=tstr.substr(0,(int)tstr.size()-4);
					}//�õ�tstr
					pathPerfix+=tstr;
					pathPerfix+="\\";
					filename=pathPerfix+filename;
				}//�õ�����������·����filename
//				cout<<filename<<endl;
				//��filename��������
				Cc3dTexture*texture=Cc3dTextureCache::sharedTextureCache()->addImage(filename.c_str());
				if(texture){
					//����������Դ������û����ݵ���ʽ����ص�lFileTexture(��lTexture)
                    lFileTexture->SetUserDataPtr(userDataIndex_texture,texture);
				}else{
					cout<<"error: create texture failed! "<<endl;
					assert(false);
				}

            }
			
        }
		//����Ƿ����ظ�����·��
		{
			bool nonSame=true;//�Ƿ������ͬ
			const int lTextureCount = lScene->GetTextureCount();
			if(lTextureCount<=1){//���������С�ڵ���1
				
			}else{//�������������1
			
				for (int i = 0; i < lTextureCount; i++)
			    {
			        FbxTexture * lTexture = lScene->GetTexture(i);
					Cc3dTexture* texture=(static_cast<Cc3dTexture*>(lTexture->GetUserDataPtr(userDataIndex_texture)));
					string texPath_i=texture->getFilePath();
					//��texPath_i����֮��ĸ�path_j�Ƚϣ��������ͬ�ߣ���˵�����ظ�
					for(int j=i+1;j<lTextureCount;j++){
						FbxTexture * lTexture = lScene->GetTexture(j);
						Cc3dTexture* texture=(static_cast<Cc3dTexture*>(lTexture->GetUserDataPtr(userDataIndex_texture)));
						string texPath_j=texture->getFilePath();
						//texPath_i��texPath_j�Ƚ�
						if(texPath_i==texPath_j){
							cout<<"����·���ظ�!"<<endl;
							cout<<texPath_i<<" "<<texPath_j<<endl;
					//		system("pause");
							nonSame=false;
							break;
						}
					}
					if(nonSame==false)break;
				}
			
			}//�õ�nonSame
			if(nonSame){
				cout<<pFbxFileName<<" ����·�����ظ�"<<endl;
			}else{
				cout<<pFbxFileName<<" ����·�����ظ�!"<<endl;
		//		system("pause");
			}
			

		}
	
	}
	
    // Triangulate all NURBS, patch and mesh under this node recursively.
    void Cmodelfbx::TriangulateRecursive(FbxNode* pNode)
    {
        FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();

        if (lNodeAttribute)
        {
            if (lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh ||
                lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eNurbs ||
                lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eNurbsSurface ||
                lNodeAttribute->GetAttributeType() == FbxNodeAttribute::ePatch)
            {
                FbxGeometryConverter lConverter(pNode->GetFbxManager());
                lConverter.TriangulateInPlace(pNode);
            }
        }

        const int lChildCount = pNode->GetChildCount();
        for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
        {
            TriangulateRecursive(pNode->GetChild(lChildIndex));
        }
    }

	void Cmodelfbx::show(){
	//	cout<<"--------"<<endl;
		glColor3f(1,1,1);
		//������תfbx����
		glPushMatrix();
		//����fbx����
		{
			if(lCurrentAnimationStack!=NULL){
				//���mCurrentAnimLayer
				// we assume that the first animation layer connected to the animation stack is the base layer
				// (this is the assumption made in the FBXSDK)
				FbxAnimLayer *mCurrentAnimLayer = lCurrentAnimationStack->GetMember(FBX_TYPE(FbxAnimLayer), 0);
				//���pose
				int mPoseIndex=-1;//������lPose��NULL�������趨�˴�Ϊ-1
				FbxPose * lPose = NULL;
			    if (mPoseIndex != -1)
				{
					 lPose = lScene->GetPose(mPoseIndex);
				}
				//����lDummyGlobalPosition
				FbxAMatrix lDummyGlobalPosition;//ģ�͵�����λ�ã�Ĭ�Ϲ���Ϊ��λ����
				DrawNodeRecursive(lScene->GetRootNode(), Time, mCurrentAnimLayer, lDummyGlobalPosition,lPose);
			}
		}
		//��ջ
		glPopMatrix();
	
	}
	
	// Draw recursively each node of the scene. To avoid recomputing 
	// uselessly the global positions, the global position of each 
	// node is passed to it's children while browsing the node tree.
	// If the node is part of the given pose for the current scene,
	// it will be drawn at the position specified in the pose, Otherwise
	// it will be drawn at the given time.
	void Cmodelfbx::DrawNodeRecursive(FbxNode* pNode, FbxTime& pTime, FbxAnimLayer* pAnimLayer,
		FbxAMatrix& pParentGlobalPosition, FbxPose* pPose)
	{
		FbxAMatrix lGlobalPosition = GetGlobalPosition(pNode, pTime,pPose, &pParentGlobalPosition);

		if (pNode->GetNodeAttribute())
		{
			// Geometry offset.
			// it is not inherited by the children.
			  FbxAMatrix lGeometryOffset = GetGeometry(pNode);
			  FbxAMatrix lGlobalOffPosition = lGlobalPosition * lGeometryOffset;

			DrawNode(pNode, pTime, pAnimLayer, pParentGlobalPosition,lGlobalOffPosition,pPose);
		}

		const int lChildCount = pNode->GetChildCount();
		for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
		{
			DrawNodeRecursive(pNode->GetChild(lChildIndex), pTime, pAnimLayer, lGlobalPosition,pPose);
		}
	}
	

	// Get the global position of the node for the current pose.
	// If the specified node is not part of the pose or no pose is specified, get its
	// global position at the current time.
	FbxAMatrix Cmodelfbx::GetGlobalPosition(FbxNode* pNode, const FbxTime& pTime,FbxPose* pPose, FbxAMatrix* pParentGlobalPosition)
	{
		FbxAMatrix lGlobalPosition;
		bool        lPositionFound = false;

		if (pPose)
		{
			int lNodeIndex = pPose->Find(pNode);

			if (lNodeIndex > -1)
			{
				// The bind pose is always a global matrix.
				// If we have a rest pose, we need to check if it is
				// stored in global or local space.
				if (pPose->IsBindPose() || !pPose->IsLocalMatrix(lNodeIndex))
				{
					lGlobalPosition = GetPoseMatrix(pPose, lNodeIndex);
				}
				else
				{
					// We have a local matrix, we need to convert it to
					// a global space matrix.
					FbxAMatrix lParentGlobalPosition;

					if (pParentGlobalPosition)
					{
						lParentGlobalPosition = *pParentGlobalPosition;
					}
					else
					{
						if (pNode->GetParent())
						{
							lParentGlobalPosition = GetGlobalPosition(pNode->GetParent(), pTime, pPose);
						}
					}

					FbxAMatrix lLocalPosition = GetPoseMatrix(pPose, lNodeIndex);
					lGlobalPosition = lParentGlobalPosition * lLocalPosition;
				}

				lPositionFound = true;
			}
		}

		if (!lPositionFound)
		{
			// There is no pose entry for that node, get the current global position instead.

			// Ideally this would use parent global position and local position to compute the global position.
			// Unfortunately the equation 
			//    lGlobalPosition = pParentGlobalPosition * lLocalPosition
			// does not hold when inheritance type is other than "Parent" (RSrs).
			// To compute the parent rotation and scaling is tricky in the RrSs and Rrs cases.
			lGlobalPosition = pNode->EvaluateGlobalTransform(pTime);
		}

		return lGlobalPosition;
	}

	// Get the matrix of the given pose
	FbxAMatrix Cmodelfbx::GetPoseMatrix(FbxPose* pPose, int pNodeIndex)
	{
		FbxAMatrix lPoseMatrix;
		FbxMatrix lMatrix = pPose->GetMatrix(pNodeIndex);

		memcpy((double*)lPoseMatrix, (double*)lMatrix, sizeof(lMatrix.mData));

		return lPoseMatrix;
	}

	// Get the geometry offset to a node. It is never inherited by the children.
	FbxAMatrix Cmodelfbx::GetGeometry(FbxNode* pNode)
	{
		const FbxVector4 lT = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		const FbxVector4 lR = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
		const FbxVector4 lS = pNode->GetGeometricScaling(FbxNode::eSourcePivot);

		return FbxAMatrix(lT, lR, lS);
	}
	// Draw the node following the content of it's node attribute.
	void Cmodelfbx::DrawNode(FbxNode* pNode, 
		FbxTime& pTime, 
		FbxAnimLayer* pAnimLayer,
		FbxAMatrix& pParentGlobalPosition,
		FbxAMatrix& pGlobalPosition,
		FbxPose* pPose)
	{
		FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();

		if (lNodeAttribute)
		{
			const FbxNodeAttribute::EType&attributeType=lNodeAttribute->GetAttributeType();
			// All lights has been processed before the whole scene because they influence every geometry.
			switch(attributeType){
			case FbxNodeAttribute::eMesh:
				// NURBS and patch have been converted into triangluation meshes.
				{
					DrawMesh(pNode, pTime, pAnimLayer, pGlobalPosition, pPose);
				}
				break;
		/*
			case FbxNodeAttribute::eMarker:
				{
				//	DrawMarker(pGlobalPosition);
				}
				break;
			case FbxNodeAttribute::eSkeleton:
				{
					//����ڵ���ģ��ʱӦ�������Ա�۲��������Ƥ�Ƿ��Ǻϣ���������ʾʱӦ�ر��Խ�ʡ������
		//			DrawSkeleton(pNode, pParentGlobalPosition, pGlobalPosition);
				}
				break;
			case FbxNodeAttribute::eCamera:
				{
			//		DrawCamera(pNode, pTime, pAnimLayer, pGlobalPosition);
				}
				break;
			case FbxNodeAttribute::eNull:
				{
			//		DrawNull(pGlobalPosition);
				}
				break;*/
			}
		}
		else
		{
			// Draw a Null for nodes without attribute.
	//		DrawNull(pGlobalPosition);
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Skeleton
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Draw a limb between the node and its parent.
	void Cmodelfbx::DrawSkeleton(FbxNode* pNode, FbxAMatrix& pParentGlobalPosition, FbxAMatrix& pGlobalPosition)
	{
		FbxSkeleton* lSkeleton = (FbxSkeleton*) pNode->GetNodeAttribute();

		// Only draw the skeleton if it's a limb node and if 
		// the parent also has an attribute of type skeleton.
		if (lSkeleton->GetSkeletonType() == FbxSkeleton::eLimbNode &&
			pNode->GetParent() &&
			pNode->GetParent()->GetNodeAttribute() &&
			pNode->GetParent()->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			GlDrawLimbNode(pParentGlobalPosition, pGlobalPosition); 
		}
	}
	void Cmodelfbx::GlDrawLimbNode(FbxAMatrix& pGlobalBasePosition, FbxAMatrix& pGlobalEndPosition)
	{
		glColor3f(1.0, 0.0, 0.0);
		glLineWidth(2.0);

		glBegin(GL_LINES);

		glVertex3dv((GLdouble *)pGlobalBasePosition.GetT());
		glVertex3dv((GLdouble *)pGlobalEndPosition.GetT());

		glEnd();
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//mesh
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// Draw the vertices of a mesh.
	void Cmodelfbx::DrawMesh(FbxNode* pNode, FbxTime& pTime, FbxAnimLayer* pAnimLayer,
		FbxAMatrix& pGlobalPosition, FbxPose* pPose)
	{
		FbxMesh* lMesh = pNode->GetMesh();
		const int lVertexCount = lMesh->GetControlPointsCount();
		const int triangleCount = lMesh->GetPolygonCount();
		// No vertex to draw.
		if (lVertexCount == 0)
		{
			return;
		}
		//���hasSkin
		bool*pHasSkin=(static_cast<bool*>(lMesh->GetUserDataPtr(userDataIndex_hasSkin)));
		//��ñ��ζ���ͷ����б�
		FbxVector4* lVertexArray=NULL;
		FbxVector4* lNormalArray=NULL;
		if(*pHasSkin){//�����skin
			//��ȡ�����б�
			lVertexArray=(static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Vertex_deformed)));
			//����ԭʼ����
			memcpy(lVertexArray, lMesh->GetControlPoints(), lVertexCount * sizeof(FbxVector4));
			//��ȡ�����б�
			lNormalArray=(static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Normal_deformed)));;
			//����ԭʼ����
			FbxVector4*lNormalArray_original=(static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Norm)));
			memcpy(lNormalArray, lNormalArray_original, triangleCount*3 * sizeof(FbxVector4));
		}else{//���û��skin
			//ֱ��ʹ��ԭʼ���ݵ�����
			lVertexArray = lMesh->GetControlPoints();
			lNormalArray = (static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Norm)));
		}
		
		//�����ζ���ͷ����б�
		if (*pHasSkin)//�����skin
		{
			//���clusterCount
			int*pClusterCount=(static_cast<int*>(lMesh->GetUserDataPtr(userDataIndex_clusterCount)));
			if (*pClusterCount)
			{
				// Deform the vertex array with the skin deformer.
				ComputeSkinDeformation(pGlobalPosition, lMesh, pTime, lVertexArray,lNormalArray,pPose);
			}


		}
		glPushMatrix();
		glMultMatrixd((const double*)pGlobalPosition);
		//����Ƥ
		{
			drawSkin(pNode,lVertexArray,lNormalArray);
		}
		glPopMatrix();

	}
	// Deform the vertex array according to the links contained in the mesh and the skinning type.
	void Cmodelfbx::ComputeSkinDeformation(FbxAMatrix& pGlobalPosition, 
		FbxMesh* pMesh, 
		FbxTime& pTime, 
		FbxVector4* pVertexArray,
		FbxVector4* pNormalArray,
		FbxPose* pPose)
	{
		FbxSkin * lSkinDeformer = (FbxSkin *)pMesh->GetDeformer(0, FbxDeformer::eSkin);
		FbxSkin::EType lSkinningType = lSkinDeformer->GetSkinningType();

		if(lSkinningType == FbxSkin::eLinear || lSkinningType == FbxSkin::eRigid)
		{
			ComputeLinearDeformation_simplify(pGlobalPosition, pMesh, pTime, pVertexArray,pNormalArray, pPose);
		//	//��������������������Ӧ����������䣬��Ч�ʻ���������
		//	ComputeLinearDeformation_unsimplify(pGlobalPosition, pMesh, pTime, pVertexArray,pNormalArray, pPose);
			
		}
	/*	else if(lSkinningType == FbxSkin::eDualQuaternion)
		{
			ComputeDualQuaternionDeformation(pGlobalPosition, pMesh, pTime, pVertexArray, pPose);
		}
		else if(lSkinningType == FbxSkin::eBlend)
		{
			int lVertexCount = pMesh->GetControlPointsCount();

			FbxVector4* lVertexArrayLinear = new FbxVector4[lVertexCount];
			memcpy(lVertexArrayLinear, pMesh->GetControlPoints(), lVertexCount * sizeof(FbxVector4));

			FbxVector4* lVertexArrayDQ = new FbxVector4[lVertexCount];
			memcpy(lVertexArrayDQ, pMesh->GetControlPoints(), lVertexCount * sizeof(FbxVector4));

			ComputeLinearDeformation(pGlobalPosition, pMesh, pTime, lVertexArrayLinear, pPose);
			ComputeDualQuaternionDeformation(pGlobalPosition, pMesh, pTime, lVertexArrayDQ, pPose);

			// To blend the skinning according to the blend weights
			// Final vertex = DQSVertex * blend weight + LinearVertex * (1- blend weight)
			// DQSVertex: vertex that is deformed by dual quaternion skinning method;
			// LinearVertex: vertex that is deformed by classic linear skinning method;
			int lBlendWeightsCount = lSkinDeformer->GetControlPointIndicesCount();
			for(int lBWIndex = 0; lBWIndex<lBlendWeightsCount; ++lBWIndex)
			{
				double lBlendWeight = lSkinDeformer->GetControlPointBlendWeights()[lBWIndex];
				pVertexArray[lBWIndex] = lVertexArrayDQ[lBWIndex] * lBlendWeight + lVertexArrayLinear[lBWIndex] * (1 - lBlendWeight);
			}
		}*/
	}
	


	
	// Deform the vertex array in classic linear way.�򻯰汾
	void Cmodelfbx::ComputeLinearDeformation_simplify(FbxAMatrix& pGlobalPosition, 
		FbxMesh* pMesh, 
		FbxTime& pTime, 
		FbxVector4* pVertexArray,
		FbxVector4* pNormalArray,
		FbxPose* pPose)
	{
		
		//���滨�����е�����ֻ�ڵ���ʱ����
		{
			// All the links must have the same link mode.
			FbxCluster::ELinkMode lClusterMode = ((FbxSkin*)pMesh->GetDeformer(0, FbxDeformer::eSkin))->GetCluster(0)->GetLinkMode();
			if(lClusterMode!=FbxCluster::eNormalize){
				cout<<"error:lClusterMode!=eNormalize��Ŀǰֻ֧��eNormalize"<<endl;
				assert(false);
				//  (1) lClusterMode == FbxCluster::eNormalize:
				//	normalized link mode, a vertex is always totally influenced by the links.
				//  ����link���������Դ˶����Ӱ��Ȩ��֮��Ϊ1
				//  (2) lClusterMode == FbxCluster::eTotalOne:
				//	total 1 link mode, a vertex can be partially influenced by the links. 
				//  ����link���������Դ˶����Ӱ��Ȩ��֮��totalLinksWeight����1������1-totalLinksWeight��������
				
			}
		}
		int lVertexCount = pMesh->GetControlPointsCount();
		FbxAMatrix*lClusterDeformation=(static_cast<FbxAMatrix*>(pMesh->GetUserDataPtr(userDataIndex_clusterDeformation)));
		memset(lClusterDeformation, 0, lVertexCount * sizeof(FbxAMatrix));

		double*lClusterWeight=(static_cast<double*>(pMesh->GetUserDataPtr(userDataIndex_clusterWeight)));
		memset(lClusterWeight, 0, lVertexCount * sizeof(double));

		// For all skins and all clusters, accumulate their deformation and weight
		// on each vertices and store them in lClusterDeformation and lClusterWeight.
		int lSkinCount = pMesh->GetDeformerCount(FbxDeformer::eSkin);
		//��ʵֻ�����һ��skin����
		if(lSkinCount>1){//�������һ��skin����һ������
			cout<<"warning:���ж���һ��skin��ֻ�����һ��skin"<<endl;
			lSkinCount=1;//ǿ��ֻ�����һ��skin��������ʡ������
		}
		
		for ( int lSkinIndex=0; lSkinIndex<lSkinCount; ++lSkinIndex)
		{
			FbxSkin * lSkinDeformer = (FbxSkin *)pMesh->GetDeformer(lSkinIndex, FbxDeformer::eSkin);

			int lClusterCount = lSkinDeformer->GetClusterCount();//ÿ��cluster��Ӧһ�����������Դ�ֵҲ�ǹ�����
			for ( int lClusterIndex=0; lClusterIndex<lClusterCount; ++lClusterIndex)
			{
				FbxCluster* lCluster = lSkinDeformer->GetCluster(lClusterIndex);
				if (!lCluster->GetLink())
					continue;

				FbxAMatrix lVertexTransformMatrix;
				ComputeClusterDeformation(pGlobalPosition, pMesh, lCluster, lVertexTransformMatrix, pTime, pPose);
				               
				int lVertexIndexCount = lCluster->GetControlPointIndicesCount();
				int* clusterControlPointIndices=lCluster->GetControlPointIndices();//cluster�Ķ���������
				double* clusterControlPointWeights= lCluster->GetControlPointWeights();//cluster�Ķ���Ȩ�ر�
				for (int k = 0; k < lVertexIndexCount; ++k) 
				{            
					int lIndex = clusterControlPointIndices[k];

					// Sometimes, the mesh can have less points than at the time of the skinning
					// because a smooth operator was active when skinning but has been deactivated during export.
					if (lIndex >= lVertexCount)
						continue;

					double lWeight = clusterControlPointWeights[k];

					if (lWeight == 0.0)
					{
						continue;
					}

					// Compute the influence of the link on the vertex.
					FbxAMatrix lInfluence = lVertexTransformMatrix;
					MatrixScale(lInfluence, lWeight);//�õ�lInfluence���󣬼���cluster(������Ĺ���)�ı任���������Դ˽�Ȩ��
					{
						// Add to the sum of the deformations on the vertex.
						MatrixAdd(lClusterDeformation[lIndex], lInfluence);

						// Add to the sum of weights to either normalize or complete the vertex.
						lClusterWeight[lIndex] += lWeight;
					}
				}//For each vertex			
			}//lClusterCount
		}

		//Actually deform each vertices here by information stored in lClusterDeformation and lClusterWeight
		for (int i = 0; i < lVertexCount; i++) 
		{
			// Deform the vertex if there was at least a link with an influence on the vertex,
			if (lClusterWeight[i] != 0.0) 
			{
				//�任����
				{
					pVertexArray[i] = lClusterDeformation[i].MultT(pVertexArray[i]);
					
				}
			
			} 
		}
		int polygonCount=pMesh->GetPolygonCount();
		for(int i=0;i<polygonCount;i++){
			//������������
			for(int j=0;j<3;j++){
				int vID=pMesh->GetPolygonVertex(i,j);//��ǰ����ID
			//	cout<<"i j:"<<i<<" "<<j<<endl;
				//�任������
				if(lClusterWeight[vID] != 0.0){
					prodv_lastRow0001_wZero(lClusterDeformation[vID],pNormalArray[3*i+j],pNormalArray[3*i+j]);
				}
			}
		}
	}
	
	void Cmodelfbx::prodv_lastRow0001_wZero(const FbxAMatrix&matrix,const FbxVector4&in,FbxVector4&out)
	//��mΪFbxAMatrix
	//double*pm=(double*)m
	//��pm��ȫ��ͬ��opengl�е�double[16],������²���:
	// pm[0] pm[4] pm[8]  pm[12]
	// pm[1] pm[5] pm[9]  pm[13]
	// pm[2] pm[6] pm[10] pm[14]
	// pm[3] pm[7] pm[11] pm[15]
	//����(pm[12],pm[13],pm[14],pm[15])Ϊƽ�Ʒ���(x,y,z,1)
	//���������������ת����ֱ��ʹ��m����
	//               m[0][0] m[0][1] m[0][2]   pm[0]  pm[1]  pm[2]  pm[3]
	// FbxAMatrix m= m[0][0] m[0][1] m[0][2] = pm[4]  pm[5]  pm[6]  pm[7]
	//				 m[0][0] m[0][1] m[0][2]   pm[8]  pm[9]  pm[10] pm[11]
	//               m[0][0] m[0][1] m[0][2]   pm[12] pm[13] pm[14] pm[15]
	//ע��˴�pm�����������pm�������������෴
	{//in��out������ͬһ����
		const double* pmatrix=(const double*)matrix;
		const double* pin=(const double*)in;
		double _out[4];//��ʱ��ת
		//ע�⣬������pmatrix,pin������Ҫ����matrix��in
		_out[0]=pin[0]*pmatrix[0]+pin[1]*pmatrix[4]+pin[2]*pmatrix[8];
		_out[1]=pin[0]*pmatrix[1]+pin[1]*pmatrix[5]+pin[2]*pmatrix[9];
		_out[2]=pin[0]*pmatrix[2]+pin[1]*pmatrix[6]+pin[2]*pmatrix[10];
		_out[3]=0;
		out=_out;
	}

	// Scale all the elements of a matrix.
	void Cmodelfbx::MatrixScale(FbxAMatrix& pMatrix, double pValue)
	{
		int i,j;

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				pMatrix[i][j] *= pValue;
			}
		}
	}

	// Add a value to all the elements in the diagonal of the matrix.
	void Cmodelfbx::MatrixAddToDiagonal(FbxAMatrix& pMatrix, double pValue)
	{
		pMatrix[0][0] += pValue;
		pMatrix[1][1] += pValue;
		pMatrix[2][2] += pValue;
		pMatrix[3][3] += pValue;
	}


	// Sum two matrices element by element.
	void Cmodelfbx::MatrixAdd(FbxAMatrix& pDstMatrix, FbxAMatrix& pSrcMatrix)
	{
		int i,j;

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				pDstMatrix[i][j] += pSrcMatrix[i][j];
			}
		}
	}

	
//Compute the transform matrix that the cluster will transform the vertex.
	void Cmodelfbx::ComputeClusterDeformation(FbxAMatrix& pGlobalPosition, 
		FbxMesh* pMesh,
		FbxCluster* pCluster, 
		FbxAMatrix& pVertexTransformMatrix,
		FbxTime pTime,
		FbxPose* pPose)
	{
		FbxCluster::ELinkMode lClusterMode = pCluster->GetLinkMode();

		FbxAMatrix lReferenceGlobalInitPosition;
		FbxAMatrix lReferenceGlobalCurrentPosition;
		
		FbxAMatrix lClusterGlobalInitPosition;
		FbxAMatrix lClusterGlobalCurrentPosition;

		FbxAMatrix lReferenceGeometry;

		FbxAMatrix lClusterRelativeInitPosition;
		FbxAMatrix lClusterRelativeCurrentPositionInverse;
		//����lClusterRelativeInitPosition
		{
			//�ȿ����ܲ��ܴ��û������л�ȡ
			FbxAMatrix *plClusterRelativeInitPosition=(static_cast<FbxAMatrix*>(pCluster->GetUserDataPtr(userDataIndex_clusterRelativeInitPosition)));
			if(plClusterRelativeInitPosition){//��ȡ�ɹ�
		//		cout<<"succ"<<endl;
				lClusterRelativeInitPosition=*plClusterRelativeInitPosition;
			}else{
		//		cout<<"fail"<<endl;
				pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
				//Multiply lReferenceGlobalInitPosition by Geometric Transformation
				lReferenceGeometry = GetGeometry(pMesh->GetNode());
				lReferenceGlobalInitPosition *= lReferenceGeometry;
				// Get the link initial global position.
				pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
				// Compute the initial position of the link relative to the reference.
				lClusterRelativeInitPosition = lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;
				//��lClusterRelativeInitPosition��ӵ�pCluster�ڵ�
				FbxAMatrix *plClusterRelativeInitPosition=new FbxAMatrix(lClusterRelativeInitPosition);
				pCluster->SetUserDataPtr(userDataIndex_clusterRelativeInitPosition,plClusterRelativeInitPosition);

			}
		}
		//����lClusterRelativeCurrentPositionInverse
		{
			lReferenceGlobalCurrentPosition = pGlobalPosition;
			// Get the link current global position.
			lClusterGlobalCurrentPosition = GetGlobalPosition(pCluster->GetLink(), pTime, pPose,NULL);
			// Compute the current position of the link relative to the reference.
			lClusterRelativeCurrentPositionInverse = lReferenceGlobalCurrentPosition.Inverse() * lClusterGlobalCurrentPosition;

		}
		// Compute the shift of the link relative to the reference.
		pVertexTransformMatrix = lClusterRelativeCurrentPositionInverse * lClusterRelativeInitPosition;


	}                 