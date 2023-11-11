#include <iostream>
#include <locale>
#include "InfinityBinary.h"

using namespace std;
using namespace freemem;

FM_System0 *fm;
int main(){
  std::wcout.sync_with_stdio(false);
  std::wcout.imbue(std::locale("en_US.utf8"));

  fm = new FM_System0();
  fm->SetHeapData(4096, 4096, 4096, 4096);
  cout << "Hello Math!!" << endl;

  fm->_tempPushLayer();
  ibi A;
  A.Init(false);
  A = ibi(2);

  while(true){
    fm->_tempPushLayer();
    int a = rand()%10;
    a = a > 0 ? a : -a;
    A = A + A - ibi(a);
    wcout << A.dataString()->c_str() << endl;
    fm->_tempPopLayer();
  }

  fm->_tempPopLayer();
  return 0;
}
