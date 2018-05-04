#include "Slice_advanced.h"

#include <iostream>

#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void slice_advanced(float* ptrTabDev,int n);

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
 |*		Constructeur			*|
 \*-------------------------------------*/

Slice_advanced::Slice_advanced(const Grid& grid, int n) :
	n(n)
    {
    // Grid
	{
	this->dg = grid.dg;
	this->db = grid.db;
	}
this->nbThread = grid.threadCounts();
this->sizeOctet = nbThread * sizeof(float); // octet
    // MM
	{

	// MM (malloc Device)
	    {
	    Device::malloc(&ptrTabDev, sizeOctet);
	    }
	ptrTab= new float[nbThread];
	Device::lastCudaError("AddVector MM (end allocation)"); // temp debug, facultatif
	}


    }

Slice_advanced::~Slice_advanced(void)
    {
    //MM (device free)
	{
	Device::free(ptrTabDev);

	Device::lastCudaError("AddVector MM (end deallocation)"); // temp debug, facultatif
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void Slice_advanced::run()
    {
    Device::lastCudaError("slice(before)"); // temp debug
    slice_advanced<<<dg,db>>>(ptrTabDev, n); // assynchrone
    Device::lastCudaError("slice (after)"); // temp debug

    //Device::synchronize(); // Temp,debug, only for printf in  GPU

    // MM (Device -> Host)
	{
	Device::memcpyDToH(ptrTab, ptrTabDev, sizeOctet); // barriere synchronisation implicite
	}
	double pi=0;
	for(int i=0;i<nbThread;i++){
	    pi += ptrTab[i];
	}
	pi = pi / (double) n;
	std::cout<<pi;
	//TODO OpenMp reduction
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
