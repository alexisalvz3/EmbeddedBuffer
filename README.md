# High-Performance Circular Buffer (Embedded C++)

A memory-safe, template-based Circular Buffer designed for resource-constrained embedded systems.

## Key Features

- **Zero Dynamic Allocation:** Uses `std::array` to ensure no heap usage (crucial for safety-critical systems).
- **Overwrite Policy:** Implements an automatic overwrite when the buffer is full, ensuring the most recent data is always preserved.
- **Compile-Time Safety:** Uses `static_assert` to prevent invalid buffer sizes before the code is even compiled.
- **Header-Only Library:** Easy to integrate into existing embedded toolchains.

## Design Decisions (Why I built it this way)

1. **Modulo Operator (%):** Used for index wrap-around to avoid CPU branching and improve deterministic performance.
2. **Templates:** Implemented using `template <typename T, size_t Size>` to allow the buffer to store any data type (from `uint8_t` to custom sensor structs) without code duplication.

## Performance Reflection (Active Recall)

- **Time Complexity:** \* Push: O(1)
  - Pop: O(1)
- **Memory Complexity:** O(N) where N is the fixed size defined at compile-time.

## How to Build

```bash
g++ -std=c++17 src/main.cpp -I include -o test_suite
./test_suite
```
