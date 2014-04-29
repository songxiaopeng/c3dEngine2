//
//  c3dInitGame.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-12-20.
//
//

#include "c3dInitGame.h"
#include "c3dALPlatformDepend.h"
#include "c3dGLPlatformDepend.h"
//
void initOpenGL(){
	initOpenGL_plat();
}
void initOpenAL(){
	initOpenAL_plat();
}
void teardownOpenAL(){
	teardownOpenAL_plat();
}
void c3dInitGame(){
	//----start global timer
	Cc3dGlobalTimer::sharedGlobalTimer()->start();
	//----�����--abc
    srand(time(0));
	//----��ʼ��openal
	initOpenAL();
	//----��ʼ��opengl
	initOpenGL();
	//----openal״̬--abc
	alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);//���þ���ģ��--abc
    alListenerf(AL_GAIN, 1.0);//set listener gain
    //----opengl״̬--abc
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
#if (C3D_TARGET_PLATFORM == C3D_PLATFORM_WIN32)
	glEnable(GL_TEXTURE_2D);//on windows, do not forget this!!!
#endif
    ////glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);// Enable point size by default on windows.(wait, it is not support on iOS!)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);//ָ������color buffersʱ���õ���ɫ��Ĭ��ֵΪ(0,0,0,0),��:http://msdn.microsoft.com/en-us/library/windows/desktop/dd318377(v=vs.85).aspx
    glEnableVertexAttribArray(ATTRIB_LOC_position);
    glEnableVertexAttribArray(ATTRIB_LOC_texCoord);
    glEnableVertexAttribArray(ATTRIB_LOC_normal);
	glEnableVertexAttribArray(ATTRIB_LOC_color);
    glEnableVertexAttribArray(ATTRIB_LOC_texCoord2);
	//----show system info
    Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->showSystemInfo();
	//----��ȡ�豸��Ϣ--abc
    cout<<"screenSize: "<<Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenSize().x()<<" "<<Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenSize().y()<<endl;
    cout<<"resolution: "<<Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getResolutionSize().x()<<" "<<Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getResolutionSize().y()<<endl;
    //----����Ĭ��shaderProgam
    buildinProgramSetUp();
   
    C3DCHECK_GL_ERROR_DEBUG();
    C3DCHECK_AL_ERROR_DEBUG();
    //init game
    initGame();
    
    C3DCHECK_GL_ERROR_DEBUG();
    C3DCHECK_AL_ERROR_DEBUG();
}
