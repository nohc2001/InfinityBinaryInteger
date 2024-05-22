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
  cout.precision(16);

  fm = new FM_System0();
  // 4KB, 4KB, 128KB, 1MB
  fm->SetHeapData(1 << 10, 1 << 10, 1 << 15, 1 << 20);
  std::cout << "Hello Math!!" << endl;

  fm->_tempPushLayer();

  ibi::StaticInit();

  unsigned int* Adata = (uint*)fm->_tempNew(4*1000);
  unsigned int* Bdata = (uint*)fm->_tempNew(4*500);
  for(int i=0;i<1000;++i){
    Adata[i] = i;
  }
  for(int i=0;i<500;++i){
    Bdata[i] = i+1;
  }

  ibi K;
  K.Init(false);
  K = ibi(true, Adata, 100);
  ibi J; J.Init(false);
  J = ibi(true, Bdata, 50);
  ibi R0; R0.Init(false); R0 = ibi(0);
  ibi R1; R1.Init(false); R1 = ibi(0);

  //std::cout << K.ToString()->c_str() << endl;
  //std::cout << J.ToString()->c_str() << endl;

  R0 = K.FFTMUL(J);
  R1 = K * J;
  std::cout << R0.ToString()->c_str() << endl;
  std::cout << R1.ToString()->c_str() << endl;

  ibr A;
  A.Init(false);
  A = ibr(3, 19);

  ibr B;
  B.Init(false);
  B = ibr(23, 11);

  ibi C;
  C.Init(false);
  C = ibi(19);
  std::cout << C.ToString()->c_str() << endl;

  while(true){
    ++count;
    fm->_tempPushLayer();
    std::cout << A.ToString()->c_str() << endl;
    std::cout << B.ToString()->c_str() << endl;
    A = A.exp_approximate(B, ibi(10));
    //wcout << A.dataString()->c_str() << endl;
    fm->_tempPopLayer();
  }

  fm->_tempPopLayer();
  return 0;
}
