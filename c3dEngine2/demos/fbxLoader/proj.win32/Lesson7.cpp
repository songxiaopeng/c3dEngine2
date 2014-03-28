#include   "resource.h "
//------------
#include"myh.h"
#include "initGame.h"
#include "logic.h"

//�˵��߶�
float heightOfMenu=20;//ʵ��ֵ����ֵ���������ӿڣ�ʹ�ӿڲ����˵���ס
//��������ʱ���ĳߴ�
float width0=1144;
float height0=width0/2+heightOfMenu;

//��GetWindowRect��õĳߴ�
float width_GetRect=0;
float height_GetRect=0;


int mosx=0;//�������
int mosy=0;
bool pause=false;


//�Ƿ������Ļ
bool updateDraw=true;
//��ʱ���
long tf=0,t=0,dt=0;//tf�ϴν���idle��t���ν���idle��dt�������ϴν���idleʱ����
long acudt_pause=0;//����ͣ������ϴν��и����뱾�ν��и��µ�ʱ����

//----����״̬(��Щδ�õ�)
bool upKeyDown=false;
bool downKeyDown=false;
bool leftKeyDown=false;
bool rightKeyDown=false;
bool sKeyDown=false;
bool fKeyDown=false;
bool eKeyDown=false;
bool jKeyDown=false;
bool iKeyDown=false;
bool kKeyDown=false;
bool lKeyDown=false;
bool dKeyDown=false;
bool aKeyDown=false;
bool cKeyDown=false;
//
bool supportVBO=false;//�Ƿ�֧��vbo
bool supportFBO=false;//�Ƿ�֧��fbo
//------------------
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application


LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

