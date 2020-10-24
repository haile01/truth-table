#include "header.h"

string trim (string s, bool &neg)
{
	// Remove all whitespaces
	string res = "";
	for (int i = 0; i < s.size(); i++)
		if (s[i] != ' ')
			res += s[i];
	vector <int> start, end;
	s = res;
	int l = 0, r = s.size() - 1;

	// Find continuous preceeding ( and succeeding )
	while (l < s.size())
	{
		if (s[l] == '(' || (l < s.size() - 1 && s[l] == '-' && s[l + 1] == '('))
		{
			l += s[l] == '(' ? 1 : 2;
			start.push_back(l);
		}
		else
			break;
	}
	while (r >= 0)
	{
		if (s[r] == ')')
		{
			r--;
			end.push_back(r);
		}
		else
			break;
	}

	// Find maximum preceeding ( and succeeding ) to remove
	int cur = start.size(), num = cur;
	for (; l <= r; l++)
	{
		if (s[l] == '(')
			cur++;
		if (s[l] == ')')
		{
			cur--;
			num = min(num, cur);
		}
	}

	cur = 0;
	// Calculate how many negatives we removed
	for (int i = 0; i < num; i++)
	{
		if (start[i] - cur == 2)
			neg = !neg;
		cur = start[i];
	}
	if (num)
		l = start[num - 1], r = end[num - 1];
	else
		l = 0, r = s.size() - 1;

	return s.substr(l, r - l + 1);
}

bool isBinary(string s)
{
	int cur = 0;
	for (int i = 0; i < s.size(); i++)
	{
		cur += s[i] == '(' ? 1 : (s[i] == ')' ? -1 : 0);
		if (cur == 0 && isOp(s[i]) && i < s.size() - 1)
			return true;
	}
	return false;
}

bool eval (string s)
{
	int cur = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '(')
			cur++;
		if (s[i] == ')')
			cur--;
		if (cur < 0)
			return false;
	}
	return cur == 0;
}

string getNeg (string s, bool binary)
{
	if (binary)
		return "-(" + s + ")";
	else
		return "-" + s;
}

bool Node::init (string s, Expr *e)
{	
	if (!eval(s))
		return false;
	s = trim(s, neg);
	
	expr = s;
	if ((e -> display.find(s)) == (e -> display.end()))
		e -> display.insert(pair <string, bool> (s, 0));
	e -> addExpr(s);

	if (!isBinary(s))
	{
		if (s[0] == '-')
		{
			neg = !neg;
			symbol = s[1];
			expr = s[1];
		}
		else
		{
			symbol = s[0];
			expr = s[0];
		}
		e -> addSymbol(symbol);
	}
	else
	{
		if (neg)
		{
			string _s = getNeg(s, 1);
			if ((e -> display.find(_s)) == (e -> display.end()))
				e -> display.insert(pair <string, bool> (_s, 0));
			e -> addExpr(_s);
		}

		int cur = 0, mxPrior = -1, ind;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == '(')
				cur++;
			if (s[i] == ')')
				cur--;
			if (isOp(s[i]) && cur == 0)
				if (mxPrior < getPrior(s[i]))
				{
					mxPrior = getPrior(s[i]);
					ind = i;
				}
		}
		l = new Node();
		r = new Node();
		l -> init(s.substr(0, ind), e);
		r -> init(s.substr(ind + 1), e);
		op = new Operator(s[ind]);
	}
	return true;
}

bool Node::calc (Expr *e)
{
	bool res;
	if (l == nullptr)
		res = e -> getVal(symbol);
	else
	{
		bool left = l -> calc(e), right = r -> calc(e);
		res = op -> eval(left, right);
	}
	e -> display[expr] = res;
	if (neg)
	{
		res = !res;
		e -> display[getNeg(expr, l != nullptr)] = res;
	}
	return res;
}

void Node::inspect ()
{
	cout << neg << " - ";
	if (symbol != ' ')
		cout << symbol << " - ";
	else
		cout << "No symbol - ";
	if (op -> c != ' ')
		cout << op -> c << "\n";
	else
		cout << "No operator\n";
	if (l)
	{
		l -> inspect();
		r -> inspect();
	}
}

Node::~Node ()
{
	if (l)
	{
		l -> ~Node();
		r -> ~Node();
	}
	delete op;
}
