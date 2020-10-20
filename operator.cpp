#include "header.h"

const vector <char> OPS = vector <char> {'^', 'v', '+', '>', '~'};

bool isOp (char c)
{
	for (int i = 0; i < OPS.size(); i++)
		if (c == OPS[i])
			return true;
	return false;
}

int getPrior (char c)
{
	if (isOp(c))
	{
		if (c == '^' || c == 'v' || c == '+')
			return 0;
		if (c == '>' || c == '~')
			return 1;
	}
	return -1;
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
	return (a & !b) ? 0 : 1;
}

bool IFF (bool a, bool b)
{
	return (a & b) || (!a & !b);
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
		case '~':
			res = IFF(a, b);
			break;
		default:
			res = 1;
	}
	return res;
}
