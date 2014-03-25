#ifndef _fbxmodel_H
#define _fbxmodel_H
#include<map>
#include<vector>
using namespace std;
#include <GL/glew.h>

#include <gl\gl.h>
#include "glext.h"
#include "model_base.h"
#include "mesh.h"
#include "texture.h"
//----------fbx
#define FBXSDK_NEW_API 0
#include <fbxsdk.h>
#include "c3dActor.h"
class CidSubMesh{
public:
	GLuint texture;
	string texPath;//纹理路径
	vector<int> polygenIndexList;//多边形索引表
	vector<int> vIDList;//顶点索引表
	CidSubMesh(){
		texture=0;
	}

};
class CidSubMeshSet{
public:
	vector<CidSubMesh> idSubMeshList;
};
//用户自定义数据的索引
//mesh上的userData
const int userDataIndex_idSubMeshSet=0;
const int userDataIndex_UV=1;
const int userDataIndex_Norm=2;
const int userDataIndex_Normal_deformed=3;
const int userDataIndex_Vertex_deformed=4;
const int userDataIndex_clusterDeformation=5;
const int userDataIndex_clusterWeight=6;
const int userDataIndex_clusterCount=7;
const int userDataIndex_hasSkin=8;
//lFileTexture上的userData
const int userDataIndex_texture=0;
const int userDataIndex_texPath=1;
//pCluster上的userData
const int userDataIndex_clusterRelativeInitPosition=0;
class Cmodelfbx:public Cmodel
{
public:
	char*fbxFileName;
	FbxManager* lSdkManager;
	FbxScene* lScene;
	FbxTime Time;
	FbxAnimStack *lCurrentAnimationStack;
	FbxTime StartTime;
	FbxTime StopTime;
	//
	Cmodelfbx(){
		
		fbxFileName=NULL;
		lSdkManager = NULL;
	    lScene = NULL;
		Time.SetMilliSeconds(0);
		StartTime.SetMilliSeconds(0);
		StopTime.SetMilliSeconds(0);
		lCurrentAnimationStack=NULL;

	}
	~Cmodelfbx(){
		
		if(lSdkManager!=NULL)destroyAllUserData_and_manager();
	}
	//-------------------------------------------------------------------------------------------
	void Init_and_load(char* _fbxFileName);
	void triangulate_loadTextures_preprocess();
	void makeSubMeshSetForThisNode(FbxNode* pNode,int userDataIndex);
	void makeSubMeshSetForEachNode(FbxNode* pNode,int userDataIndex);
	bool getHasDeformer(FbxMesh*lMesh);
	void makeOtherUserForThisNode(FbxNode* pNode,int userDataIndex_uv,int userDataIndex_norm);
	void show();
	void makeOtherUserForEachNode(FbxNode* pNode,int userDataIndex_uv,int userDataIndex_norm);
	void destroyAllUserData_and_manager();
	void destroyAllUserData();
	void clearUserDataRecursive(FbxNode* pNode);
	void prodv_lastRow0001_wZero(const FbxAMatrix&matrix,const FbxVector4&in,FbxVector4&out);
	void setTime(int t_MilliSecond);
	void selectAnimation(int iAnimationStack);
	void animationAdvance_rollback(int dms);
	void drawSkin(FbxNode*pNode,FbxVector4*lVertexArray,FbxVector4*lNormalArray);
	void loadTextures(const char * pFbxFileName);
	//-----------------------------------------------------------------------------------------------
	// Deform the vertex array in classic linear way.简化版本
	void ComputeLinearDeformation_simplify(FbxAMatrix& pGlobalPosition, 
		FbxMesh* pMesh, 
		FbxTime& pTime, 
		FbxVector4* pVertexArray,
		FbxVector4* pNormalArray,
		FbxPose* pPose);
	// Draw the vertices of a mesh.
	void DrawMesh(FbxNode* pNode, FbxTime& pTime, FbxAnimLayer* pAnimLayer,
		FbxAMatrix& pGlobalPosition, FbxPose* pPose);
	//------------------------------------------------------------------------------------------------
	void InitializeSdkObjects(FbxManager*& pSdkManager, FbxScene*& pScene);
	bool LoadScene(FbxManager* pSdkManager, FbxDocument* pScene,char* pFilename);
	void DestroySdkObjects(FbxManager* &pSdkManager);
	//get mesh smoothing info
	//set pCompute true to compute smoothing from normals by default 
	//set pConvertToSmoothingGroup true to convert hard/soft edge info to smoothing group info by default
	void GetSmoothing(FbxManager* pSdkManager, FbxNode* pNode, bool pCompute, bool pConvertToSmoothingGroup);
    // Triangulate all NURBS, patch and mesh under this node recursively.
    void TriangulateRecursive(FbxNode* pNode);	
	// Draw recursively each node of the scene. To avoid recomputing 
	// uselessly the global positions, the global position of each 
	// node is passed to it's children while browsing the node tree.
	// If the node is part of the given pose for the current scene,
	// it will be drawn at the position specified in the pose, Otherwise
	// it will be drawn at the given time.
	void DrawNodeRecursive(FbxNode* pNode, FbxTime& pTime, FbxAnimLayer* pAnimLayer,
		FbxAMatrix& pParentGlobalPosition, FbxPose* pPose);
	// Get the global position of the node for the current pose.
	// If the specified node is not part of the pose or no pose is specified, get its
	// global position at the current time.
	FbxAMatrix GetGlobalPosition(FbxNode* pNode, const FbxTime& pTime,FbxPose* pPose, FbxAMatrix* pParentGlobalPosition=NULL);
	// Get the matrix of the given pose
	FbxAMatrix GetPoseMatrix(FbxPose* pPose, int pNodeIndex);
	// Get the geometry offset to a node. It is never inherited by the children.
	FbxAMatrix GetGeometry(FbxNode* pNode);
	// Draw the node following the content of it's node attribute.
	void DrawNode(FbxNode* pNode, 
		FbxTime& pTime, 
		FbxAnimLayer* pAnimLayer,
		FbxAMatrix& pParentGlobalPosition,
		FbxAMatrix& pGlobalPosition,
		FbxPose* pPose);
	// Draw a limb between the node and its parent.
	void DrawSkeleton(FbxNode* pNode, FbxAMatrix& pParentGlobalPosition, FbxAMatrix& pGlobalPosition);
	void GlDrawLimbNode(FbxAMatrix& pGlobalBasePosition, FbxAMatrix& pGlobalEndPosition);
	// Deform the vertex array according to the links contained in the mesh and the skinning type.
	void ComputeSkinDeformation(FbxAMatrix& pGlobalPosition, 
		FbxMesh* pMesh, 
		FbxTime& pTime, 
		FbxVector4* pVertexArray,
		FbxVector4* pNormalArray,
		FbxPose* pPose);
	// Scale all the elements of a matrix.
	void MatrixScale(FbxAMatrix& pMatrix, double pValue);
	// Add a value to all the elements in the diagonal of the matrix.
	void MatrixAddToDiagonal(FbxAMatrix& pMatrix, double pValue);
	// Sum two matrices element by element.
	void MatrixAdd(FbxAMatrix& pDstMatrix, FbxAMatrix& pSrcMatrix);
	//Compute the transform matrix that the cluster will transform the vertex.
	void ComputeClusterDeformation(FbxAMatrix& pGlobalPosition, 
		FbxMesh* pMesh,
		FbxCluster* pCluster, 
		FbxAMatrix& pVertexTransformMatrix,
		FbxTime pTime,
		FbxPose* pPose);

};
#endif