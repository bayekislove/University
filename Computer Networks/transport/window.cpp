/* Kacper Bajkiewicz 314438 */

// #include <netinet/ip.h>
// #include <arpa/inet.h>
// #include <unordered_map>
#include <map>
#include <unordered_set>

// #ifndef WINDOW
// #define WINDOW

constexpr int32_t WINDOW_ENTRY_SIZE = 950;
constexpr int32_t MAX_WINDOW_SIZE = 450;

// //refactor this class so it doesnt have responsibility to send datagrams
// class Window
// {
// private:
//     int32_t _start_byte = 0;

// public:
//     int Push(int32_t start)
//     {
//         if(_window.size() < MAX_WINDOW_SIZE)
//         {
//             _window[start] = nullptr;
//             return 1;
//         }
//         return -1;
//     }

//     int Pop()
//     {
//         if(acknowledged.find(_start_byte) != acknowledged.end())
//         {
//             _start_byte 
//         }
//     }

//     int Ack(int32_t start, uint8_t* buffer)
//     {
//         _window[start] = buffer;
//         acknowledged.insert(start);
//     }

//     std::pair<int32_t, uint8_t> Pop()
//     {

//     }
// };

// #endif