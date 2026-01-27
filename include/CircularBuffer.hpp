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

public:
    static_assert(Size > 0, "Circular Buffer size must be greater than 0");
    void push(T value)
    {
        if (count == Size)
        {
            // Logic: How do you move the tail forward and wrap it?
            // Condition: checking if we have to wrap tail back to index 0

            tail = (tail + 1) % Size;
        }
        else
        {
            count++;
        }

        buffer[head] = value;
        head = (head + 1) % Size;
    }
    T pop()
    {
        if (count > 0)
        {
            T value = buffer[tail];
            tail = (tail + 1) % Size;
            count--;
            return value;
        }
        return 0;
    }
    // Return the value at current tail
    T peek()
    {
        // check case if tail is empty(count > 0)
        if (count > 0)
        {
            return buffer[tail];
        }
        else
        {
            return T();
        }
    }

    size_t getCount() const { return count; }

    bool isEmpty() const { return count == 0; }

    bool isFull() const { return count == Size; }
};

#endif
