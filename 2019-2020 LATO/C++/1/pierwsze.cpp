#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

bool if_prime(int64_t number){ ///funkcja sprawdzająca czy podana liczba jest pierwsza czy nie
    if(number == 1){
        return false;
        }
    if(number == 2){
        return true;
        }
    for(int64_t i{2}; i <= sqrt(number); i++){
        if (number % i == 0){ ///jesli jakakolwiek liczba z przedzialu (1, liczba) dzieli inputowaną liczbę, to input niepierwszy 
            return false;
        }}
    return true; 
    };

bool conversion_possibility(char* tab[], int num){ /// tu sprawdzamy czy da się zamienić każde słowo z tej tablicy na inta
    for(int i = 1; i < num; i++){
        try{ ///próbujemy wywołać funckję konwertującą
            stoll(tab[i], NULL);}
        catch(invalid_argument){ ///jesli stoi wywali blad, to znaczy, ze liczbt nie da sie przepisac
            return false; 
            }
        }
    return true;
    };

int64_t change(string word){ ///funkcja zamieniajaca stringa na
    int64_t sum=0;   ///tu przechowujemy sume
    int i; //ta zmienna determiniuje od ktorego miejsca w stringu zaczynamy (jesli ujemna to od 1)
    bool if_positive;
    if(word.front() == '-'){ /// jesli liczba jest ujemna, to pozniej przemnozymy ja przez -1
        if_positive = false;
        i = 1; ///skoro liczba jest ujemna, to jej na zerowym indeksie stringa ma "-", więc przepisywanie zaczyna sie od 1szego
        }      ///indeksu
    else{
        if_positive = true; ///jesli liczba jest dodatnia, to zwrocimy po prostu te liczbe
        i = 0;}
    int current_length = word.length() - 1;
    for(; i < word.length(); i++){
        sum = sum +((int64_t)( pow(10, current_length - i)) * (word[i] - '0')); ///to jest po to, zeby odddzielic jednostki od dziesiatek etc
        ///im dalej w i idziemy, tym bardziej zmniejsza sie wykladnik ktorym potegujemy 10
    }
    if(if_positive == false){ ///linia 35
        return (-1) * sum;
        }
    return sum;
}

vector<int64_t> to_prime_factors(int64_t num){ ///funkcja zwracająca wektor z rozkładem na czynniki pierwsze
    vector<int64_t> prime_factors;
    if(if_prime(num) == true){ ///jesli liczba jest pierwsza, to w wektorze znajduje sie tylko ona sama (bo 1ke pomijamy)
        prime_factors.insert(prime_factors.end(), num);
        return prime_factors;
        }
    int64_t stop = num; ///deklarujemy int64, ktory pozwoli nam stwierdzic, kiedy iloczyn wszystkich liczb w wektorze bedzie rowny
    while(stop > 1){ ///liczbe wlozonej (wtedy zakonczymy dzialanie petli) niezmiennik petli while: iloczyn * stop = num
        for(int64_t iterator = 2; iterator <= num; iterator++){
            if(stop % iterator == 0){
                if(if_prime(iterator == true)){
                    prime_factors.insert(prime_factors.end(), iterator); /// jesli liczba jest pierwsza i dzieli, to dodajemy 
                    stop = stop / iterator;
                    iterator--;
                    }
                }
            }
        } 
    return prime_factors; 
    };

int main(int argc, char *argv[]){
    int64_t numbers[argc];
    if(conversion_possibility(argv, argc) == false){ /// sprawdzamy czy mozna slowo zamienic na inta
        cerr << "invalid_argument" << endl; /// jesli nie, to wywalamy blad i konczymy program
        return 0;
    };
    for(int k = 1; k < argc; k++){ ///zamieniamy kazdego inputowanego stringa na inta
        numbers[k-1] = change(argv[k]);
    }
    if(argc == 1){  ///jeśli nie dostarczymy argumentu, to program wypluwa instrukcję obsługi
        cerr << "Program wypisuje rozkład na czynniki pierwsze, proszę, więc, podać jakąś liczbę!" << endl;}
    for(int x = 0; x < argc; x++){ /// wypisujemy kazdy wektor
        vector<int64_t> prime_numbers_decomposion; ///tu bedziemy przechowywac rozklad liczby
        cout << numbers[x] << " = ";
        if(numbers[x] == 1){ 
            cout << "1";
        }
        else if(abs(numbers[x]) != numbers[x]){ /// jesli liczba jest ujemna to najpierw wypisujemy -1 po czym rozkladamy jej modul
           cout << "-1 * ";
           if(numbers[x] == -1){
                cout << "\b" << "\b" << " "; 
           }
        }
        prime_numbers_decomposion = to_prime_factors(abs(numbers[x])); ///rozkladamy modul
        int i{0};
        for(int reader: prime_numbers_decomposion){
            if(i == prime_numbers_decomposion.size()-1){ ///zeby uniknac wypisania " * " bez liczby po prawej znaku mnozenia
                cout << reader;
            }
            else{
                cout << reader << " * ";
            }
            i++;
        }
        cout << endl;
    }
    return 0;
}