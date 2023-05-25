#include <cmath>
#include <iostream>
#include <string>

using namespace std;

struct Stack
{
	Stack* next;
	double info;
};

Stack* push_(Stack* p, double in)
{
	Stack* t = new Stack;
	t->info = in;
	t->next = p;
	return t;
}
Stack* push(Stack* p, char in)
{
	Stack* t = new Stack;
	t->info = in;
	t->next = p;
	return t;
}
Stack* pop(Stack* p, char* out)
{
	Stack* t = p;
	*out = p->info;
	p = p->next;
	delete t;
	return p;
}
Stack* pop_(Stack* p, double* out)
{
	Stack* t = p;
	*out = p->info;
	p = p->next;
	delete t;
	return p;
}
int prior(char operat)
{
	switch (operat)
	{
	case '^': return 4;
	case '*': case '/': return 3;
	case '-': case '+': return 2;
	case '(': return 1;
	}
	return 0;
}
string translate(string in)
{
	string out;
	Stack* st = NULL;
	char buff;
	for (int i = 0; i < in.length(); i++)
	{
		if (in[i] == '(')
		{
			st = push(st, in[i]);
		}
		if (in[i] == ')')
		{
			while ((st->info) != '(')
			{
				st = pop(st, &buff);
				out += buff;
			}
			st = pop(st, &buff);
		}
		if (in[i] >= 'a' && in[i] <= 'z')
		{
			out += in[i];
		}
		if (in[i] == '*' || in[i] == '/' || in[i] == '+' || in[i] == '-' || in[i] == '^')
		{
			while (st != NULL && prior(st->info) >= prior(in[i]))
			{
				st = pop(st, &buff);
				out += buff;
			}
			st = push(st, in[i]);
		}
	}
	while (st != NULL)
	{
		st = pop(st, &buff);
		out += buff;
	}
	return out;
}
double result(string in, double a, double b, double c, double d, double e)
{
	Stack* st_val = NULL;
	double n1, n2, res;
	for (int i = 0; i < in.length(); i++)
	{
		switch (in[i])
		{
		case 'a': st_val = push_(st_val, a); break;
		case 'b': st_val = push_(st_val, b); break;
		case 'c': st_val = push_(st_val, c); break;
		case 'd': st_val = push_(st_val, d); break;
		case 'e': st_val = push_(st_val, e); break;
		case '+':
		{
			st_val = pop_(st_val, &n2);
			st_val = pop_(st_val, &n1);
			res = n1 + n2;
			st_val = push_(st_val, res);
			break;
		}
		case '-':
		{
			st_val = pop_(st_val, &n2);
			st_val = pop_(st_val, &n1);
			res = n1 - n2;
			st_val = push_(st_val, res);
			break;
		}
		case '*':
		{
			st_val = pop_(st_val, &n2);
			st_val = pop_(st_val, &n1);
			res = n1 * n2;
			st_val = push_(st_val, res);
			break;
		}
		case '/':
		{
			st_val = pop_(st_val, &n2);
			st_val = pop_(st_val, &n1);
			res = n1 / n2;
			st_val = push_(st_val, res);
			break;
		}
		case '^':
		{
			st_val = pop_(st_val, &n2);
			st_val = pop_(st_val, &n1);
			res = pow(n1, n2);
			st_val = push_(st_val, res);
			break;
		}
		}
	}
	return res;
}

int main()
{
	string str_in;
	string str_out;
	double a, b, c, d, e;
	cout << "Enter interfix entry: ";
	getline(cin, str_in);
	str_out = translate(str_in);
	cout << "Reverse Polish entry: " << str_out << endl;
	cout << endl << "Enter a: ";
	cin >> a;
	cout << "Enter b: ";
	cin >> b;
	cout << "Enter c: ";
	cin >> c;
	cout << "Enter d: ";
	cin >> d;
	cout << "Enter e: ";
	cin >> e;
	cout << endl << "The result is: " << result(str_out, a, b, c, d, e) << endl;

	return 0;
}