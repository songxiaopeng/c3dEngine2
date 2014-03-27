//
//  c3dMeshData.h
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 14-1-25.
//
//

#ifndef __HelloOpenGL__c3dMeshData__
#define __HelloOpenGL__c3dMeshData__

#include <iostream>
#include <vector>
using namespace std;
#include "c3dIDtriangle.h"
#include "c3dVertex.h"
#include "c3dObject.h"
class Cc3dSubMeshData:public Cc3dObject{
public:
    vector<Cc3dVertex> vlist; 
    vector<Cc3dIDTriangle> IDtriList;
    void addVertex(const Cc3dVertex&vertex);
    void addIDtri(const Cc3dIDTriangle&IDtri);
    void clear(){
        vlist.clear();
        IDtriList.clear();
    }
    bool isEmpty(){ return (vlist.empty()&&IDtriList.empty());}
};
#endif /* defined(__HelloOpenGL__c3dMeshData__) */