void KillGLWindow()								// Properly Kill The Window
{

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,_T("Release Of DC And RC Failed."),_T("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,_T("Release Rendering Context Failed."),_T("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,_T("Release Device Context Failed."),_T("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,_T("Could Not Release hWnd."),_T("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass(_T("OpenGL"),hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,_T("Could Not Unregister Class."),_T("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*/
BOOL CreateGLWindow(LPCWSTR title, int winwidth, int winheight, int nbit_colorDepth,int nbit_zDepth)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)winwidth;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)winheight;		// Set Bottom Value To Requested Height


	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName =MAKEINTRESOURCE(IDR_MENU2);//�˵�
	wc.lpszClassName	= _T("OpenGL");								// Set The Class Name



	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,_T("Failed To Register The Window Class."),_T("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								_T("OpenGL"),							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,_T("Window Creation Error."),_T("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		nbit_colorDepth,							// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,//alpha����λ����Ŀǰδʹ��alpha���ԣ�������Ϊ0��������ʹ�ã���Ҫ�����޸Ĵ���!!
		0,											// Shift Bit Ignored
		0,											// Accumulation Bufferλ��
		0, 0, 0, 0,									// Accumulation Bits Ignored
		nbit_zDepth,								// Z-Buffer (Depth Buffer)  
		8,//ģ�建��λ��
		0,											// Auxiliary Bufferλ��
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,_T("Can't Create A GL Device Context."),_T("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,_T("Can't Find A Suitable PixelFormat."),_T("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,_T("Can't Set The PixelFormat."),_T("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,_T("Can't Create A GL Rendering Context."),_T("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,_T("Can't Activate The GL Rendering Context."),_T("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}


	

	glViewport(0,0,width0,height0-heightOfMenu);//�����ӿ�

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window

	return TRUE;									// Success
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
			ShellExecute(hWnd,NULL,_T("http://code.google.com/p/recombination-3d-4-on-the-beam/"),NULL,NULL,      SW_SHOWMAXIMIZED);       
			break;

		}
		break ;
	}
	return FALSE ; //û�д�����FALSE
}

void onPaint(HDC hDC);


LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		case WM_COMMAND:
		{
			switch(wParam){
			
			case ID_cheat:
				{
					
				}
				break;
			case ID_rules:
				ShellExecute( 0,_T("open"),_T("����3D-IV-5.3-��Ϸ����.mht"),0,0,SW_SHOW);
				break;
			case ID_shadow:
				{
				

				}
				break;
			case ID_fog:
				{
					
				}
				break;
			case ID_reflect:
				{
					
				
				}
				break;
			case ID_components:
				{
					
				}
				break;
			case ID_about:
				{
				
				}
				break;
			case ID_keymos:
				{
					
					
				}
				break;
				
			}
			
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			switch (wParam)
			{
				case 38://��
					upKeyDown=true;
					break;
				case 40://��
					downKeyDown=true;
					break;
				case 37://��
					leftKeyDown=true;
					break;
				case 39://��
					rightKeyDown=true;
					break;
				case 67://c
					cKeyDown=true;
					
					break;
				case 83://s
					sKeyDown=true;
					break;
				case 70://f
					fKeyDown=true;
					break;
				case 68://d
					dKeyDown=true;
					break;
				case 65://a
					aKeyDown=true;
					break;
				}
			return 0;								// Jump Back
		}
			
		case WM_KEYUP:								// Has A Key Been Released?
		{
			//keys[wParam] = FALSE;					// If So, Mark It As FALSE
			switch (wParam)
			{
			case 80://p
			
				break;
			case 38://��
				upKeyDown=false;
				break;
			case 40://��
				downKeyDown=false;
				break;
			case 37://��
				leftKeyDown=false;
				break;
			case 39://��
				rightKeyDown=false;
				break;
			case 83://s
				sKeyDown=false;
				break;
			case 70://f
				fKeyDown=false;
				break;
			case 68://d
				dKeyDown=false;
				break;
			case 67://c
				cKeyDown=false;
				break;
			case 65://a
				aKeyDown=false;
				break;
			}
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			if(width_GetRect!=0&&height_GetRect!=0){//���width_GetRect��height_GetRect�Ѿ���ʼ��
				//���Ƹı䴰�ڴ�С
				SetWindowPos(hWnd,NULL,0,0,width_GetRect,height_GetRect,SWP_NOMOVE);
			}
			
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

		
		
AllocConsole();   // ��������̨
    SetConsoleTitle(_T("Debug Output"));      // ���ÿ���̨���ڱ���
	// �ض��� STDIN
	{
		FILE*fp;
		errno_t eno=freopen_s(&fp,"CONIN$", "r+t", stdin);
		if(eno!=0){//���ɹ�
			MessageBox(NULL,_T("�ض���stdinʧ��!"),_T("error"),MB_OK|MB_ICONEXCLAMATION);
			exit(0);
		}
	}
	// �ض���STDOUT
	{
		FILE*fp;
		errno_t eno=freopen_s(&fp,"CONOUT$", "w+t", stdout);
		if(eno!=0){//���ɹ�
			MessageBox(NULL,_T("�ض���stdoutʧ��!"),_T("error"),MB_OK|MB_ICONEXCLAMATION);
			exit(0);
		}
	
	}
	
	 
	


	// Create Our OpenGL Window
	int nbit_colorDepth=24;//16;//24;
	int nbit_zDepth=32;//32;

	if (!CreateGLWindow((LPCWSTR)_T("opengl - openal | ����3D IV�����Ͼ���"),width0,height0,nbit_colorDepth,nbit_zDepth))
	{
		return 0;									// Quit If Window Was Not Created
	}
	//��GetWindowRect���»�ô��ڴ�С�������width0,height0��һ��
	{
		RECT rect;
		GetWindowRect(hWnd,&rect);
		width_GetRect=rect.right-rect.left;
		height_GetRect=rect.bottom-rect.top;
	}
	
	//��Ϸ��ʼ����������ڳ�ʼ��opengl(��������)��openal֮��
	if(initGame()==false){
		return 0;
	}

	tf=t=clock();//��ʼ��ʱ��
	

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{//--------------------------idle
	//		cout<<acudt_pause<<endl;
			tf=t;
			t=clock();
			dt=t-tf;//��һ�ν���idle�����ν���idle��ʱ����
			//�߼����������е�λ������Ҫ��dtΪ�ο����У��Ա�֤�����ƶ��ٶ���֡���޹�
			if(pause){
				acudt_pause+=dt;
				if(acudt_pause>=500){//����ͣ����£�ÿ���ϳ���ʱ��ˢ��һ�Σ���Ϊ��ֹ����
					acudt_pause=0;
					onPaint(hDC);
				}
			}else{
				acudt_pause=0;//���ǲ�����ͣģ�ͣ���acudt_pause����
				updateDraw=true;
				{
					updateLogic(min(dt,100),//������Ӧ��ָdt�����߼����������dt����ᷢ����������������ǿ����dt������
						t);
					onPaint(hDC);
				}
				
			}
		}
	}

	// Shutdown
	cout<<"�����˳�����..."<<endl;
	//--------------------- һ��Ҫ������ٿ���̨�ʹ��� -----------------------------
	 FreeConsole();//���ٿ���̨
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
