//
//  c3dNode.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 14-1-15.
//
//

#include "c3dNode.h"


 bool Cc3dNode::init(){
		Cc3dObject::init();
        //default camera
        Cc3dCamera*camera=new Cc3dCamera();
        camera->init();
        camera->autorelease();
        setCamera(camera);
        //default light
        Cc3dLight*light=new Cc3dLight();
        light->init();
        light->autorelease();
        setLight(light);
        //default passUniformCallback
        m_passUnifoCallback=buildinProgramPassUnifoCallback_texColorOnly;
        //default program
        Cc3dProgram*program=Cc3dProgramCache::sharedProgramCache()->getProgramByName("shader_texColorOnly");
        setProgram(program);
        return true;

    }
void Cc3dNode::visitUpdate(){
    if(this->getIsDoUpdateRecursively()){
        if(this->getIsDoUpdate()){
			double curTime=Cc3dGlobalTimer::sharedGlobalTimer()->getTimeFromStart();
			double lastUpdateTime=m_lastUpdateTime;
			double dt=maxf(0,curTime-lastUpdateTime);
            this->update(dt);
			m_lastUpdateTime=curTime;
        }
        
        //sort children by their visitDrawOrder
        int nchild=(int)m_childList.size();
        if(nchild!=0){
            //sort
            stable_sort(m_childList.begin(), m_childList.end(),comp_smallervisitUpdateOrder());
            for(int i=0;i<nchild;i++){
                assert(m_childList[i]);
                m_childList[i]->visitUpdate();
            }
            
        }
    }
 

}
void Cc3dNode::visitDraw(){
 //   cout<<"enter node: "<<m_name<<endl;
    if(this->getIsVisibleRecursively()){
        Cc3dModelMatStack::sharedModelMatStack()->pushMatrix();
        if(!m_isIgnorTransform)this->transform();
        
        if(this->getIsVisible()){
            this->draw();
        }
        
        
        //sort children by their visitDrawOrder
        int nchild=(int)m_childList.size();
        if(nchild!=0){
            //sort
            stable_sort(m_childList.begin(), m_childList.end(),comp_smallerVisitDrawOrder());
            for(int i=0;i<nchild;i++){
                assert(m_childList[i]);
                m_childList[i]->visitDraw();
            }
            
        }
        Cc3dModelMatStack::sharedModelMatStack()->popMatrix();
    }
  //  cout<<"quit node: "<<m_name<<endl;
}

