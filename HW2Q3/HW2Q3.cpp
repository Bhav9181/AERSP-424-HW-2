//Bhavya Patel
//AERSP 424
//HW 2

//Question 3

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <queue>

using namespace std;
using namespace chrono;

mutex mtx; // Mutex for thread synchronization

class AirTrafficController {
private:
    bool asleep; // Flag to track ATC's state (asleep/awake)
    int trafficPatternCount; // Number of aircraft in the traffic pattern
    bool runwayClear; // Flag to track runway status
    queue<int> landingQueue; // Queue for aircraft waiting for landing permission
public:
    AirTrafficController() : asleep(true), trafficPatternCount(0), runwayClear(true) {}

    void wakeUp() {
        asleep = false;
        cout << "ATC wakes up.\n";
    }

    void fallAsleep() {
        if (trafficPatternCount == 0) {  // Only fall asleep when trafficPatternCount is 0
            asleep = true;
            cout << "ATC falls asleep.\n";
        }
    }

    bool isAsleep() const {
        return asleep;
    }

    void addToTrafficPattern(int id) {
        trafficPatternCount++;
        cout << "Aircraft #" << id << " requesting landing.\n";
        if (trafficPatternCount == 1 && runwayClear) { // Check if runway is clear and first in pattern
            cout << "Aircraft #" << id << " is cleared to land.\n";
            runwayClear = false; // Set runway status to not clear
        }
        else {
            cout << "Aircraft #" << id << " waits for runway clearance.\n";
            landingQueue.push(id); // Add aircraft to landing queue
        }
    }

    void removeFromTrafficPattern() {
        trafficPatternCount--;
        cout << "Runway is now free.\n";
        runwayClear = true; // Set runway status to clear after aircraft leaves

        // Check if there are aircraft waiting in the landing queue
        if (!landingQueue.empty()) {
            int nextAircraft = landingQueue.front(); // Get the next aircraft in line
            landingQueue.pop(); // Remove the aircraft from the queue
            cout << "Aircraft #" << nextAircraft << " is cleared to land.\n";
            runwayClear = false; // Set runway status to not clear
        }
    }

    bool isTrafficPatternFull() const {
        return trafficPatternCount >= 3;
    }
};

void simulateLanding(int id, AirTrafficController& atc, long long& totalLandingTime) {
    auto start = high_resolution_clock::now(); // Start time for each landing
    this_thread::sleep_for(milliseconds(125)); // Simulate landing process taking 1 second
    {
        lock_guard<mutex> guard(mtx); // Lock to ensure ATC state consistency
        if (atc.isAsleep()) {
            atc.wakeUp();
        }
        if (!atc.isTrafficPatternFull()) {
            atc.addToTrafficPattern(id);
        }
        else {
            cout << "Aircraft #" << id << " requesting landing.\n";
            cout << "Approach pattern full. Aircraft #" << id << " redirected to another airport.\n";
            cout << "Aircraft #" << id <<" flying to another airport.\n";
            return;
        }
    }
    // Continue with landing process or other actions after landing
    this_thread::sleep_for(seconds(1));
    {
        lock_guard<mutex> guard(mtx); // Lock to ensure ATC state consistency
        atc.removeFromTrafficPattern();
        atc.fallAsleep();  // Check if ATC needs to fall asleep after each landing
    }
    auto end = high_resolution_clock::now(); // End time for each landing
    auto duration = duration_cast<milliseconds>(end - start); // Calculate landing duration
    totalLandingTime += duration.count(); // Add landing duration to total time
}

int main() {
    AirTrafficController atc;
    vector<thread> aircraftThreads;
    long long totalLandingTime = 0; // Total time for all landings

    for (int i = 1; i <= 10; i++) {
        aircraftThreads.emplace_back(simulateLanding, i, ref(atc), ref(totalLandingTime));
        this_thread::sleep_for(milliseconds(125)); // Add delay between creating threads
    }

    for (auto& thread : aircraftThreads) {
        thread.join();
    }

    int totalTimeInSeconds = static_cast<int>(totalLandingTime / 1000); // Convert milliseconds to seconds
    cout << "duration: " << totalTimeInSeconds << " seconds.\n"; // Display total time in seconds

    return 0;
}
