#include "ndsgamedialog.h"

#include <cassert>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include <stdio.h>

#include <nds.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "ndsgamedialog.h"
#include "helper.h"
#include "chapter.h"
#include "menudialog.h"
#include "helper.h"
#include "dice.h"
#include "ZanbarBoneBackground.h"

NdsGameDialog::NdsGameDialog(const int argc, char* argv[])
  : m_key_pressed{-1},
    m_options{},
    m_screen_bottom{}
{
  consoleDemoInit();
  //consoleDebugInit(DebugDevice_NOCASH);
  consoleDebugInit(DebugDevice_CONSOLE);

  videoSetMode(MODE_FB0);
  vramSetBankA(VRAM_A_LCD);

  mmInitDefaultMem((mm_addr)soundbank_bin);

  consoleInit(&m_screen_bottom, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);

  consoleSelect(&m_screen_bottom);

  const Helper h;

  if (m_verbose) { h.CoutNl("Console mode initialized"); }

  if (m_verbose)
  {
    h.CoutNl("Test waiting: wait 1 second");
    h.Wait(1.0, m_verbose);
  }

  if (m_verbose)
  {
    h.Cout("Displaying the character x:"); h.Cout('x'); h.Cout('\n');
    h.Cout("Displaying the character Y:"); h.Cout('Y'); h.Cout('\n');
    h.Cout("Displaying the character 0:"); h.Cout('0'); h.Cout('\n');
  }

  if (m_verbose)
  {
    std::stringstream s;
    s << "argc:" << argc << '\n';
    for (int i=0; i!=argc; ++i)
    {
      s << "argv[" << i << "]:" << std::string(argv[i]) << '\n';
    }
    Helper().CoutNl(s.str());
  }

  if (m_verbose) { Helper().CoutNl("Drawing Zandar Bone picture"); }

  ZanbarBoneBackground().Draw(VRAM_A,0,0);

  if (m_verbose) { Helper().CoutNl("Done showing picture"); }
}


void NdsGameDialog::CharacterChanged(const Character &character)
{
  //Keep showing Zanbar Bone's head
  /*
  //The maximum x coordinat
  const int maxx = 256;
  //The maximum y coordinat
  const int maxy = 192;
  //The maximum R/G/B color value
  const int max_color = 32;
  //Counter for the scroll effect
  int z = character.GetCondition();
  for (int y=0; y!=maxy; ++y)
  {
    for (int x=0; x!=maxx; ++x)
    {
      VRAM_A[(y*maxx)+x]
        = RGB15(
          (x+z  ) % max_color,
          (y+z  ) % max_color,
          (x+y+z) % max_color);
    }
  }
  */
}

std::string NdsGameDialog::IntToKey(const int i) const
{
  switch (i)
  {
    case 0: return "^";
    case 1: return ">";
    case 2: return "V";
    case 3: return "<";
    case 4: return "X";
    case 5: return "A";
    case 6: return "B";
    case 7: return "Y";
    case 8: return "L";
    case 9: return "R";
    case 10: return "T";
    case 11: return "E";
    default: return " ";
  }
}

Option NdsGameDialog::RequestOption(const std::vector<Option>& options)
{
  if (m_verbose) { Helper().CoutNl(__func__); }

  swiWaitForVBlank();

  m_options = options;
  std::vector<int> valid_indices;
  const int n_options{static_cast<int>(options.size())};
  for (int i=0; i!=n_options; ++i)
  {
    valid_indices.push_back(i);
    std::stringstream text;
    text << "[" << IntToKey(i) << "] " << options[i].GetText() << '\n';
    ShowText(text.str());
  }
  if (n_options == 1) { return options[0]; }

  while(1)
  {
    ProcessEvents();

    if (m_key_pressed != -1)
    {
      int key_pressed = m_key_pressed;
      if (key_pressed >= 0 && key_pressed < static_cast<int>(options.size()))
      {
        m_key_pressed = -1;
        return options[key_pressed];
      }
      else
      {
        m_key_pressed = -1;
      }
    }
  }
}

void NdsGameDialog::ShowText(const std::string& text)
{
  if (m_verbose) { Helper().CoutNl(__func__); }

  consoleSelect(&m_screen_bottom);

  double wait_character_msec{0.01};

  const std::string lines = Helper().StrToLines(text,GetNumberOfCharsPerLine());
  for (const char c: lines)
  {
    scanKeys(); //Don't forget!
    const int keys_down = keysDown();
    if (keys_down) { wait_character_msec = 0.0; }

    Helper().Cout(c);
    Helper().Wait(wait_character_msec, m_verbose);
  }
}

void NdsGameDialog::Start()
{
  if (m_verbose) { Helper().CoutNl("MOD_69008_EXPERIENCE"); }
  if (m_verbose) { Helper().CoutNl(std::to_string(MOD_69008_EXPERIENCE)); }
  if (m_verbose) { Helper().CoutNl("Before disabled mmLoad"); }

  //mmLoad(MOD_69008_EXPERIENCE); //Causes a freeze

  if (m_verbose) { Helper().CoutNl("Before disabled mmStart"); }

  //mmStart(MOD_69008_EXPERIENCE,MM_PLAY_LOOP);

  if (m_verbose) { Helper().Cout(__func__); Helper().CoutNl(": 1"); }

  Dice::Get()->SetSeed(42);

  if (m_verbose) { Helper().CoutNl(__func__); Helper().CoutNl(": 2"); }

  MenuDialog menu;

  if (m_verbose) { Helper().CoutNl(__func__); Helper().CoutNl(": 3"); }

  menu.SetObserver(this);

  if (m_verbose) { Helper().CoutNl(__func__); Helper().CoutNl(": 4"); }

  menu.Execute();
}

void NdsGameDialog::ProcessEvents()
{
  if (m_verbose) { static int n = 0; Helper().Cout(std::to_string(n++)); Helper().CoutNl(__func__); }

  scanKeys(); //Don't forget!
  const int keys_down = keysDown();
  if (keys_down)
  {
    if (     keys_down & KEY_UP    ) { m_key_pressed =  0; }
    else if (keys_down & KEY_RIGHT ) { m_key_pressed =  1; }
    else if (keys_down & KEY_DOWN  ) { m_key_pressed =  2; }
    else if (keys_down & KEY_LEFT  ) { m_key_pressed =  3; }
    else if (keys_down & KEY_X     ) { m_key_pressed =  4; }
    else if (keys_down & KEY_A     ) { m_key_pressed =  5; }
    else if (keys_down & KEY_B     ) { m_key_pressed =  6; }
    else if (keys_down & KEY_Y     ) { m_key_pressed =  7; }
    else if (keys_down & KEY_L     ) { m_key_pressed =  8; }
    else if (keys_down & KEY_R     ) { m_key_pressed =  9; }
    else if (keys_down & KEY_START ) { m_key_pressed = 10; }
    else if (keys_down & KEY_SELECT) { m_key_pressed = 11; }
  }

  swiWaitForVBlank();
}


void NdsGameDialog::Wait()
{
  if (m_verbose) { Helper().CoutNl(__func__); }
  const double n_secs{1.0};
  const int n{static_cast<int>(n_secs * 200.0)};
  for (int i=0; i!=n; ++i)
  {
    swiWaitForVBlank();
    scanKeys(); //Don't forget!
    if (keysDown()) break;
  }
  if (m_verbose) { Helper().Cout("End of: "); Helper().CoutNl(__func__); }
}
