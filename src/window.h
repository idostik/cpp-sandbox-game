#pragma once

#include <ncurses.h>
#include <string>
#include <utility>

using namespace std;

/** @brief Wrapper class around ncurses WINDOW. */
class Window
{
public:
 /**
 * @brief Construct a new Window object.
 * 
 * @param[in] height height of the Window.
 * @param[in] width width of the Window
 * @param[in] startY 'y' coordinate of top left corner (starting position)
 * @param[in] startX 'x' coordinate fo top left corner
 */
  Window(int height, int width, int startY, int startX);

  Window(const Window& win) = delete;

  Window& operator = (const Window& win) = delete;

  virtual ~Window();

  void clear();

  /** @brief Display basic border around the window */
  void addBorder();

  /** @brief Refresh window, draw what's new to the screen */
  void redraw();

  /**
   * @brief Display given char to the given coordinates.
   * 
   * @param[in] y coordinate on the 'y' axis.
   * @param[in] x  coordinate on the 'x' axis.
   * @param[in] c char to be displayed.
   */
  void drawAt(int y, int x, chtype c);

  /**
   * @brief Read one char from the user.
   * 
   * @returns int value of the loaded char.
   */
  int inputChar();

  /**
   * @brief Read string from the user.
   * 
   * @returns string that was read. 
   */
  string inputStr();

  /**
   * @brief Get the dimensions of this window.
   * 
   * @returns pair (y, x) of dimensions of this window.
   */
  pair<size_t, size_t> getDimensions() const;

  /**
   * @brief Get coordinates of the top-left corner of this window (starting coordinates).
   * 
   * @returns pair (y, x) of coordinates.
   */
  pair<size_t, size_t> getStartingPos() const;

protected:
  /** @var m_win pointer to a ncurses WINDOW object. */
  WINDOW* m_win;

  /** @var m_height height of the Window. */
  /** @var m_width width of the Window. */
  /** @var m_startY 'y' coordinate of Window's top-left corner. */
  /** @var m_startX 'x' coordinate of Window's top-left corner. */
  int m_height, m_width, m_startY, m_startX;
};
