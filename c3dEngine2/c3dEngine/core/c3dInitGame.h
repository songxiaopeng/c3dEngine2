//
//  c3dInitGame.h
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-12-20.
//
//

#ifndef __HelloOpenGL__c3dInitGame__
#define __HelloOpenGL__c3dInitGame__

#include <iostream>
using namespace std;
//
#include "c3dGestureAnalyzer.h"
#include "c3dSceneManger.h"
#include "c3dAutoreleasePool.h"
#include "c3dDeviceAndOSInfo.h"
#include "c3dAppState.h"
#include "c3dTextureCache.h"
#include "c3dAudioCache.h"
#include "c3dTimeCounter.h"
#include "c3dAssert.h"
#include "c3dProgramSetUp.h"
//
#include "initGame.h"
//
void initOpenGL();
void initOpenAL();
void teardownOpenAL();
void c3dInitGame();
#endif /* defined(__HelloOpenGL__c3dInitGame__) */
