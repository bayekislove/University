#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

std::random_device rd;
std::mt19937 gen( rd() );
std::uniform_int_distribution<> dist(500, 1000);

std::mutex mut;

bool time_expired = false;

void c(uint i)
{
    while( true )
    {
        std::unique_lock<std::mutex> lockk(mut);    
        if( time_expired ) return;
        uint time_to_sleep = dist( gen );
        std::cout << "Wątek o nazwie " << i << " będzie spał przez " << time_to_sleep << std::endl;
        lockk.unlock(); 

        std::this_thread::sleep_for( std::chrono::milliseconds( time_to_sleep ) );
    }   
};

int main()
{
    std::thread t1{ c, 1 };
    std::thread t2{ c, 2 };

    std::thread expire([&] () 
    {
        std::this_thread::sleep_for( std::chrono::seconds(60) );
        std::unique_lock<std::mutex> lockk(mut);   
        time_expired = true;
        lockk.unlock();
    });
    expire.join();

    t1.join();
    t2.join();
    
    return EXIT_SUCCESS;
}