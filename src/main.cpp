#include <iostream>
#include <fstream>
#include <string>
#include "../include/CircularBuffer.hpp"
#include "../include/Thermostat.cpp"

int main()
{
    ThermostatController myAC;

    // 1. Open a text file called sensor_data.txt
    std::ifstream inputFile("sensor_data.txt");
    float temp;
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open file!" << std::endl;
        return 1;
    }

    std::ofstream outFile("system_logs.txt");
    if (!outFile.is_open())
    {
        std::cerr << "Error: could not open file!" << std::endl;
    }

    int emergencyCount = 0;
    // 2. Reads each temperature line-by-line
    while (inputFile >> temp)
    {
        // 3. Feeds each number into ThermostatController
        myAC.update(temp, outFile);
        if (myAC.getState() == ACState::EMERGENCY)
        {
            emergencyCount++;
            if (emergencyCount >= 3)
            {
                myAC.resetSystem();
                emergencyCount = 0;
            }
        }
    }

    // 4. Logs the results to a second file called system_log.txt.

    /*

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
    */
    return 0;
}