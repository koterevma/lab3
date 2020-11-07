#include <iostream>
#include "Tree.h"
using namespace std;

int main()
{
	Tree<int> t;
	Tree<int> t2(t);
	t.add(2);
	t.add(1);
	t.add(4);
	t.lpk();
	t2.add(8);
	t2.add(3);
	t2.add(17);
	cout << endl;
	t2.lpk();
	t.add(t2);
	cout << endl << t << endl;
}