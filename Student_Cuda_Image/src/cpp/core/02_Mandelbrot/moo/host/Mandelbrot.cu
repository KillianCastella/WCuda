#include "Mandelbrot.h"

#include <iostream>
#include <assert.h>

#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void mandelbrot(uchar4* ptrDevPixels,uint w, uint h,float t,DomaineMath domaineMath);

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

Mandelbrot::Mandelbrot(const Grid& grid, uint w, uint h,int n, const DomaineMath& domaineMath, float dt) :
	Animable_I<uchar4>(grid, w, h, "Mandelbrot_Cuda_RGBA_uchar4",domaineMath), variateurAnimation(Interval<int>(30,100),dt)
    {
	//inputs
	this->n=n;
	// Tools
	this->t = 0; // protected dans Animable
    }

Mandelbrot::~Mandelbrot()
    {
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
void Mandelbrot::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("vague rgba uchar4 (before)"); // facultatif, for debug only, remove for release

    mandelbrot<<<dg,db>>>(ptrDevPixels,w,h,t, domaineMath);

    Device::lastCudaError("vague rgba uchar4 (after)"); // facultatif, for debug only, remove for release
    }

/**
 * Override
 * Call periodicly by the API
 */
void Mandelbrot::animationStep()
    {
    t = this->variateurAnimation.varierAndGet();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

