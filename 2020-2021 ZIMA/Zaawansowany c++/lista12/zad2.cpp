#include<iostream>
#include<thread>
#include<chrono>

void countdown(uint time_to_last)
{
    std::this_thread::sleep_for( std::chrono::seconds(time_to_last) );
    std::cout << "Koniec za " << 10 - time_to_last << std::endl; 
}

int main()
{
    std::thread t5{ countdown, 5 };
    std::thread t7{ countdown, 7 };
    std::thread t9{ countdown, 9 };
    std::thread t10([] () {
        std::this_thread::sleep_for( std::chrono::seconds(10) );
    });

    t5.join();
    t7.join();
    t9.join();
    t10.join();

    return EXIT_SUCCESS;
}