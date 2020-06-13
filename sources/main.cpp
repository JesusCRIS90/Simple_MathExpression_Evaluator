// string constructor
#include <iostream>
#include <string>

int main ()
{
  std::string s0 ("Initial");
  std::string s1 ();
  // constructors used in the same order as described above:

    std::cout << s0 << "\n" << s1 << std::endl;

  return 0;
}