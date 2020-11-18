#include <iostream>
#include <thread>
#include "Tree.h"
using namespace std;

struct AlphabeticOrder
{
	bool operator()(const string& s1, const string& s2, const int& i = 0)
	{
		if ((s1[i] == '\0') || (s1[i] < s2[i]))
			return true;
		else
		{
			if (s1[i] > s2[i])
				return false;
			else
				return operator()(s1, s2, i + 1);
		}
	}
};

int main()
{
	
	Tree<int> t;
	std::thread th1([&]() {
		t.add(8);
		t.add(10);
		t.add(2);
		t.add(6);
		});
	std::thread th2([&]() {
		t.add(7);
		t.add(12);
		t.add(5);
		t.add(9);
		});

	th1.join(); th2.join();
	cout << t << endl;
	/*
	Tree<string, AlphabeticOrder> abcTree;
	abcTree.add("Oliver");
	abcTree.add("Jack");
	abcTree.add("Harry");
	abcTree.add("Jacob");
	abcTree.add("Charlie");
	abcTree.add("Oscar");
	cout << abcTree << endl;
	*/
	return 0;
}
