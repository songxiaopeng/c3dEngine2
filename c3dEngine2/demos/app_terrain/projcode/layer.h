//
//  layer.h
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-12-20.
//
//

#ifndef __HelloOpenGL__layer__
#define __HelloOpenGL__layer__

#include <iostream>
#include "c3d.h"
#include "button.h"
#include "ground.h"
class Clayer:public Cc3dActor
{
protected:
  Cbutton*m_button;
  Cground*m_ground;
  bool m_isWireMode;
public:
    Clayer(){
		m_button=NULL;
		m_ground=NULL;
		m_isWireMode=false;

    } 
    virtual~Clayer(){ 
        //----remove unused resources in caches on next frame
		Cc3dTextureCache::sharedTextureCache()->removeUnusedTexturesOnNextFrame();
		Cc3dAudioCache::sharedAudioCache()->removeUnusedBuffersAndSourcesOnNextFrame();

      
    }
	void update(float dt);
	bool init();
	

};



#endif /* defined(__HelloOpenGL__layer__) */
