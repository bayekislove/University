#include<iostream>
#include<set>
#include<string>

using namespace std;

using alias = set<string>;

int main(){
    alias aliasik{"asda", "pop", "koko", "erti"};
    for(auto pom : aliasik){
        cout << pom << endl;
    }
}

