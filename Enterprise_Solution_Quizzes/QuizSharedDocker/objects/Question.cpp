#include "./Question.h"
#ifdef _WIN32
std::string file = "QuizSharedDocker/public/QuestionPool/";
#endif
#ifdef __linux__
std::string file = "../public/QuestionPool/";
#endif
int question::getQuestionID()
{
	return this->questionID;
}

question::question(std::string Question, float points) {
	this->Question = Question;
	this->points = points;
	this->questionID = 0;

	//set question id to next available number
	ifstream infile;
	infile.open(file+"QuestionNumber.data");
	string data;
	getline(infile, data); // get line
	this->questionID = atoi(data.c_str())+1;
	infile.close();

	//output new current number
	ofstream outfile;
	outfile.open(file+"QuestionNumber.data", std::ios::out);
	outfile << this->questionID;
	outfile.close();
}
bool question::addAnswer(std::string Answer, bool expected) {
	answer ans(Answer, expected, this->questionID);
	this->answers.push_back(ans);
	return true;
}
bool question::save(FILE file) {
	return false;
}
bool question::load(FILE file) {
	return false;
}
bool question::deleteAnswer(std::string Answer) {
	int size = this->answers.size();
	for (int i = 0; i < size; i++) {
		if (this->answers.at(i).getAnswer() == Answer) {
			this->answers.erase(this->answers.begin() + i);
		}
	}
	return true;
}
float question::getPointsEarned() {
	int correctCount = 0;
	int size = this->answers.size();
	int possibleAnswers = 0;
	for (int i = 0; i < size; i++) {
		if (this->answers.at(i).getExpected() == true) {
			possibleAnswers++;
		}
		if (this->answers.at(i).isCorrect() == true && this->answers.at(i).getExpected() == true) {
			correctCount++;
		}
	}
	return this->points * (correctCount / possibleAnswers);
}
int question::getType() {
	int size = this->answers.size();
	int possibleAnswers = 0;
	for (int i = 0; i < size; i++) {
		if (this->answers.at(i).getExpected() == true) {
			possibleAnswers++;
		}
	}
	if (possibleAnswers == 1) {
		return 0;
	}
	else if (possibleAnswers > 1) {
		return 1;
	}
	else {
		throw "Question has no answers! was this meant to be a written question? Not currently implemented...";
	}
}
bool question::selectAnswer(std::string Answer) {
	int size = this->answers.size();

	for (int i = 0; i < size; i++) {
		if (this->answers.at(i).getAnswer() == Answer) {
			return this->answers.at(i).select();
			
		}
	}
	return false;
}
std::vector<std::string> question::getAnswers() {
	std::vector<std::string> answers;
	int size = this->answers.size();

	for (int i = 0; i < size; i++) {
		answers.push_back(this->answers.at(i).getAnswer());
	}
	return answers;
}
std::string question::getQuestion() {
	return this->Question;
}

bool question::getExpected(std::string option)
{

	int size = this->answers.size();

	for (int i = 0; i < size; i++) {
		if (this->answers.at(i).getAnswer() == option) {
			return this->answers.at(i).getExpected();
		}
	}

	return false;
}
