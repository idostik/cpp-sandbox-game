#include "block.h"

Block::Block(size_t posY, size_t posX, BlockType type)
{
  m_posY = posY;
  m_posX = posX;
  m_icon = getBlockIcon(type);

  //assign values based on the exact type
  switch(type)
  {
    case BlockType::LADDER:
      m_solid = false;
      m_climbable = true;
      m_value = m_hardness = 0;
      break;
    case BlockType::DIRT:
      m_solid = true;
      m_climbable = false;
      m_value = m_hardness = 1;
      break;
    case BlockType::ROCK:
      m_solid = true;
      m_climbable = false;
      m_value = 3;
      m_hardness = 2;
      break;
    case BlockType::COAL:
      m_solid = true;
      m_climbable = false;
      m_value = 10;
      m_hardness = 2;
      break;
    case BlockType::IRON:
      m_solid = true;
      m_climbable = false;
      m_value = 20;
      m_hardness = 3;
      break;
    case BlockType::GOLD:
      m_solid = true;
      m_climbable = false;
      m_value = 50;
      m_hardness = 3;
      break;
    case BlockType::PLATINUM:
      m_solid = true;
      m_climbable = false;
      m_value = 150;
      m_hardness = 4;
      break;
    case BlockType::DIAMOND:
      m_solid = true;
      m_climbable = false;
      m_value = 400;
      m_hardness = 5;
      break;
    default:
    case BlockType::AIR:
      m_solid = false;
      m_climbable = false;
      m_value = m_hardness = 0;
  }
}

Block::Block(ifstream& ifs, size_t posY, size_t posX)
{
  char icon;
  char dummy; //to remove newline character, 
  bool solid, climbable;
  size_t value, hardness;

  //noskipws needs to be there in case block icon is ' ' (empty space)
  ifs >> noskipws >> dummy >> icon >> skipws >> solid >> climbable >> value >> hardness;
  if (!ifs.good())
    throw invalid_argument("failed to load block");
  m_posY = posY;
  m_posX = posX;
  m_icon = icon;
  m_solid = solid;
  m_climbable = climbable;
  m_value = value;
  m_hardness = hardness;
}

bool Block::activate(Map& mp, Player& p, MainWindow& win)
{
  if (p.getPickaxeLvl() < m_hardness)
    return false;
  p.changeMoney(m_value);
  return true;
}

void Block::serialize(ofstream& ofs) const
{
  //ORDER: type, icon, solid, climbable, value, hardness
  ofs << "B\n" << static_cast<char>(m_icon) << " " << m_solid << " " << m_climbable
  << " " << m_value << " " << m_hardness << endl; 

  if (!ofs.good())
    throw "ERROR after saving block";
  return;
}

shared_ptr<Tile> Block::clone() const
{
  return make_shared<Block> (*this);
}