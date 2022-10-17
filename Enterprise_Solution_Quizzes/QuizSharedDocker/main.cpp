#define CROW_MAIN

#include "crow_all.h"
#include <iostream>
using namespace std;

void readHtmlRequestWriteResponse(crow::response &res, string path) {

	std::ifstream in("../public/" + path, std::ifstream::in);
	
	if (in) {
		ostringstream contents;
		contents << in.rdbuf();
		in.close();
		res.write(contents.str());
	} else {
		res.code = 404;
	}
	res.end();
}

int main() {
	
	crow::SimpleApp app;

	//Default Request
	CROW_ROUTE(app, "/")
	([](const crow::request &req, crow::response &res) {
		readHtmlRequestWriteResponse(res, "index.html");
	});
	//Main Page Requests
	CROW_ROUTE(app, "/public/<string>")
	([](const crow::request &req, crow::response &res, string filename) {
		readHtmlRequestWriteResponse(res, filename);
	});
	//Images, Script & CSS Requests
	CROW_ROUTE(app, "/public/<string>/<string>")
	([](const crow::request &req, crow::response &res, string folder, string filename) {
		readHtmlRequestWriteResponse(res, folder + "/" + filename);
	});

	app.port(23500).multithreaded().run();
	return 1;
}