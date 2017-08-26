#include <StandardCplusplus.h>
#include "arduino.h"
#include "menudialog.h"

void setup()
{
  
}

void loop() 
{
  Arduino dialog;
  MenuDialog menu;
  menu.SetObserver(&dialog);
  menu.Execute();
}
