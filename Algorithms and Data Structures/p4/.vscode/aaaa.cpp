#include <stdio.h>
#include <iostream>

using namespace std;

class List
{
    public:
        List* l = nullptr;
        List* r = nullptr;
        long val = 0;
        int subvertices = 1;

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

        long remove(int p) //zwraca wartość pod usuniętym indeksem
        {
            if( this->l->subvertices == 1 && p == 0 ) 
            {
                long del_val = this->l->val;
                (this->subvertices)--;

                this->val = this->r->val;
                delete this->l;
                
                this->l = this->r->l;
                this->r = this->r->r;
                return del_val; 
            }

            else if( this->r->subvertices == 1 && p == 1 )
            {
                long del_val = this->r->val;
                (this->subvertices)--;

                this->val = this->l->val;
                delete this->r;
                
                this->r = this->l->r;
                this->l = this->l->l;
                return del_val;

            } else { //to znaczy że tutaj na pewno oba poddrzewa nie są liścmi ergo nie możemy ich wywalić
                (this->subvertices)--;
                long res = 0;

                if(this->l->subvertices < p)   
                    res = this->r->remove(p - this->l->subvertices + 1);

                else
                    res = this->r->remove(p);

                this->val -= res;
                return res;
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
    List* a = new List(2);
    a->insert(0, 1);
    a->insert(1, 3);
    a->insert(3, 4);
    a->insert(2, 5);

    a->remove(1);
}