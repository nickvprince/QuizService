#pragma once
#include "JsonDTO.h"
#ifdef __linux__
bool updateQuizJson() {
    Database db;

    sql::ResultSet* dbRes = db.executeQuery("SELECT * FROM quiz;");

    std::ofstream jsonFile;
    jsonFile.open("../public/json/quizzes.json");
    if (jsonFile.is_open()) {

        std::string str;

        while (dbRes->next()) { 
            str += "\"" + dbRes->getString("idquiz") + "\": {\n";
            str += "\"title\": \"" + dbRes->getString("title") + "\",\n";
            str += "\"startdate\": \"" + dbRes->getString("startdate") + "\",\n";
            str += "\"enddate\": \"" + dbRes->getString("enddate") + "\",\n";
            str += "\"totalpoints\": \"" + dbRes->getString("totalpoints") +"\"\n},\n";
        }

        str.replace(str.length() - 2, str.length(), "\n");

        jsonFile << "{\n" << str << "}";

    } else {
        std::cout << "Failed to write quizzes to json file" << std::endl;
        return false;
    }
    jsonFile.close();
    
    return true;
}

bool updateQuizPoolJson() {
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
        //not being used
        std::string str = jArray.dump().replace(0, 1, "[");
        str.replace(jArray.dump().length() - 1, jArray.dump().length(), "]");

        jsonFile << "{'pools': " << jArray.dump() << "}\r\n";

    } else {
        std::cout << "Failed to write question pools to json file" << std::endl;
        return false;
    }
    jsonFile.close();

    return true;
}

bool updateQuizPoolJson(std::string id) {
    Database db;

    sql::ResultSet* dbRes = db.executeQuery("SELECT * FROM quiz WHERE idquiz = '" + id + "';");
    nlohmann::json jArray;

    while(dbRes->next()){
        jArray["id"] = dbRes->getString("idquiz");
        jArray["qp_poolid"] = dbRes->getString("qp_poolid");
        jArray["title"] = dbRes->getString("title");
        jArray["startdate"] = dbRes->getString("startdate");
        jArray["enddate"] = dbRes->getString("enddate");
        jArray["duration"] = dbRes->getString("duration");
    }

    std::ofstream jsonFile;
    jsonFile.open("../public/json/currentQuiz.json");

    if (jsonFile.is_open()) {
        jsonFile << "{\"quiz\": " << jArray.dump() << "}\r\n";
    } else {
        std::cout << "Failed to write question pools to json file" << std::endl;
        return false;
    }
    jsonFile.close();

    return true;
}

bool updateQuizQuestionList(std::string id) {
    Database db;

    sql::ResultSet* dbRes = db.executeQuery("SELECT qp_poolid FROM quiz WHERE idquiz = '" + id + "';");

    string poolid = "";

    while(dbRes->next()){
        poolid = dbRes->getString("qp_poolid");
    }
    
    if(poolid != "") {
        dbRes = db.executeQuery("SELECT * FROM question WHERE qp_poolid = '" + poolid + "';");

        nlohmann::json jArray;

        while(dbRes->next()){

            sql::ResultSet* dbResAnswers = db.executeQuery("SELECT * FROM answer WHERE quizID = '" + id + "'AND studentID = 123;");
            nlohmann::json jArrayAnswers;

            jArray["idquestion"] = dbRes->getString("idquestion");
            jArray["question"] = dbRes->getString("question");
            jArray["points"] = dbRes->getString("points");

            while(dbResAnswers->next()){
                string answerID = dbResAnswers->getString("idAnswer");
                jArrayAnswers[answerID] = dbResAnswers->getString("answer");
            }

            jArray["answers"] = jArrayAnswers.dump();
            
        }

        std::ofstream jsonFile;
        jsonFile.open("../public/json/currentQuestions.json");
        
        cout << "---------------test-" << poolid << endl;
        if (jsonFile.is_open()) {
            jsonFile << "{\"Questions\": " << jArray.dump() << "}\r\n";
        } else {
            std::cout << "Failed to write question pools to json file" << std::endl;
        }
        jsonFile.close();

        return true;
    }
    return false;
}

bool updateCalendarJson(int id) {
    Database db;

    sql::ResultSet* dbRes = db.executeQuery("SELECT * FROM quiz WHERE idquiz = '" + std::to_string(id) + "';");
    nlohmann::json jArray;

    while(dbRes->next()){
        jArray["eID"] = dbRes->getString("idquiz");
        jArray["title"] = dbRes->getString("title");
        jArray["startdate"] = dbRes->getString("startdate") + "T00:00:00";
        jArray["dueDate"] = dbRes->getString("enddate") + "T00:00:00";
        jArray["tag"] = "QUIZ";
    }

    std::ofstream jsonFile;
    jsonFile.open("../public/json/createQuizInCalendar.json");

    if (jsonFile.is_open()) {
        jsonFile << jArray.dump();
    } else {
        std::cout << "Failed to write question pools to json file" << std::endl;
        return false;
    }
    jsonFile.close();

    return true;
}

#endif