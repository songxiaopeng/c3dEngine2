#include"globals.h"
typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( int );
PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = 0;

inline bool initGame(){	

wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress("wglSwapIntervalEXT");

wglSwapIntervalEXT(1);//�򿪴�ֱͬ��������֡��
//wglSwapIntervalEXT(0);//�رմ�ֱͬ��


	//-------------opengl�汾��Ϣ---------------------------------------------
	//�����http://www.opengl.org/wiki/GlGetString
	cout<<endl;
	const GLubyte* s_gl_vendor = glGetString(GL_VENDOR); 
	const GLubyte* s_gl_renderer = glGetString(GL_RENDERER);   
	const GLubyte* s_gl_version =glGetString(GL_VERSION);
	const GLubyte* s_glu_version= gluGetString(GLU_VERSION);
	cout<<"OpenGLʵ�ֳ��̣�"<<s_gl_vendor<<endl;    
	cout<<"GPU/��Ⱦ����"<<s_gl_renderer<<endl;    
	cout<<"OpenGLʵ�ְ汾�ţ�"<<s_gl_version<<endl;    
	cout<<"GLU�汾��"<<s_glu_version<<endl;   
	
	//----------------------------------------------------------------------------------------------------------------------
	srand(time(0));//�����
	//------------------------------------------------------------------------------------------------------------------------
	glClearColor(0.0,0.0,0.0,0.0);	//���������ɫ����ʱ���õ���ɫ
	glEnable(GL_DEPTH_TEST);
	//-----------------------------------------------------------------------------------------------------------------------
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//----------��ʾ
	glHint(GL_FOG_HINT,GL_FASTEST);
	glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_FASTEST);
	glHint(GL_GENERATE_MIPMAP_HINT,GL_FASTEST);
	glHint(GL_LINE_SMOOTH_HINT,GL_FASTEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_FASTEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_FASTEST); 
	glHint(GL_POLYGON_SMOOTH_HINT,GL_FASTEST); 
	glHint(GL_TEXTURE_COMPRESSION_HINT,GL_FASTEST);
	//----����
	//vbo
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	//ʵ�ⷢ��GL_POINT_SMOOTH��GL_LINE_SMOOTH��Ӱ��Ч�ʣ��������ﲻ������ȫ�ֿ�����
	//ֻ�ڷ��ò��ɵ�ʱ����ʱ����
//	//glEnable(GL_POINT_SMOOTH);
//	//glEnable(GL_LINE_SMOOTH);
	glEnable(GL_LIGHTING);//��������
	glEnable(GL_LIGHT0);//����LIGHT0
	//-----------��ɫ����
	glEnable(GL_COLOR_MATERIAL);//����������ʹ����ɫ����ĳЩ���ʲ��������Ч��
	                            //����ɫ������Щ���ʲ�����glColorMaterial�����趨
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);//GL_FRONT_AND_BACK��GL_AMBIENT_AND_DIFFUSE��ΪĬ��ֵ

	//-------------------------------------------����-------------------------------------------------------------------------- 
	//----ѡ����������
	//������GL_FLAT��GL_SMOOTH
	glShadeModel(GL_SMOOTH);//Ϊ��ʹ����Բ����Ŀǰֻ�������õ��ǵ㷨������
	//----���ò���
	//���ԶԲ�ͬ����GL_FRONT,GL_BACK,GL_FRONT����������Ŀ��
	//GL_AMBIENT(������ɫ),GL_DIFFUSE(ɢ����ɫ),GL_AMBIENT_AND_DIFFUSE,GL_SPECULAR(������ɫ),GL_SHININESS(����ָ��),
	//GL_EMISSION(�Է���)
	//����ֻ��GL_SPECULAR��GL_SHININESS�������ã�������Ĭ��ֵ
	GLfloat mat_ambient[]={1,1,1,1};
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);//��������ɫ
	GLfloat mat_diffuse[]={1,1,1,1};
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);//ɢ����ɫ
	glColor4f(1,1,1,1);//��ɫ����diffuse��color�󶨣������൱������diffuse��
	GLfloat mat_specular[]={0,0,0,1};
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);//������ɫ
	GLfloat mat_shininess[]={0};
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);//����ָ��
	GLfloat mat_emission[]={0.15,0.15,0.15,1};
	glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);//�Է���
	//----��ֹ������һ�����Ŷ���ɵĳ��ȸı䣬��glEnable(GL_NORMALIZE)Ч�ʸ�
	glDisable(GL_NORMALIZE);
	glEnable(GL_RESCALE_NORMAL);//ֻ�е���������������������Ϊһ�����ţ����������������������ͬ��
	                         //���ҷ������Ϊ��λ����ʱ���˷������ܵõ���ȷ���
	
	//----���ù�ԴLIGHT0
	//����8����ԴLIGHT0~LIGHT7
	//��������GL_AMBIENT,GL_DIFFUSE,GL_SPECULAR,GL_POSITION,GL_SPOT_DIRECTION,GL_SPOT_EXPONENT,GL_SPOT_CUTOFF,
	//GL_CONSTANT_ATTENUATION,GL_LINEAR_ATTENUATION,GL_QUADRATIC_ATTENUATION
	//����ֻ��GL_DIFFUSE��GL_SPECULAR�������ã�������Ĭ��ֵ
	GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);//������
	glLightfv(GL_LIGHT0,GL_SPECULAR,light0_specular);//�����
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);//������

	//----���ù���ģ��
	//����GL_LIGHT_MODEL_AMBIENT,GL_LIGHT_MODEL_LOCAL_VIEWR,GL_LIGHT_MODEL_TWO_SIDE,GL_LIGHT_MODEL_COLOR_CONTROL
	//����ֻ��GL_LIGHT_MODEL_AMBIENT����һ�����ã�������Ĭ��ֵ
	GLfloat lmodel_ambient[]={0.5,0.5,0.5,1.0};
   	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);
	glColor4f(1,1,1,1);

	//----���ñ����޳�
	//ע�⣬cullFace�ǰ����㷽����˳ʱ�뻹����ʱ�����޳��ģ������ύ�ķ����������޹�
	glCullFace(GL_BACK);//���ر��棬����Ѳ�����ΪGL_FRONT���������档
	glDisable(GL_CULL_FACE);
	//------------------------����-----------------------------------
	glEnable(GL_TEXTURE_2D);
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);//glDepthFunc��Ĭ��ֵ����GL_LESS


	//------------------------------------------------------
	
	//-----------------------����fbxģ��---------------------------------------
	//����fbxģ��
	cout<<endl;
	
	modelx2.Init_and_load("data\\model_fbx\\dance1\\dance1.fbx");

	modelx2.triangulate_loadTextures_preprocess();
	
	//���ö���

	modelx2.setTime(0);
	modelx2.selectAnimation(0);


	
	
	SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);
	//-------------------------------------------------------------------------------------------
	return true;

}