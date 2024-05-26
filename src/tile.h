#pragma once

#include "player.h"
#include "map.h"
#include "entity.h"
#include "mainWindow.h"

#include <ncurses.h>
#include <fstream>
#include <memory>

class Player;
class Map;

/** @brief Abstract class representing individual Tiles in map. */
class Tile : public Entity
{
public:
  virtual ~Tile() = default;

  /**
   * @brief Abstract method that activates this Tile. Depends on specific type.
   * 
   * @param[in, out] mp Map that the tile is in.
   * @param[in, out] p Player that activated the Tile.
   * @param[out] win Main window in which the Tile is displayed.
   * @returns true if this Tile should be destroyed after.
   */
  virtual bool activate(Map& mp, Player& p, MainWindow& win) = 0;

  /**
   * @brief Serialize this Tile in a given filesteream.
   * 
   * @param[out] ofs output filestream in which Tile should be serialized.
   * @throws invalidArgument if error occurrs while writing to the filestream.
   */
  virtual void serialize(ofstream& ofs) const = 0;

  /**
   * @brief Create a copy of this Tile
   * 
   * @returns shared_ptr to a copy of this Tile.
   */
  virtual shared_ptr<Tile> clone() const = 0;

  /** @returns true if Tile is solid, false otherwise. */
  bool isSolid() const;

  /** @return true if Tile is climbable, false otherwise. */
  bool isClimbable() const;

  /** @returns icon that represents this tile in a Map. */
  chtype getIcon() const;

protected:
  /** @var m_solid bool saying if Tile is solid or not */
  /** @var m_climbable bool saying if Tile is clibmable or not */
  bool m_solid, m_climbable;
};

