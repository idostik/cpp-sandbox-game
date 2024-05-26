#pragma once

#include "map.h"
#include "player.h"
#include "window.h"
#include "statusBar.h"
#include "mainWindow.h"

#include <string>
#include <ostream>
#include <ncurses.h>
#include <stdexcept>
#include <memory>

using namespace std;

/** @brief Class handling the game state. */
class Game
{
public:
  /** 
   * @brief Initialize map, player and windows. Display game manual.
   * 
   * Windows are centered in the middle of the screen.
   * 
   * @throws invalidArgument "Terminal size is to small" if the game is too big for the terminal.
  */
  Game();

  ~Game();

  Game(const Game& game) = delete;

  Game& operator = (const Game& game) = delete;

  /** @brief After user presses any key, display game board and status bar */
  void start();

  /** @brief Display Game Over screen and reset the game after player presses spacebar */
  void gameOver();

  /** 
   * @brief Check if game has ended
   * @returns true if game has ended, false otherwise.
  */
  bool hasEnded() const;
  
  /** 
   * @brief Read player input and react on it.
   * 
   * Controls:
   *  - Arrows: move player
   *  - 'w', 's', 'a', 'd': mine adjacent blocks (in according direction)
   *  - 't': place ladder above player
   *  - 'm': open menu
  */
  void proccesInput();

  /**
   * @brief Open main menu, read user input and react on it.
   * 
   * Read input until user returns back to game or quits the game.
   * 
   * Possible commands:
   * 
   *  - "upgrade-pickaxe": upgrade pickaxe, if player has enough money and is at the top of the map
   *  - "quit": quit the game
   *  - "return": close main menu and display game board
   *  - "refill-health": refill player health, if he has enough money and is at the top of the map
   *  - "save [file name]": save the current game state into a give file
   *  - "load [file name]": load game from a given file
   */
  void proccesMenuInput();

  /**
   * @brief Display what changed from the last update.
   * 
   * If player has nothing to stand on, make him fall and take damage.
   * Update StatusBar,  MainWindow and display Player.
   * Handle player death.
   */
  void update();

  /**
   * @brief Try to save the game to a file with a given name.
   * 
   * @throws invalidArgument if error occurs while trying to save.
   * @param[in] fileName name of the file the game should be saved to.
   */
  void save(const string& fileName) const;
  
  /**
   * @brief Try to load the game from a file with a given name.
   * 
   * @throws invalidArgument if error occurs while trying to load the game.
   * @param[in] fileName  name of the file the game should be loaded from.
   */
  void load(const string& fileName);

private:
  /** @var shared_ptr to the main game window displaying game. */
  shared_ptr<MainWindow> m_mainWin;

  /** @var shared_ptr to the map that stores invidual blocks. */
  shared_ptr<Map> m_map;

  /** @var shared_ptr to the Player. */
  shared_ptr<Player> m_player;
  
  /** @var shared_ptr to the Window displaying status bar. */
  shared_ptr<StatusBar> m_statusWin;

  /** @var bool saying if the game should still be running or not */
  bool m_hasEnded;
};
