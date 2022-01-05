#include <iostream>
#include <sstream>
#include <fstream>
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[]) {
    Server_t server;
    try {
        // Check whether the number of arguments is less than 2. If true, then one of the mandatory arguments is missing.
        if (argc < 3) {
            ostringstream oStream;
            oStream << "Error: Wrong number of arguments!" << endl;
            oStream << "Usage: ./p2 <username> <logfile>" << endl;
            throw Exception_t(INVALID_ARGUMENT, oStream.str());
        }
        // Server Initialization
        initServer(argv[1], server);
        // Logfile Processing
        processLog(argv[2], server);
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return 0;
    }
}