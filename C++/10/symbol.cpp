#include "symbol.hpp"

using namespace kalkulator;

std::vector<std::pair<std::string, double>> zmienna::vars;

liczba::liczba(double inpval){
    this->val = inpval;
}

double liczba::eval(){
    return this->val;
}

zmienna::zmienna(std::string inpname){
    for(int i{0}; i < zmienna::vars.size(); i++){ //we're looking whether there is var called ,inpname
        if (zmienna::vars[i].first == inpname){ //if so, then our index is "val" field;
            this->val = i;
            return;
        }
    }
    vars.push_back(make_pair(inpname, 0));
    this->val = vars.size();
}

bool zmienna::in(std::string inpname){
    for(int i{0}; i < zmienna::vars.size(); i++){ //we're looking whether there is var called ,inpname
        if (zmienna::vars[i].first == inpname){ //if so, true is returned
            return true;
        }
    }
    return false; //false else
}

double zmienna::val_lookup(std::string inpname){
    for(int i{0}; i < zmienna::vars.size(); i++){ //we're looking whether there is var called ,inpname
        if (zmienna::vars[i].first == inpname){ //if so, true is returned
            return vars[i].second;
        }
    }
}

double zmienna::get_val(int pos){
    return vars[pos].second;
}

void zmienna::assign(std::string inpname, double inpval){
    for(int i{0}; i < zmienna::vars.size(); i++){ //we're looking whether there is var called ,inpname
        if (zmienna::vars[i].first == inpname) //if so, then our index is "val" field;
            vars[i].second = inpval;
    }
}

double zmienna::eval(){
    return this->val_lookup(this->name);
}

void zmienna::clear(){
    vars = std::vector<std::pair<std::string, double>>();
}

one_argument_fn::one_argument_fn(symbol *k) : arg(k) {};
abs::abs(symbol *k) : one_argument_fn(k) {};

double abs::eval(){
    return std::abs(arg->eval());
}

sgn::sgn(symbol *k) : one_argument_fn(k) {};

double sgn::eval(){
    if(arg->eval() < 0)
        return -1;
    else if(arg->eval() == 0)
        return 0;
    return 1;
}

floor::floor(symbol *k) : one_argument_fn(k) {};

double floor::eval(){
    return std::floor(arg->eval());
}

ceil::ceil(symbol *k) : one_argument_fn(k) {};

double ceil::eval(){
    return std::ceil(arg->eval());
}

frac::frac(symbol *k) : one_argument_fn(k) {};

double frac::eval(){
    return std::abs(arg->eval()) - std::floor(std::abs(arg->eval())); 
}

sin::sin(symbol *k) : one_argument_fn(k) {};

double sin::eval(){
    return std::sin(arg->eval());
}

cos::cos(symbol *k) : one_argument_fn(k) {};

double cos::eval(){
    return std::cos(arg->eval());
}

atan::atan(symbol *k) : one_argument_fn(k) {};

double atan::eval(){
    return std::atan(arg->eval());
}

acot::acot(symbol *k) : one_argument_fn(k) {};

double acot::eval(){
    return std::atan(1/(arg->eval()));
}

exp::exp(symbol *k) : one_argument_fn(k) {};

double exp::eval(){
    return std::exp(arg->eval());
}

ln::ln(symbol *k) : one_argument_fn(k) {};

double ln::eval(){
    return std::log(arg->eval());
}

two_argument_fn::two_argument_fn(symbol *x, symbol *y) : left(x), right(y) {};

add::add(symbol *x, symbol *y) : two_argument_fn(x, y) {};

double add::eval(){
    return left->eval() + right->eval();
}

sub::sub(symbol *x, symbol *y) : two_argument_fn(x, y) {};

double sub::eval(){
    return left->eval() - right->eval();
}

div::div(symbol *x, symbol *y) : two_argument_fn(x, y) {};

double div::eval(){
    return left->eval() / right->eval();
}

mult::mult(symbol *x, symbol *y) : two_argument_fn(x, y) {};

double mult::eval(){
    return left->eval() * right->eval();
}

min::min(symbol *x, symbol *y) : two_argument_fn(x, y) {};

double min::eval(){
    return std::min(left->eval(), right->eval());
}

max::max(symbol *x, symbol *y) : two_argument_fn(x, y) {};

double max::eval(){
    return std::max(left->eval(), right->eval());
}

mod::mod(symbol *x, symbol *y) : two_argument_fn(x, y) {};

double mod::eval(){
    return std::fmod(left->eval(), right->eval()); //func from cmath
}

log::log(symbol *x, symbol *y) : two_argument_fn(x, y) {};

double log::eval(){
    return std::log(left->eval()) / std::log(right->eval()); //from logarithm base change 
}

pow::pow(symbol *x, symbol *y) : two_argument_fn(x, y) {};

double pow::eval(){
    return std::pow(left->eval(), right->eval());
}