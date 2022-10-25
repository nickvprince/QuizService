#include "QuestionPool.h"


	bool QuestionPool::save()
	{
		return false;
	}

	bool QuestionPool::load()
	{
		return false;
	}
	bool QuestionPool::addQuestion(std::string question, int type, float points) {


		return false;
	}
	bool QuestionPool::addOption(std::string question, std::string option) {


		return false;
	}
	bool QuestionPool::deleteOption(std::string question, std::string option) {


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
					this->questions[i].selectAnswer(option);
				}
			}
		}

		return true;
	}



