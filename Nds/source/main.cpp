#include <cassert>
#include <stdexcept>

#include "helper.h"
#include "ndsgamedialog.h"

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
  catch (std::logic_error& e)
  {
    Helper().Cout(e.what());
  }
  catch (std::runtime_error& e)
  {
    Helper().Cout(e.what());
  }
}
