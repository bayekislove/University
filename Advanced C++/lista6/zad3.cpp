#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

auto freqElems(vector<int>& x)
{
    unordered_map<int, int> counters;
    for (auto i : x)
    {
        ++counters[i];
    }

    vector<pair<int, int>> asda;  
    int maxCounter = (*max_element(counters.begin(), counters.end(), 
                                [] (pair<int, int> a, pair<int, int> b) {
                                    return a.second < b.second; })).second;

    for_each(counters.begin(), counters.end(), [&] (pair<int, int> a) { if(a.second == maxCounter) { asda.push_back(a); }}); 
    return asda;
}

int main()
{
    vector<int> test =  {1, 1, 3, 5, 8, 9, 5, 8, 8, 5};
    for(auto x : freqElems(test))
    {
        cout << "(" << x.first << "," << x.second << ")" << endl;
    }
}