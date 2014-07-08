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
/*
void buildinProgramPassUnifoCallback_cubemap(Cc3dNode*node, Cc3dProgram*program);
class Clayer:public Cc3dActor
{

public:
    Clayer(){
        m_board=NULL;
		m_board2=NULL;
		m_actor=NULL;
		m_fbo=NULL;
	    m_depthTex=NULL;
	    m_colorTex=NULL;
		m_isGotFBO=false;
	
    } 
    virtual~Clayer(){
		if(m_fbo)m_fbo->release();
        //----remove unused resources in caches on next frame
		Cc3dTextureCache::sharedTextureCache()->removeUnusedTexturesOnNextFrame();
		Cc3dAudioCache::sharedAudioCache()->removeUnusedBuffersAndSourcesOnNextFrame();
    }

	bool init(){
		


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
		//shadow map
		m_fbo=NULL;
		m_depthTex=NULL;
		m_colorTex=NULL;
		{
			m_fbo=new Cc3dFbo();
			m_fbo->autorelease();
			m_fbo->retain();
			//depthTex
			m_depthTex=new Cc3dTexture();
			m_depthTex->autorelease();
			m_depthTex->retain();
			int shadowMapSize=256;
			m_depthTex->initDepthTexture(shadowMapSize,shadowMapSize,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_NEAREST,GL_NEAREST);
			m_fbo->attachDepthTex(m_depthTex);
			//colorTex
			m_colorTex=new Cc3dTexture();
			m_colorTex->autorelease();
			m_colorTex->retain();
			m_colorTex->initColorTexture(shadowMapSize,shadowMapSize,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_NEAREST,GL_NEAREST);
			m_fbo->attachColorTex(m_colorTex);
		}
		//render to fbo
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo->getID());
			//we should ensoure depthMask is true before call glClear(GL_DEPTH_BUFFER_BIT...)
			//see: http://www.flipcode.com/forums/thread/9101
			//http://stackoverflow.com/questions/12475369/does-glcolormask-affect-glclear
			//http://www.opengl.org/sdk/docs/man2/xhtml/glClear.xml
			glDepthMask(GL_TRUE);
			//glClearColor(0, 0, 0, 1);
			glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);//只有深度缓存，所以只清除深度缓存，另外tile-base architecture要求bind之后立即clear更快些--abc
			glViewport(0, 0, m_depthTex->getWidth() , m_depthTex->getHeight());//离屏窗口--abc


			//注意是用camera_light
			m_actor->visitDraw();

			//recover
			glBindFramebuffer(GL_FRAMEBUFFER,0);
			glDepthMask(GL_FALSE);
			glClearColor(0, 0, 0, 0);

			m_isGotFBO=true;
		}
		//--board
		//m_board=NULL;
		//{
		//	Cc3dRect screenRect=Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect();
		//	m_board=new Cboard();
		//	m_board->autorelease();
		//	m_board->init(240, 240,m_depthTex);
		//	m_board->setCamera(camera2D);
		//	m_board->setPos(Cc3dVector4((screenRect.getMinX()+screenRect.getMaxX())/2,(screenRect.getMinY()+screenRect.getMaxY())/3*2,0,1));
		//	m_board->genVBOBuffers();
		//	m_board->submit(GL_STATIC_DRAW);
		//	addChild(m_board);
		//}
		//board2
		m_board2=NULL;
		{
			Cc3dRect screenRect=Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect();
			m_board2=new Cboard();
			m_board2->autorelease();
			m_board2->init(240, 240,m_colorTex);
			m_board2->setCamera(camera2D);
			m_board2->setPos(Cc3dVector4(0,0,0,1));//(Cc3dVector4((screenRect.getMinX()+screenRect.getMaxX())/2,(screenRect.getMinY()+screenRect.getMaxY())/3*2,0,1));
			m_board2->genVBOBuffers();
			m_board2->submit(GL_STATIC_DRAW);
			addChild(m_board2);
		}
        return true;
    }
  
	
protected:
	Cboard*m_board;
	Cboard*m_board2;
	Cc3dSkinActor*m_actor;
    Cc3dFbo*m_fbo;
	Cc3dTexture*m_depthTex;
	Cc3dTexture*m_colorTex;
	bool m_isGotFBO;

};
*/

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

		//----create cube map
		vector<string> filePathList;
		filePathList.push_back("cubemap_resource/01_02.png");
		filePathList.push_back("cubemap_resource/01_05.png");
		filePathList.push_back("cubemap_resource/01_06.png");
		filePathList.push_back("cubemap_resource/01_07.png");
		filePathList.push_back("cubemap_resource/01_08.png");
		filePathList.push_back("cubemap_resource/01_10.png");

		Cc3dTexture*cubeTex=new Cc3dTexture();
		cubeTex->autorelease();
		cubeTex->initCubeTexture(filePathList);//,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE);


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

		cout<<"modelCount:"<<m_actor->getModel()->getMeshCount()<<endl;
		m_actor->getModel()->getMeshByIndex(0)->getSubMeshByIndex(0)->setTexture(cubeTex);
	
        return true;
    }
  
	
protected:

	Cc3dSkinActor*m_actor;


};

#endif /* defined(__HelloOpenGL__layer__) */
