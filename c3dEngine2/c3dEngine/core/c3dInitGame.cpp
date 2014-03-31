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
	//----�����
    srand(time(0));
	
	//----��ʼ��openal
	initOpenAL();
	
	//----��ʼ��opengl
	initOpenGL();

	//----openal״̬
	alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);//���þ���ģ��
    alListenerf(AL_GAIN, 1.0);//set listener gain

    //----opengl״̬
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);//on windows, do not forget this!!!
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);// Enable point size by default on windows.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);//ָ������color buffersʱ���õ���ɫ��Ĭ��ֵΪ(0,0,0,0),��:http://msdn.microsoft.com/en-us/library/windows/desktop/dd318377(v=vs.85).aspx
    glEnableVertexAttribArray(ATTRIB_LOC_position);
    glEnableVertexAttribArray(ATTRIB_LOC_texCoord);
    glEnableVertexAttribArray(ATTRIB_LOC_normal);
	glEnableVertexAttribArray(ATTRIB_LOC_color);
    glEnableVertexAttribArray(ATTRIB_LOC_texCoord2);
	
	//----������ֱͬ��������֡��Ϊÿ��60֡
	typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( int );
	PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = 0;
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress("wglSwapIntervalEXT");
	wglSwapIntervalEXT(1);//1Ϊ������0Ϊ�ر�
    //----��ѯopengl�汾��Ϣ
	//�����http://www.opengl.org/wiki/GlGetString
	const GLubyte* s_gl_vendor = glGetString(GL_VENDOR); 
	const GLubyte* s_gl_renderer = glGetString(GL_RENDERER);   
	const GLubyte* s_gl_version =glGetString(GL_VERSION);
	const GLubyte* s_glu_version= gluGetString(GLU_VERSION);
	cout<<"OpenGLʵ�ֳ��̣�"<<s_gl_vendor<<endl;    
	cout<<"GPU/��Ⱦ����"<<s_gl_renderer<<endl;    
	cout<<"OpenGLʵ�ְ汾�ţ�"<<s_gl_version<<endl;    
	cout<<"GLU�汾��"<<s_glu_version<<endl;   
	//����Ƿ�֧��opengl 2.0
	cout<<endl;
	cout<<"���ϵͳ�Ƿ�֧��openGL 2.0..."<<endl;
	glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		cout<<"ϵͳ֧��openGL 2.0!"<<endl;
	else {
		cout<<"ϵͳ��֧��openGL 2.0!"<<endl;
		system("pause");
		C3DASSERT(false);
	}
	//GLSL version
    const GLubyte* s= glGetString(GL_SHADING_LANGUAGE_VERSION);
    cout<<s<<endl;
    
	//----��ȡ�豸��Ϣ
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
