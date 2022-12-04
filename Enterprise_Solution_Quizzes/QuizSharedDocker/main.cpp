#include <iostream>
using namespace std;

#ifdef _WIN32
#include "./objects/QuestionPool.h"
#include "./objects/Logger.h"
#endif


//#define __linux__
#ifdef __linux__
#define CROW_MAIN
#include <bits/stdc++.h> 
#include "crow_all.h"
#include "./objects/json.hpp"
//#include "./objects/QuestionPool.cpp"
#include "objects/Quiz.cpp"
#include "objects/JsonDTO.cpp"
#include <vector>
#include <fstream>
#include <sstream>
using namespace crow;
int passFail = 0;
std::string mode = "";
std::string timeout = "0";
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
		Logger::log("Error - 404 not found", 2, "Errors");
		res.write("404 Not Found");

	}

	//if (filename == "json/pools.json"){
	//	sendHtml(res, "createQuiz.html");
	//}

	res.end();

}

void sendScript(response& res, string filename) {
	Logger::log(("Sending " + filename), 0, "routeLogs");
	sendFile(res, "scripts/" + filename, "text/script");
}

void sendStyle(response& res, string filename) {
	Logger::log(("Sending " + filename), 0, "routeLogs");
	sendFile(res, "styles/" + filename, "text/css");
}

void sendImage(response& res, string filename) {

	if (filename.find(".jpeg") != string::npos) {
		Logger::log(("Sending " + filename), 0, "routeLogs");
		sendFile(res, "images/" + filename, "image/jpeg");
	}
	else {
		Logger::log(("Sending " + filename), 0, "routeLogs");
		sendFile(res, "images/" + filename, "image/png");
	}
}

