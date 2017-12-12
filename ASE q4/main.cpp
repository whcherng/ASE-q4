#include <list>
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <iterator>
#include <string>
#include <chrono>
#include <map>
#include <list>
#include <unordered_map>
#include "Container.h"

using namespace std;


unordered_map<string, string> unorderedMap;
map<string, string> Map;
std::list < std::pair<string, string>>  aList;

void main() {
	string fileName = "100k.txt";
	bool repeat = false;
	int choose = 0;
	int number = 1;
	do
	{
		cout << "please choose the container type to be tested" << endl;
		cout << "1.unorderd_map" << endl;
		cout << "2.map" << endl;
		cout << "3.list" << endl;
		cin >> choose;

		cout << endl;
		cout << "Please input the number of times the algorithms should be repeated" << endl;
		cin >> number;

		switch (choose) {
		case 1:
			genericTestPerformance(unorderedMap, fileName, number);
			break;
		case 2:
			genericTestPerformance(Map, fileName, number);
			break;
		case 3:
			//genericTestPerformance(aList, fileName, number);
			break;
		default:
			cout << "Invalid Choice." << endl;
		}

		cout << endl;
		cout << "Repeat?" << endl;
		cout << "1.Yes" << endl;
		cin >> choose;
		if (choose == 1)
			repeat = true;
		else
			repeat = false;
	} while (repeat);

	cout << "Result saved in Result.csv" << endl;
	system("pause");
}