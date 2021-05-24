#include <iostream>
#include "TPlex.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	TPlex k("12 23, 34 45, 56 67");

	k.Print();

	TPoint a(12, 23);
	TPoint b(34, 45);
	TPoint c(56, 67);
	
	TPlex q(&a, &b);
	q.AddLine(&b, &c);
	q.Print();

	/*TLine AB(a, b);
	TLine BC(b, c);
	TLine CD(c, d);
	TLine DA(d, a);

	AB.Print();

	TSquare ABCD(AB, BC, CD, DA);
	ABCD.Print();
  std::cout << "plex AB\n";

	TPlex q(&a, &b);
	q.Print();

	q.AddLine(&a, &c);
	std::cout<<" plex ABC \n";  
	q.Print(); 

	q.AddLine(&c, &b);
	std::cout<<" plex ABCA \n";  
	q.Print(); 

	q.AddLine(&b, &d);
	std::cout<<" plex BCABD \n";  
	q.Print(); 

	TCanvas z;
	z.AddObj(&q);
	z.AddObj(&ABCD);
	z.AddObj(&AB);

	z.Print();

	return 0;*/
}
