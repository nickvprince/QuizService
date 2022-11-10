#include "Quiz.h"
#ifdef __linux__
/// <summary>
/// Constructor for Quiz
/// Constructor is called whenever a Quiz is to be created
/// </summary>
/// <param name="title"></param>
Quiz::Quiz(std::string title, std::string startDate, std::string endDate, int duration, std::string pool) {
	this->id = 0;
	this->title = title;
	this->startDate = startDate;
	this->endDate = endDate;
	this->duration = duration;
	this->pool = pool;
	this->totalPoints = 0;
	this->pointsAchieved = 0;
}

Quiz::Quiz(int id) {
	this->id = id;
	this->title = "";
	this->startDate = "";
	this->endDate = "";
	this->duration = 0;
	this->pool = "";
	this->totalPoints = 0;
	this->pointsAchieved = 0;
}

/// <summary>
/// Modify the existing title of a Quiz
/// </summary>
/// <param name="title"></param>
/// If modification is successful
/// <returns>True</returns>
/// If modification is not successful
/// <returns>False</returns>
bool Quiz::setTitle(std::string title)
{
	this->title = title;
	if ( this->title == title ) {
		return true;
	}
	return false;
}

/// <summary>
/// Getter for title
/// </summary>
/// <returns>title</returns>
std::string Quiz::getTitle() {
	return this->title;
}

bool Quiz::saveQuiz() {

	Database db;

	db.executeQuery("INSERT INTO quiz (qp_poolid, title, startdate, enddate, duration, totalpoints) VALUES ('" + 
	this->pool + "','" +
	this->title + "','" +
	this->startDate + "','" +
	this->endDate + "'," +
	std::to_string(this->duration) + "," +
	std::to_string(this->totalPoints) + ");");


	//For testing - will be removed
	std::ofstream output;
	output.open("../public/quizzes/quizList.txt", std::ios::app);
	if (!output) {
		return false;
	}
	output << this->title << " | " << this->duration << " | " << this->pool << " | " << this->startDate << " | " << this->endDate << std::endl;
	output.close();
	return true;

}

bool Quiz::deleteQuiz() {

	Database db;
	db.executeQuery("DELETE FROM quiz WHERE idquiz = " + std::to_string(this->id) + ";");
	return true;

}

#endif //__linux__