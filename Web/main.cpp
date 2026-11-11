// Entry point of the online (WebAssembly) version of City of Thieves.
// Build with scripts/build_web.sh
#include "terminal.h"
#include "menudialog.h"

#include <emscripten.h>

#include <stdexcept>
#include <string>

// Tell the web page (see Web/game.html) that the game has ended
EM_JS(void, web_game_ended, (const char* message), {
  Module.onGameEnded(UTF8ToString(message));
});

int main()
{
  std::string message;
  try
  {
    Terminal dialog;
    MenuDialog menu;
    menu.SetObserver(&dialog);
    menu.Execute();
  }
  catch (std::logic_error& e)
  {
    message = e.what();
  }
  catch (std::runtime_error& e)
  {
    message = e.what();
  }
  web_game_ended(message.c_str());
}
