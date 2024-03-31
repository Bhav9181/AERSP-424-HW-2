//Bhavya Patel
//AERSP 424
//HW 2

//Question 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>

using namespace std;

// Constants
const int NUM_ROBOTS = 5; // Number of robots
const int NUM_TOOLS = 5; // Number of tools
const int TIME_TO_PICK_UP_TOOLS = 1; // Time taken by each robot to pick up tools

// Structure representing a Robot
struct Robot {
    int id; // Robot ID
    int timeToReachTools; // Time taken by the robot to reach tools
    int timeToCompleteTask; // Time taken by the robot to complete a task
};

// Function to perform a task using two robots
void performTask(Robot& robot1, Robot& robot2, int& totalTime, vector<int>& completionTimes) {

    // Update total time by adding time to pick up tools and time to complete the task
    totalTime += TIME_TO_PICK_UP_TOOLS + robot1.timeToCompleteTask;

    // Update completion times for both robots
    completionTimes[robot1.id] = totalTime;
    completionTimes[robot2.id] = totalTime;

    // Print task details based on whether the robots are the same or different
    if (robot1.id == robot2.id) {
        cout << "Robot " << robot1.id << " is collecting data." << endl;
        cout << "Robot " << robot1.id << " acquired tools and starts performing a task." << endl;
        cout << "Robot " << robot1.id << " finished the task and is returning the tools." << endl;
    }
    else {
        cout << "Robot " << robot1.id << " is collecting data." << endl;
        cout << "Robot " << robot2.id << " is collecting data." << endl;
        cout << "Robot " << robot1.id << " acquired tools and starts performing a task." << endl;
        cout << "Robot " << robot2.id << " acquired tools and starts performing a task." << endl;
        cout << "Robot " << robot1.id << " finished the task and is returning the tools." << endl;
        cout << "Robot " << robot2.id << " finished the task and is returning the tools." << endl;
    }
}

// Function to simulate tasks for robots
void simulateTasks(vector<Robot>& robots) {
    int totalTime = 0;
    vector<int> completionTimes(NUM_ROBOTS, 0); // Initialize completion times for each robot

    // Pair up robots for tasks
    int numPairs = (robots.size() - 1) / 2; // Calculate the number of pairs of robots
    for (int i = 0; i < numPairs; i++) {
        performTask(robots[i], robots[numPairs + i], totalTime, completionTimes); // Perform task using a pair of robots
    }

    // If there's an odd number of robots, perform the last robot's task
    if (robots.size() % 2 != 0) {
        performTask(robots.back(), robots.back(), totalTime, completionTimes); // Perform task using the last robot
    }

    cout << "Total time taken by all robots to finish tasks: " << totalTime << " seconds" << endl;
}

int main() {
    // Create a vector of Robot objects
    vector<Robot> robots;

    // Initialize robots with id, time to reach tools, and time to complete a task
    robots.push_back({ 0, 1, 5 });
    robots.push_back({ 1, 1, 5 });
    robots.push_back({ 2, 1, 5 });
    robots.push_back({ 3, 1, 5 });
    robots.push_back({ 4, 1, 5 });

    // Simulate tasks for the robots
    simulateTasks(robots);

    return 0;
}
