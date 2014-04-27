//
//  c3dGestureAnalyzer.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-11-13.
//
//
#include "c3dGestureAnalyzer.h"
static Cc3dTimeCounter*s_timeCounter=NULL;
Cc3dTimeCounter*Cc3dTimeCounter::sharedTimeCounter(){
    if(s_timeCounter==NULL){
        s_timeCounter=new Cc3dTimeCounter();
    }
    return s_timeCounter;
}
static Cc3dGestureAnalyzer*s_gestureAnalyzer=NULL;
Cc3dGestureAnalyzer* Cc3dGestureAnalyzer::sharedGestureAnalyzer(){
    if(s_gestureAnalyzer==NULL){
        s_gestureAnalyzer=new Cc3dGestureAnalyzer();
    }
    return s_gestureAnalyzer;
}
