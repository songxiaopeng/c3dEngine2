#include "mainWindowFuncs.h"

void keyDown(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
	switch (wParam)
	{
	case 38://��
		break;
	case 40://��
		break;
	case 37://��
		break;
	case 39://��
		break;
	case 67://c
		break;
	case 83://s
		break;
	case 70://f
		break;
	case 68://d
		break;
	case 65://a
		break;
	}

}

void keyUp(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
	switch (wParam)
	{
	case 80://p
		break;
	case 38://��
		break;
	case 40://��
		break;
	case 37://��
		break;
	case 39://��
		break;
	case 83://s
		break;
	case 70://f
		break;
	case 68://d
		break;
	case 67://c
		break;
	case 65://a
		break;
	}
}


void render(HDC hDC){
	
	//switch back to screen fbo
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);//tile-base architectureҪ��bind֮������clear����Щ
    glViewport(Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getMinX(),
               Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getMinY(),
               Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getWidth() ,
               Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getHeight());//��Ļ����
    
    if(Cc3dAppState::sharedAppState()->getIsInBackGround())return;

    //remove nodes marked as isRemoveOnNextFrame
    Cc3dSceneManager::sharedSceneManager()->performDelayRemove();
    //remove unused resource in caches (must after performDelayRemove)
    Cc3dTextureCache::sharedTextureCache()->performDelayRemoveUnusedTextures();
    Cc3dAudioCache::sharedAudioCache()->performDelayRemoveUnusedBuffersAndSources();
    //visitUpdate
    Cc3dSceneManager::sharedSceneManager()->getRoot()->visitUpdate();
    //visitDraw
    Cc3dSceneManager::sharedSceneManager()->getRoot()->visitDraw();
    //autorelease
    Cc3dAutoreleasePool::sharedAutoreleasePool()->releaseAll();

    //refresh
	SwapBuffers(hDC);
    
    C3DCHECK_GL_ERROR_DEBUG() ;
    
    C3DCHECK_AL_ERROR_DEBUG();
    Cc3dTimeCounter::sharedTimeCounter()->doCount();//Ҫ��������Ա�touchSequenceʱ���뱾֡ʱ��һ��
	
}


 void initOpenGL(){
	 

    GLenum GlewInitResult = glewInit();//must call after the window created 
    if (GLEW_OK != GlewInitResult)
    {
		c3dLog((char *)glewGetErrorString(GlewInitResult));//, "OpenGL error");
        C3DASSERT(false);
    }
	glGetError();//clear error bit


 }
 void initWithFrame(){
	//----�����
    srand(time(0));
	
	//----��ʼ��openal
	initOpenAL();
	
	//----��ʼ��opengl
	initOpenGL();

	//----openal״̬
	alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);//���þ���ģ��

    //----opengl״̬
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);//on windows, do not forget this!!!
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);// Enable point size by default on windows.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);//ָ������color buffersʱ���õ���ɫ��Ĭ��ֵΪ(0,0,0,0),��:http://msdn.microsoft.com/en-us/library/windows/desktop/dd318377(v=vs.85).aspx
    glEnableVertexAttribArray(ATTRIB_LOC_position_local);
    glEnableVertexAttribArray(ATTRIB_LOC_texCoord);
    glEnableVertexAttribArray(ATTRIB_LOC_normal_local);
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
    c3dDefaultShadersSetup();
   
    C3DCHECK_GL_ERROR_DEBUG();
    C3DCHECK_AL_ERROR_DEBUG();
    //init game
    initGame();
    
    C3DCHECK_GL_ERROR_DEBUG();
    C3DCHECK_AL_ERROR_DEBUG();
 }
 void initOpenAL(){
	//initialize OpenAL and clear the error bit.
	alutInit(NULL, 0);
	alGetError();//clear error bit
 
 }
 void teardownOpenAL(){
	alutExit();
 }
 void command(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
	 switch(wParam){

	 case ID_about:
		 {
			 DialogBox(hInstance,//ʵ�����
				 MAKEINTRESOURCE(ID_about_dlg),//�Ի�����ԴID
				 hWnd,//�����ھ��
				 DlgProc);//����Ĵ��ڹ��̺���

		 }
		 break;

	 }

 }
 
