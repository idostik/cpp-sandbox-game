#include "tile.h"

bool Tile::isSolid() const
{
  return m_solid;
}

bool Tile::isClimbable() const
{
  return m_climbable;
}

chtype Tile::getIcon() const
{
  return m_icon;
}
