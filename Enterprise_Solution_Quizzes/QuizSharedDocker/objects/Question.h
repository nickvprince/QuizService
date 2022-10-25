#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "answer.h"
using namespace std;
class question {
	std::string question;
	int questionID;
	std::vector<answer> answers;
	float points;
public:
	void Question(std::string question, float points);
	bool addAnswer(std::string Answer, bool expected);
	bool save(FILE file);
	bool load(FILE file);
	bool deleteAnswer(std::string Answer);
	float getPointsEarned();
	int getType();
	bool selectAnswer(std::string Answer);
	std::vector<std::string> getAnswers();
	std::string getQuestion();
	bool getExpected(std::string option);
};