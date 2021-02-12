#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<type_traits>
#include<list>
#include<string>

using namespace std;

template<typename A>
class write_in{
    private:
        A min;
        A max;
    public:
        write_in(A a, A b) : min(a), max(b) {};
        void operator() (const A& elem){
            if(min < elem && elem < max)
                cout << elem << endl;
        }
};

template<typename B>
class write_interval{
    private:
        int position_start;
        int interval;
        int position = 0;
    public:
        write_interval(int ps, int inter) : position_start(ps), interval(inter) {};
        void operator() (const B& elem){
            if(position_start > 0)
                position_start--;
            else{   
                if(position % interval == 0)
                    cout << elem << endl;
                position++;
            }
        }
};

int main(){
    vector<double> Tvect{3.14, 5.21, 41, 60.4, 7.56};
    list<string> Tlist{"a", "b", "c", "d", "e", "f", "g"};
    set<int> Tset{3, 40, 50, 33, 24, 51, 21};

    for_each(Tvect.begin(), Tvect.end(), write_in<decltype(Tvect)::value_type>(3.0, 50.0));
    for_each(Tlist.begin(), Tlist.end(), write_in<decltype(Tlist)::value_type>("b", "z"));
    for_each(Tset.begin(), Tset.end(), write_in<decltype(Tset)::value_type>(11, 35));
    cout << endl;

    for_each(Tvect.begin(), Tvect.end(), write_interval<decltype(Tvect)::value_type>(1, 2));
    for_each(Tlist.begin(), Tlist.end(), write_interval<decltype(Tlist)::value_type>(1, 2));
    for_each(Tset.begin(), Tset.end(), write_interval<decltype(Tset)::value_type>(1, 2));
    cout << endl;

    double vect_sum(0); int set_sum(0);
    for_each(Tvect.begin(), Tvect.end(), [&vect_sum] (const double &elem) { vect_sum += elem; });
    cout << vect_sum / Tvect.size();
    ///for_each(Tlist.begin(), Tlist.end(), [&] {});
    for_each(Tset.begin(), Tset.end(), [&set_sum] (const int &elem) { set_sum += elem; });
    cout << set_sum / Tset.size();

    pair<vector<double>::iterator, vector<double>::iterator> min_maxTvect(Tvect.begin(), Tvect.begin());
    for_each(Tvect.begin(), Tvect.end(), [&min_maxTvect] (const double& elem) {
        if(*min_maxTvect.first > elem)
            *min_maxTvect.first = elem;
        if(*min_maxTvect.second < elem)
            *min_maxTvect.second = elem;
    });
    cout << *min_maxTvect.first << " " << *min_maxTvect.second << endl;

    pair<list<string>::iterator, list<string>::iterator> min_maxTlist(Tlist.begin(), Tlist.begin());
    for_each(Tlist.begin(), Tlist.end(), [&min_maxTlist] (const string elem) {
        if(*min_maxTlist.first > elem)
            *min_maxTlist.first = elem;
        if(*min_maxTlist.second < elem)
            *min_maxTlist.second = elem;
    });
    cout << *min_maxTlist.first << " " << *min_maxTlist.second << endl;

    pair<set<int>::iterator, set<int>::reverse_iterator> min_maxTset(Tset.begin(), Tset.rbegin());
    cout << *min_maxTset.first << " " << *min_maxTset.second << endl;

    cout << endl;
    string concat = "";
    for_each(Tlist.begin(), Tlist.end(), [&concat] (const string &elem) {concat += elem; });
    cout << endl << concat << endl;
}