#include <omp.h>
#include <OmpTools.h>

#include "00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforPromotionTab(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforPromotionTab, n, "Pi OMP for promotion tab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * De-synchronisation avec PromotionTab
 */
double piOMPforPromotionTab(int n)
    {
    const double DX = 1 / (double) n;
    double sum = 0;
    const int NB_THREADS = OmpTools::setAndGetNaturalGranularity();
    double tabSomme[NB_THREADS];

    //initialisation séquentielle
    for (int c = 0; c < NB_THREADS; c++)
	{
	tabSomme[c] = 0;
	}

#pragma omp parallel for
    for (int i = 0; i < n; i++)
	{
	double xi = i * DX;
	const int TID = OmpTools::getTid();
	tabSomme[TID] += fpi(xi);
	}

    //réduction séquentielle
    for (int c = 0; c < NB_THREADS; c++)
	{
	sum += tabSomme[c];
	}

    return sum * DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

