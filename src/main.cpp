#include <iostream>
#include "../include/CircularBuffer.hpp"

int main()
{
    int random_value = 1;
    CircularBuffer<float, 3> buffer;
    buffer.push(10.0);
    buffer.push(20.0);
    buffer.push(30.0);
    buffer.push(40.0);
    float avg = buffer.getAverage();
    cout << avg << endl;
}