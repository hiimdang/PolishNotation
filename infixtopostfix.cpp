#include <iostream>
#include <string>
#include "queue.h"
#include "stack.h"
using namespace std;

//func create pure infix
bool isSpace(char x) { //true -> is space
	return (x == ' ' || x == '\t');
}
void createinfixPure(string& raw, string& pure) { // create a string of infix that not have any space in there
	for (int i = 0; i < raw.length(); i++) {
		if (!isSpace(raw[i])) {
			pure.push_back(raw[i]);
		}
	}
}
// ---
 
//processing pureinfix to postfix
bool isNumber(char x) {//true -> Operand. false ->!number
	return (x >= '0' && x <= '9');
}
bool isOperator(char x) { //true -> Operator. false -> !Operator
	return(x == '+' || x == '-' || x == '*' || x == '/');
}
int rankOperator(char x) {// 1: +- ; 2: */
	if (x == '+' || x == '-') {
		return 1;
	}
	if (x == '*' || x == '/') {
		return 2;
	}
}

void processing(Queue<string>& q, Stack<string>& s, string x) {
		if (isNumber(x[0])) {
			q.push(x);
		}
		if (x[0] == '(') {
			s.push(x);
		}
		if (x[0] == ')') {
			string temp;
			while (1 > 0) {
				temp = s.pop()->data;
				if (temp[0] == '(') {
					break;
				}
				q.push(temp);
			}
		}
		if (isOperator(x[0])) {
			if (s.isEmpty()) {
				s.push(x);
			}
			else {
				char topStack = s.top()->data[0];
				if (!isOperator(topStack)) { //if top of stack is not a operator
					s.push(x);
				}
				else { //top of stack is a operator
					if (rankOperator(topStack) < rankOperator(x[0])) {
						s.push(x);
					}
					else { //rankOperator of top stack is >= rankOperator of x
						string temp;
						while (1 > 0) {
							temp = s.pop()->data;
							q.push(temp);
							if (s.isEmpty()) {
								s.push(x);
								break;
							}
							if (!isOperator(s.top()->data[0])) {
								s.push(x);
								break;
							}
						}
					}
				}
			}
		}
}
void lastProcessing(Queue<string>& q, Stack<string>& s) {
	//do this shiet after checking all the infix
	while(1>0){
		string temp;
		temp.push_back(s.pop()->data[0]);
		q.push(temp);
		if (s.isEmpty()) {
			break;
		}
	}
}
//end processing pureinfix
//==> btw after this fvkin' long processing func, we got a queue that contain conflix inside
float calculate(Queue<string>& q, Stack<string>& s) {
	float num;
	for (NODEQ<string>* k = q.pHead; k != NULL; k = k->pNext) {
		if (isNumber(k->data[0])) {
			s.push(k->data);
		}
		if (isOperator(k->data[0])) {
			float p1 = stoi(s.pop()->data); //convert string to int
			float p2 = stoi(s.pop()->data);
			switch (k->data[0]) {
				case '*': {
					num = p2 * p1;
					s.push(to_string(num));
					break;
				}
				case '/': {
					num = p2 / p1;
					s.push(to_string(num));
					break;
				}
				case '+': {
					num = p2 + p1;
					s.push(to_string(num));
					break;
				}
				case '-': {
					num = p2 - p1;
					s.push(to_string(num));
					break;
				}
			}
		}
	}
	return num;
}
int main() {
	Queue<string> q;
	Stack<string> s;
	string infixRaw, infixPure;
	//---
	s.init();
	q.init();
	//---
	cout << "Infix: ";
	getline(cin, infixRaw); //input raw infix
	createinfixPure(infixRaw, infixPure); //create pure infix

	//get x and convert from pure infix to postfix
	int j;
	for (int i = 0; i < infixPure.length(); i++) {
		string x;
		if (infixPure[i] == '(' || infixPure[i] == ')' || isOperator(infixPure[i])) {
			x.push_back(infixPure[i]);
		}
		j = 0;
		while (isNumber(infixPure[i])) {
			x.push_back(infixPure[i]);
			j += 1;
			if (isNumber(infixPure[i + 1])) {
				i += 1;
			}
			else {
				break;
			}
		}
		if (x[0] != NULL) { // done get x
			processing(q, s, x);
		}
	}
	lastProcessing(q, s);
	//end get x and sthing thats fvkin' long so i dont wanna to retyping it lul
	cout << "Postfix: ";
	for (NODEQ<string>* k = q.pHead; k != NULL; k = k->pNext) {
		cout <<k->data<< " ";
	}
	//calculate postfix to final number
	cout << "\n" << "Result: (~)";
	cout << calculate(q, s);
	//End calculate
	return 0;
}
