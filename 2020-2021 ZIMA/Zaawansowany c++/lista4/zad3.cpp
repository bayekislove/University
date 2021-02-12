#include<iostream>
#include<algorithm>
#include<functional>
using namespace std;

template <typename F, typename G>
class po_kolei_pom{
    private:
        F f1;
        G f2;
    public:
        po_kolei_pom(F f1s, G f2s) : f1(f1s), f2(f2s) {};

        void operator() (auto x){
            f1(x);
            f2(x);
        }
};

template<typename F,typename G> 
po_kolei_pom<F,G>
po_kolei(F f, G g) { return po_kolei_pom<F, G>(f, g); };

int main(){
    po_kolei([](double x) { cout << "f1" << endl; }, [](double x) { cout << "f2" << endl; })(5.0);
    po_kolei(po_kolei([](double x) { cout << "f1" << endl; }, [](double x) { cout << "f2" << endl; }), 
            [](double x) { cout << "f3" << endl; });
}