#include "operators_complex.hpp"
#include <iostream>
#include <cmath>

using namespace std;

CmpFn f = [](Cmp x) -> Cmp
{
	return std::exp(x);
	//return std::exp(x);
};

CmpFn h = [](Cmp x) -> Cmp
{
	return 2.0 / (x * x * x);
	//return 1.0 / (x - 1.0);
};

int main(int arcv, char** argv)
{
	//CmpFn g = L(Conv(f, y)); 
	//CmpFn h = L(f) * L(y);
	//CmpFn g = L(f);
	CmpFn g = (D * D + 1)(f);
	
	cout << g(Cmp(3.0, 0.0)).real() << " " << h(Cmp(3.0, 0.0)).real() << endl;
	return 0;
}