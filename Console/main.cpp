#include "terminal.h"
#include "menudialog.h"

#include <iostream>
#include <stdexcept>

int main()
{
  try
  {
    Terminal dialog;
    MenuDialog menu;
    menu.SetObserver(&dialog);
    menu.Execute();
  }
  catch (std::logic_error& e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch (std::runtime_error& e)
  {
    std::cerr << e.what() << std::endl;
  }
}
