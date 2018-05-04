#include <iostream>

#include "SceneCubeCreator.h"

#include "MandelbrotProvider.h"
#include "MandelbrotProvider2.h"
#include "MandelbrotProvider3.h"
#include "MandelbrotProvider4.h"
#include "RipplingProvider.h"
#include "RayTracingProvider.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructor		*|
 \*-------------------------------------*/

SceneCubeCreator::SceneCubeCreator()
    {
    createImages();
    createScene();
    }

SceneCubeCreator::~SceneCubeCreator()
    {
    delete ptrImage1;
    delete ptrImage2;
    delete ptrImage3;
    delete ptrImage4;
    delete ptrImage5;
    delete ptrImage6;

    delete ptrScene;
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

SceneCube* SceneCubeCreator::getScene()
    {
    return ptrScene;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void SceneCubeCreator::createImages()
    {
    ptrImage1 = MandelbrotProvider().createImageGL();
    ptrImage2 = MandelbrotProvider2().createImageGL();

    ptrImage3 = MandelbrotProvider3().createImageGL();
    ptrImage4 = MandelbrotProvider4().createImageGL();
    ptrImage5 = RayTracingProvider().createImageGL();
    ptrImage6 = RipplingProvider().createImageGL();
    }

void SceneCubeCreator::createScene()
    {
    ptrScene = new SceneCube(ptrImage1, ptrImage2, ptrImage3, ptrImage4, ptrImage5, ptrImage6);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

