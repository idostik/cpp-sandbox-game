#include "mainWindow.h"

MainWindow::MainWindow(int height, int width, int startY, int startX)
  : Window(height, width, startY, startX)
{
  m_commandPos.first = m_commandPos.second= 0;
}

void MainWindow::displayHelp()
{
  string manual = 
  "Welcome to my Sandbox Game!\n\n"
  "Controls\n"
  "Move: arrows\n"
  "Mine: a,w,s,d\n"
  "Place ladder: t\n"
  "Open menu: m\n\n"
  "Press any key to start the game."
  ;
  wmove(m_win, 0, 0);
  wprintw(m_win, manual.c_str());
}

void MainWindow::openMenu()
{
  clear();
  echo(); //display player input
  curs_set(1); //display cursor
  nocbreak(); //enable line buffering

  string helpText =
  "MENU\n\n"
  "commands:\n"
  "upgrade-pickaxe\n"
  "refill-health\n"
  "save [file name]\n"
  "load [file name]\n"
  "return\n"
  "quit\n\n"
  ">"
  ;
  wmove(m_win, 0, 0);
  wprintw(m_win, helpText.c_str());

  //set where user will type and where output will be displayed
  getyx(m_win, m_commandPos.first, m_commandPos.second);
  m_outputPos.first = m_commandPos.first + 1;
  m_outputPos.second = m_commandPos.second;
}

void MainWindow::closeMenu()
{
  clear();
  noecho(); //don't display what user inputs
  curs_set(0); //hide cursor
  cbreak(); //disable line buffering
  redraw();
}

void MainWindow::displayGameOverScr()
{
  clear();
  string gameOverText = 
  "YOU DIED\n\n"
  "press space to restart the game"
  ;
  wmove(m_win, 0, 0);
  wprintw(m_win, gameOverText.c_str());
}

void MainWindow::resetInput()
{
  wmove(m_win, m_commandPos.first, m_commandPos.second);
  wclrtoeol(m_win);
  wmove(m_win, m_commandPos.first, m_commandPos.second);
}

void MainWindow::menuOutput(string str)
{
  wmove(m_win, m_outputPos.first, m_outputPos.second);
  wclrtoeol(m_win);
  wmove(m_win, m_outputPos.first, m_outputPos.second);
  wprintw(m_win, str.c_str());
}