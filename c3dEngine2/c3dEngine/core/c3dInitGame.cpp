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
	//----随机数
    srand(time(0));
	
	//----初始化openal
	initOpenAL();
	
	//----初始化opengl
	initOpenGL();

	//----openal状态
	alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);//设置距离模型
    alListenerf(AL_GAIN, 1.0);//set listener gain

    //----opengl状态
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);//on windows, do not forget this!!!
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);// Enable point size by default on windows.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);//指定清理color buffers时所用的颜色，默认值为(0,0,0,0),见:http://msdn.microsoft.com/en-us/library/windows/desktop/dd318377(v=vs.85).aspx
    glEnableVertexAttribArray(ATTRIB_LOC_position);
    glEnableVertexAttribArray(ATTRIB_LOC_texCoord);
    glEnableVertexAttribArray(ATTRIB_LOC_normal);
	glEnableVertexAttribArray(ATTRIB_LOC_color);
    glEnableVertexAttribArray(ATTRIB_LOC_texCoord2);
	
	//----开启垂直同步，限制帧率为每秒60帧
	typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( int );
	PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = 0;
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress("wglSwapIntervalEXT");
	wglSwapIntervalEXT(1);//1为开启，0为关闭
    //----查询opengl版本信息
	//详见：http://www.opengl.org/wiki/GlGetString
	const GLubyte* s_gl_vendor = glGetString(GL_VENDOR); 
	const GLubyte* s_gl_renderer = glGetString(GL_RENDERER);   
	const GLubyte* s_gl_version =glGetString(GL_VERSION);
	const GLubyte* s_glu_version= gluGetString(GLU_VERSION);
	cout<<"OpenGL实现厂商："<<s_gl_vendor<<endl;    
	cout<<"GPU/渲染器："<<s_gl_renderer<<endl;    
	cout<<"OpenGL实现版本号："<<s_gl_version<<endl;    
	cout<<"GLU版本："<<s_glu_version<<endl;   
	//检查是否支持opengl 2.0
	cout<<endl;
	cout<<"检查系统是否支持openGL 2.0..."<<endl;
	glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		cout<<"系统支持openGL 2.0!"<<endl;
	else {
		cout<<"系统不支持openGL 2.0!"<<endl;
		system("pause");
		C3DASSERT(false);
	}
	//GLSL version
    const GLubyte* s= glGetString(GL_SHADING_LANGUAGE_VERSION);
    cout<<s<<endl;
    
	//----获取设备信息
    cout<<"screenSize: "<<Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenSize().x()<<" "<<Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenSize().y()<<endl;
    cout<<"resolution: "<<Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getResolutionSize().x()<<" "<<Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getResolutionSize().y()<<endl;
    //----创建默认shaderProgam
    buildinProgramSetUp();
   
    C3DCHECK_GL_ERROR_DEBUG();
    C3DCHECK_AL_ERROR_DEBUG();
    //init game
    initGame();
    
    C3DCHECK_GL_ERROR_DEBUG();
    C3DCHECK_AL_ERROR_DEBUG();
}
