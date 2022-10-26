#include "./Answer.h"

answer::answer(std::string answer, bool expected, int questionID) {
	this->Answer = answer;
	this->expected = expected;
	this->questionID = questionID;
	this->selected = false;
}
bool answer::select() {
	if (this->selected == false) {
		this->selected = true;
		this->expected = true;
		return true;
	}
	else if (this->selected == true) {
		this->selected = false;
		this->expected = false;
		return false;
	}
	else {
		throw "Error Select not equal true or false... Is it initialized?";
	}
	return false;
}
std::string answer::getAnswer() {
	return this->Answer;
}
bool answer::isCorrect() {
	if (this->selected == this->expected) {
		return true;
	}
	else {
		return false;
	}
}
bool answer::getExpected() {
	return this->expected;
}
int answer::getQuestionID() {
	return this->questionID;
}
