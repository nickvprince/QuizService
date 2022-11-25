#pragma once
#ifdef __linux__
#include "./Question.cpp"
#endif
#ifdef _WIN32
#include "./Question.h"
#endif
#ifdef __linux__

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
	bool loadFromDb();
	std::string getID();
	bool deletePool(std::string);
	void print();
	bool getSelected(std::string question, std::string option);
		
	};

#endif