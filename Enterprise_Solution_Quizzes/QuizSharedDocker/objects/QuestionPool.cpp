#define _CRT_SECURE_NO_WARNINGS
#include "./QuestionPool.h"

/// <summary>
/// saves the question pool into the QuestionPool directory
/// </summary>
/// <returns></returns>
bool QuestionPool::save()
	{
		bool passed = false;
		ofstream outfile;
		FILE* file;
		string tmp = "../public/QuestionPool/pools/" + this->ID + ".pool";
		if (file = fopen(tmp.c_str(), "r")) { // if file already exists return false
			fclose(file);
			return false;
		}
		outfile.open("../public/QuestionPool/pools/currentPools.pool", std::ios::app); // append this pool title to the list of titles
		outfile << this->ID << endl;
		outfile.close();

		outfile.open("../public/QuestionPool/pools/" +this->ID+".pool", std::ios::out); // write pool
		int size = this->questions.size();
		for(int i=0; i < size; i++) {
			outfile << "---Question Start---" << endl;
			outfile << this->questions.at(i).getQuestion()<<endl;
			outfile << this->questions.at(i).getQuestionID()<<endl;
			outfile << this->questions.at(i).getPoints() << endl;
			std::vector<std::string> options = this->questions.at(i).getAnswers();
			for (int b = 0; b < options.size(); b++) {
				outfile << options.at(b) <<endl;
				outfile << this->questions.at(i).getExpected(options.at(b))<<endl;
			}
			outfile << "---Question End---"<<endl;
			passed = true;
		}
		outfile.close();
		return passed;
	}

/// <summary>
/// load data from file into this object
/// </summary>
/// <returns></returns>
bool QuestionPool::load()
	{
		return false;
	}
/// <summary>
/// gets the current pool name
/// </summary>
/// <returns></returns>
std::string QuestionPool::getID()
{
	return this->ID;
}

/// <summary>
/// initialize a pool with the name provided
/// </summary>
/// <param name="poolName"></param>
QuestionPool::QuestionPool(std::string poolName)
	{
		this->ID = poolName;
	}
/// <summary>
/// Add a question to this question pool and allocate points to it
/// </summary>
/// <param name="Question"></param>
/// <param name="points"></param>
/// <returns></returns>
bool QuestionPool::addQuestion(std::string Question, float points) {
		question q(Question, points);
		this->questions.push_back(q);
		return true;
	}
/// <summary>
/// add an option to the question provided and the expected answer to go with it
/// </summary>
/// <param name="question"></param>
/// <param name="option"></param>
/// <param name="expected"></param>
/// <returns></returns>
bool QuestionPool::addOption(std::string question, std::string option, bool expected) {
		for (int i = 0; i < this->questions.size(); i++) {
			if (this->questions[i].getQuestion() == question) {
				this->questions[i].addAnswer(option, expected);
				return true;
			}
		}
		return false;
	}
/// <summary>
/// remove option from the question provided.
/// </summary>
/// <param name="question"></param>
/// <param name="option"></param>
/// <returns></returns>
bool QuestionPool::deleteOption(std::string question, std::string option) {
		
		for (int i = 0; i < this->questions.size(); i++) {
			if (this->questions[i].getQuestion() == question) {
				this->questions[i].deleteAnswer(option);
				return true;
			}
		}

		return false;
	}
	/// <summary>
	/// get a vector of all the questions in this question pool
	/// </summary>
	/// <returns></returns>
	std::vector<std::string> QuestionPool::getQuestions() {
		std::vector<std::string> names;
		for (int i = 0; i < this->questions.size(); i++) {
			names.push_back(this->questions[i].getQuestion());
		}
		return names;
	}
	/// <summary>
	/// get all the options of a given question as a vector
	/// </summary>
	/// <param name="question"></param>
	/// <returns></returns>
	std::vector<std::string> QuestionPool::getOptions(std::string question) {
		for (int i = 0; i < this->questions.size(); i++) {
			if (this->questions[i].getQuestion() == question) {
				return this->questions[i].getAnswers();
			}
		}
		std::vector<std::string> failed;
		return failed;
	}
/// <summary>
/// set the expected checked or not of the option to the inputted answer
/// </summary>
/// <param name="question"></param>
/// <param name="option"></param>
/// <param name="answer"></param>
/// <returns></returns>
bool QuestionPool::setAnswer(std::string question, std::string option, bool answer) {
		for (int i = 0; i < this->questions.size(); i++) {
			if (this->questions[i].getQuestion() == question) {
				if (this->questions[i].getExpected(option) == answer) {
					return true;
				}
				else if (this->questions[i].getExpected(option) != answer) {
					return this->questions[i].setExpected(answer,option);

				}
			}
		}

		return false;
	}



