#include<fstream>
#include<memory>
#include<string>

class line_writer{
    std::ofstream stream;

    public:
        line_writer(std::string name){
            stream = std::ofstream(name + ".txt");
        }

        ~line_writer(){
            stream.close();
        }

        void write(std::string str){
            stream << str << std::endl;
        }
};

int main(){

    line_writer *strumyczek = new line_writer("test"); 
    std::shared_ptr<line_writer> ptr1{strumyczek};
    std::shared_ptr<line_writer> ptr2{strumyczek};
    std::shared_ptr<line_writer> ptr3{strumyczek};

    ptr1->write("a");
    ptr2->write("x");
    ptr3->write("c");
}