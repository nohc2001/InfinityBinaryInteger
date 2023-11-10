#include <iostream>
#include "InfinityBinary.h"

using namespace std;
using namespace freemem;

FM_System0 *fm;

int main(){
  fm = new FM_System0();
  fm->SetHeapData(4096, 4096, 4096, 4096);
  cout << "Hello Math!!" << endl;

  fm->_tempPushLayer();

  ibi A;
  A.Init(false);
  A = ibi(123);
  ibi B;
  B.Init(false);
  B = ibi(382);

  A = A - B;
  lcstr* str = A.dataString();
  cout << str->c_str() << endl;

  fm->_tempPopLayer();
  return 0;
}
