#include <iostream>
using namespace std;

#ifdef __linux__

#define CROW_MAIN

#include "crow_all.h"

void readHtmlRequestWriteResponse(crow::response& res, string path) {

	std::ifstream in("../public/" + path, std::ifstream::in);

	if (in) {
		ostringstream contents;
		contents << in.rdbuf();
		in.close();
		res.write(contents.str());
	}
	else {
		res.code = 404;
	}
	res.end();
}
#endif //__linux__


int main() {

#ifdef _WIN32
	std::cout << "Hello World" << std::endl;
#endif // _WIN32

#ifdef __linux__
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

	//serice port
	app.port(27501).multithreaded().run();
	return 1;

#endif //__linux__
}