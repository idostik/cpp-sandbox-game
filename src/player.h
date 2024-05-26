#pragma once

#include "mainWindow.h"
#include "map.h"
#include "direction.h"
#include "entity.h"

#include <ncurses.h>
#include <utility>
#include <fstream>
#include <memory>

class Map;

/** @brief Player that can move on the map and interact with other Tiles on it. */
class Player : public Entity
{
public:
  /**
   * @brief Construct a new Player object.
   * 
   * @param[in] y value of 'y' coordinate.
   * @param[in] x value of 'x' coordinate.
   * @param[in] c icon that will be displayed as player in the MainWindow.
   * @param[in] win shared_ptr to the MainWindow where game will be displayed.
   * @param[in] mp shared_ptr to Map of the game.
   * @param[in] maxHealth max value of player's health.
   */
  Player(int y, int x, chtype c, shared_ptr<MainWindow> win, shared_ptr<Map> mp, int maxHealth);

  /**
   * @brief Construct a new Player object from a filestream.
   * 
   * @param[in] ifs input file stream from which Player will be constructed.
   * @param[in] win shared_ptr to the MainWindow where game will be displayed.
   * @param[in] mp shared_ptr to Map of the game.
   * @throws invalidArgument if error occured while reading from file.
   */
  Player(ifstream& ifs, shared_ptr<MainWindow> win, shared_ptr<Map> mp);

  Player(const Player& p) = default;

  Player& operator = (const Player& p) = default;

  /**
   * @brief Save Player object to the given output file stream.
   * 
   * @param[out] ofs output file stream to which Player will be saved.
   * throws invalidArgument if error occurs while saving to file stream.
   */
  void serialize(ofstream& ofs) const;

  /** @brief Reset player to the begining state. */
  void reset();

  /**
   * @brief Try to move in the given direction.
   * 
   * @param[in] dir direction in which to move.
   * @returns true if Player was able to move in the given Direction (no solid Tile was in the way),
   * false otherwise.
   */
  bool move(Direction dir);

  /**
   * @brief Try to mine in the given direction.
   * Activates Tile in the given direction (it can be a Trap, Enemy or just a regular Block).
   * 
   * @param[in] dir direction in which to mine.
   */
  void mine(Direction dir);

  /**
   * @brief Try to place ladder above Player.
   * 
   * @returns true if ladder can be placed, false otherwise.
   */
  bool placeLadder() const;

  /**
   * @brief Determine whether player should fall or not.
   * 
   * @returns true if Player should fall, false otherwise (he is standing on solid or climbable Tile).
   */
  bool shouldFall();

  /** Change player's health. */
  void changeHealth(int change);

  /** Change player's money. */
  void changeMoney(int change);

  /**
   * @brief Try to upgrade Player's pickaxe.
   * 
   * @returns true if Player has enough money, false otherwise.
   */
  bool upgradePickaxe();

  /**
   * @brief Try to refill Player's health.
   * 
   * @returns true if Player has enough money, false otherwise.
   */
  bool refillHealth();

  /** @returns Player's current health. */
  int getHealth() const;

  /** @returns Player's current money. */
  size_t getMoney() const;

  /** @returns Player's current pickaxeLvl. */
  size_t getPickaxeLvl() const;

  /** @returns Player's current pickaxePrice. */
  size_t getPickaxePrice() const;

  /** @returns amount of money needed for health refill. */
  size_t getHealthPrice() const;

private:
  /** @var shared_ptr to MainWindow Player should be displayed in. */
  shared_ptr<MainWindow> m_win;

  /** @var shared_ptr to Map Player moves in. */
  shared_ptr<Map> m_map;

  /** @var m_maxHealth max health Player can have. */
  /** @var m_health Player's current health. */
  int m_maxHealth, m_health;

  /** @var m_pickaxeLvl Player's current pickaxe level. */
  /** @var m_money Player's current amout of money. */
  size_t m_pickaxeLvl, m_money;
};
