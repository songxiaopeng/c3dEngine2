#include"globals.h"
typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( int );
PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = 0;

inline bool initGame(){	

wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress("wglSwapIntervalEXT");

wglSwapIntervalEXT(1);//打开垂直同步，限制帧率
//wglSwapIntervalEXT(0);//关闭垂直同步


	//-------------opengl版本信息---------------------------------------------
	//详见：http://www.opengl.org/wiki/GlGetString
	cout<<endl;
	const GLubyte* s_gl_vendor = glGetString(GL_VENDOR); 
	const GLubyte* s_gl_renderer = glGetString(GL_RENDERER);   
	const GLubyte* s_gl_version =glGetString(GL_VERSION);
	const GLubyte* s_glu_version= gluGetString(GLU_VERSION);
	cout<<"OpenGL实现厂商："<<s_gl_vendor<<endl;    
	cout<<"GPU/渲染器："<<s_gl_renderer<<endl;    
	cout<<"OpenGL实现版本号："<<s_gl_version<<endl;    
	cout<<"GLU版本："<<s_glu_version<<endl;   
	
	//----------------------------------------------------------------------------------------------------------------------
	srand(time(0));//随机数
	//------------------------------------------------------------------------------------------------------------------------
	glClearColor(0.0,0.0,0.0,0.0);	//设置清除颜色缓冲时所用的颜色
	glEnable(GL_DEPTH_TEST);
	//-----------------------------------------------------------------------------------------------------------------------
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//----------暗示
	glHint(GL_FOG_HINT,GL_FASTEST);
	glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_FASTEST);
	glHint(GL_GENERATE_MIPMAP_HINT,GL_FASTEST);
	glHint(GL_LINE_SMOOTH_HINT,GL_FASTEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_FASTEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_FASTEST); 
	glHint(GL_POLYGON_SMOOTH_HINT,GL_FASTEST); 
	glHint(GL_TEXTURE_COMPRESSION_HINT,GL_FASTEST);
	//----启用
	//vbo
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	//实测发现GL_POINT_SMOOTH和GL_LINE_SMOOTH较影响效率，所以这里不将它们全局开启，
	//只在非用不可的时候临时开启
//	//glEnable(GL_POINT_SMOOTH);
//	//glEnable(GL_LINE_SMOOTH);
	glEnable(GL_LIGHTING);//开启光照
	glEnable(GL_LIGHT0);//开启LIGHT0
	//-----------颜色材质
	glEnable(GL_COLOR_MATERIAL);//开启它可以使用颜色代替某些材质参数，提高效率
	                            //用颜色代替哪些材质参数用glColorMaterial进行设定
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);//GL_FRONT_AND_BACK和GL_AMBIENT_AND_DIFFUSE均为默认值

	//-------------------------------------------光照-------------------------------------------------------------------------- 
	//----选择明暗技术
	//可以用GL_FLAT或GL_SMOOTH
	glShadeModel(GL_SMOOTH);//为了使球体圆滑（目前只有球体用的是点法向量）
	//----设置材质
	//可以对不同的面GL_FRONT,GL_BACK,GL_FRONT设置如下项目：
	//GL_AMBIENT(环境颜色),GL_DIFFUSE(散射颜色),GL_AMBIENT_AND_DIFFUSE,GL_SPECULAR(镜面颜色),GL_SHININESS(镜面指数),
	//GL_EMISSION(自发光)
	//这里只对GL_SPECULAR和GL_SHININESS作了设置，其余用默认值
	GLfloat mat_ambient[]={1,1,1,1};
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);//环境光颜色
	GLfloat mat_diffuse[]={1,1,1,1};
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);//散射颜色
	glColor4f(1,1,1,1);//颜色（等diffuse与color绑定，它就相当于设置diffuse）
	GLfloat mat_specular[]={0,0,0,1};
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);//镜面颜色
	GLfloat mat_shininess[]={0};
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);//镜面指数
	GLfloat mat_emission[]={0.15,0.15,0.15,1};
	glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);//自发光
	//----防止法线因一致缩放而造成的长度改变，比glEnable(GL_NORMALIZE)效率高
	glDisable(GL_NORMALIZE);
	glEnable(GL_RESCALE_NORMAL);//只有当法线向量所经历的缩放为一致缩放（即各个方向的缩放数量相同）
	                         //并且法线最初为单位向量时，此方法才能得到正确结果
	
	//----设置光源LIGHT0
	//共有8个光源LIGHT0~LIGHT7
	//设置项有GL_AMBIENT,GL_DIFFUSE,GL_SPECULAR,GL_POSITION,GL_SPOT_DIRECTION,GL_SPOT_EXPONENT,GL_SPOT_CUTOFF,
	//GL_CONSTANT_ATTENUATION,GL_LINEAR_ATTENUATION,GL_QUADRATIC_ATTENUATION
	//这里只对GL_DIFFUSE和GL_SPECULAR进行设置，其余用默认值
	GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);//漫反射
	glLightfv(GL_LIGHT0,GL_SPECULAR,light0_specular);//镜面光
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);//环境光

	//----设置光照模型
	//包括GL_LIGHT_MODEL_AMBIENT,GL_LIGHT_MODEL_LOCAL_VIEWR,GL_LIGHT_MODEL_TWO_SIDE,GL_LIGHT_MODEL_COLOR_CONTROL
	//这里只对GL_LIGHT_MODEL_AMBIENT进行一下设置，其余用默认值
	GLfloat lmodel_ambient[]={0.5,0.5,0.5,1.0};
   	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);
	glColor4f(1,1,1,1);

	//----设置背面剔除
	//注意，cullFace是按顶点方向是顺时针还是逆时针来剔除的，而与提交的法向量方向无关
	glCullFace(GL_BACK);//隐藏背面，如果把参数改为GL_FRONT则隐藏正面。
	glDisable(GL_CULL_FACE);
	//------------------------纹理-----------------------------------
	glEnable(GL_TEXTURE_2D);
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);//glDepthFunc的默认值就是GL_LESS


	//------------------------------------------------------
	
	//-----------------------加载fbx模型---------------------------------------
	//加载fbx模型
	cout<<endl;
	
	modelx2.Init_and_load("data\\model_fbx\\dance1\\dance1.fbx");

	modelx2.triangulate_loadTextures_preprocess();
	
	//设置动画

	modelx2.setTime(0);
	modelx2.selectAnimation(0);


	
	
	SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);
	//-------------------------------------------------------------------------------------------
	return true;

}