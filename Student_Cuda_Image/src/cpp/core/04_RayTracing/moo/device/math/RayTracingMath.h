#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_GPU.h"
#include "cudaTools.h"
#include "Sphere.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RayTracingMath(int w, int h, int nbSphere, Sphere* ptrDevTabSphere)
	    {
	    this->nbSphere = nbSphere;
	    this->ptrDevTabSphere = ptrDevTabSphere;
	    }

	// constructeur copie automatique car pas pointeur dans RaytracingMath

	__device__
	         virtual ~RayTracingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor, int i, int j, float t)
	    {
	    Sphere* ptrCurrentSphere = nullptr;
	    Sphere* ptrClosestSphere = nullptr;
	    float2 xySol = make_float2(j, i);
	    float hCarre;
	    float closestDz;
	    float closestDistance = 0;
	    bool hasSphere = false;
	    for (int n = 0; n < nbSphere; n++)
		{
		ptrCurrentSphere = &ptrDevTabSphere[n];
		hCarre = ptrCurrentSphere->hCarre(xySol);
		if (ptrCurrentSphere->isEnDessous(hCarre))
		    {
		    hasSphere = true;
		    float currentDz = ptrCurrentSphere->dz(hCarre);
		    float currentSphereDist = ptrCurrentSphere->distance(currentDz);
		    if (currentSphereDist < closestDistance || ptrClosestSphere == nullptr)
			{
			closestDz = currentDz;
			closestDistance = currentSphereDist;
			ptrClosestSphere = ptrCurrentSphere;
			}
		    }
		}
	    if (hasSphere)
		{
		ColorTools::HSB_TO_RVB(ptrClosestSphere->getHueStart() + ptrClosestSphere->hue(t), 1, ptrClosestSphere->brightness(closestDz), ptrColor);
		}
	    else
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    ptrColor->w = 255; // opaque
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	int nbSphere;
	Sphere* ptrDevTabSphere;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
