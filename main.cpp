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

  unsigned int A_data[3] = {4294967295, 4294967295, 4294967295};
  unsigned int B_data[3] = {20000, 4294964295, 4224967295};
  ibi A;
  A.Init(false);
  A = ibi(true, A_data, 3);
  ibi B;
  B.Init(false);
  B = ibi(2);

  A = B - A;
  wcout << A.dataString()->c_str() << endl;

  fm->_tempPopLayer();
  return 0;
}
