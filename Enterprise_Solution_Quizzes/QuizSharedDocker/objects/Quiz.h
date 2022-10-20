#pragma once
#include <string>

class Quiz {
	int totalPoints;
	int pointsAchieved;
	std::string title;
	int startDate;
	int endDate;
public:
	Quiz(std::string);
	bool setTitle(std::string);
	std::string getTitle();
	bool deleteQuiz();
};