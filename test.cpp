#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;
int main() {
    // Get the current time point
    system_clock::time_point start = system_clock::now();

    // Perform some time-consuming operation
    for (int i = 0; i < 1000000; ++i) {
        // Simulate some computation
        int result = i * i;
    }

    // Get the current time point again
    auto end = system_clock::now();
    // Calculate the duration
    duration<double> elapsed_seconds = end - start;
    double x = elapsed_seconds.count();
    // Output the duration
    //cout << "Time taken: " << x << " seconds\n";

    return 0;
}