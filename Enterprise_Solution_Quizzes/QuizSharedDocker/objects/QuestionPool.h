#pragma once
#ifdef __linux__
#include "./Question.cpp"
#endif
#ifdef _WIN32
#include "./Question.h"
#endif

class QuestionPool {
	std::string ID;
	std::vector<question> questions;
public:
	QuestionPool(std::string poolname);
	bool addQuestion(std::string question, float points);
	bool getExpected(std::string question, std::string answer);
	bool addOption(std::string question, std::string option,bool expected);
	bool deleteOption(std::string question, std::string option);
	std::vector<std::string> getQuestions();
	std::vector<std::string> getOptions(std::string question);
	bool setAnswer(std::string question, std::string option, bool answer);
	bool save(int overWrite);
	bool load();
	void deleteQuestionPool(std::string poolid);
	std::string getID();
};