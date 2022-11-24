#pragma once
#include "Database.h"
#ifdef __linux__

Database::Database() {

    this->protocol = "tcp://";
    this->ipAddress = "10.0.0.30";
    this->port = "3306";
    this->username = "root";
    this->password = "admin";
    this->schema = "QuizMYSQL";
    this->connString = this->protocol + this->ipAddress + ":" + this->port;

    /* Create a connection */
    this->driver = get_driver_instance();
    this->con = driver->connect(this->connString, this->username, this->password);
    /* Connect to the MySQL test database */
    this->con->setSchema(this->schema);

}

sql::ResultSet* Database::executeQuery(std::string query) {

    try {
        this->stmt = con->createStatement();
        this->res = this->stmt->executeQuery(query);
        delete this->stmt;

    } catch (sql::SQLException &e) {

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