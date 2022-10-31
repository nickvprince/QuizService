#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#ifdef __linux__
#include "Answer.cpp"
#endif
#ifdef _WIN32
#include "answer.h"
#endif
class question {
	std::string Question;
	int questionID;
	std::vector<answer> answers;
	float points;
public:
	int getQuestionID();
	question(std::string question, float points);
	bool addAnswer(std::string Answer, bool expected);
	bool deleteAnswer(std::string Answer);
	float getPointsEarned();
	int getType();
	bool selectAnswer(std::string Answer);
	std::vector<std::string> getAnswers();
	std::string getQuestion();
	bool getExpected(std::string option);
	float getPoints();
};