#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"
#include "IndiceTools_GPU.h"
#include "NbSphere.h"

#include "math/RayTracingMath.h"

using namespace gpu;

__constant__ Sphere TAB_CM[NB_SPHERE];

// Attention : 	Choix du nom est impotant!
//		VagueDevice.cu et non Vague.cu
// 		Dans ce dernier cas, probl�me de linkage, car le nom du .cu est le meme que le nom d'un .cpp (host)
//		On a donc ajouter Device (ou n'importequoi) pour que les noms soient diff�rents!

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void rayTracing(uchar4* ptrDevPixels, uint w, uint h, float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void rayTracing(uchar4* ptrDevPixels, uint w, uint h, float t)
    {
    RayTracingMath rayTracingMath = RayTracingMath(w, h, NB_SPHERE, TAB_CM);

    const int WH = w * h;
    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    int i;	// in [0,h[
    int j; 	// in [0,w[

    int s = TID;  // in [0,...
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j); 	// update (i, j)

	rayTracingMath.colorIJ(&ptrDevPixels[s], i, j, t); 	// update ptrDevPixels[s]

	s += NB_THREAD;
	}
    }
__host__ void uploadToCM(Sphere* ptrTabSphere)
    {
    size_t size = NB_SPHERE * sizeof(Sphere);
    int offset = 0;
    HANDLE_ERROR(cudaMemcpyToSymbol(TAB_CM, ptrTabSphere, size, offset, cudaMemcpyHostToDevice));
    }
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

