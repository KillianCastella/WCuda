#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_GPU.h"
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

class MandelbrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ MandelbrotMath() :
		calibreur(Interval<float>(-1, 1), Interval<float>(0, 1))
	    {

	    }

	// constructeur copie automatique car pas pointeur dans RaytracingMath

	__device__
	      virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorXY(uchar4* ptrColor, float x, float y, float t)
	    {
	    float z = f(x, y, t);
	    if (z > t)
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    else
		{
		float hue = z;
		//calibreur.calibrer(&hue);
		ColorTools::HSB_TO_RVB(hue, ptrColor);
		}

	    ptrColor->w = 255; // opaque
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/
    private:
	__device__
	float f(float x, float y, float t)
	    {
	    float a = 0.f;
	    float b = 0.f;
	    int i = 0;
	    while (i <= t && (a * a + b * b) <= 4)
		{
		float aCopy = a;
		a = (a * a - b * b) + x;
		b = 2 * aCopy * b + y;
		i++;
		}
	    return i;

	    }
    private:
	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
