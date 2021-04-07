#include <iostream>
#include <vector>
#include <cmath>
#include <stack>

namespace kalkulator{   
    class symbol{
        public:
            int some_num;
            virtual double eval() = 0;
    };

    class operand : public symbol{
        public:
            double val;
    };

    class liczba : public operand{
        public:
            double eval();
            liczba(double num);
    };

    class zmienna : public operand{
        //field val tells us where to look for variable value in vars vector (which stores all the values)
        private:
            std::string name;
            static std::vector<std::pair<std::string, double>> vars;
        public:
            zmienna(std::string inpname);
            double val_lookup(std::string inp);
            bool in(std::string inp);
            double get_val(int position);
            void assign(std::string inp, double inpval);
            double eval();
            void clear();
    };

    class stala : public operand{
        public:
            stala();
    };

    class funkcja : public symbol{};

    class one_argument_fn : public funkcja{
        protected:
            symbol *arg;
        public:
            one_argument_fn(symbol *inp);
    };

    class abs : public one_argument_fn{
        public:
            abs(symbol *inp);
            double eval();
    };

    class sgn : public one_argument_fn{
        public:
            double eval();
            sgn(symbol *inp);
    };

    class floor : public one_argument_fn{
        public:
            double eval();
            floor(symbol *inp);
    };

    class ceil : public one_argument_fn{
        public:
            double eval();
            ceil(symbol *inp);
    };

    class frac : public one_argument_fn{
        public:
            double eval();
            frac(symbol *inp);
    };

    class sin : public one_argument_fn{
        public:
            double eval();
            sin(symbol *inp);
    };

    class cos : public one_argument_fn{
        public:
            double eval();
            cos(symbol *inp);
    };

    class atan : public one_argument_fn{
        public:
            double eval();
            atan(symbol *inp);
    };

    class acot : public one_argument_fn{
        public:
            double eval();
            acot(symbol *inp);
    };

    class exp : public one_argument_fn{
        public:
            double eval();
            exp(symbol *inp);
    };

    class ln : public one_argument_fn{
        public:
            double eval();
            ln(symbol *inp);
    };

    class two_argument_fn : public funkcja{
        protected:
            symbol *left; symbol *right;
        public:
            two_argument_fn(symbol *x, symbol *y);
    };

    class add : public two_argument_fn{
        public:
            add(symbol *x, symbol *y);
            double eval();
    };

    class sub : public two_argument_fn{
        public:
            sub(symbol *x, symbol *y);
            double eval();
    };

    class mult : public two_argument_fn{
        public:
            mult(symbol *x, symbol *y);
            double eval();
    };

    class div : public two_argument_fn{
        public:
            div(symbol *x, symbol *y);
            double eval();
    };

    class log : public two_argument_fn{
        public:
            log(symbol *x, symbol *y);
            double eval();
    };

    class min : public two_argument_fn{
        public:
            min(symbol *x, symbol *y);
            double eval();
    };

    class max : public two_argument_fn{
        public:
            max(symbol *x, symbol *y);
            double eval();
    };

    class mod : public two_argument_fn{
        public:
            mod(symbol *x, symbol *y);
            double eval();
    };

    class pow : public two_argument_fn{
        public:
            pow(symbol *x, symbol *y);
            double eval();
    };
}