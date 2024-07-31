#pragma once
//Data analyzing class. It consists of reading the data and saving the keywords into struct named Data. Struct has two members: Total amount of
//keywords found in a file and vector pair that consists of keyword and its amount inside the file.
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
struct Data {
	vector<pair<string, float>> vData;
	float TotalAmount;
};
class AnalyzeFileData {
public:
	AnalyzeFileData(string fileName);
	~AnalyzeFileData();
	void GetDataFrequency();
	void GetDataGraph();
	int GetDataReadingSize();
private:
	void OpenFile();
	void ReadFile();
	void Analyze(vector<char>vBUFFER);
	void SaveData(string sCombination); 
	void OrganizeStruct();
	
	string fileName;
	static const int DisplayDataAmount = 10;
	static const int BUFFER_SIZE = 1024;
	static const int maxBarWidth = 250;

	ifstream file;
	Data FileData;
	
};