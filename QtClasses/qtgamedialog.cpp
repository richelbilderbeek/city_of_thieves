#include "qtgamedialog.h"

#include <QKeyEvent>
#include <QTimer>
#include <QTextCursor>

#include <boost/lexical_cast.hpp>

#include "ui_qtgamedialog.h"
#include "chapter.h"
#include "menudialog.h"
#include "helper.h"
#include "dice.h"

QtGameDialog::QtGameDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtGameDialog),
  m_key_pressed{-1},
  m_options{}
{
  ui->setupUi(this);

  Dice::Get()->SetSeed(42);

  #ifdef QT5_TODO_FIND_CORRECT_DEFINE
  QTimer::singleShot(100,Qt::VeryCoarseTimer,this,SLOT(Start()));
  #else
  QTimer::singleShot(100,this,SLOT(Start()));
  #endif
}

QtGameDialog::~QtGameDialog()
{
  delete ui;
}

void QtGameDialog::keyPressEvent(QKeyEvent * e)
{
  int key_pressed = e->key();
  if (key_pressed == Qt::Key_Escape) close();
  m_key_pressed = 999;
  if (m_options.size() > 0 && key_pressed == Qt::Key_0) { m_key_pressed = 0; return; }
  if (m_options.size() > 1 && key_pressed == Qt::Key_1) { m_key_pressed = 1; return; }
  if (m_options.size() > 2 && key_pressed == Qt::Key_2) { m_key_pressed = 2; return; }
  if (m_options.size() > 3 && key_pressed == Qt::Key_3) { m_key_pressed = 3; return; }
  if (m_options.size() > 4 && key_pressed == Qt::Key_4) { m_key_pressed = 4; return; }
  if (m_options.size() > 5 && key_pressed == Qt::Key_5) { m_key_pressed = 5; return; }
  if (m_options.size() > 6 && key_pressed == Qt::Key_6) { m_key_pressed = 6; return; }
  if (m_options.size() > 7 && key_pressed == Qt::Key_7) { m_key_pressed = 7; return; }
  if (m_options.size() > 8 && key_pressed == Qt::Key_8) { m_key_pressed = 8; return; }
  if (m_options.size() > 9 && key_pressed == Qt::Key_9) { m_key_pressed = 9; return; }
  if (m_options.size() > 10 && key_pressed == Qt::Key_A) { m_key_pressed = 10; return; }
  if (m_options.size() > 11 && key_pressed == Qt::Key_B) { m_key_pressed = 11; return; }
  if (m_options.size() > 12 && key_pressed == Qt::Key_C) { m_key_pressed = 12; return; }
  if (m_options.size() > 13 && key_pressed == Qt::Key_D) { m_key_pressed = 13; return; }
  if (m_options.size() > 14 && key_pressed == Qt::Key_E) { m_key_pressed = 14; return; }
  if (m_options.size() > 15 && key_pressed == Qt::Key_F) { m_key_pressed = 15; return; }
  if (m_options.size() > 16 && key_pressed == Qt::Key_G) { m_key_pressed = 16; return; }
  if (m_options.size() > 17 && key_pressed == Qt::Key_H) { m_key_pressed = 17; return; }
  assert(m_options.size() < 19);
}

void QtGameDialog::CharacterChanged(const Character &character)
{
  ui->label_condition->setText(
    (
      std::string("Condition: ")
    + std::to_string(character.GetCondition())
    + "/"
    + std::to_string(character.GetInitialCondition())
    ).c_str()
  );
  ui->label_skill->setText(
    (
      std::string("Skill: ")
    + std::to_string(character.GetSkill())
    + "/"
    + std::to_string(character.GetInitialSkill())
    ).c_str()
  );
  ui->label_luck->setText(
    (
      std::string("Luck: ")
    + std::to_string(character.GetLuck())
    + "/"
    + std::to_string(character.GetInitialLuck())
    ).c_str()
  );
  ui->label_gold->setText(
    (
      std::string("Gold: ")
    + std::to_string(character.GetGold())
    ).c_str()
  );
  ui->label_provisions->setText(
    (
      std::string("Provisions: ")
    + std::to_string(character.GetProvisions())
    ).c_str()
  );
  ui->list_items->clear();
  {
    //std::stringstream text;
    //text << "Items:\n";
    for (const auto item: character.GetItems())
    {
      if (static_cast<int>(item) < 100)
      {
        ui->list_items->addItem(ToPrettyStr(item).c_str());
        //text << " * " << ToPrettyStr(item) << "\n";
      }
    }
    //std::string s{text.str()}; s.pop_back(); //Remove newline at end
    //ui->label_items->setText(s.c_str());
  }
}

Option QtGameDialog::RequestOption(const std::vector<Option>& options)
{
  m_options = options;
  std::vector<int> valid_indices;
  const int n_options{static_cast<int>(options.size())};
  for (int i=0; i!=n_options; ++i)
  {
    valid_indices.push_back(i);
    std::stringstream text;
    text << "[" << i << "] " << options[i].GetText() << '\n';
    ShowText(text.str());
  }
  if (n_options == 1) { return options[0]; }

  m_key_pressed = -1;

  while(1)
  {
    qApp->processEvents();
    if (m_key_pressed != -1)
    {
      int key_pressed = m_key_pressed;
      assert(key_pressed >= 0);
      assert(key_pressed < static_cast<int>(options.size()));
      m_key_pressed = -1;
      return options[key_pressed];
    }
  }
}

void QtGameDialog::ShowText(const std::string& text)
{
  QTextCursor d(ui->plainTextEdit->textCursor());

  #ifdef NDEBUG
  double waiting_time{0.01}; //Only have suspense in release mode
  #else
  double waiting_time{0.00}; //No suspense in debug mode
  #endif

  for (const char c: text)
  {
    const std::string s{boost::lexical_cast<std::string>(c)};
    d.insertText(s.c_str());
    Helper().Wait(waiting_time);
    //TODO: Speed up text display when user presses a key
    //This approach does not work:
    if (m_key_pressed != -1)
    {
      waiting_time = 0.0;
      m_key_pressed = -1;
    }
    ui->plainTextEdit->moveCursor(QTextCursor::End);
    qApp->processEvents();
  }
}

void QtGameDialog::Wait()
{
  #ifdef NDEBUG
  Helper().Wait(1.0); //Only have suspense in release mode
  #endif
}

void QtGameDialog::Start()
{
  MenuDialog menu;

  menu.SetObserver(this);

  menu.Execute();

  close();
}