BOOL CALLBACK DlgProc (HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case  WM_INITDIALOG :
		return TRUE ;//�Ի����ʼ������
	case  WM_COMMAND : //�����
		switch (LOWORD (wParam))
		{
		case  IDOK :
		case  IDCANCEL :
			EndDialog (hDlg, 0) ;//�رնԻ���
			return TRUE ;
		case ID_LINK:
			ShellExecute(hWnd,NULL,_T("https://github.com/wantnon2/superSingleCell-c3dEngine"),NULL,NULL,      SW_SHOWMAXIMIZED);       
			break;

		}
		break ;
	}
	return FALSE ; //û�д�����FALSE
}

 bool IsExtensionSupported( char* szTargetExtension ) 
{ 
    const unsigned char *pszExtensions = NULL; 
    const unsigned char *pszStart; 
    unsigned char *pszWhere, *pszTerminator; 
  
    // Extension names should not have spaces 
    pszWhere = (unsigned char *) strchr( szTargetExtension, ' ' ); 
    if( pszWhere || *szTargetExtension == '\0' ) 
        return false; 
  
    // Get Extensions String 
    pszExtensions = glGetString( GL_EXTENSIONS ); 
  
    // Search The Extensions String For An Exact Copy 
    pszStart = pszExtensions; 
    for(;;) 
    { 
        pszWhere = (unsigned char *) strstr( (const char *) pszStart, szTargetExtension ); 
        if( !pszWhere ) 
            break; 
        pszTerminator = pszWhere + strlen( szTargetExtension ); 
        if( pszWhere == pszStart || *( pszWhere - 1 ) == ' ' ) 
            if( *pszTerminator == ' ' || *pszTerminator == '\0' ) 
                return true; 
        pszStart = pszTerminator; 
    } 
    return false; 
} 
 void lbuttonDown(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
	 isTouching=true;
	 //get mouse position in window (origin at left up)
	 //see: http://my.oschina.net/ypimgt/blog/65327
	 float x=LOWORD(lParam);
	 float y=HIWORD(lParam);
	 //y+=captionHeight+frameBoarder*2;
	 //cout<<"mos down:"<<x<<" "<<y<<endl;
	 Cc3dTouch c3dTouch=Cc3dTouch(x,y,e_c3dTouchBegan,Cc3dTimeCounter::sharedTimeCounter()->getCount());
	 Cc3dTouchSequence::sharedTouchSequence()->addTouch(c3dTouch);
	 //     NSLog(@"touchesBegan:(%f,%f)",touchPoint.x,touchPoint.y);
 }
 void lbuttonUp(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
	 isTouching=false;
	 //get mouse position in window (origin at left up)
	 //see: http://my.oschina.net/ypimgt/blog/65327
	 float x=LOWORD(lParam);
	 float y=HIWORD(lParam);
	 //y+=captionHeight+frameBoarder*2;
	 //cout<<"mos up:"<<x<<" "<<y<<endl;
	 Cc3dTouch c3dTouch=Cc3dTouch(x,y,e_c3dTouchEnd,Cc3dTimeCounter::sharedTimeCounter()->getCount());
	 Cc3dTouchSequence::sharedTouchSequence()->addTouch(c3dTouch);
	 //  NSLog(@"touchesEnded:(%f,%f)",touchPoint.x,touchPoint.y);
 }
 void mouseMove(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
	 if(isTouching){
		 //get mouse position in window (origin at left up)
		 //see: http://my.oschina.net/ypimgt/blog/65327
		 float x=LOWORD(lParam);
		 float y=HIWORD(lParam);
		 //y+=captionHeight+frameBoarder*2;
		 //cout<<"mos move:"<<x<<" "<<y<<endl;
		 Cc3dTouch c3dTouch=Cc3dTouch(x,y,e_c3dTouchMove,Cc3dTimeCounter::sharedTimeCounter()->getCount());
		 Cc3dTouchSequence::sharedTouchSequence()->addTouch(c3dTouch);
		 //       NSLog(@"touchesMoved:(%f,%f)",touchPoint.x,touchPoint.y);
	 }
	 //below code is for WM_MOUSELEAVE
	 //if we want WM_MOUSELEAVE works, we should call TrackMouseEvent
	 //see:http://www.cnblogs.com/hailoong/archive/2010/10/30/1865293.html
	 {
		 static TRACKMOUSEEVENT tme;
		 tme.cbSize = sizeof(TRACKMOUSEEVENT);
		 tme.dwFlags = TME_LEAVE;
		 tme.dwHoverTime = HOVER_DEFAULT;
		 tme.hwndTrack = hWnd;
		 TrackMouseEvent(&tme);
	 }
 }
 void mouseLeave(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
	 //----the same as WM_LBUTTONUP
	 isTouching=false;
	 //get mouse position in window (origin at left up)
	 //see: http://my.oschina.net/ypimgt/blog/65327
	 float x=LOWORD(lParam);
	 float y=HIWORD(lParam);
	 //y+=captionHeight+frameBoarder*2;
	 //cout<<"mos up:"<<x<<" "<<y<<endl;
	 Cc3dTouch c3dTouch=Cc3dTouch(x,y,e_c3dTouchEnd,Cc3dTimeCounter::sharedTimeCounter()->getCount());
	 Cc3dTouchSequence::sharedTouchSequence()->addTouch(c3dTouch);
	 //  NSLog(@"touchesEnded:(%f,%f)",touchPoint.x,touchPoint.y);

 }
 void winSize(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
	 //�������߶�
	 //http://baike.baidu.com/link?url=jsZlb4o0MUkNjSDUiKiEg7yqz-PyaVPQkh8SsKCrrCmctxxNlGCy1zDe61VofSE0iN5P_aw8Dv6KD7fDi0eXh_
	 captionHeight=GetSystemMetrics(SM_CYCAPTION);
	 //cout<<"captionHeight:"<<captionHeight<<endl;
	 //�߿�߶�
	 frameBoarder=GetSystemMetrics(SM_CYSIZEFRAME);
	 //cout<<"frameBoarder:"<<frameBoarder<<endl;
	 float width = Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenSize().x()+frameBoarder*2;
	 float height = Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenSize().y()+frameBoarder*2+captionHeight;
	 //restrict the window size
	 SetWindowPos(hWnd,NULL,0,0,width,height,SWP_NOMOVE);
 }

 void createAndInitConsole(){
	AllocConsole();   // ��������̨
    SetConsoleTitle(_T("Debug Output"));      // ���ÿ���̨���ڱ���
	// �ض��� STDIN
	{
		FILE*fp;
		errno_t eno=freopen_s(&fp,"CONIN$", "r+t", stdin);
		if(eno!=0){//���ɹ�
			MessageBox(NULL,_T("�ض���stdinʧ��!"),_T("error"),MB_OK|MB_ICONEXCLAMATION);
			assert(false);
		}
	}
	// �ض���STDOUT
	{
		FILE*fp;
		errno_t eno=freopen_s(&fp,"CONOUT$", "w+t", stdout);
		if(eno!=0){//���ɹ�
			MessageBox(NULL,_T("�ض���stdoutʧ��!"),_T("error"),MB_OK|MB_ICONEXCLAMATION);
			assert(false);
		}
	
	}
 }