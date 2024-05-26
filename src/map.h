#pragma once

#include "tile.h"
#include "blockType.h"
#include "mainWindow.h"

#include <ncurses.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <memory>

using namespace std;

class Tile;

/** @brief Class storing all the Tiles that make the game board and are displayed in a MainWindow */
class Map 
{
public:
  /**
   * @brief Construct a new Map object.
   * 
   * @param[in] boardHeight how high should the Map be.
   * @param[in] boardWidth how tall wide should the Map be.
   */
  Map(size_t boardHeight, size_t boardWidth);

  /**
   * @brief Construct a new Map object from a given file stream.
   * 
   * @param[in] ifs 
   * @param[in] boardHeight how high should the Map be.
   * @param[in] boardWidth how wide should the Map be.
   */
  Map(ifstream& ifs, size_t boardHeight, size_t boardWidth);

  /**
   * @brief Construct a copy of existing Map.
   * 
   * @param[in] map reference to other already existing Map object.
   */
  Map(const Map& map);

  Map& operator = (const Map& map) = delete;

  ~Map();

  /**
   * @brief Pseudo randomly generate Tiles that fill the Map.
   * 
   * More valueable Blocks are generated at the bottom, cheaper ones closer to the top.
   * The top of the map is filled with air only. First few rows of ground are filled mainly with dirt, then rock.
   * Higher value minerals are more sparse. There is a chance a Trap or Enemy is generated instead of 
   * higher value mineral (Coal, Iron, ...)
   */
  void generate();

  /**
   * @brief Display the whole map to the given MainWindow.
   * 
   * @param[out] win MainWindow in which map should be printed.
   */
  void print(MainWindow& win) const;

  /**
   * @brief Serialize to the given output file stream.
   * 
   * @param[out] ofs file stream in which to serialize.
   * @throws invalidArgument if error occurs while writing to the stream.
   */
  void serialize(ofstream& ofs) const;

  /** @returns Map depth. */
  size_t getDepth() const;

  /** @returns Map width. */
  size_t getWidth() const;

  /** @returns how many rows were filled with air when game started. */
  size_t getAirLvl() const;

  /**
   * @brief Get tile at given coordinates.
   * 
   * @param[in] y 'y' axis coordinate
   * @param[in] x 'x' axis coordinate
   * @return shared_ptr to a Tile if it exists, nullptr otherwise.
   */
  shared_ptr<Tile> getTile(size_t y, size_t x);

  /**
   * @brief Replace Tile at specified coordinates with a new one.
   * 
   * @param[in] y 'y' axis coordinate
   * @param[in] x 'x' axis coordinate
   * @param[in, out] newTile shared_ptr to a new Tile that will replace the old one.
   * @return shared_ptr to a new Tile if it is valid, nullptr otherwise.
   */
  shared_ptr<Tile> changeTile(size_t y, size_t x, shared_ptr<Tile> newTile);

private:
  /** @var m_depth max depth (height) of the map */
  /** @var m_with max width of the map */
  size_t m_depth, m_width;

  /** @var 2D vector of shared_ptr's to Tiles. Outer vector represents row, inner column. */
  vector<vector<shared_ptr<Tile>>> m_map;
};
