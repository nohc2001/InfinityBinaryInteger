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

  unsigned int A_data[3] = {4294967295, 4294967295, 4294967295};
  ibi A;
  A.Init(false);
  A = ibi(true, A_data, 3);
  ibi B;
  B.Init(false);
  B = ibi(1);

  A = B - A;
  cout << A.dataString()->c_str() << endl;

  fm->_tempPopLayer();
  return 0;
}
