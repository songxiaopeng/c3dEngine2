//
//  layer.h
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-12-20.
//
//

#ifndef __HelloOpenGL__layer__
#define __HelloOpenGL__layer__

#include <iostream>
#include "c3d.h"
#include "globalVars.h"
#include "extension.h"
#include "c3dExtension.h"


void buildinProgramPassUnifoCallback_cubemap(Cc3dNode*node, Cc3dProgram*program);
class Clayer:public Cc3dActor
{

public:
    Clayer(){

		m_actor=NULL;
	
	
    } 
    virtual~Clayer(){

        //----remove unused resources in caches on next frame
		Cc3dTextureCache::sharedTextureCache()->removeUnusedTexturesOnNextFrame();
		Cc3dAudioCache::sharedAudioCache()->removeUnusedBuffersAndSourcesOnNextFrame();
    }

	bool init(){

		//----create cubeTexture
		vector<string> filePathList;
		filePathList.push_back("cubemap_resource/px.png");
		filePathList.push_back("cubemap_resource/nx.png");
		filePathList.push_back("cubemap_resource/py.png");
		filePathList.push_back("cubemap_resource/ny.png");
		filePathList.push_back("cubemap_resource/pz.png");
		filePathList.push_back("cubemap_resource/nz.png");
		Cc3dTexture*cubeTex=new Cc3dTexture();
		cubeTex->autorelease();
		cubeTex->initCubeTexture(filePathList);


		//----fbx model
		m_actor=Cc3dFbxLoader::sharedFbxLoader()->load("cubemap_resource/apple.fbx",0);//set the last parameter to ZERO to read static model

		m_actor->setPos(Cc3dVector4(0,0,0,1));
		m_actor->setLight(light0);
		m_actor->setCamera(camera);
		m_actor->setProgram(Cc3dProgramCache::sharedProgramCache()->getProgramByName("cubemap"));
		m_actor->setPassUnifoCallback(buildinProgramPassUnifoCallback_cubemap);//xxx,need change

		m_actor->genVBOBuffers();
		m_actor->submit(GL_STATIC_DRAW);
		addChild(m_actor);

		//change texture to cubeTexture
		int nMesh=(int)m_actor->getModel()->getMeshCount();
		for(int i=0;i<nMesh;i++){
			int nSubMesh=(int)m_actor->getModel()->getMeshByIndex(i)->getSubMeshCount();
			for(int j=0;j<nSubMesh;j++){
				m_actor->getModel()->getMeshByIndex(i)->getSubMeshByIndex(j)->setTexture(cubeTex);
			}
		}
		
	
        return true;
    }
  
	
protected:

	Cc3dSkinActor*m_actor;


};

#endif /* defined(__HelloOpenGL__layer__) */
