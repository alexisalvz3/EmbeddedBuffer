#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP

#include <array>
#include <cstdint>
#include <iostream>

using namespace std;

template <typename T, size_t Size>
class CircularBuffer
{
private:
    array<T, Size> buffer;
    int head = 0;
    int tail = 0;
    size_t count = 0;
    T runningSum = 0;

public:
    static_assert(Size > 0, "Circular Buffer size must be greater than 0");
    // Adds value to buffer; overwrites oldest data if full
    void push(T value)
    {
        if (count == Size)
        {
            // Update sum by swapping the outgoing value with the new one
            runningSum = runningSum - buffer[head] + value;
            tail = (tail + 1) % Size;
        }
        else
        {
            runningSum += value;
            count++;
        }

        buffer[head] = value;
        head = (head + 1) % Size; // Wrap-around logic
    }

    // Removes and returns the oldest value; returns default T if empty
    T pop()
    {
        if (count > 0)
        {
            T value = buffer[tail];
            runningSum -= value;

            tail = (tail + 1) % Size;
            count--;

            // Reset sum to 0 to prevent floating-point rounding errors over time
            if (count == 0)
                runningSum = 0;

            return value;
        }
        return T();
    }

    // Returns oldest value without removing it
    T peek() const
    {
        return (count > 0) ? buffer[tail] : T();
    }

    // O(1) average calculation using the maintained running sum
    float getAverage() const
    {
        if (count == 0)
            return 0.0f;
        return static_cast<float>(runningSum) / count;
    }

    size_t getCount() const { return count; }

    bool isEmpty() const { return count == 0; }

    bool isFull() const { return count == Size; }
};

#endif
