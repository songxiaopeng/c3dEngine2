//
//  c3dGlobalTimer.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-11-19.
//
//

#include "c3dGlobalTimer.h"
static Cc3dGlobalTimer*s_globalTimer=NULL;
Cc3dGlobalTimer*Cc3dGlobalTimer::sharedGlobalTimer(){
    if(s_globalTimer==NULL){
        s_globalTimer=new Cc3dGlobalTimer();
    }
    return s_globalTimer;
}