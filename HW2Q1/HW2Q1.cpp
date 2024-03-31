//Bhavya Patel
//AERSP 424
//HW 2

//Question 1

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

// Abstract base class for sensors
class Sensor {
public:
    virtual void gatherData() const = 0;
    virtual void processData() const = 0;
    virtual ~Sensor() {}
};

// Temperature sensor class
class TemperatureSensor : public Sensor {
public:
    void gatherData() const override {
        cout << "Gathering data from Temperature Sensor." << endl;
    }

    void processData() const override {
        cout << "Processing data from Temperature Sensor." << endl;
    }
};

// Pressure sensor class
class PressureSensor : public Sensor {
public:
    void gatherData() const override {
        cout << "Gathering data from Pressure Sensor." << endl;
    }

    void processData() const override {
        cout << "Processing data from Pressure Sensor." << endl;
    }
};

// Position sensor class
class PositionSensor : public Sensor {
public:
    void gatherData() const override {
        cout << "Gathering data from Position Sensor." << endl;
    }

    void processData() const override {
        cout << "Processing data from Position Sensor." << endl;
    }
};

// Sensor factory class
class SensorFactory {
public:
    static Sensor* createSensor(const string& sensorType) {
        if (sensorType == "Temperature") {
            return new TemperatureSensor();
        }
        else if (sensorType == "Pressure") {
            return new PressureSensor();
        }
        else if (sensorType == "Position") {
            return new PositionSensor();
        }
        else {
            return 0;
        }
    }
};

// Aerospace control system class
class AerospaceControlSystem {
private:
    vector<Sensor*> sensors;

public:
    void addSensor(Sensor* sensor) {
        sensors.push_back(sensor);
    }

    void monitorAndAdjust() {
        for (Sensor* sensor : sensors) {
            sensor->gatherData();
            sensor->processData();
            cout << "Adjusting controls based on sensor data." << endl;
        }
    }

    ~AerospaceControlSystem() {
        for (Sensor* sensor : sensors) {
            delete sensor;
        }
    }
};

int main() {
    AerospaceControlSystem ctrlSys;

    // Adding sensors to the control system
    ctrlSys.addSensor(SensorFactory::createSensor("Temperature"));
    ctrlSys.addSensor(SensorFactory::createSensor("Pressure"));
    ctrlSys.addSensor(SensorFactory::createSensor("Position"));

    // Monitoring and adjusting based on sensor data
    ctrlSys.monitorAndAdjust();

    return 0;
}
