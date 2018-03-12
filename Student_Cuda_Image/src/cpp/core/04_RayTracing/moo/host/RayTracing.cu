#include "RayTracing.h"

#include <iostream>
#include <assert.h>

#include "SphereCreator.h"

#include "Device.h"
#include "NbSphere.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/
__shared__ Sphere TAB_SM[NB_SPHERE];
extern __global__ void rayTracing(uchar4* ptrDevPixels,uint w, uint h,float t);
extern __global__ void rayTracing(uchar4* ptrDevPixels,uint w, uint h,float t,Sphere* ptrDevTabSphere);
extern void uploadToCM(Sphere* ptrTabSphere);
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

RayTracing::RayTracing(const Grid& grid, uint w, uint h, float dt) :
	Animable_I<uchar4>(grid, w, h, "Raytracing_Cuda_RGBA_uchar4")
    {
    // Inputs
    this->dt = dt;
    this->nbSphere=NB_SPHERE;

    //memory managament
    SphereCreator sphereCreator(NB_SPHERE, w, h); // sur la pile
    Sphere* ptrTabSphere = sphereCreator.getTabSphere();

    this->sizeOctet = NB_SPHERE * sizeof(Sphere); // octet

    // transfert to GM
    Device::malloc(&ptrDevTabSphere, this->sizeOctet);
    Device::memcpyHToD(ptrDevTabSphere, ptrTabSphere, this->sizeOctet);
    //transfert to CM
    uploadToCM(ptrTabSphere);

    // Tools
    this->t = 0; // protected dans Animable
    }

RayTracing::~RayTracing()
    {
    Device::free(ptrDevTabSphere);
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void RayTracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("vague rgba uchar4 (before)"); // facultatif, for debug only, remove for release

    rayTracing<<<dg,db>>>(ptrDevPixels,w,h,t); //version CM


    //rayTracing<<<dg,db,sizeOctet>>>(ptrDevPixels,w,h,t,ptrDevTabSphere);//Version SM

    Device::lastCudaError("vague rgba uchar4 (after)"); // facultatif, for debug only, remove for release
    }

/**
 * Override
 * Call periodicly by the API
 */
void RayTracing::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

