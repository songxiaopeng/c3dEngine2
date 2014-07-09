//
//  initGame.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-12-20.
//
//

#include "initGame.h"
#include "c3d.h"
#include "c3dExtension.h"
#include "globalVars.h"
#include "extension.h"
#include "ball.h"
//cube mapping articles: 
//http://chimera.labs.oreilly.com/books/1234000001814/ch08.html
//http://blog.csdn.net/huangzhipeng/article/details/7957233
//http://www.nvidia.com/object/cube_map_ogl_tutorial.html


void initGame(){
	 //program
	 {
		 string programFolder = "cubemap_resource/";
        string programName="cubemap";
        Cc3dProgram*program=Cc3dProgramCache::sharedProgramCache()->createProgram(programFolder+"/"+programName+".vert", programFolder+"/"+programName+".frag", programName);
        program->attachUniform("projMat");
		program->attachUniform("viewMat");
        program->attachUniform("modelMat");
        program->attachUniform("normMat");
        program->attachUniform("texture");
        program->attachUniform("lightPos_world");
		program->attachUniform("eyePos_world");
        

    }
	//----light
	{
		light0=new Cc3dLight();
		light0->autorelease();
		light0->retain();
		light0->setPos(1000,5000,1000);//(50,200,500);
	//	light0->setSpecular(0.4,0.4,0.4);
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
        camera2D->autorelease();
        camera2D->retain();//must retain
        camera2D->setRange(range);
        camera2D->setProjectionMode(ec3dOrthographicMode);
    }
   //----camera
    {
        camera=new Cc3dCamera();
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

	//----layer
	//----create cubeTexture
		vector<string> filePathList;
		filePathList.push_back("cubemap_resource/px.png");
		filePathList.push_back("cubemap_resource/nx.png");
		filePathList.push_back("cubemap_resource/py.png");
		filePathList.push_back("cubemap_resource/ny.png");
		filePathList.push_back("cubemap_resource/pz.png");
		filePathList.push_back("cubemap_resource/nz.png");
		Cc3dTexture*cubeTex=new Cc3dTexture();
		cubeTex->autorelease();
		cubeTex->initCubeTexture(filePathList);


		//----box
	
		Cball*ball=new Cball();
		ball->autorelease();
		ball->setName("box");
		ball->makeBall(4,20,20,"");

		ball->setPos(Cc3dVector4(0,0,0,1));
		ball->setLight(light0);
		ball->setCamera(camera);
		ball->setProgram(Cc3dProgramCache::sharedProgramCache()->getProgramByName("cubemap"));
	    ball->setPassUnifoCallback(buildinProgramPassUnifoCallback_cubemap);

	    ball->genVBOBuffers();
		ball->submit(GL_STATIC_DRAW);

		//change texture to cubeTexture
		int nMesh=(int)ball->getModel()->getMeshCount();
		for(int i=0;i<nMesh;i++){
			int nSubMesh=(int)ball->getModel()->getMeshByIndex(i)->getSubMeshCount();
			for(int j=0;j<nSubMesh;j++){
				ball->getModel()->getMeshByIndex(i)->getSubMeshByIndex(j)->setTexture(cubeTex);
			}
		}
	//----add to scene
    Cc3dSceneManager::sharedSceneManager()->getRoot()->addChild(ball);
}


void buildinProgramPassUnifoCallback_cubemap(Cc3dNode*node, Cc3dProgram*program){
    assert(node);
    assert(program);
    Cc3dSubMesh*submesh=(Cc3dSubMesh*)node;
    assert(program->getName()=="cubemap");
	assert(submesh->getLight());
	assert(submesh->getCamera());
    Cc3dMatrix4 modelMat=Cc3dModelMatStack::sharedModelMatStack()->getTopMat();
    Cc3dMatrix4 projMat=submesh->getCamera()->calculateProjectionMat();
    Cc3dMatrix4 viewMat=submesh->getCamera()->calculateViewMat();

	//calculate normal mat
    //http://www.lighthouse3d.com/tutorials/glsl-tutorial/the-normal-matrix/
    //http://www.songho.ca/opengl/gl_normaltransform.html
    //http://www.arcsynthesis.org/gltut/Illumination/Tut09%20Normal%20Transformation.html
    Cc3dMatrix4 normMat=transpose(inverse(modelMat));
	
	Cc3dVector4 lightPos=submesh->getLight()->getPos();
	Cc3dVector4 eyePos=submesh->getCamera()->getEyePos();
  /*  Cc3dVector4 diffuseMaterial=submesh->getMaterial()->getDiffuse();
    Cc3dVector4 diffuseLight=submesh->getLight()->getDiffuse();
    Cc3dVector4 ambientMaterial=submesh->getMaterial()->getAmbient();
    Cc3dVector4 ambientLight=submesh->getLight()->getAmbient();
	Cc3dVector4 specularMaterial=submesh->getMaterial()->getSpecular();
	Cc3dVector4 specularLight=submesh->getLight()->getSpecular();
	float shininess=submesh->getMaterial()->getShininess();*/
    //
    Cc3dMatrix4 PVMmat=projMat*viewMat*modelMat;
   
    // 
    program->passUnifoValue1i("texture", 0);//texture attach point 0
    program->passUnifoValueMatrixNfv("viewMat", viewMat.getArray(), viewMat.getArrayLen());
	program->passUnifoValueMatrixNfv("projMat", projMat.getArray(), projMat.getArrayLen());
	program->passUnifoValueMatrixNfv("modelMat", modelMat.getArray(), modelMat.getArrayLen());
	program->passUnifoValueMatrixNfv("normMat", normMat.getArray(), normMat.getArrayLen());
	program->passUnifoValueNfv("lightPos_world", lightPos.getArray(),lightPos.getArrayLen());
	program->passUnifoValueNfv("eyePos_world", eyePos.getArray(),eyePos.getArrayLen());
}