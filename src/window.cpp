#include "window.h"

#define MAX_STR_LEN 30

Window::Window(int height, int width, int startY, int startX)
  : m_height(height), m_width(width), m_startY(startY), m_startX(startX)
{
  m_win = newwin(m_height, m_width, m_startY, m_startX);
  keypad(m_win, true);
}

Window::~Window()
{
  clear();
  delwin(m_win);
}
void Window::clear()
{
  wclear(m_win);
}

void Window::addBorder()
{
  box(m_win, 0, 0);
}

void Window::redraw()
{
  wrefresh(m_win);
}

void Window::drawAt(int y, int x, const chtype c)
{
  wmove(m_win, y, x);
  waddch(m_win, c);
}


int Window::inputChar()
{
  return wgetch(m_win);
}

string Window::inputStr()
{
  char input[MAX_STR_LEN + 1];
  wgetnstr(m_win, input, MAX_STR_LEN);
  return input;
}

pair<size_t, size_t> Window::getDimensions() const
{
  return pair(m_height, m_width);
}

pair<size_t, size_t> Window::getStartingPos() const
{
  return pair(m_startY, m_startX);
}
