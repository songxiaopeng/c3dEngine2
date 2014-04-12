//
//  c3dTouchSequence.h
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 14-2-21.
//
//

#ifndef __HelloOpenGL__c3dTouchSequence__
#define __HelloOpenGL__c3dTouchSequence__

#include <iostream>
using namespace std;
#include "c3dVector.h"
enum Ec3dTouchType{
    e_c3dTouchBegan=0,
    e_c3dTouchMove,
    e_c3dTouchEnd,
};
class Cc3dTouch{
public:
    Cc3dVector2 m_point;
    Ec3dTouchType m_type;
    double m_time;
    Cc3dTouch(){
        initMembers();
    }
    Cc3dTouch(float x,float y,Ec3dTouchType touchType, double time){
        initMembers();
        init(x, y, touchType, time);
    }
    void init(float x,float y,Ec3dTouchType touchType, double time){
        m_point.init(x, y);
        m_type=touchType;
        m_time=time;
    }
    Cc3dVector2 getPoint()const{return m_point;}
    double getTime()const{return m_time;}
    Ec3dTouchType getType()const{return m_type;}
    void print(){
        cout<<"touch: "<<m_point.x()<<" "<<m_point.y()<<" "<<m_type<<" "<<m_time<<endl;
    }
protected:
    void initMembers(){
        m_time=0;
        m_type=e_c3dTouchBegan;
    }
    
};
const int touchSequenceMaxLength=100;
const double timeLongLongAgo=-100000;
class Cc3dTouchSequence{
public:
    static Cc3dTouchSequence*sharedTouchSequence();
    Cc3dTouchSequence(){
        //put 3 guard
        m_touchList.push_back(Cc3dTouch(0,0,e_c3dTouchBegan,timeLongLongAgo));
        m_touchList.push_back(Cc3dTouch(0,0,e_c3dTouchMove,timeLongLongAgo+1));
        m_touchList.push_back(Cc3dTouch(0,0,e_c3dTouchEnd,timeLongLongAgo+2));
        
    }
    void addTouch(const Cc3dTouch&touch){
        //limit the length of touchList not exceed touchSequenceMaxLength
        int n=(int)m_touchList.size();
        if(n<touchSequenceMaxLength){//add directly
            m_touchList.push_back(touch);
        }else{
            //move left
            for(int i=0;i<n-1;i++){
                m_touchList[i]=m_touchList[i+1];
            }
            //fill touch to tail element
            m_touchList[n-1]=touch;
			//the first three element set as guard
            m_touchList[0]=Cc3dTouch(0,0,e_c3dTouchBegan,timeLongLongAgo);
            m_touchList[1]=Cc3dTouch(0,0,e_c3dTouchMove,timeLongLongAgo+1);
            m_touchList[2]=Cc3dTouch(0,0,e_c3dTouchEnd,timeLongLongAgo+2);
        }
    }
    vector<Cc3dTouch> getTouchList() {
        return m_touchList;
    }
    vector<Cc3dTouch> getLatestTouches(){
        double latestTouchTime=getLatestTouchTime();
        return getTouchesAtTime(latestTouchTime);
    }
    double getLatestTouchTime(){
        assert(m_touchList.empty()==false);
        return m_touchList[(int)m_touchList.size()-1].getTime();
    }
    vector<Cc3dTouch> getTouchesAtTime(double time){
        vector<Cc3dTouch> touches;
        int n=(int)m_touchList.size();
        for(int i=0;i<n;i++){
            const Cc3dTouch&touch=m_touchList[i];
            if(touch.getTime()==time){
                touches.push_back(touch);
            }
        }
        return touches;
    }
    double getLatestTouchTypeTime(Ec3dTouchType type){
        int n=(int)m_touchList.size();
        for(int i=n-1;i>=0;i--){
            const Cc3dTouch&touch=m_touchList[i];
            if(touch.getType()==type){
                return touch.getTime();
            }
        }
        assert(false);
    }
    vector<Cc3dTouch> getLatestTouchesWithType(Ec3dTouchType type){
        double latestTouchBeganTime=getLatestTouchTypeTime(type);
        return getTouchesAtTimeWithType(latestTouchBeganTime, type);
    }
    vector<Cc3dTouch> getTouchesAtTimeWithType(double time,Ec3dTouchType type){
        vector<Cc3dTouch> touches;
        int n=(int)m_touchList.size();
        for(int i=0;i<n;i++){
            const Cc3dTouch&touch=m_touchList[i];
            if(touch.getTime()==time&&touch.getType()==type){
                touches.push_back(touch);
            }
        }
        return touches;
    }
	vector<Cc3dTouch> getTouchesInTimeSpanWithType(double time0,double time1,Ec3dTouchType type){//time span is [time0,time1]
		assert(time0<=time1);
        vector<Cc3dTouch> touches;
        int n=(int)m_touchList.size();
        for(int i=0;i<n;i++){
            const Cc3dTouch&touch=m_touchList[i];
            if(touch.getTime()>=time0&&touch.getTime()<=time1&&touch.getType()==type){
                touches.push_back(touch);
            }
        }
        return touches;
    }
    double getEarlierTime(double time){
        assert(time>=0);
        int n=(int)m_touchList.size();
        for(int i=n-1;i>=0;i--){
            const Cc3dTouch&touch=m_touchList[i];
            if(touch.getTime()<time){
                return touch.getTime();
            }
        }
        assert(false);
    }
    vector<Cc3dTouch> getTouchesAtEarlierTime(double time){
        double earlierTime=getEarlierTime(time);
        return getTouchesAtTime(earlierTime);
    }
    vector<Cc3dTouch> getTouchesAtEarlierTimeWithType(double time,Ec3dTouchType type){
        double earlierTime=getEarlierTime(time);
        return getTouchesAtTimeWithType(earlierTime,type);
    }
    int getTouchCount()const{return (int)m_touchList.size();}
protected:
    vector<Cc3dTouch> m_touchList;
    
};
#endif /* defined(__HelloOpenGL__c3dTouchSequence__) */
