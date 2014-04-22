//
//  initGame.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-12-20.
//
//

#include "initGame.h"
#include "c3d.h"
#include "box.h"
#include "globalVars.h"
#include "btBulletDynamicsCommon.h"
void initGame(){

/*	//----light
	{
		light0=new Cc3dLight();
		light0->autorelease();
		light0->retain();
		light0->setPos(100,50,20);
		light0->setAmbient(0.5,0.5,0.5);
	}
	 //----camera2D
    {
        float left=0;
        float right=Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getWidth();
        float top=Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getHeight();
        float bottom = 0;
        float _near = -1;//note: near and far is key word in vs2010, so here we use _near and _far
        float _far = 1;
        Cc3dRange range(left,right,bottom,top,_near,_far);
        camera2D=new Cc3dCamera();
        camera2D->init();
        camera2D->autorelease();
        camera2D->retain();//must retain
        camera2D->setRange(range);
        camera2D->setProjectionMode(ec3dOrthographicMode);
    }
    //----camera
    {
        camera=new Cc3dCamera();
        camera->init();
        camera->autorelease();
        camera->retain();//must retain
        camera->setFovy(70);
        camera->setAspect((float)Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getWidth()/Cc3dDeviceAndOSInfo::sharedDeviceAndOSInfo()->getScreenRect().getHeight());
        camera->setzNear(0.5);
        camera->setzFar(10000);
        float eyePos[3]={10,5,5};
        float eyeTg[3]={0,0,0};
        float up[3]={0,1,0};
        camera->setEyePos(Cc3dVector3(eyePos).toV4(1));
        camera->setCenter(Cc3dVector3(eyeTg).toV4(1));
        camera->setUp(Cc3dVector3(up).toV4(0));
        camera->updateFrustum();
    }

	//----box
	
    Cbox*box=new Cbox();
	box->autorelease();
	box->setName("box");
	box->makeBox(2,"box_resource/tex/box.png");

	box->setPos(Cc3dVector4(0,0,0,1));
	box->setLight(light0);
    box->setCamera(camera);
	box->setProgram(Cc3dProgramCache::sharedProgramCache()->getProgramByName("classicLighting"));
    box->setPassUnifoCallback(buildinProgramPassUnifoCallback_classicLighting);

    box->genVBOBuffers();
	box->submit(GL_STATIC_DRAW);
 

	//----add to scene
    Cc3dSceneManager::sharedSceneManager()->getRoot()->addChild(box);
    */
    
    ///-----includes_end-----
    
	int i;
	///-----initialization_start-----
    
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    
	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);
    
	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
    
	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    
	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
    
	dynamicsWorld->setGravity(btVector3(0,-10,0));
    
	///-----initialization_end-----
    
	///create a few basic rigid bodies
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.),btScalar(50.),btScalar(50.)));
    
	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
    
	collisionShapes.push_back(groundShape);
    
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,-56,0));
    
	{
		btScalar mass(0.);
        
		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);
        
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass,localInertia);
        
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);
        
		//add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);
	}
    
    
	{
		//create a dynamic rigidbody
        
		//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		collisionShapes.push_back(colShape);
        
		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();
        
		btScalar	mass(1.f);
        
		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);
        
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass,localInertia);
        
        startTransform.setOrigin(btVector3(2,10,0));
		
        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);
        
        dynamicsWorld->addRigidBody(body);
	}
    
    
    
    /// Do some simulation
    
    
	///-----stepsimulation_start-----
	for (i=0;i<100;i++)
	{
		dynamicsWorld->stepSimulation(1.f/60.f,10);
		
		//print positions of all objects
		for (int j=dynamicsWorld->getNumCollisionObjects()-1; j>=0 ;j--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				btTransform trans;
				body->getMotionState()->getWorldTransform(trans);
				printf("world pos = %f,%f,%f\n",float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
			}
		}
	}
    
	///-----stepsimulation_end-----
    
	//cleanup in the reverse order of creation/initialization
	
	///-----cleanup_start-----
    
	//remove the rigidbodies from the dynamics world and delete them
	for (i=dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}
    
	//delete collision shapes
	for (int j=0;j<collisionShapes.size();j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}
    
	//delete dynamics world
	delete dynamicsWorld;
    
	//delete solver
	delete solver;
    
	//delete broadphase
	delete overlappingPairCache;
    
	//delete dispatcher
	delete dispatcher;
    
	delete collisionConfiguration;
    
	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	collisionShapes.clear();
    
	///-----cleanup_end-----
    
}