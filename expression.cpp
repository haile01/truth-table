#include "header.h"
#include <iomanip>
#include <algorithm>

bool Expr::getVal (char c)
{
	int pos = findSymbol(c);
	if (pos == -1)
	{
		cout << "[ERROR] Symbol not found!\n";
		return true;
	}
	else
		return symbols[pos].second;
}

void Expr::addSymbol (char c)
{
	if (findSymbol(c) == -1)
		symbols.push_back(make_pair(c, 0));
}

int Expr::findSymbol (char c)
{
	for (int i = 0; i < symbols.size(); i++)
		if (symbols[i].first == c)
			return i;
	return -1;
}

void Expr::addExpr (string s)
{
	if (findExpr(s) == -1 && s.size() > 1)
		expr.push_back(pair <string, int> (s, s.size()));
}

int Expr::findExpr (string s)
{
	for (int i = 0; i < expr.size(); i++)
		if (expr[i].first == s)
			return i;
	return -1;
}

bool compSymbols (pair <char, bool> a, pair <char, bool> b)
{
	return a.first < b.first;
}

void Expr::init (string s)
{
	clear();
	n = new Node();
	n -> init(s, this);
	sort(symbols.begin(), symbols.end(), compSymbols);
	string tmp;
	for (int i = 0; i < symbols.size(); i++)
	{
		tmp = symbols[i].first;
		expr.push_back(pair <string, int> (tmp, 1));
	}
}

bool Expr::next()
{
	int ind = symbols.size() - 1;
	bool mem = 1;
	while (ind >= 0 && mem)
	{
		if (!symbols[ind].second)
			mem = 0;
		symbols[ind].second ^= 1;
		ind--;
	}
	return !mem;
}

bool compExpr (pair <string, int> a, pair <string, int> b)
{
	return a.second == b.second ? a.first[0] < b.first[0] : a.second < b.second;
}

void Expr::colTitle()
{
	sort(expr.begin(), expr.end(), compExpr);
	cout << left;
	for (int i = 0; i < expr.size(); i++)
		cout << "|" << setw(expr[i].second) << expr[i].first;
	cout << "\n";
	for (int i = 0; i < expr.size(); i++)
	{
		cout << "+";
		for (int j = 0; j < expr[i].second; j++)
			cout << "-";
	}
	cout << "\n";
}

void Expr::show()
{
	cout << left;
	for (int i = 0; i < expr.size(); i++)
		cout << "|" << setw(expr[i].second) << (int)display[expr[i].first];
	cout << "\n";
	for (int i = 0; i < expr.size(); i++)
	{
		cout << "+";
		for (int j = 0; j < expr[i].second; j++)
			cout << "-";
	}
	cout << "\n";
}

void Expr::truthTable ()
{
	colTitle();
	do
	{
		n -> calc(this);
		show();
	} while (next());
}

void Expr::inspect ()
{
	n -> inspect();
}

void Expr::debug ()
{
	cout << "Available expressions\n";
	for (int i = 0; i < expr.size(); i++)
		cout << expr[i].first << " " << expr[i].second << "\n";
}

void Expr::clear ()
{
	n -> clear();
	symbols.clear();
	expr.clear();
	display.clear();
}

Expr::~Expr()
{
	clear();
}
