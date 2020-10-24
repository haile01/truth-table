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
int getPrior (char c);

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
        ~Node();
};

string trim (string s, bool &neg);
bool isBinary(string s);
bool eval (string s);

//Expression
struct Expr
{
	Node *n;
	vector < pair <char, bool> > symbols;
	// first: symbol character
	// second: current symbol value (true or false)
	map <string, bool> display;
	// first: expression
	// second: current value (true or false)
	vector < pair <string, int> > expr;
	// first: expression
	// second: expression width

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
	~Expr();
};
