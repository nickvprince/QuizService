#include <iostream>
using namespace std;

#ifdef _WIN32
#include "./objects/QuestionPool.h"
#include "./objects/json.hpp"
#endif


//#define __linux__
#ifdef __linux__
#define CROW_MAIN
#include <bits/stdc++.h> 
#include "crow_all.h"
#include "./objects/json.hpp"
#include "./objects/QuestionPool.cpp"
#include "objects/Quiz.cpp"
#include <vector>
#include <fstream>
#include <sstream>
using namespace crow;

void sendFile(response& res, string filename, string contentType);
void sendScript(response& res, string filename);
void sendStyle(response& res, string filename);
void sendImage(response& res, string filename);
void sendHtml(response& res, string filename);

void sendFile(response& res, string filename, string contentType) {

	// Create the full file path
	string root = "../public/";
	string filepath = root.append(filename);

	// On each send, we output the filename to console, (troubleshooting purposes)
	cout << endl << "FILEPATH: " << filepath << endl;

	// Read the input file 
	ifstream input(filepath, ifstream::in);

	if (input) {

		ostringstream contents;
		contents << input.rdbuf();
		input.close();

		// Set the type of content so crow knows what it's reading
		res.set_header("Content-Type", contentType);
		res.write(contents.str());

	}
	else {

		// Set the proper error code and write the message to the browser when there is an error
		res.code = 404;
		res.write("404 Not Found");

	}

	//if (filename == "json/pools.json"){
	//	sendHtml(res, "createQuiz.html");
	//}

	res.end();

}

void sendScript(response& res, string filename) {
	sendFile(res, "scripts/" + filename, "text/script");
}

void sendStyle(response& res, string filename) {
	sendFile(res, "styles/" + filename, "text/css");
}

void sendImage(response& res, string filename) {

	if (filename.find(".jpeg") != string::npos) {
		sendFile(res, "images/" + filename, "image/jpeg");
	}
	else {
		sendFile(res, "images/" + filename, "image/png");
	}
}

void sendQuizText(response& res, string filename) {
	sendFile(res, "quizzes/" + filename, "text/plain");
}


void sendPool(response& res, string filename) {
	std::cout << "SENDPOOL" << " QuestionPool/" + filename;
	ifstream file;
	file.open("../public/QuestionPool/" + filename);
	if (!file.is_open())
	{
		res.code = 500;
		res.write("Available pools File Error");
	}

	string line;
	while (getline(file, line))
	{
		string output = "Question Pool :" + line + "\n";
		res.write(output);
	}
	file.close();
	res.set_header("Content-Type", "text/plain");
	// Create the full file path
	string root = "../public/";
	string filepath = root.append(filename);

	// On each send, we output the filename to console, (troubleshooting purposes)
	cout << endl << "FILEPATH: " << filepath << endl;
	res.end();
}

void sendJson(response& res, string filename) {
	sendFile(res, "json/" + filename, "application/json");
}

void sendJsonArray(response& res, nlohmann::json text) {
	res.set_header("Content-Type", "application/json");
	res.write(to_string(text));
	res.end();
}


void sendHtml(response& res, string filename) {
	sendFile(res, filename, "text/html");
}


#endif //__linux__
string boolToString(bool input) {
	if (input == 1) {
		return "true";
	}
	else if (input == 0) {
		return "false";
	}
	else {
		return NULL;
	}
}

