#include <iostream>
#include "../include/CircularBuffer.hpp"
#include "../include/Thermostat.cpp"

int main()
{
    ThermostatController myAC;

    std::cout << "--- Starting AC Simulation ---" << std::endl;

    // Simulate temperature rising from 70 to 80
    for (float t = 70.0f; t <= 80.0f; t += 0.5f)
    {
        std::cout << "Sensor reading: " << t << "F" << std::endl;
        myAC.update(t);
    }

    // Simulate temperature falling from 80 to 70
    // Simulate temperature falling further to "clear" the buffer
    for (float t = 80.0f; t >= 65.0f; t -= 0.5f)
    { // Lowered to 65
        std::cout << "Sensor reading: " << t << "F" << std::endl;
        myAC.update(t);
    }

    myAC.update(105.0f);
    myAC.update(70.0f);
    myAC.resetSystem();
    myAC.update(70.0f);

    return 0;
}