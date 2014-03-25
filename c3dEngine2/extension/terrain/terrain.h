//
//  terrain.h
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-11-16.
//
//

#ifndef __HelloOpenGL__terrain__
#define __HelloOpenGL__terrain__

#include <iostream>
using namespace std;
#include <math.h>
#include "c3dMesh.h"
#include "c3dActor.h"


class Cij{
protected:
    int m_i,m_j;
public:
    Cij(){
        initMembers();
    }
    virtual~Cij(){};
    Cij(int i,int j){
        initMembers();
        init(i, j);
    }
    void init(int i,int j){
        m_i=i;
        m_j=j;
    }
    int getI()const{return m_i;}
    int getJ()const{return m_j;}
protected:
    void initMembers(){
        m_i=0;
        m_j=0;
    }
};
typedef unsigned char       BYTE;
//bmp每个像素对应一个grid，每个grid有四个顶点
//markmat每个元素对应一个顶点
class Cterrain:public Cc3dActor
{
protected:

	float reso;//LOD分辨率
	vector<vector<bool> > markmat;//标记数组，用来标记各区域是否被分割
    vector<Cij> markedElementIndexList;//记录markmat中被置1的元素的index，便于以后归零
    string m_heightMapFileName;//高度图文件名
    int m_quadtreeDepth;//四叉树深度（包含根节点），全部节点数为(pow(4,depth)-1)/3
    float m_heightScale;//地形高度缩放因子
    Cc3dRange m_range;//地形范围
    float gridSize;//markmat上一格的x或z跨度,x跨度与z跨度相等
	float m_uvScale;//纹理缩放系数，u和v的放缩系数相等，都为kuv
    vector<vector<float> > landMat;//高程数组
    vector<vector<Cc3dVector4> > normalMat;//法向数组
public:
	Cterrain(){
        m_quadtreeDepth=9;
        gridSize=0;
		m_uvScale=1;
		reso=15000;//10000;//5000
        m_heightScale=1;
	}
    bool init(const string&fileNameWithExt,const Cc3dRect&rect,float heightScale,int depth,Cc3dTexture*texture);
    Cc3dMesh*getMesh(){
        assert((int)getModel()->getMeshCount()==1);
        return getModel()->getMeshByIndex(0);
    }
    void setUVScale(float value){m_uvScale=value;}
    float getUVScale()const{return m_uvScale;}
    void setHeightScale(float value){m_heightScale=value;}
    float getHeightScale()const{return m_heightScale;}
    const Cc3dRange&getRange()const{return m_range;}
    void update(const Cc3dCamera&camera);
    float getHAndNormal(float x,float z,Cc3dVector4&norm)const;
    float getH(float x,float z)const ;
protected:
    void makeUp(int jmin,int jmax,int imin,int imax);
    void showAndMark(int jmin,int jmax,int imin,int imax,int curDepth);
    void readLandMat();
    void fillNormalMat();
    void makeMesh();

};



#endif /* defined(__HelloOpenGL__terrain__) */
