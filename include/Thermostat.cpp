#include "CircularBuffer.hpp"
#include <iostream>
#include <ostream>
#include <format>
#include <fstream>
#include <sstream>

// Using an enum class for type-safe states
enum class ACState
{
    IDLE,
    COOLING,
    EMERGENCY
};

class ThermostatController
{
private:
    EmbeddedProject::CircularBuffer<float, 3> tempSensor;
    ACState currentState = ACState::IDLE;

    const float UPPER_THRESHOLD = 77.0f;
    const float LOWER_THRESHOLD = 72.0f;

public:
    void resetSystem()
    {
        if (currentState == ACState::EMERGENCY)
        {
            std::cout << "User reset the system. Returning to IDLE..." << std::endl;
            // resetting buffer after emergency spike to not mess up average
            tempSensor.clear();
            currentState = ACState::IDLE;
        }
    }

    void update(float newReading, std::ostream &logStream = std::cout, int minuteCount = 0)
    {
        // HIGH PRIORITY CHECK: Raw Reading (ignore the buffer)
        if (newReading > 100.0f)
        {
            if (currentState != ACState::EMERGENCY)
            {
                currentState = ACState::EMERGENCY;
            }
        }
        // 2. If we are in emergency (old or new), LOCK the system
        if (currentState == ACState::EMERGENCY)
        {
            logStream << "!!! SYSTEM LOCKED: EMERGENCY STATE !!!" << std::endl;
            return;
        }
        // 1. Push new reading to our buffer
        tempSensor.push(newReading);
        // 2. Get smoothed Average of our buffer
        float currentAvgTemp = tempSensor.getAverage();
        // Create a formatted string (use ostringstream for portability)
        std::ostringstream oss;
        oss << "Minute " << minuteCount << " | Sensor: " << newReading << " | Avg: " << currentAvgTemp << " C\n";
        std::string iteration = oss.str();
        logStream << iteration;
        // TASK: WRITE THE SWITCH/CASE logic here

        switch (currentState)
        {
        case ACState::IDLE:
            if (currentAvgTemp > UPPER_THRESHOLD)
            {
                currentState = ACState::COOLING;
                logStream << "[IDLE -> COOLING] Current Avg: " << currentAvgTemp << "F. Turning AC ON." << std::endl;
            }
            break;

        case ACState::COOLING:
            if (currentAvgTemp < LOWER_THRESHOLD)
            {
                currentState = ACState::IDLE;
                logStream << "[COOLING -> IDLE] Current Avg: " << currentAvgTemp << "F. Room cooled. Turning AC OFF." << std::endl;
            }
            break;
        }
    }

    ACState getState()
    {
        return ThermostatController::currentState;
    }

    float getAverage() const { return tempSensor.getAverage(); }
};