//
//  initGame.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-12-20.
//
//

#include "initGame.h"
#include "c3d.h"
#include "globalVars.h"
#include "ground.h"
void initGame(){

	//----light
	{
		light0=new Cc3dLight();
		light0->autorelease();
		light0->retain();
		light0->setPos(1000,500,2000);
		light0->setAmbient(0.5,0.5,0.5);
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
        camera->setzFar(100000);
		float eyePos[3]={0,300,1800};//{0,500,100};//{0,300,1800};
        float eyeTg[3]={0,0,0};
        float up[3]={0,1,0};
        camera->setEyePos(Cc3dVector3(eyePos).toV4(1));
        camera->setCenter(Cc3dVector3(eyeTg).toV4(1));
        camera->setUp(Cc3dVector3(up).toV4(0));
        camera->updateFrustum();
    }

	glPolygonMode(GL_FRONT_AND_BACK   ,GL_LINE   );

	 //--ground
  
        Cground*m_ground=new Cground();
        m_ground->autorelease();
        m_ground->setName("ground");
        
        //加载数据并生成地形
        
        //----地面
		const float blockWidth=331.371*8.67;
		const float blockHeight=331.371*8.67;
        //加载texture
        Cc3dTexture*texture=Cc3dTextureCache::sharedTextureCache()->addImage("terrain_resource/texture_2048x2048.png");
        //初始化ground
        Cc3dRect rect(-blockWidth/2, -blockHeight/2, blockWidth, blockHeight);
        m_ground->init("terrain_resource/heightMap.bmp",rect,0.3,9,texture);
        m_ground->setUVScale(1);
        m_ground->getMesh()->setDiffuseRGB(1, 1, 1);
        m_ground->getMesh()->setAmbient(0.2, 0.2, 0.2);
        m_ground->setCamera(camera);
        m_ground->setLight(light0);
        m_ground->setPassUnifoCallback(buildinProgramPassUnifoCallback_classicLighting);
        m_ground->setProgram(Cc3dProgramCache::sharedProgramCache()->getProgramByName("classicLighting"));
		m_ground->setReso(20000);//(5000);//
        //提交数据
        m_ground->submitVertex(GL_STATIC_DRAW);
        m_ground->getMesh()->getSubMeshByIndex(0)->clearMeshData();
        
    

	//----add to scene
    Cc3dSceneManager::sharedSceneManager()->getRoot()->addChild(m_ground);
}