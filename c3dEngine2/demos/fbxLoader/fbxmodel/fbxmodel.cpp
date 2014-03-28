#include "fbxmodel.h"

	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//初始化
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Cmodelfbx::Init_and_load(char* _fbxFileName){
		fbxFileName=_fbxFileName;
		cout<<"加载\"";
		cout<<fbxFileName;
		cout<<"\":";
		//加载fbx场景
		InitializeSdkObjects(lSdkManager,lScene);
		LoadScene(lSdkManager,lScene,fbxFileName);
		cout<<"完成!"<<endl;
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
//系统自带语句			FBXSDK_printf("FBX SDK version %s\n\n", pSdkManager->GetVersion());
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
//系统自带语句			FBXSDK_printf("Call to FbxImporter::Initialize() failed.\n");
//系统自带语句			FBXSDK_printf("Error returned: %s\n\n", lImporter->GetLastErrorString());

			if (lImporter->GetLastErrorID() == FbxIOBase::eFileVersionNotSupportedYet ||
				lImporter->GetLastErrorID() == FbxIOBase::eFileVersionNotSupportedAnymore)
			{
//系统自带语句				FBXSDK_printf("FBX version number for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
//系统自带语句				FBXSDK_printf("FBX version number for file %s is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
			}

			return false;
		}



