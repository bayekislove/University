#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <random>
#include <chrono>

using namespace std;

random_device rd;
mt19937 gen( rd() );
uniform_int_distribution<> dist(30, 200);

condition_variable c_cv;
condition_variable p_cv;
mutex mut;

class storehouse
{
    private:
        uint stored;
        uint capacity;

    public:
        storehouse(uint capacity)
        {
            this->capacity = capacity;
            this->stored = 0;
        }

        bool empty()
        {
            return this->stored == 0;
        }

        bool full()
        {
            return this->stored == this->capacity;
        }

        void remove_item(){ this->stored--; };

        void add_item(){ this->stored++; };

        int amount(){ return this->stored; };
};

storehouse storehome(10);

void cons_thread()
{
    while(true)
    {
        unique_lock<mutex> lockk(mut);

        if( !storehome.empty() )
        {
            storehome.remove_item();
            cout << "Zabrano przedmiot, jest ich teraz: " << storehome.amount() << '\n';
            p_cv.notify_all();
        }
        else
        {
            c_cv.wait(lockk, [&] () { return !storehome.empty(); });
        }

        lockk.unlock();
        this_thread::sleep_for( chrono::milliseconds( dist(gen) ) );
    }
}

void prod_thread()
{
    while(true)
    {
        unique_lock<mutex> lockk(mut);

        if( !storehome.full() )
        {
            storehome.add_item();
            cout << "Dodano przedmiot, jest ich teraz: " << storehome.amount() << '\n';
            c_cv.notify_all();
        }
        else
        {
            p_cv.wait(lockk, [&] () { return !storehome.full(); });
        }

        lockk.unlock();
        this_thread::sleep_for( chrono::milliseconds( dist(gen) ) );
    }
}

int main()
{
    thread consumer(cons_thread);
    thread producer(prod_thread);

    consumer.join();
    producer.join();    
}