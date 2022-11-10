#ifdef __linux__
#include <iostream>
#include <string>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
using namespace sql;
using namespace std;


class Database {

    std::string protocol;
    std::string ipAddress;
    std::string port;
    std::string username;
    std::string password;
    std::string schema;
    std::string connString;

    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;

public:
    Database();
    sql::ResultSet* executeQuery(std::string query);
    ~Database();

};

#endif