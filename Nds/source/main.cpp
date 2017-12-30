#include <cassert>
#include <stdexcept>
#include <iostream>

#include "helper.h"
#include "ndsgamedialog.h"

// For 32 bit systems, add this line:
// https://github.com/devkitPro/buildscripts/issues/26
extern "C" void __sync_synchronize() {}

int main(int argc, char* argv[0])
{
  #ifndef NDEBUG
  NO DEBUG MODE IN NDS
  #endif
  assert(1==2);


  try
  {
    NdsGameDialog d(argc,argv);
    d.Start();
  }
  catch (std::exception& e)
  {
    fprintf(stderr, "debug message in no$gba window %s", e.what());
    std::cout << "Error: " << e.what() << '\n';
    std::clog << "Error: " << e.what() << '\n';
    std::cerr << "Error: " << e.what() << '\n';
    Helper().Cout(e.what());
    for (int i=0; i!=1000; ++i) swiWaitForVBlank();
    return 1;
  }
  catch (...)
  {
    fprintf(stderr, "Unknown error");
    std::cout << "Unknown error\n";
    std::clog << "Unknown error\n";
    std::cerr << "Unknown error\n";
    for (int i=0; i!=1000; ++i) swiWaitForVBlank();
    return 1;
  }
}
