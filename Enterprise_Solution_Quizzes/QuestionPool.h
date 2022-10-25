#pragma once
#include <string>
#include <vector>
#include "QuizSharedDocker/objects/Question.h"
class QuestionPool {
	std::string ID;
	std::vector<question> questions;
public:
	bool addQuestion(std::string question, int type, float points);
	bool addOption(std::string question, std::string option);
	bool deleteOption(std::string question, std::string option);
	std::vector<std::string> getQuestions();
	std::vector<std::string> getOptions(std::string question);
	bool setAnswer(std::string question, std::string option, bool answer);
	bool save();
	bool load();


};