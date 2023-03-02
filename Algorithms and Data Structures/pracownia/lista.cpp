#include <stdio.h>
#include <iostream>

using namespace std;

class List
{
    public:
        List* l = nullptr;
        List* r = nullptr;
        long val = 0;
        int subvertices = 0;

        List(long val)
        {
            this->l = nullptr;
            this->r = nullptr;
            this->subvertices = 1;
            this->val = val;
        }

        void insert(int p, int x)
        {
            if( this->subvertices == 1 )
            {
                if(p == 0){
                    this->l = new List(x);
                    this->r = new List(this->val);
                } else {
                    this->r = new List(x);
                    this->l = new List(this->val);
                } 

                this->subvertices = 2;
                this->val = this->val + x;
            } else {
                this->val += x;
                (this->subvertices)++;

                if(this->l->subvertices < p)
                    r->insert(p - l->subvertices, x);
                else
                    l->insert(p, x);
            }
        }

        long remove(int p, int pom) //zwraca wartość pod usuniętym indeksem
        {
            (this->subvertices)--;
            long to_del;

            if( this->l->subvertices == 1 && p == pom ){
                to_del = this->l->val;
                this->l = this->r->l;
                this->r = this->r->r;
            }

            else if( this->r->subvertices == 1 && p == this->l->subvertices + pom ){
                to_del = this->r->val;
                this->r = this->l->r;
                this->l = this->l->l;
            } 

            else {
                if( this->l->subvertices + pom > p ){
                    to_del = l->remove(p, pom);
                } else {
                    to_del = r->remove(p, pom + this->l->subvertices);
                }
            }

            this->val -= to_del;
            return to_del;
        }

        long sum(int p1, int p2, int lower_bound, int upper_bound)
        {
            if( p1 == lower_bound && p2 == upper_bound )
                return this->val;

            int left_max_index = lower_bound + this->l->subvertices - 1;
            int right_min_index = left_max_index + 1;

            long left = 0;
            long right = 0;

            if( p2 > left_max_index ){ //musimy zajrzeć do prawego poddrzewa żeby policzyć całą sumę (prawo)
                right = this->r->sum( max(p1, right_min_index), p2, right_min_index, upper_bound );
            } 
            if ( p1 < right_min_index ) { //musimy zajrzeć do lewego poddrzewa, żeby policzyć sumę (lewo)
                left = this->l->sum( p1, min(p2, left_max_index), lower_bound, left_max_index );
            }
            return left + right;
        }
};

int main()
{
    List* a = nullptr;
    int how_many;
    scanf( "%d", &how_many );

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    char instruction;
    long arg1, arg2;
    for(int i = 0; i < how_many; i++){
        cin >> instruction;
        if( instruction == 'I' ){
            cin >> arg1 >> arg2;
            if(a == nullptr){
                a = new List(arg2);
            } else 
                a->insert(arg1, arg2);
        } else if ( instruction == 'D' ){
            cin >> arg1;
            if(a->subvertices == 1)
                a = nullptr;
            else
                a->remove(arg1, 1);
        } else if ( instruction == 'S' ){
            cin >> arg1 >> arg2;
            printf("%ld \n", a->sum(arg1, arg2, 1, a->subvertices));
        }
    }
}