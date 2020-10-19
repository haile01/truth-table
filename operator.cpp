#include "header.h"

const vector <char> OPS = vector <char> {'^', 'v', '+', '>'};

bool isOp (char c)
{
	for (int i = 0; i < OPS.size(); i++)
		if (c == OPS[i])
			return true;
	return false;
}

bool AND (bool a, bool b)
{
	return a & b;
}

bool OR (bool a, bool b)
{
	return a | b;
}

bool XOR (bool a, bool b)
{
	return a ^ b;
}

bool IMPLY (bool a, bool b)
{
	return 0 ? (a & !b) : 1;
}

bool Operator::eval (bool a, bool b)
{
	bool res;
	switch (Operator::c)
	{
		case '^':
			res = AND(a, b);
			break;
		case 'v':
			res = OR(a, b);
			break;
		case '+':
			res = XOR(a, b);
			break;
		case '>':
			res = IMPLY(a, b);
			break;
		default:
			res = 1;
	}
	return res;
}
