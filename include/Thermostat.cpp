#include "CircularBuffer.hpp"
#include <iostream>

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
    EmbeddedProject::CircularBuffer<float, 10> tempSensor;
    ACState currentState = ACState::IDLE;

    const float UPPER_THRESHOLD = 77.0f;
    const float LOWER_THRESHOLD = 72.0f;

public:
    void resetSystem()
    {
        if (currentState == ACState::EMERGENCY)
        {
            std::cout << "User reset the system. Returning to IDLE..." << std::endl;
            currentState = ACState::IDLE;
        }
    }
    void update(float newReading)
    {
        // HIGH PRIORITY CHECK: Raw Reading (ignore the buffer)
        if (newReading > 100.0f)
        {
            if (currentState != ACState::EMERGENCY)
            {
                cout << "!!! EMERGENCY OVERHEAT: ALARM SOUNDING !!!" << std::endl;
                currentState = ACState::EMERGENCY;
            }
        }
        // 1. Push new reading to our buffer
        tempSensor.push(newReading);
        // 2. Get smoothed Average of our buffer
        float currentAvgTemp = tempSensor.getAverage();

        // TASK: WRITE THE SWITCH/CASE logic here

        switch (currentState)
        {

        case ACState::EMERGENCY:
            // How do we get OUT of emergency? (Usually requires a manual reset)
            break;

        case ACState::IDLE:
            if (currentAvgTemp > UPPER_THRESHOLD)
            {
                currentState = ACState::COOLING;
                std::cout << "[IDLE -> COOLING] Current Avg: " << currentAvgTemp << "F. Turning AC ON." << std::endl;
            }
            break;

        case ACState::COOLING:
            if (currentAvgTemp < LOWER_THRESHOLD)
            {
                currentState = ACState::IDLE;
                std::cout << "[COOLING -> IDLE] Current Avg: " << currentAvgTemp << "F. Room cooled. Turning AC OFF." << std::endl;
            }
            break;
        }
    }
};