//系统自带语句		FBXSDK_printf("FBX version number for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

		if (lImporter->IsFBX())
		{
//系统自带语句			FBXSDK_printf("FBX version number for file %s is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);

			// From this point, it is possible to access animation stack information without
			// the expense of loading the entire file.

//系统自带语句			FBXSDK_printf("Animation Stack Information\n");

			lAnimStackCount = lImporter->GetAnimStackCount();

//系统自带语句			FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
//系统自带语句			FBXSDK_printf("    Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
//系统自带语句			FBXSDK_printf("\n");

			for(i = 0; i < lAnimStackCount; i++)
			{
				FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

//系统自带语句				FBXSDK_printf("    Animation Stack %d\n", i);
//系统自带语句				FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
//系统自带语句				FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

				// Change the value of the import name if the animation stack should be imported 
				// under a different name.
//系统自带语句				FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

				// Set the value of the import state to false if the animation stack should be not
				// be imported. 
//系统自带语句				FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
//系统自带语句				FBXSDK_printf("\n");
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

	void Cmodelfbx::DestroySdkObjects(FbxManager* &pSdkManager)//一定要传指针的引用，因为需要将指针置NULL
	{
		// Delete the FBX SDK manager. All the objects that have been allocated 
		// using the FBX SDK manager and that haven't been explicitly destroyed 
		// are automatically destroyed at the same time.
		if (pSdkManager) pSdkManager->Destroy();
		pSdkManager = NULL;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//预处理
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
		//将mesh添加到lMesh节点
		lMesh->SetUserDataPtr(userDataIndex,mesh);
		//制作mesh
		//每个材质对应一个subMesh
		{
			
			//获得材质索引表
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
			//获得材质索引表长度
			const int MaterialIndiceCount=lMaterialIndice->GetCount();
			if(MaterialIndiceCount==0){
				cout<<"error: MaterialIndiceCount==0 !"<<endl;
				return;
			}
	
			//-------------------------------判断uv映射模式及获得lUVName
			const char * lUVName = NULL;
			FbxStringList lUVNames;//这个不能放到下面的括号里面去，因为将来lUVName是要指向lUVNames[0]的
			//如果lUVNames放在了下面的括号里面，括号结束时lUVName被析构，造成lUVName成空引用
			{
				//是否有uv
				bool mHasUV = lMesh->GetElementUVCount() > 0;
				if(mHasUV==false){
					cout<<"没有uv!"<<endl;
					return;
				}else{
					//uv映射模式
					const FbxGeometryElementUV * lUVElement = lMesh->GetElementUV(0);
					FbxGeometryElement::EMappingMode lUVMappingMode=lUVElement->GetMappingMode();
					if(lUVMappingMode!=FbxGeometryElement::eByPolygonVertex){
						cout<<"error:uv映射模式不是eByPolygonVertex，目前尚不支持其它模式!"<<endl;
						system("pause");
						exit(0);
						return;
					}else{
						//获得uvSet名称
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
			}//得到lUVName
			//cout<<"lUVName:"<<lUVName<<endl;
			//---------------------判断norm映射模式
			bool mHasNormal = lMesh->GetElementNormalCount() > 0;
			if (mHasNormal)
			{
				FbxGeometryElement::EMappingMode lNormalMappingMode = lMesh->GetElementNormal(0)->GetMappingMode();
				if (lNormalMappingMode == FbxGeometryElement::eNone)
				{
					cout<<"error:没有法向数据!"<<endl;
					system("pause");
					exit(0);
				}
				if (mHasNormal && lNormalMappingMode != FbxGeometryElement::eByPolygonVertex)
				{
					cout<<"error:norm映射模式不是eByPolygonVertex，目前尚不支持其它模式!"<<endl;
					system("pause");
					exit(0);
				}
			}
			//-------------
			//求材质索引最大值
			int maxMaterialIndex=-1;
			for(int i=0;i<MaterialIndiceCount;i++){
				int curMaterialIndex=lMaterialIndice->GetAt(i);
				if(curMaterialIndex>maxMaterialIndex){
					maxMaterialIndex=curMaterialIndex;
				}
			}//得到maxMaterialIndex
			if(maxMaterialIndex==-1){
				cout<<"error: maxMaterialIndex==-1"<<endl;
				return;
			}
			//生成subMesh列表（每个材质生成一个subMesh）
			vector<Cc3dSubMesh*> subMeshList;
			for(int i=0;i<MaterialIndiceCount;i++){
				Cc3dSubMesh*subMesh=new Cc3dSubMesh();
				subMesh->autorelease();
				subMesh->init();
				subMeshList.push_back(subMesh);
			}
			//为各subMesh填充纹理
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
			//遍历各多边形,填充到subMesh
			const int triangleCount = lMesh->GetPolygonCount();
			for (int i = 0; i < triangleCount; i++)
			{
				//当前多边形号：i
				Cc3dSubMesh*subMesh=subMeshList[i];
				//----获得uv
				FbxVector2 uv0;
				FbxVector2 uv1;
				FbxVector2 uv2;
				lMesh->GetPolygonVertexUV(i, 0, lUVName, uv0);
				lMesh->GetPolygonVertexUV(i, 1, lUVName, uv1);
				lMesh->GetPolygonVertexUV(i, 2, lUVName, uv2);
				//----获得法向量
				FbxVector4 norm0;
				FbxVector4 norm1;
				FbxVector4 norm2;
				lMesh->GetPolygonVertexNormal(i, 0, norm0);
				lMesh->GetPolygonVertexNormal(i, 1, norm1);
				lMesh->GetPolygonVertexNormal(i, 2, norm2);
				norm0[3]=0;
				norm1[3]=0;
				norm2[3]=0;
				//----顶点
				FbxVector4 pos0=lMesh->GetControlPoints()[lMesh->GetPolygonVertex(i,0)];
				FbxVector4 pos1=lMesh->GetControlPoints()[lMesh->GetPolygonVertex(i,1)];
				FbxVector4 pos2=lMesh->GetControlPoints()[lMesh->GetPolygonVertex(i,2)];
				pos0[3]=1;
				pos1[3]=1;
				pos2[3]=1;
				//----由uv,norm,pos合成顶点
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
			//将subMeshList中所有mesh添加到mesh
			int nSubMesh=(int)subMeshList.size();
			for(int i=0;i<nSubMesh;i++){
				mesh->addSubMesh(subMeshList[i]);
			}
		}
		//将mesh添加到this
		this->addMesh(mesh);
	

		

	}
	void Cmodelfbx::makeSubMeshSetForEachNode(FbxNode* pNode,int userDataIndex)
	{
		FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();
		if (lNodeAttribute//有属性节点
			&&lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh//且属性节点为的类型为eMesh
			)//为pNode制作并绑定idSubMeshSet
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
		//获得mesh
		FbxMesh*lMesh=pNode->GetMesh();
		if(!lMesh){
			cout<<"error: lMesh==NULL!"<<endl;
			return;
		}
		//获得多边形个数
		const int triangleCount = lMesh->GetPolygonCount();
		//获得顶点个数
		const int lVertexCount = lMesh->GetControlPointsCount();
		//为pUVs和pNorms开辟空间
		float*pUVs=new float[triangleCount*3*2];//(pUVs[6*i],pUVs[6*i+1])为i号三角形第一个顶点的uv坐标
									   	  //(pUVs[6*i+2],pUVs[6*i+3])为i号三角形第二个顶点的uv坐标
										  //(pUVs[6*i+4],pUVs[6*i+5])为i号三角形第三个顶点的uv坐标
		FbxVector4*pNorms=new FbxVector4[triangleCount*3];//pNorms[3*i]为i号三角形第一个顶点的norm
															//pNorms[3*i+1]为i号三角形第二个顶点的norm
															//pNorms[3*i+2]为i号三角形第三个顶点的norm
		//为clusterCount,hasSkin开辟空间
		int*pClusterCount=new int;
		bool*pHasSkin=new bool;
		//为lVertexArray，lNormalArray，lClusterDeformation，lClusterWeight开辟空间
		FbxVector4* lVertexArray= NULL;
		FbxVector4* lNormalArray= NULL;
		FbxAMatrix* lClusterDeformation=NULL;
		double* lClusterWeight=NULL;
		//开辟空间
		{
			if (lVertexCount == 0){
				//各指针均保持为NULL
			}else{//lVertexCount!=0
				//仅当有蒙皮时才生成（为的是不破坏原数据，否则可以直接用原始数据的引用）
				if(getHasDeformer(lMesh)){
					lVertexArray = new FbxVector4[lVertexCount];
					lNormalArray = new FbxVector4[3*triangleCount];
					lClusterDeformation = new FbxAMatrix[lVertexCount];
					lClusterWeight = new double[lVertexCount];
				}
			}
		}

		//添加到lMesh节点
		lMesh->SetUserDataPtr(userDataIndex_uv,pUVs);
		lMesh->SetUserDataPtr(userDataIndex_norm,pNorms);
		lMesh->SetUserDataPtr(userDataIndex_clusterCount,pClusterCount);
		lMesh->SetUserDataPtr(userDataIndex_hasSkin,pHasSkin);
		lMesh->SetUserDataPtr(userDataIndex_Vertex_deformed,lVertexArray);
		lMesh->SetUserDataPtr(userDataIndex_Normal_deformed,lNormalArray);
		lMesh->SetUserDataPtr(userDataIndex_clusterDeformation,lClusterDeformation);
		lMesh->SetUserDataPtr(userDataIndex_clusterWeight,lClusterWeight);
		//填充pCLusterCount
		{
			//we need to get the number of clusters
			const int lSkinCount = lMesh->GetDeformerCount(FbxDeformer::eSkin);
			int lClusterCount = 0;
			for (int lSkinIndex = 0; lSkinIndex < lSkinCount; ++lSkinIndex)
			{
				lClusterCount += ((FbxSkin *)(lMesh->GetDeformer(lSkinIndex, FbxDeformer::eSkin)))->GetClusterCount();
			}//得到lClusterCount
			*pClusterCount=lClusterCount;
		}
		//填充pHasSkin
		{
			*pHasSkin=getHasDeformer(lMesh);//此处不严谨
		}
		//填充pUVs和pNorms
		{
			//-------------------------------判断uv映射模式及获得lUVName
			const char * lUVName = NULL;
			FbxStringList lUVNames;//这个不能放到下面的括号里面去，因为将来lUVName是要指向lUVNames[0]的
			//如果lUVNames放在了下面的括号里面，括号结束时lUVName被析构，造成lUVName成空引用
			{
				//是否有uv
				bool mHasUV = lMesh->GetElementUVCount() > 0;
				if(mHasUV==false){
					cout<<"没有uv!"<<endl;
					return;
				}else{
					//uv映射模式
					const FbxGeometryElementUV * lUVElement = lMesh->GetElementUV(0);
					FbxGeometryElement::EMappingMode lUVMappingMode=lUVElement->GetMappingMode();
					if(lUVMappingMode!=FbxGeometryElement::eByPolygonVertex){
						cout<<"error:uv映射模式不是eByPolygonVertex，目前尚不支持其它模式!"<<endl;
						system("pause");
						exit(0);
						return;
					}else{
						//获得uvSet名称
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
			}//得到lUVName
			//cout<<"lUVName:"<<lUVName<<endl;
			//---------------------填充pUVs
			FbxVector2 lCurrentUV;//临时uv
			const int triangleCount = lMesh->GetPolygonCount();
			for (int i = 0; i < triangleCount; i++)
			{
				//----填充pUVs
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
			//---------------------判断norm映射模式
			bool mHasNormal = lMesh->GetElementNormalCount() > 0;
			if (mHasNormal)
			{
				FbxGeometryElement::EMappingMode lNormalMappingMode = lMesh->GetElementNormal(0)->GetMappingMode();
				if (lNormalMappingMode == FbxGeometryElement::eNone)
				{
					cout<<"error:没有法向数据!"<<endl;
					system("pause");
					exit(0);
				}
				if (mHasNormal && lNormalMappingMode != FbxGeometryElement::eByPolygonVertex)
				{
					cout<<"error:norm映射模式不是eByPolygonVertex，目前尚不支持其它模式!"<<endl;
					system("pause");
					exit(0);
				}
			}
			//---------------------求顶点法向量(填充pNorms)
	//		memset(pNorms, 0, triangleCount*3 * sizeof(FbxVector4));//首先全部初始化为0
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
		if (lNodeAttribute//有属性节点
			&&lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh//且属性节点为的类型为eMesh
			)//为pNode制作并绑定idSubMeshSet
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
	//清除userData
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Cmodelfbx::destroyAllUserData_and_manager(){
		destroyAllUserData();//删除用户自定义数据
		DestroySdkObjects(lSdkManager);//删除manager
	}
	void Cmodelfbx::destroyAllUserData(){
		//清除用户保存的纹理句柄和纹理索引
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
		//清楚递归用户数据
		clearUserDataRecursive(lScene->GetRootNode());
	}
	
	void Cmodelfbx::clearUserDataRecursive(FbxNode* pNode)
	{
		FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();
		if (lNodeAttribute//有属性节点
			&&lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh//且属性节点为的类型为eMesh
			)
		{	
			FbxMesh*lMesh=pNode->GetMesh();
			//销毁UV
			float*pUVs=(static_cast<float*>(lMesh->GetUserDataPtr(userDataIndex_UV)));
			if(pUVs!=NULL)delete []pUVs;
			//销毁Norm
			FbxVector4*pNorms=(static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Norm)));
			if(pNorms!=NULL)delete []pNorms;
			//销毁Vertex_deformed
			FbxVector4* lVertexArray=(static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Vertex_deformed)));
			if(lVertexArray!=NULL)delete []lVertexArray;
			//销毁Norm_deformed
			FbxVector4* lNormalArray=(static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Normal_deformed)));
			if(lNormalArray!=NULL)delete []lNormalArray;
			//销毁clusterDeformation
			FbxAMatrix*lClusterDeformation=(static_cast<FbxAMatrix*>(lMesh->GetUserDataPtr(userDataIndex_clusterDeformation)));
			if(lClusterDeformation!=NULL)delete []lClusterDeformation;
			//销毁clusterWeight
			double*lClusterWeight=(static_cast<double*>(lMesh->GetUserDataPtr(userDataIndex_clusterWeight)));
			if(lClusterWeight!=NULL)delete []lClusterWeight;
			//销毁clusterCount
			int*pClusterCount=(static_cast<int*>(lMesh->GetUserDataPtr(userDataIndex_clusterCount)));
			if(pClusterCount!=NULL)delete pClusterCount;
			//销毁hasSkin
			bool*pHasSkin=(static_cast<bool*>(lMesh->GetUserDataPtr(userDataIndex_hasSkin)));
			if(pHasSkin!=NULL)delete pHasSkin;
			//销毁所有cluster的用户数据
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
	//绘制
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Cmodelfbx::setTime(int t_MilliSecond){
		Time.SetMilliSeconds(t_MilliSecond);
	}
	void Cmodelfbx::selectAnimation(int iAnimationStack){
		FbxArray<FbxString*> mAnimStackNameArray;
		lScene->FillAnimStackNameArray(mAnimStackNameArray);
		const int lAnimStackCount = mAnimStackNameArray.GetCount();
		if(iAnimationStack<0||iAnimationStack>=lAnimStackCount){
			cout<<"error: 无效的iAnimationStack值!"<<endl;
			//销毁mAnimStackNameArray
			FbxArrayDelete(mAnimStackNameArray);
			return;
		}
		// select the base layer from the animation stack
		lCurrentAnimationStack = lScene->FindMember(FBX_TYPE(FbxAnimStack), mAnimStackNameArray[iAnimationStack]->Buffer());
		if (lCurrentAnimationStack == NULL)
		{
			// this is a problem. The anim stack should be found in the scene!
			cout<<"erorr: 未发现AnimationStack!"<<endl;
			//销毁mAnimStackNameArray
			FbxArrayDelete(mAnimStackNameArray);
			return;
		}
		//设置当前AnimationStack为lCurrentAnimationStack
		lScene->GetEvaluator()->SetContext(lCurrentAnimationStack);
		//计算此动画的起止时间
		{
			FbxTime mStart,mStop;//起止时间（临时使用）
			FbxTakeInfo* lCurrentTakeInfo = lScene->GetTakeInfo(*(mAnimStackNameArray[iAnimationStack]));
			if (lCurrentTakeInfo)
			{
				mStart = lCurrentTakeInfo->mLocalTimeSpan.GetStart();
				mStop = lCurrentTakeInfo->mLocalTimeSpan.GetStop();
		//		cout<<"mStart:"<<mStart.GetMilliSeconds()<<endl;
		//		cout<<"mStop:"<<mStop.GetMilliSeconds()<<endl;


			}else{
				cout<<"没有得到CurrentTakeInfo"<<endl;
			}
			if(lCurrentTakeInfo==NULL//没得到lCurrentTakeInfo
				||mStart.GetMilliSeconds()<0//或者由lCurrentTakeInfo中得到的Start为负值
				)
			{
				// Take the time line value
				FbxTimeSpan lTimeLineTimeSpan;
				lScene->GetGlobalSettings().GetTimelineDefaultTimeSpan(lTimeLineTimeSpan);

				mStart = lTimeLineTimeSpan.GetStart();
				mStop  = lTimeLineTimeSpan.GetStop();
			}//得到mStart和mStop
			StartTime=mStart;
			StopTime=mStop;
		}
	//	cout<<"StartTime:"<<StartTime.GetMilliSeconds()<<endl;
	//	cout<<"StopTime:"<<StopTime.GetMilliSeconds()<<endl;
	//	cout<<"StartTime:"<<StartTime.GetSecondDouble()<<endl;
	//	cout<<"StopTime:"<<StopTime.GetSecondDouble()<<endl;
		//将Time置为与StartTime一致
		Time=StartTime;
		//销毁mAnimStackNameArray
		FbxArrayDelete(mAnimStackNameArray);

	}
	void Cmodelfbx::animationAdvance_rollback(int dms){//动画前进dms毫秒，如果超出长度就绕回
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
		
		//画各subMesh
		CidSubMeshSet*pIdSubMeshSet=(static_cast<CidSubMeshSet*>(lMesh->GetUserDataPtr(userDataIndex_idSubMeshSet)));
		float*pUVs=(static_cast<float*>(lMesh->GetUserDataPtr(userDataIndex_UV)));
		const int nidSubMesh=(int)pIdSubMeshSet->idSubMeshList.size();
		for(int i=0;i<nidSubMesh;i++){
			CidSubMesh&idSubMesh=pIdSubMeshSet->idSubMeshList[i];
			//画idSubMesh
			//绑定纹理
			glBindTexture(GL_TEXTURE_2D,idSubMesh.texture);
			glBegin(GL_TRIANGLES);
			//画各三角形
			int j=0;
			int jMul3=0;
			int nTriangle=(int)idSubMesh.polygenIndexList.size();
			for(;j<nTriangle;j++){
				const int triangleIndex=idSubMesh.polygenIndexList[j];
				//画triangleIndex号三角形
				//获得三顶点
				const int ID0=idSubMesh.vIDList[jMul3++];
				const int ID1=idSubMesh.vIDList[jMul3++];
				const int ID2=idSubMesh.vIDList[jMul3++];
				//求uv
				const float *u0=pUVs+triangleIndex*6;//即pUVs+triangleIndex*6
				const float *u1=u0+2;
				const float *u2=u0+4;
				//画
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
	//将各纹理文件的路径从lScene提取出来
	//然后通过textureManager提交到GPU，并将显存句柄保存到textureManager
	{
		 // Load the textures into GPU, only for file texture now
        const int lTextureCount = lScene->GetTextureCount();
        for (int lTextureIndex = 0; lTextureIndex < lTextureCount; ++lTextureIndex)
        {
            FbxTexture * lTexture = lScene->GetTexture(lTextureIndex);
            FbxFileTexture * lFileTexture = FbxCast<FbxFileTexture>(lTexture);//只是转了一下类型，其实lFileTexture就是lTexture
            if (lFileTexture && !lFileTexture->GetUserDataPtr())
            {
                // Try to load the texture from absolute path
				const char* tfilename=lFileTexture->GetFileName();
                string filename =tfilename; 
				//将后缀名改为.bmp
				int len=(int)filename.size();
				int iDot=-1;
				for(int i=len-1;i>=0;i--){
					if(filename[i]=='.'){
						iDot=i;
						break;
					}
				}
				if(iDot==-1){//没找到'.'
					cout<<"无效的文件名!"<<endl;
			//		return;
				}else{//找到'.'
					filename=filename.substr(0,iDot);
					filename+=".bmp";
				}//后缀名已改为.bmp
				//将前面的路径名都删除，只剩下文件名
				{
					//找最后一个\或/
					int iBar=-1;
					int len=(int)filename.size();
					for(int i=len-1;i>=0;i--){
						if(filename[i]=='\\'||filename[i]=='/'){
							iBar=i;
							break;
						}
					}
					if(iBar==-1){//没找到\或/
						//说明没有，现在就是符合要求的
					}else{//找到\或/
						//将\或/及其前面的字符都去掉
						filename=filename.substr(iBar+1,len-(iBar+1));
					}
				
				}
				//添加自己目录的路径名
				{

					string pathPerfix="data\\model_fbx\\";
					//从fbxFileName中提取最后一级文件名(并且要把.fbx去掉)，存到tstr
					string tstr=fbxFileName;
					{
						//找最后一个\或/
						int iBar=-1;
						int len=(int)tstr.size();
						for(int i=len-1;i>=0;i--){
							if(tstr[i]=='\\'||tstr[i]=='/'){
								iBar=i;
								break;
							}
						}
						if(iBar==-1){//没找到\或/
							//说明没有，现在就是符合要求的
						}else{//找到\或/
							//将\或/及其前面的字符都去掉
							tstr=tstr.substr(iBar+1,len-(iBar+1));
						}
						//将tstr的最后四个字符(一定是.fbx)去掉
						tstr=tstr.substr(0,(int)tstr.size()-4);
					}//得到tstr
					pathPerfix+=tstr;
					pathPerfix+="\\";
					filename=pathPerfix+filename;
				}//得到完整的纹理路径名filename
//				cout<<filename<<endl;
				//以filename生成纹理
				Cc3dTexture*texture=Cc3dTextureCache::sharedTextureCache()->addImage(filename.c_str());
				if(texture){
					//将此纹理的显存句柄以用户数据的形式保存回到lFileTexture(即lTexture)
                    lFileTexture->SetUserDataPtr(userDataIndex_texture,texture);
				}else{
					cout<<"error: create texture failed! "<<endl;
					assert(false);
				}

            }
			
        }
		//检查是否有重复纹理路径
		{
			bool nonSame=true;//是否均不相同
			const int lTextureCount = lScene->GetTextureCount();
			if(lTextureCount<=1){//如果纹理数小于等于1
				
			}else{//如果纹理数大于1
			
				for (int i = 0; i < lTextureCount; i++)
			    {
			        FbxTexture * lTexture = lScene->GetTexture(i);
					Cc3dTexture* texture=(static_cast<Cc3dTexture*>(lTexture->GetUserDataPtr(userDataIndex_texture)));
					string texPath_i=texture->getFilePath();
					//用texPath_i与其之后的各path_j比较，如果有相同者，则说明有重复
					for(int j=i+1;j<lTextureCount;j++){
						FbxTexture * lTexture = lScene->GetTexture(j);
						Cc3dTexture* texture=(static_cast<Cc3dTexture*>(lTexture->GetUserDataPtr(userDataIndex_texture)));
						string texPath_j=texture->getFilePath();
						//texPath_i与texPath_j比较
						if(texPath_i==texPath_j){
							cout<<"纹理路径重复!"<<endl;
							cout<<texPath_i<<" "<<texPath_j<<endl;
					//		system("pause");
							nonSame=false;
							break;
						}
					}
					if(nonSame==false)break;
				}
			
			}//得到nonSame
			if(nonSame){
				cout<<pFbxFileName<<" 纹理路径无重复"<<endl;
			}else{
				cout<<pFbxFileName<<" 纹理路径有重复!"<<endl;
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
		//整体旋转fbx场景
		glPushMatrix();
		//绘制fbx场景
		{
			if(lCurrentAnimationStack!=NULL){
				//获得mCurrentAnimLayer
				// we assume that the first animation layer connected to the animation stack is the base layer
				// (this is the assumption made in the FBXSDK)
				FbxAnimLayer *mCurrentAnimLayer = lCurrentAnimationStack->GetMember(FBX_TYPE(FbxAnimLayer), 0);
				//获得pose
				int mPoseIndex=-1;//就想让lPose得NULL，所以设定此处为-1
				FbxPose * lPose = NULL;
			    if (mPoseIndex != -1)
				{
					 lPose = lScene->GetPose(mPoseIndex);
				}
				//定义lDummyGlobalPosition
				FbxAMatrix lDummyGlobalPosition;//模型的世界位置（默认构造为单位矩阵）
				DrawNodeRecursive(lScene->GetRootNode(), Time, mCurrentAnimLayer, lDummyGlobalPosition,lPose);
			}
		}
		//消栈
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
					//这个在调试模型时应开启，以便观察骨骼与蒙皮是否吻合，但最终显示时应关闭以节省计算量
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
		//获得hasSkin
		bool*pHasSkin=(static_cast<bool*>(lMesh->GetUserDataPtr(userDataIndex_hasSkin)));
		//获得变形顶点和法线列表
		FbxVector4* lVertexArray=NULL;
		FbxVector4* lNormalArray=NULL;
		if(*pHasSkin){//如果有skin
			//获取顶点列表
			lVertexArray=(static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Vertex_deformed)));
			//拷贝原始数据
			memcpy(lVertexArray, lMesh->GetControlPoints(), lVertexCount * sizeof(FbxVector4));
			//获取法线列表
			lNormalArray=(static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Normal_deformed)));;
			//拷贝原始数据
			FbxVector4*lNormalArray_original=(static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Norm)));
			memcpy(lNormalArray, lNormalArray_original, triangleCount*3 * sizeof(FbxVector4));
		}else{//如果没有skin
			//直接使用原始数据的引用
			lVertexArray = lMesh->GetControlPoints();
			lNormalArray = (static_cast<FbxVector4*>(lMesh->GetUserDataPtr(userDataIndex_Norm)));
		}
		
		//填充变形顶点和法线列表
		if (*pHasSkin)//如果有skin
		{
			//获得clusterCount
			int*pClusterCount=(static_cast<int*>(lMesh->GetUserDataPtr(userDataIndex_clusterCount)));
			if (*pClusterCount)
			{
				// Deform the vertex array with the skin deformer.
				ComputeSkinDeformation(pGlobalPosition, lMesh, pTime, lVertexArray,lNormalArray,pPose);
			}


		}
		glPushMatrix();
		glMultMatrixd((const double*)pGlobalPosition);
		//画蒙皮
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
		//	//如果想适用于最广的情况，应该用下面这句，但效率会有所降低
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
	


	
	// Deform the vertex array in classic linear way.简化版本
	void Cmodelfbx::ComputeLinearDeformation_simplify(FbxAMatrix& pGlobalPosition, 
		FbxMesh* pMesh, 
		FbxTime& pTime, 
		FbxVector4* pVertexArray,
		FbxVector4* pNormalArray,
		FbxPose* pPose)
	{
		
		//下面花括号中的内容只在调试时开放
		{
			// All the links must have the same link mode.
			FbxCluster::ELinkMode lClusterMode = ((FbxSkin*)pMesh->GetDeformer(0, FbxDeformer::eSkin))->GetCluster(0)->GetLinkMode();
			if(lClusterMode!=FbxCluster::eNormalize){
				cout<<"error:lClusterMode!=eNormalize，目前只支持eNormalize"<<endl;
				assert(false);
				//  (1) lClusterMode == FbxCluster::eNormalize:
				//	normalized link mode, a vertex is always totally influenced by the links.
				//  所有link（骨骼）对此顶点的影响权重之和为1
				//  (2) lClusterMode == FbxCluster::eTotalOne:
				//	total 1 link mode, a vertex can be partially influenced by the links. 
				//  所有link（骨骼）对此顶点的影响权重之和totalLinksWeight不足1，其余1-totalLinksWeight由自身贡献
				
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
		//其实只处理第一个skin即可
		if(lSkinCount>1){//如果多于一个skin，给一个警报
			cout<<"warning:含有多于一个skin，只处理第一个skin"<<endl;
			lSkinCount=1;//强制只处理第一个skin，这样节省计算量
		}
		
		for ( int lSkinIndex=0; lSkinIndex<lSkinCount; ++lSkinIndex)
		{
			FbxSkin * lSkinDeformer = (FbxSkin *)pMesh->GetDeformer(lSkinIndex, FbxDeformer::eSkin);

			int lClusterCount = lSkinDeformer->GetClusterCount();//每个cluster对应一个骨骼，所以此值也是骨骼数
			for ( int lClusterIndex=0; lClusterIndex<lClusterCount; ++lClusterIndex)
			{
				FbxCluster* lCluster = lSkinDeformer->GetCluster(lClusterIndex);
				if (!lCluster->GetLink())
					continue;

				FbxAMatrix lVertexTransformMatrix;
				ComputeClusterDeformation(pGlobalPosition, pMesh, lCluster, lVertexTransformMatrix, pTime, pPose);
				               
				int lVertexIndexCount = lCluster->GetControlPointIndicesCount();
				int* clusterControlPointIndices=lCluster->GetControlPointIndices();//cluster的顶点索引表
				double* clusterControlPointWeights= lCluster->GetControlPointWeights();//cluster的顶点权重表
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
					MatrixScale(lInfluence, lWeight);//得到lInfluence矩阵，即本cluster(相关联的骨骼)的变换矩阵乘以其对此节权重
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
				//变换顶点
				{
					pVertexArray[i] = lClusterDeformation[i].MultT(pVertexArray[i]);
					
				}
			
			} 
		}
		int polygonCount=pMesh->GetPolygonCount();
		for(int i=0;i<polygonCount;i++){
			//遍历三个顶点
			for(int j=0;j<3;j++){
				int vID=pMesh->GetPolygonVertex(i,j);//当前顶点ID
			//	cout<<"i j:"<<i<<" "<<j<<endl;
				//变换法向量
				if(lClusterWeight[vID] != 0.0){
					prodv_lastRow0001_wZero(lClusterDeformation[vID],pNormalArray[3*i+j],pNormalArray[3*i+j]);
				}
			}
		}
	}
	
	void Cmodelfbx::prodv_lastRow0001_wZero(const FbxAMatrix&matrix,const FbxVector4&in,FbxVector4&out)
	//设m为FbxAMatrix
	//double*pm=(double*)m
	//则pm完全等同于opengl中的double[16],遵从如下布局:
	// pm[0] pm[4] pm[8]  pm[12]
	// pm[1] pm[5] pm[9]  pm[13]
	// pm[2] pm[6] pm[10] pm[14]
	// pm[3] pm[7] pm[11] pm[15]
	//其中(pm[12],pm[13],pm[14],pm[15])为平移分量(x,y,z,1)
	//而如果不进行类型转化，直接使用m，则：
	//               m[0][0] m[0][1] m[0][2]   pm[0]  pm[1]  pm[2]  pm[3]
	// FbxAMatrix m= m[0][0] m[0][1] m[0][2] = pm[4]  pm[5]  pm[6]  pm[7]
	//				 m[0][0] m[0][1] m[0][2]   pm[8]  pm[9]  pm[10] pm[11]
	//               m[0][0] m[0][1] m[0][2]   pm[12] pm[13] pm[14] pm[15]
	//注意此处pm矩阵与上面的pm矩阵行列正好相反
	{//in和out可以是同一变量
		const double* pmatrix=(const double*)matrix;
		const double* pin=(const double*)in;
		double _out[4];//临时中转
		//注意，下面用pmatrix,pin，而不要再用matrix和in
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
		//计算lClusterRelativeInitPosition
		{
			//先看看能不能从用户数据中获取
			FbxAMatrix *plClusterRelativeInitPosition=(static_cast<FbxAMatrix*>(pCluster->GetUserDataPtr(userDataIndex_clusterRelativeInitPosition)));
			if(plClusterRelativeInitPosition){//获取成功
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
				//将lClusterRelativeInitPosition添加到pCluster节点
				FbxAMatrix *plClusterRelativeInitPosition=new FbxAMatrix(lClusterRelativeInitPosition);
				pCluster->SetUserDataPtr(userDataIndex_clusterRelativeInitPosition,plClusterRelativeInitPosition);

			}
		}
		//计算lClusterRelativeCurrentPositionInverse
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