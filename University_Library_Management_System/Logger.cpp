#include "Logger.h"
#include <fstream>
#include <ctime>

Logger* Logger::instance = NULL;

Logger* Logger::getInstance() {
    if (instance == NULL)
        instance = new Logger();
    return instance;
}

void Logger::log(string msg) {
    cout << "[LOG]: " << msg << endl;

    ofstream file("audit_log.txt", ios::app);

    time_t now = time(0);
    string dt = ctime(&now);

    file << dt.substr(0, dt.length() - 1)
         << " | " << msg << endl;

    file.close();
}