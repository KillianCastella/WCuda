#include "MandelbrotProvider4.h"

#include "Mandelbrot.h"

#include "MathTools.h"
#include "Grid.h"
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
Animable_I<uchar4>* MandelbrotProvider4::createAnimable()
    {
    DomaineMath domaineMath = DomaineMath(-0.34,0.07,-1.03,-0.66);
    // Animation;
    float dt = 2 ;

    // Dimension
    int w = 16 * 60;
    int h = 16 * 60;

    // Grid Cuda
    int mp = Device::getMPCount();
    int coreMP = Device::getCoreCountMP();

    dim3 dg = dim3(mp, 2, 1);
    dim3 db = dim3(coreMP, 2, 1);

    Grid grid(dg,db);

    return new Mandelbrot(grid,w, h,domaineMath,dt);
    }

Image_I* MandelbrotProvider4::createImageGL(void)
    {
    ColorRGB_01 colorTexte(1, 0, 0); // Green
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

