#pragma once__
#include "QuestionPool.h"
#ifdef __linux__

/// <summary>
/// saves the question pool into the QuestionPool directory
/// </summary>
/// <returns></returns>
bool QuestionPool::save(int overWrite)
	{
	if (overWrite == 2)
	{
		Database db;
			
			string poolid = this->ID;

			db.executeQuery("INSERT INTO qp (poolid) VALUES ('"+poolid+"')");

			int size = this->questions.size();
			for (int i = 0; i < size; i++)
			{
				string question = this->questions.at(i).getQuestion();
				string questionid = to_string(this->questions.at(i).getQuestionID());
				string points = to_string(this->questions.at(i).getPoints());
				std::vector<std::string> options = this->questions.at(i).getAnswers();

				db.executeQuery("INSERT INTO question(idquestion, question, points, qp_poolid) VALUES ('"+questionid+"','"+question+"','"+points+"','"+poolid+"')");

				for (int b = 0; b < options.size(); b++)
				{
					string option = options.at(b);
					string answer = to_string(this->questions.at(i).getExpected(options.at(b)));

					db.executeQuery("INSERT INTO answer (answer, expected, selected, question_idquestion) VALUES ('" + option + "','" + answer + "','" + "0" + "','" + questionid + "')");
				}
			}




		return true;

	}


		bool passed = false;
		ofstream outfile;
		FILE* file;
#endif
#ifdef __linux__
		string tmp = "../public/QuestionPool/pools/" + this->ID + ".pool";
#endif
#ifdef _WIN32
		string tmp = "./QuizSharedDocker/public/QuestionPool/pools/" + this->ID + ".pool";
#endif
#ifdef __linux__
		if (file = fopen(tmp.c_str(), "r")) { // if file already exists return false
			fclose(file);
			if (overWrite == false) {
				return false;
			}
		}
		if (overWrite == false) {
			outfile.open("../public/QuestionPool/pools/currentPools.pool", std::ios::app); // append this pool title to the list of titles
			outfile << this->ID << endl;
			outfile.close();
		}
#endif
#ifdef _WIN32
		outfile.open("./QuizSharedDocker/public/QuestionPool/pools/" + this->ID + ".pool");
#endif
#ifdef __linux__
		outfile.open("../public/QuestionPool/pools/" +this->ID+".pool", std::ios::out); // write pool
#endif
#ifdef __linux__
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

	FILE* file;
	fstream outfile;
#endif
#ifdef __linux__
	string tmp = ("../public/QuestionPool/pools/" + (string)this->ID + ".pool").c_str();
#endif
#ifdef _WIN32
	string tmp = ("./QuizSharedDocker/public/QuestionPool/pools/" + this->ID + ".pool");
#endif
#ifdef __linux__
	if (file = fopen(tmp.c_str(), "r")) { // if doesnt exist return false
		fclose(file);
	}
	else {
		return false;
	}
#endif
#ifdef __linux__
	outfile.open(("../public/QuestionPool/pools/" + (string)this->ID + ".pool").c_str(), std::ios::in);
#endif
#ifdef _WIN32

	outfile.open(("./QuizSharedDocker/public/QuestionPool/pools/" + this->ID + ".pool").c_str(), std::ios::in);
#endif
#ifdef __linux__
	if (outfile.is_open()) {   //checking whether the file is open
		std::vector<answer> answers;
		std::string title;
		int id;
		float points=0;
		std::string answerID;
		int expected;
		string tp;
		int index = 0;
		while (!outfile.eof()) { //read data from file object and put it into string.
			getline(outfile, tp);
			if (tp[tp.size() - 1] != '\r') {
				tp += '\r';
			}

			int checkIndex;
#endif
#ifdef _WIN32
			checkIndex = 0;
#endif
#ifdef __linux__
			checkIndex = 13;
#endif
#ifdef __linux__
			if (strcmp(tp.c_str(), "---Question Start---") == checkIndex) {
				index = -1;
			}
			else if (strcmp(tp.c_str(), "---Question End---") == checkIndex) {
				index = 5;
				
			}
			switch (index) {
			case 0: // question title
				title = tp.c_str();
				break;
			case 1: //questionID
				id = atoi(tp.c_str());
				break;
			case 2: // points
				points = atof(tp.c_str());
				break;
			case 3: // answer
				answerID = tp.c_str();
				break;
			case 4: { // selected or not || add answer to answers vector
				index -= 2; // set next index to another answer
				expected = atoi(tp.c_str());
				answer ans(answerID, expected, id);
				answers.push_back(ans);
				break;
			}
			case 5: {// end question so add it
				question q(title, points);
				while (!answers.empty()) {
					q.addAnswer(answers.at(answers.size() - 1).getAnswer(), answers.at(answers.size() - 1).getExpected());
					answers.pop_back();
				}
				this->questions.push_back(q);
			
				break;
			}
			default:
				break;
			}
			index++;
		}
	}
	else {
		return false;
	}
	outfile.close();
	if (this->questions.size() == 0) {
		return false;
	}
		return true;
	}

	bool QuestionPool::loadFromDb()
	{
		Database db;
		std::vector<answer> answers;
		std::string title;
		float points = 0;
		std::string Answer;
		int expected;
		std::string idquestion;
		bool exp = false;

		
		sql::ResultSet* dbRes = db.executeQuery("SELECT * FROM question where qp_poolid = '" + this->ID + "';");

		while (dbRes->next())
		{
			title = dbRes->getString("question");
			points = stof(dbRes->getString("points"));

			question q(title, points);

			idquestion = dbRes->getString("idquestion");

			sql::ResultSet* dbRes2 = db.executeQuery("SELECT * FROM answer where question_idquestion = '" + idquestion + "';");
			while (dbRes2->next())
			{
				Answer = dbRes2->getString("answer");
				expected = stoi(dbRes2->getString("expected"));
				
				if (expected == 1)
				{
					exp = true;
				}

				answer ans(Answer, exp, stoi(idquestion));

				answers.push_back(ans);	
			}
			while (!answers.empty())
			{
				q.addAnswer(answers.at(answers.size() - 1).getAnswer(), answers.at(answers.size() - 1).getExpected());
				answers.pop_back();
			}

			this->questions.push_back(q);

		}
		if (questions.size() == 0)
		{
			return false;
		}
		return true;
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
bool QuestionPool::getExpected(std::string question, std::string answer)
{
	for (int i = 0; i < this->questions.size(); i++) {
		if (strcmp(this->questions.at(i).getQuestion().c_str(), question.c_str()) == 0) {
			return this->questions.at(i).getExpected(answer);
		}
	}
	throw "ERROR";
	return false;
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


#endif