#include<iostream>
#include<string>
#include "MyStack.h"
#define SIZE 20
using namespace std;
static int precedence(char ch) {
	switch (ch)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '^':
		return 3;
	}
	return -1;
}
bool isOperator(char ch) {
	if (ch == '^' || ch == '/' || ch == '*' || ch == '+' || ch == '-')
		return true;
	return false;
}
bool isOperand(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
		return true;
	return false;
}
bool isBalancedParenth(string notation) {
	MyStack stack;
	char topOfStack = '\0';
	for (int i = 0; i < notation.length(); i++) {
		if (notation[i] == '(' || notation[i] == '{' || notation[i] == '[') {
			stack.push(notation[i]);
			continue;
		}
		if (!stack.isEmpty()) {
			switch (notation[i])
			{
			case ')':
				topOfStack = stack.pop();
				if (topOfStack == '{' || topOfStack == '[')
					return false;
				break;

			case '}':
				topOfStack = stack.pop();
				if (topOfStack == '(' || topOfStack == '[')
					return false;
				break;
			case ']':
				topOfStack = stack.pop();
				if (topOfStack == '(' || topOfStack == '{')
					return false;
				break;
			}
		}
	}
	return (stack.isEmpty());
}
string reversePolish(string infixNotation) {
	MyStack stack;
	string postfixNotation = "";
	for (int i = 0; i < infixNotation.length(); i++) {
		if (isOperator(infixNotation[i])) {
			while (stack.retTop() != '#' && stack.retTop() != '(' && (precedence(infixNotation[i]) <= precedence(stack.retTop())))
				postfixNotation += stack.pop();
			stack.push(infixNotation[i]);
		}
		else if (isOperand(infixNotation[i])) {
			postfixNotation += infixNotation[i];
		}
		else if (infixNotation[i] == '(') {
			stack.push(infixNotation[i]);
		}
		else if (infixNotation[i] == ')') {
			while (stack.retTop() != '#' && stack.retTop() != '(') {
				postfixNotation += stack.pop();
			}
			stack.pop();
		}
	}
	while (stack.retTop() != '#') {
		postfixNotation += stack.pop();
	}
	return postfixNotation;
}
string polish(string notation) {
	string reverseNotation = "";
	string prefix = "";
	for (int i = notation.length(); i >= 0; i--) {
		char token = notation[i];
		if (token == '(')
			notation[i] = ')';
		if (token == ')')
			notation[i] = '(';
		reverseNotation += notation[i];
	}
	string postfix = reversePolish(reverseNotation);
	for (int i = postfix.length(); i >= 0; i--) {
		prefix += postfix[i];
	}
	return prefix;
}
int evaluate(string postfixNotation) {
	MyStack stack;
	int num1 = 0;
	int num2 = 0;
	int answer = 0;
	for (int i = 0; i < postfixNotation.length(); i++) {

		if (isOperand(postfixNotation[i]))
			stack.push(postfixNotation[i]);
		else if (isOperator(postfixNotation[i])) {
			num1 = static_cast<int>(stack.pop()) - 48;
			num2 = static_cast<int>(stack.pop()) - 48;
			if (postfixNotation[i] == '^') {
				answer = num2 ^ num1;
				stack.push(answer + 48);
			}
			else if (postfixNotation[i] == '/') {
				answer = num2 / num1;
				stack.push(answer + 48);
			}
			else if (postfixNotation[i] == '*') {
				answer = num2 * num1;
				stack.push(answer + 48);
			}
			else if (postfixNotation[i] == '-') {
				answer = num2 - num1;
				stack.push(answer + 48);
			}
			else if (postfixNotation[i] == '+') {
				answer = num2 + num1;
				stack.push(answer + 48);
			}
		}

	}
	return answer;
}
int main() {
	string infixNotation = "";
	cout << "Enter the infix Notation:";
	getline(cin, infixNotation);
	int choice = 0;
	while (true) {
		cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "\t\t\t                MENU                \n";
		cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "\t\t\t          1. Infix to Postfix       \n";
		cout << "\t\t\t          2. Infix to Prefix        \n";
		cout << "\t\t\t          3. Evaluate               \n";
		cout << "\t\t\t          4. Check Parenth Balance  \n";
		cout << "\t\t\t          5. EXIT                   \n";
		cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
		cout << "Enter your choice:";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Postfix Notation is : " << reversePolish(infixNotation) << endl;
			break;
		case 2:
			cout << "Prefix Notation is : " << polish(infixNotation) << endl;
			break;
		case 3: {
			cin.ignore(1, '\n');
			string evaluateNotation = "";
			cout << "Enter the Notation to evaluate:";
			getline(cin, evaluateNotation);
			cout << "Answer: " << evaluate(reversePolish(evaluateNotation))<<endl;
			break; 
		}
		case 4: {
			cin.ignore(1, '\n');
			string parenthNotation = "";
			cout << "Enter the Notation:";
			getline(cin, parenthNotation);
			if (isBalancedParenth(parenthNotation))
				cout << "-: Parenthesis are Balanced! :-\n";
			else
				cout << "-: Braces are Unbalanced! :-\n";
			break; 
		}
		case 5:
			exit(-1);
		default:
			cout << "Invalid command!\n";
		}
	}
	cout << endl;
	system("pause");
	return 0;
}