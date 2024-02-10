#include <iostream>
#include <locale>
#include "InfinityBinary.h"

using namespace std;
using namespace freemem;

FM_System0 *fm;
unsigned int cc = 0;
int main(){
  std::wcout.sync_with_stdio(false);
  std::wcout.imbue(std::locale("en_US.utf8"));

  fm = new FM_System0();
  fm->SetHeapData(4096, 4096, 4096, 4096);
  cout << "Hello Math!!" << endl;
  fm->_tempPushLayer();

  ibr A;
  A.Init(false);
  A = ibr(3, 19);

  ibr B;
  B.Init(false);
  B = ibr(2, 11);

  ibi C;
  C.Init(false);
  C = ibi(19);
  cout << C.ToString()->c_str() << endl;

  while(true){
    ++cc;
    fm->_tempPushLayer();
    cout << A.ToString()->c_str() << endl;
    A = A + B;
    //wcout << A.dataString()->c_str() << endl;
    fm->_tempPopLayer();
  }

  fm->_tempPopLayer();
  return 0;
}
