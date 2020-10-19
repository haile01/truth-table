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
	s = trim(s, Node::neg);
	
	Node::expr = s;
	if ((e -> display.find(s)) == (e -> display.end()))
		e -> display.insert(pair <string, bool> (s, 0));
	e -> addExpr(s);

	if (!isBinary(s))
	{
		if (s[0] == '-')
		{
			Node::neg = !Node::neg;
			Node::symbol = s[1];
			Node::expr = s[1];
		}
		else
		{
			Node::symbol = s[0];
			Node::expr = s[0];
		}
		e -> addSymbol(Node::symbol);
	}
	else
	{
		if (Node::neg)
		{
			string _s = getNeg(s, 1);
			if ((e -> display.find(_s)) == (e -> display.end()))
				e -> display.insert(pair <string, bool> (_s, 0));
			e -> addExpr(_s);
		}

		int i, cur = 0;
		for (i = 0; i < s.size(); i++)
		{
			if (s[i] == '(')
				cur++;
			if (s[i] == ')')
				cur--;
			if (isOp(s[i]) && cur == 0)
				break;
		}
		Node::l = new Node();
		Node::r = new Node();
		Node::l -> init(s.substr(0, i), e);
		Node::r -> init(s.substr(i + 1), e);
		Node::op = new Operator(s[i]);
	}
	return true;
}

bool Node::calc (Expr *e)
{
	bool res;
	if (Node::l == nullptr)
		res = e -> getVal(Node::symbol);
	else
	{
		bool l = Node::l -> calc(e), r = Node::r -> calc(e);
		res = Node::op -> eval(l, r);
	}
	e -> display[Node::expr] = res;
	if (Node::neg)
	{
		res = !res;
		e -> display[getNeg(Node::expr, Node::l != nullptr)] = res;
	}
	return res;
}

void Node::inspect ()
{
	cout << Node::neg << " - ";
	if (Node::symbol != ' ')
		cout << Node::symbol << " - ";
	else
		cout << "No symbol - ";
	if (Node::op -> c != ' ')
		cout << Node::op -> c << "\n";
	else
		cout << "No operator\n";
	if (Node::l)
	{
		Node::l -> inspect();
		Node::r -> inspect();
	}
}

void Node::clear ()
{
	if (Node::l)
	{
		Node::l -> clear();
		Node::r -> clear();
		delete Node::l;
		delete Node::r;
	}
	delete Node::op;
}
