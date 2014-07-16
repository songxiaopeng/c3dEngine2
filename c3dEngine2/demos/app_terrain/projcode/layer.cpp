//
//  ground.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-12-20.
//
//

#include "layer.h"
#include "globalVars.h"
bool Clayer::init(){
	//----button
	m_button=new Cbutton();
	m_button->autorelease();
	{	
		m_button->setName("button");
		m_button->init(64,32,"terrain_resource/button.png","terrain_resource/button_dn.png","terrain_resource/text1.png");

		m_button->setPos(Cc3dVector4(50,400,0,1));
		m_button->setCamera(camera2D);

		m_button->genVBOBuffers();
		m_button->submit(GL_STATIC_DRAW);


	}
	 



	 //--ground

	m_ground=new Cground();
	m_ground->autorelease();
	m_ground->setName("ground");

	//�������ݲ����ɵ���--abc

	//----����--abc
	const float blockWidth=2872;
	const float blockHeight=2872;
	//����texture
	Cc3dTexture*texture=Cc3dTextureCache::sharedTextureCache()->addImage("terrain_resource/texture_2048x2048.png");
	//��ʼ��ground
	Cc3dRect rect(-blockWidth/2, -blockHeight/2, blockWidth, blockHeight);
	m_ground->initWithFile("terrain_resource/heightMap.bmp",rect,0.3,9,texture);
	m_ground->setUVScale(1);
	m_ground->getMesh()->setDiffuseRGB(1, 1, 1);
	m_ground->getMesh()->setAmbient(0.2, 0.2, 0.2);
	m_ground->setCamera(camera);
	m_ground->setLight(light0);
	m_ground->setPassUnifoCallback(buildinProgramPassUnifoCallback_classicLighting);
	m_ground->setProgram(Cc3dProgramCache::sharedProgramCache()->getProgramByName("classicLighting"));
	m_ground->setReso(10);//

	//�ύ����--abc
	m_ground->submitVertex(GL_STATIC_DRAW);
	m_ground->getMesh()->getSubMeshByIndex(0)->clearMeshData();

   
	//----add to this layer
    this->addChild(m_ground);
	this->addChild(m_button);
	return true;
}