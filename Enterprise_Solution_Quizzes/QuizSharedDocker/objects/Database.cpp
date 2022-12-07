#pragma once
#include "Database.h"
#include "./Logger.h"
#ifdef __linux__

Database::Database() {

    this->protocol = "tcp://";
    this->ipAddress = "192.168.0.246";
    this->port = "3306";
    this->username = "root";
    this->password = "admin";
    this->schema = "QuizMYSQL";
    Logger::log("Database initialized " +this->ipAddress + ":"+this->port, 0, "databaseLogs");
    this->connString = this->protocol + this->ipAddress + ":" + this->port;
    try {
        /* Create a connection */
        this->driver = get_driver_instance();
        this->con = driver->connect(this->connString, this->username, this->password);
    }
    catch (exception e) {
        Logger::log("Connection to database failed", 3, "databaseLogs");
        Logger::log("Connection to database failed", 3, "Errors");
    }
    /* Connect to the MySQL test database */
    try{
    this->con->setSchema(this->schema);
}
catch (exception e) {
    Logger::log("set schema failed", 3, "databaseLogs");
    Logger::log("set schema failed", 3, "Errors");
}

}

sql::ResultSet* Database::executeQuery(std::string query) {

    try {
        Logger::log("Executing query "+query, 0, "databaseLogs");
        this->stmt = con->createStatement();
        this->res = this->stmt->executeQuery(query);
        delete this->stmt;

    } catch (sql::SQLException &e) {
        Logger::log(e.what(), 3, "databaseLogs");
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return this->res;

}

Database::~Database() {
    // delete this->con;
    // delete this->res;
}

#endif // __linux__
