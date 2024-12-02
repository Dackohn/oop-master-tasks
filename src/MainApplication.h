#include "Semaphore.h"

class MainApplication {
private:
    CircularQueue<Car> electricQueue;
    CircularQueue<Car> gasQueue;
    Statistics electricStats, gasStats;
    CarStation electricStation;
    CarStation gasStation;
    Semaphore semaphore;

public:
    MainApplication(const std::string& folder, int readInt, int serveInt)
        : electricQueue(), gasQueue(),
          electricStats(), gasStats(),
          electricStation(&electricQueue, &electricStats),
          gasStation(&gasQueue, &gasStats),
          semaphore(&electricStation, &gasStation, folder, readInt, serveInt) {}

    void start() {
        semaphore.start();
        semaphore.printStatistics();
    }
};
