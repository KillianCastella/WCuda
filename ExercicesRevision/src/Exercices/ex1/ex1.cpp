#include <stdlib.h>
#include <iostream>

using std::cout;
using std::ostream;
using std::endl;

struct ABC{
	double a,b,c;
	ABC(double a,double b,double c){
	    this->a=a;
	    this->b=b;
	    this->c=c;
	}
};
ostream& operator<<( ostream &flux, ABC const& abc )
{
    flux<<abc.a<<abc.b<<abc.c;
    return flux;
}
void useEx1(void)
    {
        ABC abc(1.0, 2.0, 3.0);
        cout<<abc<<endl;
    }
