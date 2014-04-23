//
//  physicsActor.h
//  c3d
//
//  Created by ck02-084 on 14-4-23.
//
//

#ifndef __c3d__physicsActor__
#define __c3d__physicsActor__

#include <iostream>
using namespace std;
#include "c3d.h"
#include "btBulletDynamicsCommon.h"
class CphysicsActor:public Cc3dActor
{
public:
    CphysicsActor(){
        m_body=NULL;
        m_shape=NULL;
    }
    ~CphysicsActor(){
        if (m_body)
        {
            delete m_body->getMotionState();
            delete m_body;
        }
        if (m_shape){
            delete m_shape;
        }
    }
    bool init(){
        Cc3dActor::init();
        //----display
        //create box mesh
        this->setModel(makeBoxModel(0.5));
        //----physics
        //rotation
        Cc3dTransform transform=getTransform();
        Cc3dMatrix4 RTmat=transform.getRTmat();
        btMatrix3x3 rotMatrix=btMatrix3x3(RTmat.getAt(0),RTmat.getAt(4),RTmat.getAt(8),//row0
                                          RTmat.getAt(1),RTmat.getAt(5),RTmat.getAt(9),//row1
                                          RTmat.getAt(2),RTmat.getAt(6),RTmat.getAt(10)//row2
                                          );//Constructor with row major formatting
        btScalar yaw,pitch,roll;
        rotMatrix.getEulerZYX(yaw, pitch, roll);
        btQuaternion rotation;
        rotation.setEulerZYX(yaw, pitch, roll);
        //position
        btVector3 position = btVector3(transform.getPos().x(), transform.getPos().y(), transform.getPos().z());
        //shape
        m_shape = new btBoxShape(btVector3(btScalar(0.5),btScalar(0.5),btScalar(0.5)));
        createShapeWithSubMeshData(this->getMeshByIndex(0)->getSubMeshByIndex(0)->getSubMeshData(), true, m_shape);
        //motionState
        btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(rotation, position));
        //body mass
        btScalar bodyMass = 1.0;
        //body inertia
        btVector3 bodyInertia;
        m_shape->calculateLocalInertia(bodyMass, bodyInertia);
        //bodyCI
        btRigidBody::btRigidBodyConstructionInfo bodyCI = btRigidBody::btRigidBodyConstructionInfo(bodyMass, motionState, m_shape, bodyInertia);
        //body
        m_body=new btRigidBody(bodyCI);
        //save this to body
        m_body->setUserPointer(this);
        //linear factor
        m_body->setLinearFactor(btVector3(1,1,1));//if want no action on z, use (1,1,0)
        return true;
    }
protected:
    static Cc3dModel* makeBoxModel(float d);
    static void createShapeWithSubMeshData(const Cc3dSubMeshData*subMeshData,bool isConvex,btCollisionShape*shape){
        assert(shape==NULL);
        if (isConvex)
        {
            shape = new btConvexHullShape();
            int vertexCount=subMeshData->getVertexCount();
            for (int i = 0; i < vertexCount; i++)
            {
                const Cc3dVertex&vertex=subMeshData->getVertexByIndex(i);
                btVector3 btv = btVector3(vertex.getPos().x(), vertex.getPos().y(), vertex.getPos().z());
                ((btConvexHullShape*)shape)->addPoint(btv);
            }
        }
        else
        {
            btTriangleMesh* mesh = new btTriangleMesh();
            int IDtriCount=subMeshData->getIDtriCount();
            for (int i=0; i < IDtriCount; i++)
            {
                const Cc3dIDTriangle&IDtri=subMeshData->getIDtriByIndex(i);
                const Cc3dVertex&v0=subMeshData->getVertexByIndex(IDtri.vID[0]);
                const Cc3dVertex&v1=subMeshData->getVertexByIndex(IDtri.vID[1]);
                const Cc3dVertex&v2=subMeshData->getVertexByIndex(IDtri.vID[2]);
                
                btVector3 bv0 = btVector3(v0.getPos().x(), v0.getPos().y(), v0.getPos().z());
                btVector3 bv1 = btVector3(v1.getPos().x(), v1.getPos().y(), v1.getPos().z());
                btVector3 bv2 = btVector3(v2.getPos().x(), v2.getPos().y(), v2.getPos().z());
                
                mesh->addTriangle(bv0, bv1, bv2);
            }
            shape = new btBvhTriangleMeshShape(mesh, true);
        }
        
    }
  
protected:
    btRigidBody* m_body;
    btCollisionShape* m_shape;
    
    
};
#endif /* defined(__c3d__physicsActor__) */
