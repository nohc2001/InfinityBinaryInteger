#include <iostream>
#include <locale>
#include "InfinityBinary.h"

using namespace std;
using namespace freemem;

FM_System0 *fm;
unsigned int count = 0;
int main(){
  std::wcout.sync_with_stdio(false);
  std::wcout.imbue(std::locale("en_US.utf8"));

  fm = new FM_System0();
  fm->SetHeapData(4096, 4096, 4096, 4096);
  cout << "Hello Math!!" << endl;

  fm->_tempPushLayer();
  unsigned int AData[10] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
  unsigned int BData[2] = { 123456, 7890 };
  ibi A;
  A.Init(false);
  A = ibi(true, AData, 10);

  ibi B;
  B.Init(false);
  B = ibi(true, BData, 2);

  while(true){
    ++count;
    fm->_tempPushLayer();
    A = A / B;
    wcout << A.dataString()->c_str() << endl;
    fm->_tempPopLayer();
  }

  fm->_tempPopLayer();
  return 0;
}
