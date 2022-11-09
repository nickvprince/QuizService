#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//#define __linux__
#ifdef __linux__

#define CROW_MAIN

#include "crow_all.h"
#include "objects/Quiz.cpp"

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

	if ( input ) {

		ostringstream contents;
		contents << input.rdbuf();
		input.close();

		// Set the type of content so crow knows what it's reading
		res.set_header("Content-Type", contentType);
		res.write(contents.str());

	} else {

		// Set the proper error code and write the message to the browser when there is an error
		res.code = 404;
		res.write("404 Not Found");

	}

	res.end();

}

void sendScript(response& res, string filename) {
	sendFile(res, "scripts/" + filename, "text/script");
}

void sendStyle(response& res, string filename) {
	sendFile(res, "styles/" + filename, "text/css");
}

void sendImage(response& res, string filename) {

	if ( filename.find(".jpeg") != string::npos ) {
		sendFile(res, "images/" + filename, "image/jpeg");
	} else {
		sendFile(res, "images/" + filename, "image/png");
	}
}

void sendQuizText(response& res, string filename) {
	sendFile(res, "quizzes/" + filename, "text/plain");
}

void sendJson(response& res, string filename){
	sendFile(res, "json/" + filename, "application/json");
}

void sendHtml(response& res, string filename) {
	sendFile(res, filename, "text/html");
}


#endif //__linux__

#ifdef __linux__
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
using namespace sql;
#endif


int main() {

#ifdef __linux__
    sql::Driver *myDriver;
    sql::Connection *myConn;
    sql::Statement *myStmt;
    sql::ResultSet  *myRes;

    sql::ConnectOptionsMap options;
    options["CLIENT_MULTI_STATEMENTS"] = true;

    myDriver = get_driver_instance();
    myConn = myDriver->connect("tcp://192.168.0.246", "root", "admin");
    myConn->setSchema("QuizSQL");

    try {

        myStmt = myConn->createStatement();
        myRes = myStmt->executeQuery("CREATE TABLE Persons (PersonID int,LastName varchar(255),FirstName varchar(255),Address varchar(255),City varchar(255));");
        delete myRes;
        delete myStmt;
        delete myConn;
    } catch (sql::SQLException &e) {
        if(e.what()){
            std::cout << "Error -> " << e.what() << std::endl;
        }
    }

    try {

        myStmt = myConn->createStatement();
        myRes = myStmt->executeQuery("INSERT INTO Persons (PersonID,LastName,FirstName,Address,City) VALUES (001, 'Ahmed', 'Islam', 'CNSTA BLVD', 'Waterloo'),(002, 'Prince', 'Nick', 'CNSTA BLVD', 'Fergus');");
        delete myRes;
        delete myStmt;
        delete myConn;
    } catch (sql::SQLException &e) {
        if(e.what()){
            std::cout << "Error -> " << e.what() << std::endl;
        }
    }

#endif


#ifdef _WIN32
	std::cout << "Hello World" << std::endl;
	Quiz q("1", "2", "3", 5);
	q.saveQuiz();
#endif // _WIN32

#ifdef __linux__
	crow::SimpleApp app;

	// Default Route
	CROW_ROUTE(app, "/")
	([](const request& req, response& res) {
		sendHtml(res, "index.html");
	});

	// Calling html from products pages
	CROW_ROUTE(app, "/<string>")
	([](const request& req, response& res, string filename) {
		//createQuiz Query
		if(filename == "createQuiz.html"){
			auto quizTitle = req.url_params.get("quizTitle");
			auto quizDuration = req.url_params.get("quizDuration");
			auto quizPool = req.url_params.get("quizPool");
			auto quizStartDate = req.url_params.get("quizStartDate");
			auto quizEndDate = req.url_params.get("quizEndDate");

			ostringstream quizTitleString, quizDurationString, quizPoolString, 
						quizStartDateString, quizEndDateString;

			quizTitleString << quizTitle ? quizTitle: "";
			quizDurationString << quizDuration ? quizDuration: "";
			quizPoolString << quizPool ? quizPool: "";
			quizStartDateString << quizStartDate ? quizStartDate: "";
			quizEndDateString << quizEndDate ? quizEndDate: "";

			if((quizTitleString.str() != "" && quizDurationString.str() != "" &&
			quizPoolString.str() != "" && quizStartDateString.str() != "" && quizEndDateString.str() != "")) {
				Quiz currentQuiz(quizTitleString.str(), quizStartDateString.str(), quizEndDateString.str(), stoi(quizDurationString.str()));
				currentQuiz.saveQuiz();
				std::cout << currentQuiz.getTitle() << "-------------" << std::endl; // for testing
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


	CROW_ROUTE(app, "/json/<string>")
	([](const request& req, response& res, string filename) {
		sendJson(res, filename);
	});
	


	//serice port
	app.port(27501).multithreaded().run();
	return 1;

#endif //__linux__
}