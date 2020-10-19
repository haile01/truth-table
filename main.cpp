#include "header.h"
using namespace std;

int main()
{
	Expr *e = new Expr();
	string s;
	getline(cin, s);
	e -> init(s);
	e -> truthTable();
	e -> clear();
	delete e;
}
