#include "./Answer.h"
#include "./Logger.cpp"
/// <summary>
/// initializer with the answer, what the expected result should be, and the question ID that goes with it
/// </summary>
/// <param name="answer"></param>
/// <param name="expected"></param>
/// <param name="questionID"></param>
answer::answer(std::string answer, bool expected, int questionID) {
	
	this->Answer = answer;
	this->expected = expected;
	this->questionID = questionID;
	this->selected = false;
	Logger::log("Answer "+this->Answer+" Created", 0, "answerLog");
}
/// <summary>
/// alters the state of this answer, if false becomes true, if true becomes false
/// </summary>
/// <returns></returns>
bool answer::select() {
	if (this->selected == false) {
		this->selected = true;
		Logger::log("Answer " + this->Answer + " set to selected", 0, "answerLog");
		return true;
	}
	else if (this->selected == true) {
		this->selected = false;
		Logger::log("Answer " + this->Answer + " set to diselected", 0, "answerLog");
		return false;
	}
	else {
		Logger::log("Error Select not equals true or false", 0, "Errors");
		throw "Error Select not equal true or false... Is it initialized?";
	}
	Logger::log("ERROR - Answer::select returned false", 0, "answerLog");
	return false;
}
/// <summary>
/// Returns the string of what the answer is ie: What is a dog? answer = "dog"
/// </summary>
/// <returns></returns>
std::string answer::getAnswer() {
	return this->Answer;
}
/// <summary>
/// Returns true if the value of selected is what is expected
/// </summary>
/// <returns></returns>
bool answer::isCorrect() {
	if (this->selected == this->expected) {
		return true;
	}
	else {
		return false;
	}
}
/// <summary>
/// returns true if the answer is supposed to be selected and false if its not
/// </summary>
/// <returns></returns>
bool answer::getExpected() {
	return this->expected;
}
/// <summary>
/// returns the question ID
/// </summary>
/// <returns></returns>
int answer::getQuestionID() {
	return this->questionID;
}

bool answer::setExpected(bool expected)
{
	this->expected = expected;
	return this->expected;
}
