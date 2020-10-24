#include "header.h"
using namespace std;

int main()
{
	Expr *e = new Expr();
	while (1)
	{
		string s;
		getline(cin, s);
		if (s.substr(0, 4) == "done")
			break;
		e -> init(s);
		e -> truthTable();
	}
	e -> clear();
	delete e;
}
