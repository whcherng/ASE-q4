#pragma once
#include <string>
#include <allocators>
#include <unordered_map>
#include <list>
#include <fstream>
#include <map>
#include <algorithm>


using namespace std;

template <typename MAP>
void genericTestPerformance(MAP& forward_map,string fileName,int times=1)
{
	MAP& backward_map= MAP();
	using K = string;
	using T = string;

	ofstream myfile;
	myfile.open("result.csv");

	for (int i = 0; i < times; i++) {
		// record the start time of the algorithm
		auto phaseStart = std::chrono::steady_clock::now();

		//Load the contents into a searchable data structure decided.
		ifstream inFile(fileName);
		string temp;
		T easterly;
		K westerly;
		while (getline(inFile, temp)) {


			MAP::iterator it = forward_map.end();
			MAP::iterator it_backward = backward_map.end();

			easterly = temp.substr(0, temp.find(','));
			westerly = temp.substr(temp.find(',') + 1);
			forward_map.insert(it,make_pair(easterly, westerly));
			backward_map.insert(it_backward,make_pair(westerly, easterly));
		}

		//record the end time of the algorithm
		auto phaseEnd = std::chrono::steady_clock::now();

		//measure the time used
		auto phaseElapsed = std::chrono::duration_cast <std::chrono::microseconds> (phaseEnd - phaseStart);
		//output the duration 
		std::cout << "insert time: " << float(phaseElapsed.count() / 1E6) << std::endl;

		//Create an empty sequence container suitable for storing the resulting sequence of names.
		list<T> emptySequenceContainer;

		//Arbitrarily choose one of the names as a starting point.
		MAP::iterator it = forward_map.begin();

		//Add the name to the back of the result sequence
		emptySequenceContainer.push_back(it->first);


		//Identify westerly neighbourm repeat until 
		//the most westerly man has been added to the sequence.
		for (int i = 0; i < forward_map.size(); i++) {
			MAP::iterator it = forward_map.find(emptySequenceContainer.back());
			if (it != forward_map.end())
				emptySequenceContainer.push_back(it->second);
			else
				break;
		}

		//method2
	/*	for (int i = 0; i < forward_map.size(); i++) {
			auto back_value=emptySequenceContainer.back();
			auto it = std::find_if(forward_map.begin(), forward_map.end(),
				[back_value](const std::pair<K, T>& element) { return element.first == back_value; });
			if (it != forward_map.end())
				emptySequenceContainer.push_back(it->second);
			else
				break;
		}*/

		//Identify easterly neighbourm repeat until 
		//the most easterly man has been added to the sequence.
		for (int i = 0; i < backward_map.size(); i++) {
			MAP::iterator it = backward_map.find(emptySequenceContainer.front());
			if (it != backward_map.end())
				emptySequenceContainer.push_front(it->second);
			else
				break;
		}

		//method 2
	/*	for (int i = 0; i < backward_map.size(); i++) {
			auto front_value = emptySequenceContainer.front();
			auto it = std::find_if(backward_map.begin(), backward_map.end(),
				[front_value](const std::pair<K, T>& element) { return element.first == front_value; });
			if (it != backward_map.end())
				emptySequenceContainer.push_front(it->second);
			else
				break;
		}*/

		//record the end time of the algorithm
		 phaseEnd = std::chrono::steady_clock::now();

		//measure the time used
		 phaseElapsed = std::chrono::duration_cast <std::chrono::microseconds> (phaseEnd - phaseStart);


		//output the duration 
		std::cout << "Call(s) elapsed time: " << float(phaseElapsed.count() / 1E6) << std::endl;
		myfile << float(phaseElapsed.count() / 1E6) << ",";

		system("pause");

		//output the size 
		cout << emptySequenceContainer.size() << endl;
		for (string x : emptySequenceContainer)
			cout << x << endl;
	}
	myfile.close();
}


