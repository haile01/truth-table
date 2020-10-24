#include "header.h"
#include <iomanip>
#include <algorithm>

bool Expr::getVal (char c)
{
	int pos = Expr::findSymbol(c);
	if (pos == -1)
	{
		cout << "[ERROR] Symbol not found!\n";
		return true;
	}
	else
		return Expr::symbols[pos].second;
}

void Expr::addSymbol (char c)
{
	if (Expr::findSymbol(c) == -1)
		symbols.push_back(make_pair(c, 0));
}

int Expr::findSymbol (char c)
{
	for (int i = 0; i < Expr::symbols.size(); i++)
		if (Expr::symbols[i].first == c)
			return i;
	return -1;
}

void Expr::addExpr (string s)
{
	if (Expr::findExpr(s) == -1 && s.size() > 1)
		Expr::expr.push_back(pair <string, int> (s, s.size()));
}

int Expr::findExpr (string s)
{
	for (int i = 0; i < Expr::expr.size(); i++)
		if (Expr::expr[i].first == s)
			return i;
	return -1;
}

bool compSymbols (pair <char, bool> a, pair <char, bool> b)
{
	return a.first < b.first;
}

void Expr::init (string s)
{
	Expr::clear();
	Expr::n = new Node();
	Expr::n -> init(s, this);
	sort(Expr::symbols.begin(), Expr::symbols.end(), compSymbols);
	string tmp;
	for (int i = 0; i < Expr::symbols.size(); i++)
	{
		tmp = Expr::symbols[i].first;
		Expr::expr.push_back(pair <string, int> (tmp, 1));
	}
}

bool Expr::next()
{
	int ind = Expr::symbols.size() - 1;
	bool mem = 1;
	while (ind >= 0 && mem)
	{
		if (!Expr::symbols[ind].second)
			mem = 0;
		Expr::symbols[ind].second ^= 1;
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
	sort(Expr::expr.begin(), Expr::expr.end(), compExpr);
	cout << left;
	for (int i = 0; i < Expr::expr.size(); i++)
		cout << "|" << setw(Expr::expr[i].second) << Expr::expr[i].first;
	cout << "\n";
	for (int i = 0; i < Expr::expr.size(); i++)
	{
		cout << "+";
		for (int j = 0; j < Expr::expr[i].second; j++)
			cout << "-";
	}
	cout << "\n";
}

void Expr::show()
{
	cout << left;
	for (int i = 0; i < Expr::expr.size(); i++)
		cout << "|" << setw(Expr::expr[i].second) << (int)Expr::display[Expr::expr[i].first];
	cout << "\n";
	for (int i = 0; i < Expr::expr.size(); i++)
	{
		cout << "+";
		for (int j = 0; j < Expr::expr[i].second; j++)
			cout << "-";
	}
	cout << "\n";
}

void Expr::truthTable ()
{
	Expr::colTitle();
	do
	{
		Expr::n -> calc(this);
		Expr::show();
	} while (Expr::next());
}

void Expr::inspect ()
{
	Expr::n -> inspect();
}

void Expr::debug ()
{
	cout << "Available expressions\n";
	for (int i = 0; i < Expr::expr.size(); i++)
		cout << Expr::expr[i].first << " " << Expr::expr[i].second << "\n";
}

void Expr::clear ()
{
	Expr::n -> clear();
	delete Expr::n;
	Expr::symbols.clear();
	Expr::expr.clear();
	Expr::display.clear();
}	
