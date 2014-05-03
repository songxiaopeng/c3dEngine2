//
//  mainWindowFuncs.h
//  c3d
//
//  Created by apple on 14-5-3.
//
//

#ifndef __c3d__mainWindowFuncs__
#define __c3d__mainWindowFuncs__

#include <iostream>
using namespace std;
//
#include "c3dSceneManger.h"
#include "c3dAutoreleasePool.h"
#include "c3dDeviceAndOSInfo.h"
#include "c3dAppState.h"
#include "c3dTextureCache.h"
#include "c3dAudioCache.h"
#include "c3dGlobalTimer.h"
#include "c3dProgramSetUp.h"
#include "c3dInitGame.h"
void render(EAGLContext*context, GLuint frameBuffer,GLuint colorRenderBuffer);
void initWithFrame();
#endif /* defined(__c3d__mainWindowFuncs__) */
