#include <string.h>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

struct Node;
struct Expr;
struct Operator;

//Operator
struct Operator
{
	char c;
	bool eval(bool a, bool b);
	Operator (char c): c(c) {};
	Operator (): c(' ') {};
};

bool isOp (char c);
bool AND (bool a, bool b);
bool OR (bool a, bool b);
bool XOR (bool a, bool b);
bool IMPLY (bool a, bool b);

//Separator
struct Node{
        bool neg;
        char symbol;
	string expr;
        Operator *op;
        Node *l, *r;

        Node (): symbol(' '), neg(0), l(nullptr), r(nullptr), op(new Operator()), expr("") {};
        bool init (string s, Expr *e);
        bool calc (Expr *e);
        void inspect();
        void clear();
};

string trim (string s, bool &neg);
bool isBinary(string s);
bool eval (string s);

//Expression
struct Expr
{
	Node *n;
	vector < pair <char, bool> > symbols;
	map <string, bool> display;
	vector < pair <string, int> > expr;

	Expr (): n(new Node()) {};
	void addSymbol (char c);
	void addExpr (string s);
	bool getVal (char c);
	int findSymbol (char c);
	int findExpr (string s);
	void init (string s);
	void truthTable();
	bool next();
	void colTitle();
	void show();

	void debug();
	void inspect();
	void clear();
};
