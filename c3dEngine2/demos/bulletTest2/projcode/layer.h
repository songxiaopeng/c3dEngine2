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
#include "btBulletDynamicsCommon.h"
#include "physicsActor.h"
#include "globalVars.h"
class Clayer:public Cc3dActor
{

public:
    Clayer(){
        m_broadphase=NULL;
        m_collisionConfiguration=NULL;
        m_dispatcher=NULL;
        m_solver=NULL;
        m_world=NULL;
        count=0;
	
    } 
    virtual~Clayer(){
        destroyPhysics();
        //----remove unused resources in caches on next frame
		Cc3dTextureCache::sharedTextureCache()->removeUnusedTexturesOnNextFrame();
		Cc3dAudioCache::sharedAudioCache()->removeUnusedBuffersAndSourcesOnNextFrame();
    }
	void update(float dt){
        cout<<"dt:"<<dt<<endl;
        cout<<"1.f/60:"<<1.f/60<<endl;
        count++;
        if(count==100)exit(0);
        m_world->stepSimulation(1.f/60.f,10);
		
		//print positions of all objects
		for (int j=m_world->getNumCollisionObjects()-1; j>=0 ;j--)
		{
			btCollisionObject* obj = m_world->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
                CphysicsActor*actor=(CphysicsActor*)body->getUserPointer();
                actor->setActorPos(actor->getBodyPos());
                cout<<"pos:"<<actor->getBodyPos().x()<<" "<<actor->getBodyPos().y()<<" "<<actor->getBodyPos().z()<<endl;
            }
		}
    }
	bool init(){
        initPhysics();
        initActors();
        return true;
    }
    void initActors(){
        CphysicsActor*actor=new CphysicsActor();
        actor->autorelease();
        actor->init();
    //    actor->setBodyPos(Cc3dVector4(0,10,0,1));
        actor->setLight(light0);
        actor->setCamera(camera);
        actor->setProgram(Cc3dProgramCache::sharedProgramCache()->getProgramByName("classicLighting"));
        actor->setPassUnifoCallback(buildinProgramPassUnifoCallback_classicLighting);
        actor->genVBOBuffers();
        actor->submit(GL_STATIC_DRAW);
        m_actorList.push_back(actor);
        this->addChild(actor);
        m_world->addRigidBody(actor->getBody());

    }
	
protected:
    void initPhysics(){
        //
        m_broadphase = new btDbvtBroadphase();
        //
        m_collisionConfiguration = new btDefaultCollisionConfiguration();
        m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
        //
        m_solver = new btSequentialImpulseConstraintSolver();
        //
        m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
        //
        m_world->setGravity(btVector3(0,-10,0));
    }
    void destroyPhysics(){
        if(m_world)delete m_world;
        if(m_solver)delete m_solver;
        if(m_collisionConfiguration)delete m_collisionConfiguration;
        if(m_dispatcher)delete m_dispatcher;
        if(m_broadphase)delete m_broadphase;
    }

protected:
    btBroadphaseInterface*                  m_broadphase;
    btDefaultCollisionConfiguration*        m_collisionConfiguration;
    btCollisionDispatcher*                  m_dispatcher;
    btSequentialImpulseConstraintSolver*    m_solver;
    btDiscreteDynamicsWorld*                m_world;
protected:
    vector<CphysicsActor*>m_actorList;
    int count;
};



#endif /* defined(__HelloOpenGL__layer__) */
