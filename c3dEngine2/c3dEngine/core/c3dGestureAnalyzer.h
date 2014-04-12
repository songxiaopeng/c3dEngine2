//
//  c3dGestureAnalyzer.h
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-11-13.
//
//

#ifndef __HelloOpenGL__c3dGestureAnalyzer__
#define __HelloOpenGL__c3dGestureAnalyzer__
#include <iostream>
using namespace std;
#include "c3dGlobalTimer.h"
#include "c3dVector.h"
#include "c3dTouchSequence.h"
#include "c3dDeviceAndOSInfo.h"

class Cc3dGestureAnalyzer
{

public:
    Cc3dGestureAnalyzer(){
        
    }
    virtual~Cc3dGestureAnalyzer(){
        
    }
    static Cc3dGestureAnalyzer* sharedGestureAnalyzer();
    Cc3dVector2 getPoint()const{//math coordinate (origin at left down corner)
        Cc3dTouch touch=Cc3dTouchSequence::sharedTouchSequence()->getLatestTouches()[0];
        Cc3dVector2 point=Cc3dVector2(touch.getPoint().x(),
                           Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenSize().y()-touch.getPoint().y());
        return point;
    }

    Cc3dVector2 getEarlierPoint()const{
        Cc3dTouch touch=Cc3dTouchSequence::sharedTouchSequence()->getLatestTouches()[0];
        double time=touch.getTime();
        double earlierTime=Cc3dTouchSequence::sharedTouchSequence()->getEarlierTime(time);
        vector<Cc3dTouch> earlierTouches=Cc3dTouchSequence::sharedTouchSequence()->getTouchesAtTime(earlierTime);
        assert(earlierTouches.empty()==false);
        Cc3dVector2 point=Cc3dVector2(earlierTouches[0].getPoint().x(),
                                      Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenSize().y()-earlierTouches[0].getPoint().y());
        return point;
    }
    Cc3dVector2 getLatestTouchBeganPoint()const {
        Cc3dVector2 point=Cc3dVector2(Cc3dTouchSequence::sharedTouchSequence()->getLatestTouchesWithType(e_c3dTouchBegan)[0].getPoint().x(),
                                      Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenSize().y()-Cc3dTouchSequence::sharedTouchSequence()->getLatestTouchesWithType(e_c3dTouchBegan)[0].getPoint().y());
        return point;
    }
    double getLatestTouchBeganTime()const{
        return Cc3dTouchSequence::sharedTouchSequence()->getLatestTouchTypeTime(e_c3dTouchBegan);
    }


    bool getIsTapOnce(){
		//if current is up, and the latest down is not too long from crrent time, then juged as TapOnce
		double curTime=Cc3dGlobalTimer::sharedGlobalTimer()->getTimeFromStart();
		double dTime=1.0f/60;
        if(Cc3dTouchSequence::sharedTouchSequence()->getTouchesInTimeSpanWithType(curTime-dTime,curTime, e_c3dTouchEnd).empty()==false){
			double latestTouchBeganTime=Cc3dTouchSequence::sharedTouchSequence()->getLatestTouchTypeTime(e_c3dTouchBegan);
            if(curTime-latestTouchBeganTime<2){//10
				//cout<<"isTapOnce"<<endl;
                return true;
            }
        }
        return false;
    }
    Cc3dVector2 getTouchMoveSpeed(){
        if(getIsDown()){
            Cc3dVector2 currentTouchPoint=this->getPoint();
            Cc3dVector2 earlierTouchPoint=Cc3dTouchSequence::sharedTouchSequence()->getTouchesAtEarlierTime(Cc3dGlobalTimer::sharedGlobalTimer()->getTimeFromStart())[0].getPoint();
            return (currentTouchPoint-earlierTouchPoint)*(1.0/(0.01+Cc3dGlobalTimer::sharedGlobalTimer()->getTimeFromStart()-Cc3dTouchSequence::sharedTouchSequence()->getEarlierTime(Cc3dGlobalTimer::sharedGlobalTimer()->getTimeFromStart())));
        }else{
            return Cc3dVector2(0, 0);
        }
    }
    bool getIsDown()const {
		//by compare the order of latest touchBegan and touchend to judge whether in press down state
        Cc3dTouch touchBegan=Cc3dTouchSequence::sharedTouchSequence()->getLatestTouchesWithType(e_c3dTouchBegan)[0];
        Cc3dTouch touchEnd=Cc3dTouchSequence::sharedTouchSequence()->getLatestTouchesWithType(e_c3dTouchEnd)[0];
        if(touchBegan.getTime()<touchEnd.getTime()){

            return false;
        }else{
			//cout<<"isDown"<<endl;
            return true;
        }
    }

};
#endif /* defined(__HelloOpenGL__c3dGestureAnalyzer__) */
