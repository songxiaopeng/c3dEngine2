//
//  initGame.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-12-20.
//
//

#include "initGame.h"
#include "c3d.h"
#include "box.h"
#include "globalVars.h"
#include "passUnifoCallBack.h"
#include "programSetUp.h"
#include "fbxmodel.h"
void initGame(){
	programSetUp();

	//----light
	{
		light0=new Cc3dLight();
		light0->autorelease();
		light0->retain();
		light0->setPos(100,50,20);
	}
	 //----camera2D
    {
        float left=0;
        float right=Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getWidth();
        float top=Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getHeight();
        float bottom = 0;
        float _near = -1;//note: near and far is key word in vs2010, so here we use _near and _far
        float _far = 1;
        Cc3dRange range(left,right,bottom,top,_near,_far);
        camera2D=new Cc3dCamera();
        camera2D->init();
        camera2D->autorelease();
        camera2D->retain();//must retain
        camera2D->setRange(range);
        camera2D->setProjectionMode(ec3dOrthographicMode);
    }
    //----camera
    {
        camera=new Cc3dCamera();
        camera->init();
        camera->autorelease();
        camera->retain();//must retain
        camera->setFovy(70);
        camera->setAspect((float)Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getWidth()/Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getHeight());
        camera->setzNear(0.5);
        camera->setzFar(10000);
        float eyePos[3]={10,5,5};
        float eyeTg[3]={0,0,0};
        float up[3]={0,1,0};
        camera->setEyePos(Cc3dVector3(eyePos).toV4(1));
        camera->setCenter(Cc3dVector3(eyeTg).toV4(1));
        camera->setUp(Cc3dVector3(up).toV4(0));
        camera->updateFrustum();
    }

	//----box
	Cmodelfbx*fbxmodel=new Cmodelfbx();
	fbxmodel->autorelease();

	fbxmodel->Init_and_load("fbxLoader_resource/girl/girl.fbx");

	fbxmodel->triangulate_loadTextures_preprocess();
	fbxmodel->setTime(0);
	fbxmodel->selectAnimation(0);

	fbxmodel->setPos(Cc3dVector4(0,0,0,1));
	fbxmodel->setLight(light0);
    fbxmodel->setCamera(camera);
	fbxmodel->setProgram(Cc3dProgramCache::sharedProgramCache()->getProgramByName("classicLighting"));
    fbxmodel->setPassUnifoCallback(passUnifoCallback_classicLighting);

    fbxmodel->genVBOBuffers();
	fbxmodel->submit(GL_STATIC_DRAW);
    

	//----add to scene
    Cc3dSceneManager::sharedSceneManager()->getRoot()->addChild(fbxmodel);
}