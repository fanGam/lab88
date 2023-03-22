/*ѕо заданной постфиксной форме построить дерево выражений
и вычислить полученное значение*/
//1*2+3*4=>1 2 * 3 4 * +
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <iomanip>
#include <deque>
#include <stack>

using namespace std;

struct TNode
{
	int Data;
	TNode* Left, * Right;
};

typedef TNode* PNode;

int Trans(string str)
{
	if (str == "+") return -1;
	if (str == "-") return -2;
	if (str == "*") return -3;
	if (str == "/") return -4;
	if (str == "%") return -5;
	if (str == "^") return -6;
	return stoi(str);
}

char Printing(int x)
{
	if (x == -1) return '+';
	if (x == -2) return '-';
	if (x == -3) return '*';
	if (x == -4) return '/';
	if (x == -5) return '%';
	if (x == -6) return '^';
}

int Calc(PNode Root)
{
	if (Root->Data > 0) return Root->Data;
	switch (Root->Data)
	{
	case -1: return Calc(Root->Left) + Calc(Root->Right);
	case -2: return Calc(Root->Left) - Calc(Root->Right);
	case -3: return Calc(Root->Left) * Calc(Root->Right);
	case -4: return Calc(Root->Left) / Calc(Root->Right);
	case -5: return Calc(Root->Left) % Calc(Root->Right);
	case -6: return (int)pow(Calc(Root->Left), Calc(Root->Right));
	}
}

void Print(PNode& Root, int level)
{
	if (Root != NULL) {
		if (Calc(Root) == 0) {
			for (int i = 0; i < level; i++)
				cout << setw(4) << ' ';
			cout << setw(4) << "0" << endl;
		}
		else if (Root->Left != NULL && Root->Right != NULL) {
			if (Calc(Root->Left) == Calc(Root->Right)) {
				for (int i = 0; i < level; i++)
					cout << setw(4) << ' ';
				cout << setw(4) << 0 << endl;
			}
		}
		else {
			Print(Root->Right, level + 1);
			for (int i = 0; i < level; i++)
				cout << setw(4) << ' ';
			if (Root->Data < 0)
				cout << setw(4) << Printing(Root->Data) << endl;
			else
				cout << setw(4) << Root->Data << endl;
			Print(Root->Left, level + 1);
		}
	}
}

void Print1(PNode& Root, int level) {
	if (Root != NULL) {
		Print1(Root->Right, level + 1);
		for (int i = 0; i < level; i++)
			cout << setw(4) << ' ';
		if (Root->Data < 0) {
			if (Calc(Root) >= 0 && Calc(Root) < 10) {
				cout << setw(4) << Calc(Root) << endl;
			}
			else {
				cout << setw(4) << Printing(Root->Data) << endl;
			}
		}
		else
			cout << setw(4) << Root->Data << endl;
		Print1(Root->Left, level + 1);
	}
}

void Del(PNode Root)
{
	if (Root != NULL)
	{
		Del(Root->Left);
		Del(Root->Right);
		delete Root;
	}
}

//PNode CREATE(queue<PNode> st, PNode& Root, int depth) {
//	Root->Data = st.front()->Data;
//	st.pop();
//	Root->Left = CREATE(st, Root->Left);
//	st.pop();
//	Root->Right = CREATE(st, Root->Right);
//	return Root;
//}

int main()
{
	ifstream f("input.txt");
	string str;
	PNode t = NULL, Root;
	deque<PNode>dq;
	stack<PNode>st;
	bool ar = true;
	while (f >> str)
	{
		int op = Trans(str);
		t = new TNode;
		t->Data = op;
		t->Left = t->Right = NULL;
		dq.push_back(t);
	}
	//cout << endl;
	//cout << dq.size() << endl;
	//dqr = dq.rbegin();
	while (!dq.empty()) {
		t = *dq.rbegin();
		if (t->Data >= 0){
			st.push(t);
		}
		else {
			t->Right = st.top();
			st.pop();
			t->Left = st.top();
			st.pop();
			st.push(t);
		}
		dq.pop_back();
	}
	cout << endl;
	Root = t;
	Print1(Root, 0);
	cout << Calc(Root);
	Del(Root);
	return 0;
}