void sendQuizText(response& res, string filename) {
	Logger::log(("Sending " + filename), 0, "routeLogs");
	sendFile(res, "quizzes/" + filename, "text/plain");
}

	
void sendPool(response& res, string filename) {
	Logger::log(("Sending " + filename), 0, "routeLogs");
	ifstream file;
	file.open("../public/QuestionPool/"+filename);
	if (!file.is_open())
	{
		res.code = 500;
		Logger::log("ERROR - 500 available pools file error", 0, "Errors");
		res.write("Available pools File Error");
		}

	string line;
	while (getline(file, line))
	{
		string output = "Question Pool :" + line +"\n";
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

void sendJson(response& res, string filename){
	Logger::log(("Sending JSON "+filename), 0, "routeLogs");
	sendFile(res, "json/" + filename, "application/json");
}

void sendJsonArray(response& res, nlohmann::json text) {
	res.set_header("Content-Type", "application/json");
	Logger::log(("Sending " +to_string(text)), 0, "routeLogs");
	res.write(to_string(text));
	res.end();
}
	

void sendHtml(response& res, string filename) {
	Logger::log(("Sending "+filename), 0, "routeLogs");
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

std::cout <<"Hello world! -- This is not a windows project!";

#endif // _WIN32

#ifdef __linux__
Logger::log("STARTUP", -1, "startLogs");
	crow::SimpleApp app;
	// Default Route
	CROW_ROUTE(app, "/")
		([](const request& req, response& res) {
		Logger::log("Getting Mode", 0, "routeLogs");
		sendHtml(res, "getMode.html");
	});


	CROW_ROUTE(app, "/setMode/<string>")
		([](const request& req, response& res, std::string modeIn) {
		Logger::log("Setting Mode"+modeIn, 0, "routeLogs");
		if (modeIn == "na") {
			timeout ="1";
		}
		mode = modeIn;
		res.end();
			});

	CROW_ROUTE(app, "/timeout")
		([](const request& req, response& res) {
		Logger::log("getting timeout", 0, "routeLogs");
		res.write(timeout);
		res.end();
			});
	CROW_ROUTE(app, "/getMode")
		([](const request& req, response& res) {
		Logger::log("getting Mode" + mode, 0, "routeLogs");
		res.write(mode);
		res.end();
			});

	CROW_ROUTE(app, "/switch")
		([](const request& req, response& res) {
		Logger::log("Switching Mode", 0, "routeLogs");
		if (mode == "prof") {
			mode = "stud";
			sendHtml(res, "studentIndex.html");
		}
		else if (mode == "stud") {
			mode = "prof";
			sendHtml(res, "index.html");
		}
		
		sendHtml(res, "00.html");
			});

	/// <summary>
	/// view quiz get request to get the data for a quiz
	/// </summary>
	/// <returns></returns>
	CROW_ROUTE(app, "/viewQuiz.html").methods(crow::HTTPMethod::GET) //-----------
		([](const request& req, response& res) {
		auto quizID = req.url_params.get("quizID");
		ostringstream quizIDString;

		quizIDString << quizID ? quizID : "";

		if (quizIDString.str() != "") {
			updateQuizPoolJson(quizIDString.str());
			sendHtml(res,"quizViewer.html");//passed
		}
		sendHtml(res, "viewQuiz.html"); // failed
			});

	/// <summary>
	/// Used to log errors using javascript
	/// </summary>
	/// <returns></returns>
	CROW_ROUTE(app, "/log/<string>/<int>").methods(crow::HTTPMethod::POST)
		([](const request& req, response& res, std::string log, int severity) {
		std::string output = std::string(log);
		Logger::log(output, severity, "webLogs");
		res.end();
			});
	/// <summary>
	/// used as a route to see if success or failure
	/// </summary>
	/// <returns></returns>
	CROW_ROUTE(app, "/succeeded").methods(crow::HTTPMethod::GET)
		([](const request& req, response& res) {

		if (passFail == 0) {
			res.write("Pool Deletion Failed");
			Logger::log("Pool Deletion Failed Sent", 1, "routeLogs");
		}
		else if (passFail == 1) {
			res.write("pool Deletion Successful");
			Logger::log("Pool deleted successfully Sent", 0, "routeLogs");
		}
		else {
			res.write("Error 500 : Unknown Error");
			Logger::log("Variable Succeeded not set to 0 or 1", 2, "Errors");
		}

		res.end();
			});


	/// <summary>
	/// submit a quiz to the gradebook
	/// </summary>
	/// <returns></returns>
	CROW_ROUTE(app, "/submitQuiz").methods(crow::HTTPMethod::GET)
		([](const request& req, response& res) {


		std::string poolname = req.url_params.get("pool");
		QuestionPool pool(poolname);
		pool.loadFromDb();
		pool.print();
		/********************************
		*** Pool data start *************
		*********************************/
		QuestionPool q(poolname);
		int countFrom = 100; // max questions
		std::vector<char*> questions = req.url_params.get_list("Questions");
		for (int i = 0; i < questions.size(); i++) {

			q.addQuestion(questions.at(i), 1); // add question to pool

			std::vector<char*> answers = req.url_params.get_list("Q" + to_string(countFrom) + "A"); // options for question || alter this |	Start at 100 work backwards if size is zero assume no answers and move on until answers are found work until 0 ( note 100 max questions and speed hinge {fix later})

			while (answers.size() == 0) {
				countFrom--;
				answers = req.url_params.get_list("Q" + to_string(countFrom) + "A");

			}
			//std::cout << "Answers : Q" << countFrom << "A\n";
			countFrom--;
			std::vector<char*> selected = req.url_params.get_list("Checked" + to_string(countFrom + 1)); // selected for question || alter this
			//std::cout << "Selected : Checked" << (countFrom + 1) << "\n";

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

		/********************************
		*** Pool data end *************
		*********************************/
		
		// q = students answers pool && pool = fromDB ie:/ pool is what the answers are supposed to be and q is what the student selected -- under expected instead of selected
		std::vector<std::string> questions2 = q.getQuestions();

		float availablePoints = questions2.size();
		float totalPoints = 0;
		for (int i = 0; i < questions2.size(); i++) {
			float correctOptions = 0;
			float correctSelected = 0;
			std::vector<std::string> options2 = q.getOptions(questions2.at(i));

			for (int b = 0; b < options2.size(); b++) {

				bool studentAnswer = q.getExpected(questions2.at(i), options2.at(b));

				bool Answer = pool.getExpected(questions2.at(i), options2.at(b));

				if (Answer == true) {

					correctOptions++;
				}
				if (studentAnswer==true&& Answer == true) {

					correctSelected++;
				}
			}// for all options

			if (correctSelected == 0 || correctOptions == 0) {

			}
			else {
				totalPoints += float(correctSelected / correctOptions);
			}
			//std::cout << "Print float attempt : " << atof(correctSelected / correctOptions);
		}
		q.print();
		std::cout << "\n" << "Points Earned : " << totalPoints << "\t" << "TotalPoints : " << availablePoints << "\n";
		res.write(to_string(totalPoints));
		res.end();
	});


	/// <summary>
	/// used to delete pools from the filesystem
	/// </summary>
	/// <returns></returns>
	CROW_ROUTE(app, "/deletePool/<string>").methods(crow::HTTPMethod::POST)
		([](const request& req, response& res, string poolname) {

		QuestionPool pool(poolname);
		if (pool.deletePool(pool.getID()) == false) {
			passFail = 0;
			Logger::log("Pool deletion failed", 1, "Errors");
		}
		else {
			passFail = 1;
		}
		Logger::log("Sending Question Pool.html", 0, "routeLogs");
		sendHtml(res, "questionPool.html");
			});


	CROW_ROUTE(app, "/getPool/<string>")
		([](const request& req, response& res, string poolname) {
		Database db;
		sql::ResultSet* dbRes2 = db.executeQuery("SELECT * from qp where poolid = '" + poolname + "';");
		int count = 0;

		while (dbRes2->next()) {
			count++;
		}
		if (count <= 0) {
			sendHtml(res, "index.html");
		}

		QuestionPool pool(poolname);
		pool.loadFromDb(); // load pool
		std::vector<std::string> questions = pool.getQuestions();
		
	
		std::ofstream jsonFile;
		jsonFile.open("../public/json/tmpPoolData.json");//fill temp file
		if (jsonFile.is_open()) {
			std::string str;
			jsonFile << "{\n";
			std::vector<std::string> questions = pool.getQuestions();
			for (int i = 0; i < questions.size(); i++) {
				std::vector<std::string> answers = pool.getOptions(questions.at(i));
				std::string tmp = questions.at(i);
			
				jsonFile << '"' + tmp + '"' + ": {\n"; // write question

				for (int b = 0; b < answers.size(); b++) {
					string str = "";
					if (b == answers.size() - 1) {
						std::string tmp2 = answers.at(b);
						
						str = '"' + tmp2 + '"' + ": " + '"' + boolToString(pool.getExpected(questions.at(i), answers.at(b))) + "" + '"' + "\n";
					}
					else {
						std::string tmp2 = answers.at(b);

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
	CROW_ROUTE(app, "/savepool").methods(crow::HTTPMethod::GET)
		([](const request& req, response& res) {
		auto isOverwrite = req.url_params.get("type");
		ostringstream isOverwriteString;
		isOverwriteString << isOverwrite ? isOverwrite : "";
		string overWrite = "2";
		std::string poolname = req.url_params.get("pool");
		QuestionPool q(poolname);
		int countFrom = 100; // max questions
		std::vector<char*> questions = req.url_params.get_list("Questions");
		for (int i = 0; i <questions.size(); i++) {
			
			q.addQuestion(questions.at(i), 1); // add question to pool

			std::vector<char*> answers = req.url_params.get_list("Q" + to_string(countFrom) + "A"); // options for question || alter this |	Start at 100 work backwards if size is zero assume no answers and move on until answers are found work until 0 ( note 100 max questions and speed hinge {fix later})

			while (answers.size() == 0) {
				countFrom--;
				answers = req.url_params.get_list("Q" + to_string(countFrom) + "A");
			}
			countFrom--;
			std::vector<char*> selected = req.url_params.get_list("Checked" + to_string(countFrom+1)); // selected for question || alter this
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
			result = q.save(2);
			
		}
		else {
			result = q.save(0);
		}

		overWrite = "";

		if (result == true && overWrite != "") {
			updateQuizPoolJson();
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

		updateQuizJson();
		updateQuizPoolJson();

		//createQuiz Query
		if (filename == "createQuiz.html" || filename == "selectQuiz.html" || filename == "editQuiz.html") {

			if (filename == "createQuiz.html") {
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
			} else if (filename == "editQuiz.html") {
				auto quizID = req.url_params.get("quizID");
				auto quizTitle = req.url_params.get("quizTitle");
				auto quizDuration = req.url_params.get("quizDuration");
				auto quizPool = req.url_params.get("quizPool");
				auto quizStartDate = req.url_params.get("quizStartDate");
				auto quizEndDate = req.url_params.get("quizEndDate");

				ostringstream quizIDString, quizTitleString, quizDurationString, quizPoolString,
					quizStartDateString, quizEndDateString;

				quizIDString << quizID ? quizID : "";
				quizTitleString << quizTitle ? quizTitle : "";
				quizDurationString << quizDuration ? quizDuration : "";
				quizPoolString << quizPool ? quizPool : "";
				quizStartDateString << quizStartDate ? quizStartDate : "";
				quizEndDateString << quizEndDate ? quizEndDate : "";

				if ((quizIDString.str() != "" && quizTitleString.str() != "" && quizDurationString.str() != "" &&
					quizPoolString.str() != "" && quizStartDateString.str() != "" && quizEndDateString.str() != "" && quizPoolString.str() != "")) {
					Quiz currentQuiz(stoi(quizIDString.str()), quizTitleString.str(), quizStartDateString.str(), quizEndDateString.str(), stoi(quizDurationString.str()), quizPoolString.str());
					cout << "----------------------------I got here\n\n";
					currentQuiz.updateQuiz();
					std::cout << currentQuiz.getTitle() << "-------------" << std::endl; // for testing

					updateQuizJson();
					updateQuizPoolJson(quizIDString.str());

					filename = "selectQuiz.html";
				}
			} else if (filename == "selectQuiz.html") {

				auto quizID = req.url_params.get("quizID");
				ostringstream quizIDString;

				quizIDString << quizID ? quizID : "";

				if(quizIDString.str() != ""){
					updateQuizPoolJson(quizIDString.str());
					
					filename = "editQuiz.html";
				}
			}
		} else if(filename == "deleteQuiz.html") {

			auto quizID = req.url_params.get("quizID");
	
			ostringstream quizIDString;

			quizIDString << quizID ? quizID : "";
			
			if (quizIDString.str() != "") {
				Quiz currentQuiz(stoi(quizIDString.str()));
				currentQuiz.deleteQuiz();
				filename = "quizLandingPage.html";
			}

		} else if(filename == "takeQuiz.html"){
			auto quizID = req.url_params.get("quizID");
			ostringstream quizIDString;

			quizIDString << quizID ? quizID : "";
			
			if (quizIDString.str() != "") {
			
				updateQuizPoolJson(quizIDString.str());
				//updateQuizQuestionList(quizIDString.str());
			}
			else {
				sendHtml(res, "studentIndex.html");
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
		updateQuizPoolJson();
		sendPool(res, folder+"/"+name);
	});

	CROW_ROUTE(app, "/json/<string>")
	([](const request& req, response& res, string filename) {
		sendJson(res, filename);
	});
	
	//service port
	app.port(8080).multithreaded().run();
	Logger::log("SHUTDOWN", -1, "startLogs");
	return 1;

#endif //__linux__

}