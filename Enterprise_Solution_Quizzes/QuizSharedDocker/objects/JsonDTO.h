#pragma once
#ifdef __linux__
#include "Database.cpp"

bool updateQuizJson();
bool updateQuizPoolJson();
bool updateQuizPoolJson(std::string id);
#endif