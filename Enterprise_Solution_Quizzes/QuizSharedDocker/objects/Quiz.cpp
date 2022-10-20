#include "Quiz.h"

/// <summary>
/// Constructor for Quiz
/// Constructor is called whenever a Quiz is to be created
/// </summary>
/// <param name="title"></param>
Quiz::Quiz(std::string title) {
	this->title = title;
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

bool Quiz::deleteQuiz() {

}