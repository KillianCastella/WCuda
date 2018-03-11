#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"

using namespace cpu;
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {
    public:

    	MandelbrotMath(uint n) : calibreur(Interval<float>(-1, 1), Interval<float>(0, 1))
    	    {
    	    this->n = n;
    	    }

    	// constructeur copie: pas besoin car pas attribut ptr

    	virtual ~MandelbrotMath(void)
    	    {
    	    // rien
    	    }

    	/*--------------------------------------*\
    	|*		Methode			*|
    	\*--------------------------------------*/

        public:

    	void colorIJ(uchar4* ptrColorIJ, int i, int j, float t)
    	    {
    	    float z = f(i,j,t);

    	    if (z<0){
    		 ptrColorIJ->x = 0;
    		 ptrColorIJ->y = 0;
    		 ptrColorIJ->z = 0;
    	    }
    	    else{
    		ColorTools::HSB_TO_RVB(z, ptrColorIJ);
    	    }
    	    ptrColorIJ->w =255;
    	    }

        private:

    	float f(int i, int j, float t)
    	    {
    	       float N = t;
    	       float a=0;
    	       float b =0;

    	       int k=0;
    	       do{
    		   k++;
    		   float aOld = a;
    		   a = (a*a-b*b)+i;
    		   b = 2* aOld*b+j;
    	       }while(k <= N && (a * a + b * b) <= 4);
    	       if(k<N){
    		   return -1.0;
    	       }
    	       return (1/N)*k;
    	    }

    	/*--------------------------------------*\
    	|*		Attribut			*|
    	 \*-------------------------------------*/

        private:

    	uint n;
   	// Tools
   	Calibreur<float> calibreur;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
