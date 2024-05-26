#pragma once

#include <ncurses.h>

/** @brief List of all possible types a Block can have. */
enum class BlockType : int
{
  LADDER = -4,
  AIR = -3,
  DIRT = -2,
  ROCK = -1,
  COAL = 0,
  IRON = 1,
  GOLD = 2,
  PLATINUM = 3,
  DIAMOND = 4,
  LAST = 5,
};

/**
 * @brief Assigns each type an icon.
 * 
 * @param type type of the Block.
 * @returns chtype icon that should be displayed in MainWindow as this block.
 */
inline chtype getBlockIcon (BlockType type = BlockType::AIR)
{
  switch (type)
  {
    case BlockType::LADDER:
      return 'H';
    case BlockType::AIR:
      return ' ';
    case BlockType::DIRT:
      return 'D';
    case BlockType::ROCK:
      return 'R';
    case BlockType::COAL:
      return 'C';
    case BlockType::IRON:
      return 'I';
    case BlockType::GOLD:
      return 'G';
    case BlockType::PLATINUM:
      return 'P';
    case BlockType::DIAMOND:
      return '&';
    default:
      return '?';
  }
}
