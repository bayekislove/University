#include <stdio.h>
#include <stdint.h>

struct A {
    int8_t a; //1B
    int8_t c;  //1B
    int16_t d; //2bajty
    void *b; //4B
};

struct B {
    uint16_t a; //2 bajty
    double b; //8 bajtów
    void* c; //8 bajtów
};

int main(){
    struct A c;
    uint32_t sizea = sizeof(c);
    printf( "Struct size -> %d int8_t size -> %ld int16_t size %d void* size-> %d \n", sizea, sizeof(uint8_t), sizeof(uint16_t), sizeof(void*) );
    //można zaoszczędzić 8 bajtów

    struct B d;
    uint32_t sizeb = sizeof(d);
    printf( "%u \n", sizeb ); 
    //niepoukładana struktura zajmuje 24 bajty
}