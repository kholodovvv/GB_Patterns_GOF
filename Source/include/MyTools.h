#pragma once

#include <string>

//namespace MyTools {

/*void OpenLogFile(const std::string& FN);

void CloseLogFile();

void WriteToLog(const std::string& str);

void WriteToLog(const std::string& str, int n);

void WriteToLog(const std::string& str, double d);
*/

class FileLogger{ //Интерфейс
public:
    ~FileLogger() = default;
    virtual void OpenLogFile(const std::string& FN) = 0;
    virtual void CloseLogFile() = 0;
    virtual void WriteToLog(const std::string& str) = 0;
    virtual void WriteToLog(const std::string& str, int n) = 0;
    virtual void WriteToLog(const std::string& str, double d) = 0;
};

class FileLoggerSingletone: public FileLogger{ //Реальный объект
public:
    static FileLogger& getInstance();

    virtual void OpenLogFile(const std::string& FN) override;
    virtual void CloseLogFile() override;
    virtual void WriteToLog(const std::string& str) override;
    virtual void WriteToLog(const std::string& str, int n) override;
    virtual void WriteToLog(const std::string& str, double d) override;

private:
    friend FileLogger& InternalInstance();
    FileLoggerSingletone() = default;
    FileLoggerSingletone(const FileLoggerSingletone& root) = delete;
    FileLoggerSingletone operator= (const FileLoggerSingletone&) = delete;
    FileLoggerSingletone(FileLoggerSingletone&& root) = delete;
    FileLoggerSingletone& operator= (FileLoggerSingletone&&) = delete;
    ~FileLoggerSingletone() = default;
};

//}; // namespace MyTools

class ProxyLoggerSingletone: public FileLogger{
public:

    virtual void OpenLogFile(const std::string &FN) override;

    virtual void CloseLogFile() override;

    virtual void WriteToLog(const std::string& str) override;

    virtual void WriteToLog(const std::string& str, int n) override;

    virtual void WriteToLog(const std::string& str, double d) override;

    static FileLogger& getInstance() {
        static ProxyLoggerSingletone theInstance;
        return theInstance;
    }

private:
    ProxyLoggerSingletone(){
    }
    ~ProxyLoggerSingletone(){
    }
    ProxyLoggerSingletone(const ProxyLoggerSingletone& root) = delete;
    ProxyLoggerSingletone& operator=(const ProxyLoggerSingletone&) = delete;
    ProxyLoggerSingletone(ProxyLoggerSingletone&& root) = delete;
    ProxyLoggerSingletone& operator=(ProxyLoggerSingletone&&) = delete;

    time_t startTime, finishTime;
    uint16_t countOperation;
    double deltaTime, passedTime;
};
