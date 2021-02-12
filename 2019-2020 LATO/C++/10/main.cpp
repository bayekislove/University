#include "symbol.hpp"

bool if_exit(std::string inp);
bool if_clear(std::string inp);
bool if_print(std::string inp);
bool if_assign(std::string inp);
double evaluator(std::string inp, kalkulator::zmienna &var);
void start_message();

int main(){
    kalkulator::zmienna *init_vars = new kalkulator::zmienna("init_var"); //variable to manage all variables
    start_message();
    while(true){
        std::string input_line;
        std::getline(std::cin, input_line);
        if(if_exit(input_line)){
            std::cout << "Thanks for using me! Looking forward to see you next time!" << '\n';
            return 0;
        }

        else if(if_print(input_line)){
            try{
                std::cout << evaluator(input_line.substr(6), *init_vars) << '\n';
            }
            catch(std::invalid_argument &exep){
                std::cout << "It looks like your expression isn't correct" << '\n';
            }
            catch(std::domain_error &e){
                std::cout << "You've used unknown variable" << '\n';
            }
        }

        else if(if_clear(input_line)){
            init_vars->clear();
            kalkulator::zmienna *init_vars = new kalkulator::zmienna("init_var"); //we need to make it again to regain control over all the vars
        }

        else if(if_assign(input_line)){
            //we have to look for our value first, it is located between the end of 'assign' and start of word 'to'
            if(input_line.find(" to ") >= 0){
                std::string val_to_parse = input_line.substr(7, input_line.find(" to ") - 7);
                double val = evaluator(val_to_parse, *init_vars);
                std::string name = input_line.substr(input_line.find(" to ") + 4);
                if(name.length() < 8){
                    if(name == "exit" || name == "assign" || name == "clear" || name == "print")
                        std::cout << "Please, type correct variable name!" << std::endl;
                    if(!(init_vars->in(name))){
                        kalkulator::zmienna* nowa = new kalkulator::zmienna(name);
                    }
                    init_vars->assign(name, val);
                }
                else
                    std::cout<< "Try something shorter for your var name ;)" << '\n';
            }
            else{
                std::cout<<"You forgot to write 'to'!" << '\n';
            }
        }
        else if(init_vars->in(input_line)){
            std::cout << "Var: " << input_line << " equals " << init_vars->val_lookup(input_line) << '\n';
        }
        else{
            std::cout<<"I can't understand your command :c Type it once again, please ;)" << '\n';
        }
    }
}

inline void start_message(){
    std::cout << "Welcome to RPN calculator! \n";
    std::cout << "Type 'print' to get evaluation of your RPN expression (remember, write numbers using dots, not colons)! \n";
    std::cout << "Type 'assign X to Y' in order to assign value X to var Y, remember not to add names longer than 7 chars! \n";
    std::cout << "Type 'clear' to remove all your variables values! \n";
    std::cout << "Type 'exit' to quit the calculator :c \n";
    std::cout << '\n';
}

bool if_exit(std::string inp){
    if(inp.find("exit") == 0)
        return true;
    return false;
}

bool if_print(std::string inp){
    if(inp.find("print") == 0){
        return true;
    }
    return false;
}

bool if_assign(std::string inp){
    if(inp.find("assign") == 0)
        return true;
    return false;
}

bool if_clear(std::string inp){
    if(inp.find("clear") == 0)
        return true;
    return false;
}

double evaluator(std::string to_parse, kalkulator::zmienna &env){ //it will get us acces to vars envoirment
    using namespace std;
    stack<kalkulator::symbol*> parsed;
    vector<string> one_arg_functions = vector<string>{"cos", "sin", "abs", "sgn", "ln", "ceil", "frac", "floor", "atan", "acot", "exp"};
    vector<string> two_arg_functions = vector<string>{"+", "-", "/", "*", "max", "min", "mod", "pow", "log"};
    //we need to parse our expression first
    //parsed expression will be put on stack list, there will exist second stack to check type-compability and expression correctness
    for(int i{0}; i < to_parse.size(); i++){
        if(to_parse[i] == ' ')
            i++;
        string pom = to_parse.substr(i, to_parse.find(" ", i) - i); //cuts substring from begining to first found spacesign
        try{
            parsed.push(new kalkulator::liczba(stod(pom)));
            i += pom.length();
        }
        catch(invalid_argument &exep){
            bool onearg_fn = false;
            for(string fn : one_arg_functions){
                if(fn == pom)
                    onearg_fn = true;
            }
            bool twoarg_fn = false;
            for(string fn : two_arg_functions){
                if(fn == pom)
                    twoarg_fn = true;
            }
            if(onearg_fn){
                if(parsed.empty())
                    throw(invalid_argument("EXPRESSION AIN'T CONSTRUCTED WELL"));
                kalkulator::symbol *argument = parsed.top();
                parsed.pop();
                if(pom == "abs")
                    parsed.push(new kalkulator::abs(argument));
                else if(pom == "sgn")
                    parsed.push(new kalkulator::sgn(argument));
                else if(pom == "cos")
                    parsed.push(new kalkulator::cos(argument));
                else if(pom == "sin")
                    parsed.push(new kalkulator::sin(argument));
                else if(pom == "exp")
                    parsed.push(new kalkulator::exp(argument));
                else if(pom == "ceil")
                    parsed.push(new kalkulator::ceil(argument));
                else if(pom == "floor")
                    parsed.push(new kalkulator::floor(argument));
                else if(pom == "atan")
                    parsed.push(new kalkulator::atan(argument));
                else if(pom == "acot")
                    parsed.push(new kalkulator::acot(argument));
                else if(pom == "ln")
                    parsed.push(new kalkulator::ln(argument));
                else if(pom == "frac")
                    parsed.push(new kalkulator::frac(argument));
                i += pom.length();
            }
            else if(twoarg_fn){
                if(parsed.size() < 2)
                    throw(invalid_argument("EXPRESSION AIN'T CONSTRUCTED WELL"));
                kalkulator::symbol *arg2 = parsed.top();
                parsed.pop();
                kalkulator::symbol *arg1 = parsed.top();
                parsed.pop();
                if(pom == "+")
                    parsed.push(new kalkulator::add(arg1, arg2));
                if(pom == "-")
                    parsed.push(new kalkulator::sub(arg1, arg2));
                if(pom == "/")
                    parsed.push(new kalkulator::div(arg1, arg2));
                if(pom == "*")
                    parsed.push(new kalkulator::mult(arg1, arg2));
                if(pom == "min")
                    parsed.push(new kalkulator::min(arg1, arg2));
                if(pom == "max")
                    parsed.push(new kalkulator::max(arg1, arg2));
                if(pom == "pow")
                    parsed.push(new kalkulator::pow(arg1, arg2));
                if(pom == "log")
                    parsed.push(new kalkulator::log(arg1, arg2));
                i += pom.length();   
            }
            else{
                if(env.in(pom))//if var is in env, it is parsed by its name
                    parsed.push(new kalkulator::zmienna("pom"));
                else
                    throw(std::domain_error(""));
            }
        }
    }
    if(parsed.size() > 1) //we know that if stack has more than one element, something is incorrect 
        throw(std::invalid_argument("A"));
    try{
        return (parsed.top())->eval();
    }
    catch(std::exception &e){
        throw(std::logic_error("a"));
    }
}