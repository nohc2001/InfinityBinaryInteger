#include <iostream>
#include <locale>
#include "InfinityBinary.h"

using namespace std;
using namespace freemem;

IBI_INIT

FM_System0 *fm;
unsigned int count = 0;
int main(){
  std::wcout.sync_with_stdio(false);
  std::wcout.imbue(std::locale("en_US.utf8"));

  fm = new FM_System0();
  fm->SetHeapData(4096, 4096, 4096, 4096);
  cout << "Hello Math!!" << endl;
  fm->_tempPushLayer();

  unsigned int* Adata = (uint*)fm->_tempNew(4*1000);
  unsigned int* Bdata = (uint*)fm->_tempNew(4*500);
  for(int i=0;i<1000;++i){
    Adata[i] = i;
  }
  for(int i=0;i<500;++i){
    Bdata[i] = -i;
  }

  ibi K;
  K.Init(false);
  K = ibi(true, Adata, 1000);
  ibi J; J.Init(false);
  J = ibi(true, Bdata, 500);

  K = K+J;

  ibr A;
  A.Init(false);
  A = ibr(3, 19);

  ibr B;
  B.Init(false);
  B = ibr(23, 11);

  ibi C;
  C.Init(false);
  C = ibi(19);
  cout << C.ToString()->c_str() << endl;

  while(true){
    ++count;
    fm->_tempPushLayer();
    cout << A.ToString()->c_str() << endl;
    cout << B.ToString()->c_str() << endl;
    A = A.exp_approximate(B, ibi(10));
    //wcout << A.dataString()->c_str() << endl;
    fm->_tempPopLayer();
  }

  fm->_tempPopLayer();
  return 0;
}
