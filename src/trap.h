#pragma once

#include "tile.h"
#include "blockType.h"
#include "map.h"
#include "player.h"

/** @brief Tile that disguises as other Block but explodes on activation. */

class Trap : public Tile
{
public:
  /**
   * @brief Construct a new Trap object.
   * 
   * @param[in] icon icon that will be displayed in game as this trap.>
   * @param[in] posY 'y' coordinate.
   * @param[in] posX 'x' coordinate.
   */
  Trap(BlockType icon, size_t posY, size_t posX);

  /**
   * @brief Construct a new Trap object from file stream.
   *  
   * @param[in] ifs input file stream to read from.
   * @param[in] posY 'y' coordinate.
   * @param[in] posX 'x' coordinate.
   * @throws invalidArgument if error occurs while reading from file stream.
   */
  Trap(ifstream& ifs, size_t posY, size_t posX);

  ~Trap() = default;

  /**
   * @brief Deal damage to Player and destroy surrounding Tiles.
   * 
   * @param[in, out] mp Map in which this Trap is.
   * @param[in, out] p Player that activated this Trap.
   * @param[out] win MainWindow where the game is displayed.
   * @return true 
   * @return false 
   */
  bool activate(Map& mp, Player& p, MainWindow& win) override;

  /**
   * @brief Serialize to output file stream.
   * 
   * @param[out] ofs output file stream to which Trap should be serialized.
   * @throws invalidArgument if error occurs while writing to filestream.
   */
  void serialize(ofstream& ofs) const override;

  /**
   * @brief Copy this Trap.
   * 
   * @return shared_ptr to a copy of this Trap.
   */
  virtual shared_ptr<Tile> clone() const override;
};