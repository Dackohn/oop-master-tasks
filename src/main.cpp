#include "MainApplication.h"
int main() {
    std::string folderPath = "queue";
    int readInterval = 1;
    int serveInterval = 1.5;

    MainApplication app(folderPath, readInterval, serveInterval);
    app.start();

    return 0;
}
