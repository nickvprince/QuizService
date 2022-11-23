#pragma once
#ifdef __linux__

#include <string>
#include <fstream>
#include "Database.cpp"

class Quiz {
	int id;
	std::string title;
	std::string startDate;
	std::string endDate;
	int duration;
	std::string pool;
	int totalPoints;
	int pointsAchieved;
public:
	Quiz(std::string title, std::string startDate, std::string endDate, int duration, std::string pool);
	Quiz(int id, std::string title, std::string startDate, std::string endDate, int duration, std::string pool);
	Quiz(int id);
	bool setTitle(std::string);
	std::string getTitle();
	bool saveQuiz();
	bool updateQuiz();
	bool deleteQuiz();
};

#endif //__linux__