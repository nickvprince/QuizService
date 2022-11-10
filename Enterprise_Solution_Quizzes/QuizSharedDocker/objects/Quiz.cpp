#include "Quiz.h"
#ifdef __linux__
/// <summary>
/// Constructor for Quiz
/// Constructor is called whenever a Quiz is to be created
/// </summary>
/// <param name="title"></param>
Quiz::Quiz(std::string title, std::string startDate, std::string endDate, int duration) {
	this->id = 0;
	this->title = title;
	this->startDate = startDate;
	this->endDate = endDate;
	this->duration = duration;
	this->pool = "No Current Pool";
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
	return false;
}
#endif //__linux__