#define _CRT_SECURE_NO_WARNINGS
#include "./QuestionPool.h"


bool QuestionPool::save()
	{
		bool passed = false;
		ofstream outfile;
		FILE* file;
		if (file = fopen("a.txt", "r")) {
			fclose(file);
			return false;
		}
		outfile.open("../public/QuestionPool/pools/currentPools.pool", std::ios::app);
		outfile << this->ID << endl;
		outfile.close();

		outfile.open("../public/QuestionPool/pools/" +this->ID+".pool", std::ios::out);
		int size = this->questions.size();
		for(int i=0; i < size; i++) {
			outfile << "---Question Start---" << endl;
			outfile << this->questions.at(i).getQuestion()<<endl;
			outfile << this->questions.at(i).getQuestionID()<<endl;
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

bool QuestionPool::load()
	{
		return false;
	}
QuestionPool::QuestionPool(std::string poolName)
	{
		this->ID = poolName;
	}
bool QuestionPool::addQuestion(std::string Question, float points) {
		question q(Question, points);
		this->questions.push_back(q);
		return true;
	}
bool QuestionPool::addOption(std::string question, std::string option, bool expected) {
		for (int i = 0; i < this->questions.size(); i++) {
			if (this->questions[i].getQuestion() == question) {
				this->questions[i].addAnswer(option, expected);
				return true;
			}
		}
		return false;
	}
bool QuestionPool::deleteOption(std::string question, std::string option) {
		
		for (int i = 0; i < this->questions.size(); i++) {
			if (this->questions[i].getQuestion() == question) {
				this->questions[i].deleteAnswer(option);
				return true;
			}
		}

		return false;
	}
	std::vector<std::string> QuestionPool::getQuestions() {
		std::vector<std::string> names;
		for (int i = 0; i < this->questions.size(); i++) {
			names.push_back(this->questions[i].getQuestion());
		}
		return names;
	}
	std::vector<std::string> QuestionPool::getOptions(std::string question) {
		for (int i = 0; i < this->questions.size(); i++) {
			if (this->questions[i].getQuestion() == question) {
				return this->questions[i].getAnswers();
			}
		}
		std::vector<std::string> failed;
		return failed;
	}
bool QuestionPool::setAnswer(std::string question, std::string option, bool answer) {
		for (int i = 0; i < this->questions.size(); i++) {
			if (this->questions[i].getQuestion() == question) {
				if (this->questions[i].getExpected(option) == false) {
					return this->questions[i].selectAnswer(option);
					
				}
			}
		}

		return false;
	}



