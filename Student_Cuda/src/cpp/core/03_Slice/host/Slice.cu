#include <iostream>

#include "Device.h"
#include "Slice.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void slice(float* ptrTabDev,int n);

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

Slice::Slice(const Grid& grid, int n) :
	n(n),pi(0)
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
	std::cout <<"|"<< sizeOctet<<"|";
	// MM (malloc Device)
	    {
	    Device::malloc(&ptrTabDev, sizeOctet);
	    }
	ptrTab = new float[nbThread];
	Device::lastCudaError("AddVector MM (end allocation)"); // temp debug, facultatif
	}

    }

Slice::~Slice(void)
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

float Slice::run()
    {
    Device::lastCudaError("slice(before)"); // temp debug
    slice<<<dg,db>>>(ptrTabDev, n); // assynchrone
    Device::lastCudaError("slice (after)"); // temp debug

    //Device::synchronize(); // Temp,debug, only for printf in  GPU

    // MM (Device -> Host)
	{
	Device::memcpyDToH(ptrTab, ptrTabDev, sizeOctet); // barriere synchronisation implicite
	}
    for (int i = 0; i < nbThread; i++)
	{
	pi += ptrTab[i];
	}
    pi = pi / (float) n;
    std::cout << pi;
    return pi;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
