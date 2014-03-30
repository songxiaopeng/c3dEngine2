//
//  c3dGlobalTimer.h
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-11-19.
//
//

#ifndef __HelloOpenGL__c3dGlobalTimer__
#define __HelloOpenGL__c3dGlobalTimer__

#include <iostream>
using namespace std;
#include <time.h>
#include <assert.h>



class Cc3dGlobalTimer
{
protected:
	//all time is second
	double m_startTime;
    double m_curTime;
	bool m_isStarted;
public:
    static Cc3dGlobalTimer*sharedGlobalTimer();
    Cc3dGlobalTimer(){
        m_startTime=0;
		m_curTime=0;
		m_isStarted=false;
    }
    virtual~Cc3dGlobalTimer(){};
	void start(){
		m_startTime=(double)clock()/CLOCKS_PER_SEC;
		m_curTime=m_startTime;
		m_isStarted=true;
	}
    double getTimeFromStart(){
		assert(m_isStarted);
		m_curTime=(double)clock()/CLOCKS_PER_SEC;
        return max(0.0,m_curTime-m_startTime);//must use 0.0, not 0
    }
};
#endif /* defined(__HelloOpenGL__c3dGlobalTimer__) */
