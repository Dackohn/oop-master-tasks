#include "MainApplication.h"
int main() {
    std::string folderPath = "queue";
    int readInterval = 2;
    int serveInterval = 3;

    MainApplication app(folderPath, readInterval, serveInterval);
    app.start();

    return 0;
}
