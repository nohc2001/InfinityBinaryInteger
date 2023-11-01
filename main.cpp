#include <iostream>
#include "InfinityBinary.h"

using namespace std;
using namespace freemem;

int main(){
  cout << "Hello Math!!" << endl;

  fm->_tempPushLayer();

  ibi A;
  A.Init(false);
  A = ibi(123);
  ibi B;
  B.Init(false);
  B = ibi(382);

  A = A - B;
  cout << A.ToString(10).c_str() << endl;

  fm->_tempPopLayer();
  return 0;
}
