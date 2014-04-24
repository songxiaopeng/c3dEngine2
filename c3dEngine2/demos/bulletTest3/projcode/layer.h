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

	
    } 
    virtual~Clayer(){
        destroyPhysics();
        //----remove unused resources in caches on next frame
		Cc3dTextureCache::sharedTextureCache()->removeUnusedTexturesOnNextFrame();
		Cc3dAudioCache::sharedAudioCache()->removeUnusedBuffersAndSourcesOnNextFrame();
    }
	void update(float dt){

        m_world->stepSimulation(dt,10);
		
		//print positions of all objects
        //cout<<"body count:"<<m_world->getNumCollisionObjects()<<endl;
		for (int j=m_world->getNumCollisionObjects()-1; j>=0 ;j--)
		{
			btCollisionObject* obj = m_world->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
                CphysicsActor*actor=(CphysicsActor*)(((CphysicsBody*)body->getUserPointer())->getHostPointer());
                actor->setPos(actor->getBody()->getPosition());
                actor->setRotation(actor->getBody()->getRotation());
                //cout<<"pos:"<<actor->getBody()->getPosition().x()<<" "<<actor->getBody()->getPosition().y()<<" "<<actor->getBody()->getPosition().z()<<endl;
            }
		}
    }
	bool init(){
        initPhysics();
        initActors();
        return true;
    }
    void initActors(){
        //----box
        {
            //model
            Cc3dModel* boxModel=makeBoxModel(0.5);
            //actor
            CphysicsActor*actor=new CphysicsActor();
            actor->autorelease();
            actor->init();
            actor->setModel(boxModel);
            actor->setLight(light0);
            actor->setCamera(camera);
            actor->setProgram(Cc3dProgramCache::sharedProgramCache()->getProgramByName("classicLighting"));
            actor->setPassUnifoCallback(buildinProgramPassUnifoCallback_classicLighting);
            actor->genVBOBuffers();
            actor->submit(GL_STATIC_DRAW);
            //body
            CphysicsBody*body=new CphysicsBody();
            body->autorelease();
            body->init();
            body->initWithMeshData(1.0f, getPosListFromSubMeshData(*actor->getMeshByIndex(0)->getSubMeshByIndex(0)->getSubMeshData()),
                                   getIDtriListFromSubMeshData(*actor->getMeshByIndex(0)->getSubMeshByIndex(0)->getSubMeshData()),
                                   true,
                                   actor->getTransform().getRTmat());
            body->setPosition(Cc3dVector4(0,6,0,1));
            //assemble
            actor->setBody(body);
            //add to scene
            this->addChild(actor);
            m_world->addRigidBody(actor->getBody()->getBody());
            //add to list
            m_actorList.push_back(actor);
        }
        //----ground
        {
            //model
            Cc3dModel* boxModel=makeBoxModel(3,1,3);
            //actor
            CphysicsActor*actor=new CphysicsActor();
            actor->autorelease();
            actor->init();
            actor->setModel(boxModel);
            actor->setLight(light0);
            actor->setCamera(camera);
            actor->setProgram(Cc3dProgramCache::sharedProgramCache()->getProgramByName("classicLighting"));
            actor->setPassUnifoCallback(buildinProgramPassUnifoCallback_classicLighting);
            actor->genVBOBuffers();
            actor->submit(GL_STATIC_DRAW);
            //body
            CphysicsBody*body=new CphysicsBody();
            body->autorelease();
            body->init();
            body->initWithMeshData(0.0f, getPosListFromSubMeshData(*actor->getMeshByIndex(0)->getSubMeshByIndex(0)->getSubMeshData()),
                                   getIDtriListFromSubMeshData(*actor->getMeshByIndex(0)->getSubMeshByIndex(0)->getSubMeshData()),
                                   true,
                                   actor->getTransform().getRTmat());
            //assemble
            actor->setBody(body);
            //add to scene
            this->addChild(actor);
            m_world->addRigidBody(actor->getBody()->getBody());
            //add to list
            m_actorList.push_back(actor);
        }
        
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

};



#endif /* defined(__HelloOpenGL__layer__) */
