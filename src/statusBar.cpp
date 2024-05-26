#include "statusBar.h"

#include <string>

#define HP_POS 4
#define MONEY_POS_OFFSET 5

StatusBar::StatusBar(int height, int width, int startY, int startX) 
  : Window(height, width, startY, startX)
{
  m_hpPos = HP_POS;
  m_depthPos = width/2 + 2;
  m_moneyPos = width - MONEY_POS_OFFSET;
}

void StatusBar::displayDescrition()
{
  wmove(m_win, 0, m_hpPos - 3);
  wprintw(m_win, "HP:");
  displayHealth(0);
  wmove(m_win, 0, m_depthPos - 6);
  wprintw(m_win, "Depth:");
  displayDepth(0);
  wmove(m_win, 0, m_moneyPos - 2);
  wprintw(m_win, "$:");
  displayMoney(0);
}

void StatusBar::displayHealth(int num)
{
  
  wmove(m_win, 0, m_hpPos);
  //spaces at the end to delete '0' when going from 100 to 10
  wprintw(m_win, (std::to_string(num) + " ").c_str()); 
}

void StatusBar::displayMoney(size_t num)
{
  wmove(m_win, 0, m_moneyPos);
  //spaces at the end to delete '0' when going from 100 to 10
  wprintw(m_win, (std::to_string(num) + "  ").c_str());
}

void StatusBar::displayDepth(size_t num)
{
  wmove(m_win, 0, m_depthPos);
  //spaces at the end to delete '0' when going from 100 to 10
  wprintw(m_win, (std::to_string(num) + "  ").c_str());
}