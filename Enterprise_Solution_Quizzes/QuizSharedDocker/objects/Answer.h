#pragma once
#include <string>
using namespace std;

class answer {
private:
	std::string Answer;
	int questionID;
	bool selected;
	bool expected;
public:
	answer(std::string answer, bool expected, int questionID);
	bool select();
	std::string getAnswer();
	bool isCorrect();
	bool getExpected();
	int getQuestionID();
	bool setExpected(bool expected);
};