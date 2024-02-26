// expression evaluator.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <stack>
#include <map>

using namespace std;

bool isOperator(char c)
{
	// define operators array
	// char operators[] = { '+', '-', '*', '/', '^', '(', ')', '&', '|', '<', '>', '=' };
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
	case '(':
	case ')':
	case '&':
	case '|':
	case '<':
	case '>':
	case '=': return true;
	default: return false;
	}
}


string infixToPostfix(string infix, map<char, int> precedence)
{
	// remove spaces from infix expression
	infix.erase( remove(infix.begin(), infix.end(), ' ') , infix.end());
	
	stack<char> operators;
	string postfix;
	for (int i = 0; i < infix.length(); i++)
	{
		if (isOperator(infix[i]))
		{
			if (operators.empty())
			{
				operators.push(infix[i]);
			}
			else
			{
				if (infix[i] == ')')
				{
					while (operators.top() != '(')
					{
						postfix += operators.top();
						operators.pop();
					}
					operators.pop();
				}
				else if (infix[i] == '(')
				{
					operators.push(infix[i]);
				}
				else
				{
					if (precedence[infix[i]] > precedence[operators.top()])
					{
						operators.push(infix[i]);
					}
					else
					{
						while (!operators.empty() && precedence[infix[i]] <= precedence[operators.top()])
						{
							postfix += operators.top();
							operators.pop();
						}
						operators.push(infix[i]);
					}
				}
			}
		}
		else
		{
			postfix += infix[i];
		}
	}
	while (!operators.empty())
	{
		postfix += operators.top();
		operators.pop();
	}
	return postfix;
}
// a function to rverse brackets direction in a string
void reverseBrackets(string* infix)
{
	for (int i = 0; i < (*infix).length(); i++)
	{
		if ((*infix)[i] == '(')
			(*infix)[i] = ')';
		else if ((*infix)[i] == ')')
			(*infix)[i] = '(';
	}
}

// evaluate postfix expression
int evaluatePostfix(string postfix)
{
    stack<int> operands;
    for (int i = 0; i < postfix.length(); i++)
    {
        if (isOperator(postfix[i]))
        {
            int op2 = operands.top();
            operands.pop();
            int op1 = operands.top();
            operands.pop();
            switch (postfix[i])
            {
                case '+':
                    operands.push(op1 + op2);
                    break;
                case '-':
                    operands.push(op1 - op2);
                    break;
                case '*':
                    operands.push(op1 * op2);
                    break;
                case '/':
                    operands.push(op1 / op2);
                    break;
                case '^':
                    operands.push(pow(op1, op2));
                    break;
				case '&':
					operands.push((op1 && op2)? 1 : 0);
					break;
				case '|':
					operands.push((op1 || op2)? 1 : 0);
					break;
				case '<':
					operands.push((op1 < op2)? 1 : 0);
					break;
				case '>':
					operands.push((op1 > op2)? 1 : 0);
					break;
				case '=':
					operands.push((op1 == op2)? 1 : 0);
					break;
                default:
                    break;
            }
        }
        else
        {
            operands.push(postfix[i] - '0');
        }
    }
    return operands.top();
}

// evaluate postfix right to left associativity
int evaluatePostfixRightToLeft(string postfix)	
{
	stack<int> operands;
	for (int i = 0; i < postfix.length(); i++)
	{
		if (isOperator(postfix[i]))
		{
			int op1 = operands.top();
			operands.pop();
			int op2 = operands.top();
			operands.pop();
			switch (postfix[i])
			{
				case '+':
					operands.push(op1 + op2);
					break;
				case '-':
					operands.push(op1 - op2);
					break;
				case '*':
					operands.push(op1 * op2);
					break;
				case '/':
					operands.push(op1 / op2);
					break;
				case '^':
					operands.push(pow(op1, op2));
					break;
				case '&':
					operands.push((op1 && op2)? 1 : 0);
					break;
				case '|':
					operands.push((op1 || op2)? 1 : 0);
					break;
				case '<':
					operands.push((op1 < op2)? 1 : 0);
					break;
				case '>':
					operands.push((op1 > op2)? 1 : 0);
					break;
				case '=':
					operands.push((op1 == op2)? 1 : 0);
					break;
				default:
					break;
			}
		}
		else
		{
			operands.push(postfix[i] - '0');
		}
	}
	return operands.top();
}


// evaluate postfix expression
int main()
{
	// take infix expression as input
	string infix;
	cout << "Enter infix expression: ";
	getline(cin, infix);

	
	// determine precedence of operators
	cout << "Enter precedence of operators (+, -, *, /, ^, &, |, <, >, =) from 1 to 5 accordingly: \n";
	cout << "Note: 1 is the lowest precedence and 10 is the highest precedence\n";
	cout << "Note: operators with the same precedence will be evaluated according to associativity\n";
	map<char, int> precedence;
	// precedence['+'] = 1;
	// precedence['-'] = 1;
	// precedence['*'] = 2;
	// precedence['/'] = 2;
	// precedence['^'] = 3;
	for (char op : { '+', '-', '*', '/', '^', '&', '|', '<', '>', '=' })
	{
		int p;
		cout << "Enter precedence of " << op << ": ";
		cin >> p;
		if(p < 1 || p > 10)
		{
			cout << "\nInvalid input\n";
			exit(1);
		}
		precedence[op] = p;
	}
	// print the precendence
	cout << "Precedence of operators:\n";
	for (auto it = precedence.begin(); it != precedence.end(); it++)
	{
		cout << it->first << " : " << it->second << endl;
	}

	// determine evaluation method
	cout << "1- left to right\n2- right to left\nEnter evaluation method: ";
	int method;
	cin >> method;
	if (method == 2)
	{
		reverse(infix.begin(), infix.end());
		reverseBrackets(&infix);
	}
	else if (method != 1)
	{
		cout << "\nInvalid input\n";
		exit(1);
	}
	cout << "Infix expression: " << infix << endl;

	// convert infix to postfix
	string postfix = infixToPostfix(infix, precedence);
	cout << "Postfix expression: " << postfix << endl;

	// evaluate postfix expression
	if(method == 1)
		cout << "Result: " << evaluatePostfix(postfix) << endl;
	else
		cout << "Result: " << evaluatePostfixRightToLeft(postfix) << endl;
	return 0;
}
