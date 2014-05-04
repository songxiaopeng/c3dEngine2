//
//  initGame.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-12-20.
//
//

#include "initGame.h"
#include "c3d.h"
#include "c3dExtension.h"
#include "globalVars.h"
#include "extension.h"
void initGame(){
	Cc3dRect screenRect=Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect();

	//----light
	{
		light0=new Cc3dLight();
		light0->autorelease();
		light0->retain();
		light0->setPos(1000,5000,1000);//(50,200,500);
		light0->setSpecular(0.4,0.4,0.4);
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
        camera2D->autorelease();
        camera2D->retain();//must retain
        camera2D->setRange(range);
        camera2D->setProjectionMode(ec3dOrthographicMode);
    }
    //----camera
    {
        camera=new Cc3dCamera();
        camera->autorelease();
        camera->retain();//must retain
        camera->setFovy(70);
        camera->setAspect((float)Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getWidth()/Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getHeight());
        camera->setzNear(0.5);
        camera->setzFar(10000);
        float eyePos[3]={0,30,50};
        float eyeTg[3]={0,30,0};
        float up[3]={0,1,0};
        camera->setEyePos(Cc3dVector3(eyePos).toV4(1));
        camera->setCenter(Cc3dVector3(eyeTg).toV4(1));
        camera->setUp(Cc3dVector3(up).toV4(0));
        camera->updateFrustum();
    }

	//load fbx
	string fbxFilePath="fbxLoader_resource/girl/girl.fbx";
	float aniFrameInterval=1.0f/10;//1.0f/25;//frame interval value we want (second)
	Cc3dSkinActor*actor=Cc3dFbxLoader::sharedFbxLoader()->load(fbxFilePath.c_str(),aniFrameInterval);
	//actor is just for export, no need to fully set up and add to scene
	// actor->setPos(Cc3dVector4(0,0,0,1));
	// actor->setLight(light0);
    // actor->setCamera(camera);
	// actor->setProgram(Cc3dProgramCache::sharedProgramCache()->getProgramByName("classicLighting"));
    // actor->setPassUnifoCallback(buildinProgramPassUnifoCallback_classicLighting);
    // actor->genVBOBuffers();
 	// actor->submit(GL_STATIC_DRAW);
	// Cc3dSceneManager::sharedSceneManager()->getRoot()->addChild(actor);

	//export to my own format
	//do not use girl.cfc (do not use dot in folderName), because it can cause getFullPath fail on iOS(on iOS, the getFullPath function is not implemented very well)
	//export values only
	{
		string exportPath="export/girl_cfc";
		bool valueOnly=true;//export values only. small, but not very readable.
		cout<<"export values only..."<<endl;
		actor->doExport(exportPath,valueOnly);
		cout<<"export done! model has exported to:"<<exportPath<<endl;
	}
	//export values and keys
	{
		string exportPath="export/girl_readable_cfc";
		bool valueOnly=false;//export values and keys. big, but more readable. 
		cout<<"export values and keys..."<<endl;
		actor->doExport(exportPath,valueOnly);
		cout<<"export done! model has exported to:"<<exportPath<<endl;
	}

	//text
	Cboard*text=new Cboard();
	text->init(240,30,"exportFbxToMyOwnFormat_resource/text.png");
	text->setPos(Cc3dVector4((screenRect.getMinX()+screenRect.getMaxX())/2,(screenRect.getMinY()+screenRect.getMaxY())/2,0,1));
	text->setLight(light0);
    text->setCamera(camera2D);
	text->genVBOBuffers();
	text->submit(GL_STATIC_DRAW);
	//text add to scene
	Cc3dSceneManager::sharedSceneManager()->getRoot()->addChild(text);
}