int main() {


#ifdef _WIN32

	//std::cout <<"Hello world! -- This is not a windows project!";
	std::ofstream jsonFile;
	
	QuestionPool pool = QuestionPool("pool1");
	pool.addQuestion("Hello", 1);
	pool.addOption("Hello", "One", 0);
	pool.addOption("Hello", "Two", 1);
	pool.addOption("Hello", "Three", 0);
	pool.addQuestion("Goodbye", 1);
	pool.addOption("Goodbye", "One", 0);
	pool.addOption("Goodbye", "Two", 1);
	pool.addOption("Goodbye", "Three", 1);
	jsonFile.open("./QuizSharedDocker/public/json/tmpPoolData.json");
	if (jsonFile.is_open()) {
		std::string str;
		jsonFile << "{\n";
		std::vector<std::string> questions = pool.getQuestions();
		for (int i = 0; i < questions.size(); i++) {
			std::vector<std::string> answers = pool.getOptions(questions.at(i));
			jsonFile << '"' + questions.at(i) + '"' + ": {\n"; // write question

			for (int b = 0; b < answers.size(); b++) {
				string str = "";
				if (b == answers.size() - 1) {
					str = '"' + answers.at(b) + '"' + ": " + '"' + boolToString(pool.getExpected(questions.at(i), answers.at(b))) + "" + '"' + "\n";
				}
				else {
					str = '"' + answers.at(b) + '"' + ": " + '"' + boolToString(pool.getExpected(questions.at(i), answers.at(b))) + "" + '"' + ", \n";
				}
				jsonFile << str;

			}
			if (i == questions.size() - 1) {
				jsonFile << "}\n";
			}
			else {
				jsonFile << "},\n";
			}
		}
		jsonFile << "}";
		jsonFile.close();
	}

#endif // _WIN32

#ifdef __linux__
	crow::SimpleApp app;
	// Default Route
	CROW_ROUTE(app, "/")
		([](const request& req, response& res) {
		sendHtml(res, "index.html");
			});
	CROW_ROUTE(app, "/getPool/<string>")
		([](const request& req, response& res, string poolname) {
		QuestionPool pool(poolname);
		pool.load(); // load pool
		std::ofstream jsonFile;
		jsonFile.open("../public/json/tmpPoolData.json");//fill temp file
		if (jsonFile.is_open()) {
			std::string str;
			jsonFile << "{\n";
			std::vector<std::string> questions = pool.getQuestions();
			for (int i = 0; i < questions.size(); i++) {
				std::vector<std::string> answers = pool.getOptions(questions.at(i));
				std::string tmp = questions.at(i);
				tmp.pop_back();
				jsonFile << '"' + tmp + '"' + ": {\n"; // write question

				for (int b = 0; b < answers.size(); b++) {
					string str = "";
					if (b == answers.size() - 1) {
						std::string tmp2 = answers.at(b);
						tmp2.pop_back();
						str = '"' + tmp2 + '"' + ": " + '"' + boolToString(pool.getExpected(questions.at(i), answers.at(b))) + "" + '"' + "\n";
					}
					else {
						std::string tmp2 = answers.at(b);
						tmp2.pop_back();
						str = '"' + tmp2 + '"' + ": " + '"' + boolToString(pool.getExpected(questions.at(i), answers.at(b))) + "" + '"' + ", \n";
					}
					jsonFile << str;

				}
				if (i == questions.size() - 1) {
					jsonFile << "}\n";
				}
				else {
					jsonFile << "},\n";
				}
			}
			jsonFile << "}";
			jsonFile.close();
		}
		sendJson(res, "../json/tmpPoolData.json");
			});

	/// <summary>
	/// Savepool is called from questionPool.html. This function saves a question pool objects to file and returns to questionPool page with either a pass or fail query string
	/// </summary>
	/// <returns></returns>
	CROW_ROUTE(app, "/savepool")
		([](const request& req, response& res) {
		auto isOverwrite = req.url_params.get("type");
		ostringstream isOverwriteString;
		isOverwriteString << isOverwrite ? isOverwrite : "";
		string overWrite = isOverwriteString.str();
		std::string poolname = req.url_params.get("pool");
		QuestionPool q(poolname);
		std::vector<char*> questions = req.url_params.get_list("Questions");
		for (int i = questions.size()-1; i >-1; i--) {
			q.addQuestion(questions.at(i), 1); // add question to pool
			std::vector<char*> answers = req.url_params.get_list("Q" + to_string(questions.size() - 1 - i) + "A"); // options for question
			std::vector<char*> selected = req.url_params.get_list("Checked" + to_string(questions.size() - 1 - i)); // selected for question
			for (int b = 0; b < answers.size(); b++) { // add all options to question
				bool selectTrueFalse = false;
				for (int c = 0; c < selected.size(); c++) { // check if this option is selected or not
					if (strcmp(answers.at(b), selected.at(c)) == 0) { // if match found
						selectTrueFalse = true;
					}
				}
				if (selectTrueFalse == true) { // if this answer is supposed to be true add question with expected true
					q.addOption(questions.at(i), answers.at(b), 1);
				}
				else {
					q.addOption(questions.at(i), answers.at(b), 0); // else add answer with expected false
				}
				selectTrueFalse = false;
			}
		}
		bool result;
		if (overWrite != "") {
			result = q.save(1);

		}
		else {
			result = q.save(0);
		}
		if (result == true && overWrite != "") {

			sendHtml(res, "selectPool.html");
		}
		else if (result == true) {
			sendHtml(res, "savepoolPass.html");
		}
		else {
			sendHtml(res, "savepoolFail.html");
		}

			});

	// Calling html from products pages
	CROW_ROUTE(app, "/<string>")
		([](const request& req, response& res, string filename) {
		//createQuiz Query
		if (filename == "createQuiz.html") {

			Database db;

			sql::ResultSet* dbRes = db.executeQuery("SELECT * FROM qp;");
			nlohmann::json jArray = nlohmann::json::array();

			int i = 0;
			while (dbRes->next()) {
				jArray[i] = dbRes->getString("poolid");
				i++;
			}

			//std::cout << "Pool: " << jArray << std::endl;

			std::ofstream jsonFile;
			jsonFile.open("../public/json/pools.json");
			if (jsonFile.is_open()) {

				std::string str = jArray.dump().replace(0, 1, "[");
				str.replace(jArray.dump().length() - 1, jArray.dump().length(), "]");
				jsonFile << "{'pools': " << jArray.dump() << "}\r\n";

			}
			else {
				std::cout << "Failed to write question pools to json file" << std::endl;
			}

			jsonFile.close();

			auto quizTitle = req.url_params.get("quizTitle");
			auto quizDuration = req.url_params.get("quizDuration");
			auto quizPool = req.url_params.get("quizPool");
			auto quizStartDate = req.url_params.get("quizStartDate");
			auto quizEndDate = req.url_params.get("quizEndDate");

			ostringstream quizTitleString, quizDurationString, quizPoolString,
				quizStartDateString, quizEndDateString;

			quizTitleString << quizTitle ? quizTitle : "";
			quizDurationString << quizDuration ? quizDuration : "";
			quizPoolString << quizPool ? quizPool : "";
			quizStartDateString << quizStartDate ? quizStartDate : "";
			quizEndDateString << quizEndDate ? quizEndDate : "";

			if ((quizTitleString.str() != "" && quizDurationString.str() != "" &&
				quizPoolString.str() != "" && quizStartDateString.str() != "" && quizEndDateString.str() != "" && quizPoolString.str() != "")) {
				Quiz currentQuiz(quizTitleString.str(), quizStartDateString.str(), quizEndDateString.str(), stoi(quizDurationString.str()), quizPoolString.str());
				currentQuiz.saveQuiz();
				std::cout << currentQuiz.getTitle() << "-------------" << std::endl; // for testing
				filename = "quizLandingPage.html";
			}

		}
		else if (filename == "deleteQuiz.html") {

			Database db;

			sql::ResultSet* dbRes = db.executeQuery("SELECT * FROM quiz;");

			std::ofstream jsonFile;
			jsonFile.open("../public/json/quizzes.json");
			if (jsonFile.is_open()) {

				std::string str;

				while (dbRes->next()) {
					str += "'" + dbRes->getString("idquiz") + "': {\n";
					str += "'title': '" + dbRes->getString("title") + "'\n},\n";
				}

				str.replace(str.length() - 2, str.length(), "\n");

				jsonFile << "{\n" << str << "}";

			}
			else {
				std::cout << "Failed to write quizzez to json file" << std::endl;
			}

			jsonFile.close();

			auto quizID = req.url_params.get("quizID");

			ostringstream quizIDString;

			quizIDString << quizID ? quizID : "";

			if (quizIDString.str() != "") {
				Quiz currentQuiz(stoi(quizIDString.str()));
				currentQuiz.deleteQuiz();
				filename = "quizLandingPage.html";
			}

		}

		sendHtml(res, filename);

			});

	CROW_ROUTE(app, "/scripts/<string>")
		([](const request& req, response& res, string filename) {
		sendScript(res, filename);
			});

	CROW_ROUTE(app, "/styles/<string>")
		([](const request& req, response& res, string filename) {
		sendStyle(res, filename);
			});

	// Images in parent images folder
	CROW_ROUTE(app, "/images/<string>")
		([](const request& req, response& res, string filename) {
		sendImage(res, filename);
			});

	CROW_ROUTE(app, "/quizzes/<string>")
		([](const request& req, response& res, string filename) {
		sendQuizText(res, filename);
			});

	/// <summary>
	/// gets the text file of all the question pools
	/// </summary>
	/// <returns></returns>
	CROW_ROUTE(app, "/QuestionPool/<string>/<string>")
		([](const request& req, response& res, string folder, string name) {
		sendPool(res, folder + "/" + name);
			});

	CROW_ROUTE(app, "/json/<string>")
		([](const request& req, response& res, string filename) {
		sendJson(res, filename);
			});

	//service port
	app.port(27501).multithreaded().run();
	return 1;

#endif //__linux__

}
