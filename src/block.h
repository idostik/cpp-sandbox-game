#pragma once

#include "tile.h"
#include "blockType.h"
#include "map.h"
#include "player.h"

/** @brief Class representing material or a ladder in Map. */
class Block : public Tile
{
public:
  /**
   * @brief Construct a new Block object
   * 
   * Block atributes depend on the given type.
   * 
   * @param[in] posY 'y' coordinate
   * @param[in] posX 'x' coordinate
   * @param[in] type type of the created Block. 
   */
  Block(size_t posY, size_t posX, BlockType type = BlockType::AIR);

  /**
   * @brief Construct a new Block object from a given file stream.
   * 
   * @param[in] ifs filestream to read from
   * @param[in] posY 'x' coordinate of the Block in Map
   * @param[in] posX 'y' coordinate fo the Block in Map
   * @throws invalidArgument if error occurs while trying to read from file stream.
   */
  Block(ifstream& ifs, size_t posY, size_t posX);

  ~Block() = default;

  /**
   * @brief Try to mine this Block.
   * Give Player money based on value if successful.
   * Player needs to have big enough pickaxe level. 
   * 
   * @param[in, out] mp Map in which this block is.
   * @param[in, out] p Player that activated this Block.
   * @param[out] win MainWindow where the game is displayed.
   * @returns true if block was successfully mined, false otherwise. 
   */
  bool activate(Map& mp, Player& p, MainWindow& win) override;

  /**
   * @brief Try to serialize this Block into a given output file stream.
   * 
   * @param[out] ofs file stream in which Block should be serialized to.
   * @throws invalidArgument if error occurs while writing to the file stream.
   */
  void serialize(ofstream& ofs) const override;

  /** @returns shared_ptr to the copy of this Block. */
  virtual shared_ptr<Tile> clone() const override;

private:
  /** @var m_value value of this Block (how much money Player gets upon mining). */
  /** @var m_hardness how high does Player's pickaxe level need to be in order to mine this Block. */
  size_t m_value, m_hardness;
};