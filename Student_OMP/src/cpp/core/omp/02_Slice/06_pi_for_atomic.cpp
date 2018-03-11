#include <omp.h>

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

bool isPiOMPforAtomic_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforAtomic(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforAtomic_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforAtomic, n, "Pi OMP for atomic");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * synchronisation couteuse! NUL!
 */
double piOMPforAtomic(int n)
    {
    const double DX = 1 / (double) n;
    double sum = 0;
#pragma omp parallel for
    for (int i = 0; i < n; i++)
	{
	double xi = i * DX;
#pragma omp atomic
	sum += fpi(xi); //seulement l'addition est protégée, fpi est exécutée en parallèle! (Un chouilla moins mauvais que 05)
	}
    return sum * DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

