#pragma once
#include <string>
#include <fstream>

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
	Quiz(std::string title, std::string startDate, std::string endDate, int duration);
	bool setTitle(std::string);
	std::string getTitle();
	bool saveQuiz();
	bool deleteQuiz();
};