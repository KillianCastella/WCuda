#include <omp.h>
#include "OmpTools.h"
#include "../02_Slice/00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerPromotionTab(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerPromotionTab, n, "Pi OMP Entrelacer promotionTab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * pattern cuda : excellent!
 */
double piOMPEntrelacerPromotionTab(int n)
    {
    const double DX = 1 / (double) n;
    const int NB_THREAD =  OmpTools::setAndGetNaturalGranularity();
    double tabSommeThread[NB_THREAD];
	#pragma omp parallel
	{
	//NB-THREAD doit absolument se trouver dans la section parallel sinon il y a un seul thread ;) autre possibilité :  OmpTools::setAndGetNaturalGranularity()
	//const int NB_THREAD = OmpTools::getNbThread();
	double sommeThread;
	const int TID = OmpTools::getTid();
	int s = TID;
	double xs;
	while (s < n)
	    {
	    xs = s * DX;
	    sommeThread += fpi(xs);
	    s += NB_THREAD;
	    }
	tabSommeThread[TID]=sommeThread;
	}
	//reduction séquentielle du tableau promu
	double somme=0;
	for(int i=0;i<NB_THREAD;i++)
	    {
		somme += tabSommeThread[i];
	    }
	return somme*DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

