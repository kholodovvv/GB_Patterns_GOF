#include "MyTools.h"

#include <stdint.h>
#include <time.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <sstream>


//namespace MyTools {

std::ofstream logOut;

FileLogger& InternalInstance(){
    static FileLoggerSingletone theInstance;
    return theInstance;
}


void ProxyLoggerSingletone::OpenLogFile(const std::string &FN){
    time(&startTime);

    InternalInstance().OpenLogFile(FN);

    time(&finishTime);
    deltaTime = difftime(finishTime, startTime);
    passedTime += deltaTime;
    countOperation += 1;
}

void ProxyLoggerSingletone::CloseLogFile() {
    time(&startTime);

    InternalInstance().CloseLogFile();

    time(&finishTime);
    deltaTime = difftime(finishTime, startTime);
    passedTime += deltaTime;
    countOperation += 1;
    std::cout << "average execution time: ";
    std::cout << passedTime / countOperation << " sec" << std::endl;
}

void ProxyLoggerSingletone::WriteToLog(const std::string &str) {
    time(&startTime);
    countOperation += 1;

    std::ostringstream oss;
    oss << countOperation;
    InternalInstance().WriteToLog(oss.str() + ": " + str);

    time(&finishTime);
    deltaTime = difftime(finishTime, startTime);
    passedTime += deltaTime;
}

void ProxyLoggerSingletone::WriteToLog(const std::string &str, int n) {
    time(&startTime);
    countOperation += 1;
    std::ostringstream oss;
    oss << countOperation;

    InternalInstance().WriteToLog(oss.str() + ": " + str, n);

    time(&finishTime);
    deltaTime = difftime(finishTime, startTime);
    passedTime += deltaTime;
}

void ProxyLoggerSingletone::WriteToLog(const std::string &str, double d) {
    time(&startTime);
    countOperation += 1;
    std::ostringstream oss;
    oss << countOperation;
    
    InternalInstance().WriteToLog(oss.str() + ": " + str, d);

    time(&finishTime);
    deltaTime = difftime(finishTime, startTime);
    passedTime += deltaTime;
}

void FileLoggerSingletone::OpenLogFile(const std::string &FN) { logOut.open(FN, std::ios_base::out); }

void FileLoggerSingletone::CloseLogFile() {
  if (logOut.is_open()) {
    logOut.close();
  }
}

std::string GetCurDateTime() {
  auto cur = std::chrono::system_clock::now();
  time_t time = std::chrono::system_clock::to_time_t(cur);
  char* buf = ctime(&time);
  return std::string(buf);
}

void FileLoggerSingletone::WriteToLog(const std::string &str) {
  if (logOut.is_open()) {
    logOut << GetCurDateTime() << " - " << str << std::endl;
  }
}

void FileLoggerSingletone::WriteToLog(const std::string &str, int n) {
  if (logOut.is_open()) {
    logOut << GetCurDateTime() << " - " << str << n << std::endl;
  }
}

void FileLoggerSingletone::WriteToLog(const std::string &str, double d) {
  if (logOut.is_open()) {
    logOut << GetCurDateTime() << " - " << str << d << std::endl;
  }
}

FileLogger& FileLoggerSingletone::getInstance() {
    return ProxyLoggerSingletone::getInstance();
}
//} // namespace MyTools

