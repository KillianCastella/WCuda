#include <iostream>
#include "VectorTools.h"
#include "Grid.h"
#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "Slice_advanced.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSlice_advanced(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSlice_advanced()
    {
    int n = 1000;

    // Partie interessante GPGPU
	{
	// Grid cuda
	int mp = Device::getMPCount();
	int coreMP = Device::getCoreCountMP();

	//entrelacement
	dim3 dg = dim3(mp, 2, 1);  		// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
	dim3 db = dim3(coreMP, 2, 1);   	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
	Grid grid(dg, db);

	//1à1
//	dim3 dg = dim3(mp, 3, 1);  		// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
//	dim3 db = dim3(coreMP, 3, 1);   	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
//	Grid grid(dg, db);

	Slice_advanced slice_advanced(grid, n); // on passse la grille à AddVector pour pouvoir facilement la faire varier de l'extérieur (ici) pour trouver l'optimum
	slice_advanced.run();

	}

    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

