#include<iostream>
#include<string>

using namespace std;

inline istream& clearline(istream &in){
    char pom;
    while(in){ 
        if(in.get() == '\\')
            if(in.get() == 'n')
                return in;
    }
    return in;
}

inline ostream& comma(ostream &os){
    return os << ", ";
}

inline ostream& colon(ostream &os){
    return os << ": ";
}

class ignore{
    public:
        int many;
        ignore(int inp_many) : many(inp_many) {};
        friend istream& operator>>(istream& is, const ignore &inp){
            int i{0};
            while(is && i < inp.many){ 
                if(is.get() == '\\')
                    if(is.get() == 'n')
                        return is;
                i++;
            }
            return is;
        }
};

class index{
    public:
        int positions; int num;
        index(int pos_init, int num_init) : positions(pos_init), num(num_init) {};
        friend ostream& operator<<(ostream& os, const index &inp){
            string num_string = to_string(inp.num);
            os << "[";

            if(inp.positions < num_string.length())
                return os << num_string << ']';

            for(int i{0}; i < inp.positions - num_string.length(); i++)
                os << "0";

            return os << num_string << "]";
        }
};

int main(){
    cout << comma << "Jarosław Polskę Zbaw" << '\n';
    cout << colon << "Test1" << '\n';
    string s;
    cout << index(5, 191202) <<'\n';
    cin >> ignore(4) >> s; //ignoruje 4 znaki
    cout << s << '\n';
    return 0;
}