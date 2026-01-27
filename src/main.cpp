#include <iostream>
#include "../include/CircularBuffer.hpp"

int main()
{
    int random_value = 1;
    CircularBuffer<int, 5> buffer;
    for (int i = 1; i < 11; i++)
    {
        buffer.push(i);
    }

    while (!buffer.isEmpty())
    {
        int value = buffer.pop();
        cout << value << endl;
    }
}