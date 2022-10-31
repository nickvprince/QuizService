#include "./Question.h"
#ifdef _WIN32
std::string file = "QuizSharedDocker/public/QuestionPool/";
#endif
#ifdef __linux__
std::string file = "./public/QuestionPool/";
#endif
/// <summary>
/// return the question ID of this question
/// </summary>
/// <returns></returns>
int question::getQuestionID()
{
	return this->questionID;
}

/// <summary>
/// Initialize a question with a string ie, the question " What is a dog" and the points that can be achieved
/// </summary>
/// <param name="Question"></param>
/// <param name="points"></param>
question::question(std::string Question, float points) {
	this->Question = Question;
	this->points = points;
	this->questionID = 0;

	//set question id to next available number
	ifstream infile;
	infile.open("../public/QuestionPool/QuestionNumber.data");
	string data;
	getline(infile, data); // get line
	this->questionID = atoi(data.c_str())+1;
	infile.close();

	//output new current number
	ofstream outfile;
	outfile.open("../public/QuestionPool/QuestionNumber.data", std::ios::out);
	outfile << this->questionID;
	outfile.close();
}
/// <summary>
/// add an answer to this question with the string of the answer, and if it should be selected or not.
/// </summary>
/// <param name="Answer"></param>
/// <param name="expected"></param>
/// <returns></returns>
bool question::addAnswer(std::string Answer, bool expected) {
	answer ans(Answer, expected, this->questionID);
	this->answers.push_back(ans);
	return true;
}
/// <summary>
/// remove an answer from this question with the string provided fails if aswer was never there
/// </summary>
/// <param name="Answer"></param>
/// <returns></returns>
bool question::deleteAnswer(std::string Answer) {
	int size = this->answers.size();
	for (int i = 0; i < size; i++) {
		if (this->answers.at(i).getAnswer() == Answer) {
			this->answers.erase(this->answers.begin() + i);
			return true;
		}
	}
	return false;
}
/// <summary>
/// Evaluates all the answers in this question and gives the value of points earned, ie 1/1 or 0.66/1
/// </summary>
/// <returns></returns>
float question::getPointsEarned() {
	int correctCount = 0;
	int size = this->answers.size();
	int possibleAnswers = 0;
	for (int i = 0; i < size; i++) {
		if (this->answers.at(i).getExpected() == true) {
			possibleAnswers++;
		}
		if (this->answers.at(i).isCorrect() == true) {
			correctCount++;
		}
	}
	return this->points * (correctCount / possibleAnswers);
}
/// <summary>
/// get if this question is multiple choice or multiple answer 0 for multiple choice and 1 for multiple answer
/// </summary>
/// <returns></returns>
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
/// <summary>
/// selects the answer provided
/// </summary>
/// <param name="Answer"></param>
/// <returns></returns>
bool question::selectAnswer(std::string Answer) {
	int size = this->answers.size();

	for (int i = 0; i < size; i++) {
		if (this->answers.at(i).getAnswer() == Answer) {
			return this->answers.at(i).select();
			
		}
	}
	return false;
}
/// <summary>
/// get a vector of all the answer titles in this question
/// </summary>
/// <returns></returns>
std::vector<std::string> question::getAnswers() {
	std::vector<std::string> answers;
	int size = this->answers.size();

	for (int i = 0; i < size; i++) {
		answers.push_back(this->answers.at(i).getAnswer());
	}
	return answers;
}
/// <summary>
/// Get the title of this question as a string
/// </summary>
/// <returns></returns>
std::string question::getQuestion() {
	return this->Question;
}
/// <summary>
/// get the expected result of an answer provided, ie should be checked or not
/// </summary>
/// <param name="option"></param>
/// <returns></returns>
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

/// <summary>
/// get the amount of points related to this question
/// </summary>
/// <returns></returns>
float question::getPoints()
{
	return this->points;
}
