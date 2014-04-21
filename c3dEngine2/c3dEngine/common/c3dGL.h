//
//  c3dGL.h
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-11-13.
//
//

#ifndef __HelloOpenGL__c3dGL__
#define __HelloOpenGL__c3dGL__
#if (C3D_TARGET_PLATFORM == C3D_PLATFORM_WIN32) 
	#include "GL/glew.h"
//----------------------------
	//put stdlib.h before glut.h is to solve the exit-redefinition error
    //see: http://stackoverflow.com/questions/14402/glut-exit-redefinition-error
	#include <stdlib.h>
	#include "GL/glut.h"
//----------------------------	
	#include "GL/gl.h"
	#include "GL/glext.h"
	#include "GL/glu.h"
	#include "GL/GLAUX.H"
#else
    #include <OpenGLES/ES2/gl.h>
#endif

#endif /* defined(__HelloOpenGL__c3dGL__) */
