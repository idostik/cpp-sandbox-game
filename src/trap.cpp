#include "trap.h"
#include "block.h"

#define DAMAGE 30

Trap::Trap(BlockType icon, size_t posY, size_t posX)
{
  //trap can only represent higher value minerals
  if (static_cast<int>(icon) < 0)
    icon = BlockType::COAL;
  m_icon = getBlockIcon(icon);
  m_posY = posY;
  m_posX = posX;
  m_solid = true;
  m_climbable = false;
}

Trap::Trap(ifstream& ifs, size_t posY, size_t posX)
{
  //dummy and noskipws in case icon was ' ' (empty space)
  char icon, dummy;
  
  ifs >> noskipws >> dummy >> icon >> skipws;
  if(!ifs.good())
    throw invalid_argument("Save data are invalid");

  m_posY = posY;
  m_posX = posX;
  m_icon = icon;
  m_solid = true;
  m_climbable = false;
}

bool Trap::activate(Map& mp, Player& p, MainWindow& win)
{
  p.changeHealth(-DAMAGE);

  auto newTile = mp.changeTile(m_posY - 1, m_posX, make_shared<Block> (m_posY - 1, m_posX));
  if (newTile)
    newTile->display(win);
  newTile = mp.changeTile(m_posY + 1, m_posX, make_shared<Block> (m_posY + 1, m_posX));
  if (newTile)
    newTile->display(win);
  newTile = mp.changeTile(m_posY, m_posX - 1, make_shared<Block> (m_posY, m_posX - 1));
  if (newTile)
    newTile->display(win);
  newTile = mp.changeTile(m_posY, m_posX + 1, make_shared<Block> (m_posY, m_posX + 1));
  if (newTile)
    newTile->display(win);
  return true;
}

void Trap::serialize(ofstream& ofs) const
{
  //ORDER: type, icon
  ofs << "T\n" << static_cast<char>(m_icon) << endl; 
  if (!ofs.good())
    throw "Error while saving";
  return;
}

shared_ptr<Tile> Trap::clone() const
{
  return make_shared<Trap> (*this);
}