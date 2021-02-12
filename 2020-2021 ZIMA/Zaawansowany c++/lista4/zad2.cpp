#include<iostream>
#include<functional>
#include<algorithm>
#include<numeric>
using namespace std;

template<typename F, typename G, typename H>
class compose_f_gx_hx_pom{
    private:

        F f;
        G g;
        H h;

    public:
        compose_f_gx_hx_pom(F fs, G gs, H hs) : f(fs), g(gs), h(hs) {};

        auto operator() (auto x){
            return f( g(x), h(x) );
        }
};

template<typename F,typename G,typename H> 
compose_f_gx_hx_pom<F,G,H>
compose_f_gx_hx(F f, G g, H h) { return compose_f_gx_hx_pom<F,G,H>(f,g,h);};

double trzy(double k){
    return 1.0;
}

double dwa(double k){
    return 2.0;
}

double jeden(double x, double y){
    return x + y;
}

int main(){
    cout << compose_f_gx_hx(jeden, dwa, trzy)(3.0) << endl;
}