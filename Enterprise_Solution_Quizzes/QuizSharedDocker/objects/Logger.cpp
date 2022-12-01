#define _CRT_SECURE_NO_WARNINGS
#include "Logger.h"
#include <chrono>
#include <fstream>
#include <iostream>
#ifdef _WIN32
#define LOGSPATH "./QuizSharedDocker/Logs/"
#endif
#ifdef __linux__
#define LOGSPATH "../Logs/"
#endif
#define DEFAULT_LOG "log"
#define LOGEXTENSION ".log"
void Logger::log(std::string message)
{
	Logger::log(message, -1, DEFAULT_LOG);

}

void Logger::log(std::string message, int severity)
{
	Logger::log(message, severity, DEFAULT_LOG);

}

void Logger::log(std::string message, int severity, std::string logname)
{
	auto now = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(now);

	std::ofstream outfile;
	outfile.open((std::string)LOGSPATH + (std::string)logname + (std::string)LOGEXTENSION, std::ios::app);

	outfile << message << "\t\t Severity :" << severity << "\t\t" << std::ctime(&end_time);
	outfile.close();
}
