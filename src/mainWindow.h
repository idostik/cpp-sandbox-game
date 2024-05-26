#pragma once

#include "window.h"

#include <string>

/** @brief Main Window with the game board and player */
class MainWindow : public Window
{
public:
 /**
 * @brief Construct a new Main Window object.
 * 
 * @param[in] height height of the MainWindow.
 * @param[in] width width of the MainWindow.
 * @param[in] startY 'y' coordinate of top left corner.
 * @param[in] startX 'x' coordinate of top left corner.
 */
  MainWindow(int height, int width, int startY, int startX);

  MainWindow(const MainWindow& mainWin) = delete;

  MainWindow& operator = (const MainWindow& mainWin) = delete;

  /** @brief Display info how to play the game. */
  void displayHelp();

  /** @brief Draw menu screen, change ncurses input proccessing settings. */
  void openMenu();

  /** @brief Erase menu screen, change ncurses input proccessing settings back. */
  void closeMenu();

  /** @brief Display Game Over screen with instructions. */
  void displayGameOverScr();

  /**
   * @brief Print the given string to the screen as menu output after a command.
   * 
   * @param[in] str string that should be displayed.
   */
  void menuOutput(string str);

  /** @brief Clear input line and reset cursor pos to the begining. */
  void resetInput();

private:
  /** @var m_commandPos coordinates of menu input line. */
  /** @var m_outputPos coordinates of menu output line. */
  pair<int, int> m_commandPos, m_outputPos;
};