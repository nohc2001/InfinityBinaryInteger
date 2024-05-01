#include <iostream>
using namespace std;
typedef unsigned int v8ui __attribute__ ((vector_size (32)));

int main(){
    v8ui A = {0, 1, 2, 3, 4, 5, 6, 7};
    v8ui B = {7, 6, 5, 4, 3, 2, 1, 0};
    v8ui C = (A > B) ? A : B;
    for(int i=0;i<8;++i){
        cout << C[i] << endl;
    }   
    return 0;
}