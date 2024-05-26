#include "map.h"
#include "block.h"
#include "trap.h"
#include "enemy.h"

#define AIR_LVL 2
#define DIRT_LVL 5

//defines how deep should better minerals spawn (higher value means deeper)
#define DEPTH_COEFICIENT 5
//probability of how likely it is for a better mineral (coal, iron, gold...) to spawn
#define SPECIAL_PROB 20
//how likely it is for trap to spawn instead of better mineral
#define TRAP_PROB 15
//how likely it is for enemy to spawn instead of better mineral
#define ENEMY_PROB 15
#define MAX_PROB 100

Map::Map (size_t boardHeight, size_t boardWidth) 
  : m_depth(boardHeight), m_width(boardWidth) 
{
  generate();
}

Map::Map (ifstream& ifs, size_t boardHeight, size_t boardWidth)
  : m_depth(boardHeight), m_width(boardWidth)
{
  m_map.resize(boardHeight);
  size_t posY, posX;
  posY = posX = 0;
  string type = "";

  while (posY < boardHeight && ifs >> type)
  {
    if (type == "B")
      m_map.at(posY).push_back(make_shared<Block> (ifs, posY, posX));
    else if (type == "T")
      m_map.at(posY).push_back(make_shared<Trap> (ifs, posY, posX)); 
    else if (type == "E")
      m_map.at(posY).push_back(make_shared<Enemy> (ifs, posY, posX)); 
    else
      throw invalid_argument("Save data are invalid");
    if (++posX >= boardWidth)
    {
      posX = 0;
      posY++;
    }
  }
  if (!ifs.good())
    throw invalid_argument("Save data are invalid");
}

Map::Map (const Map& map)
  : m_depth(map.m_depth), m_width(map.m_width)
{
  m_map.resize(m_depth);
  size_t posY = 0;
  for (auto row : map.m_map)
  {
    for (auto tile : row)
    {
      m_map[posY].push_back(tile->clone());
    }
    posY++;
  }
}

Map::~Map()
{
}

void Map::generate()
{
  m_map.clear();
  m_map.resize(m_depth);
  size_t posY = 0;
  //fill space above ground with air
  for (; posY < AIR_LVL; posY++)
    for (size_t posX = 0; posX < m_width; posX++)
      m_map[posY].push_back(make_shared<Block> (posY, posX));

  srand(time(0));
  BlockType basicType = BlockType::DIRT;

  for (; posY < m_depth; posY++)
  {
    if (posY > DIRT_LVL && basicType != BlockType::ROCK)
      basicType = BlockType::ROCK;
    size_t maxMineral = posY / DEPTH_COEFICIENT + 1;
    //check limit
    if (maxMineral > static_cast<int>(BlockType::LAST))
      maxMineral = static_cast<int>(BlockType::LAST);

    for (size_t posX = 0; posX < m_width; posX++)
    {
      size_t probability = rand() % MAX_PROB;
      if (probability < SPECIAL_PROB)
      {
        size_t typeNum = rand() % maxMineral;
        int specialBlockProb = rand() % MAX_PROB;
        //spawn better mineral or trap
        if (specialBlockProb < TRAP_PROB)
        {
          m_map[posY].push_back(make_shared<Trap> (static_cast<BlockType>(typeNum), posY, posX));
          continue;
        }
        else if (specialBlockProb < TRAP_PROB + ENEMY_PROB)
        {
          m_map[posY].push_back(make_shared<Enemy> (posY, posX));
          continue;
        }
        m_map[posY].push_back(make_shared<Block> (posY, posX, static_cast<BlockType>(typeNum)));
        continue;
      }
      //spawn basic mineral
      m_map[posY].push_back(make_shared<Block> (posY, posX, basicType));
    }
  }
}

void Map::print(MainWindow& win) const
{
  for (auto row : m_map)
    for (auto tile : row)
      tile->display(win);
}

void Map::serialize(ofstream& ofs) const
{
  for (auto row : m_map)
    for (auto tile : row)
      tile->serialize(ofs);

  if (!ofs.good())
    throw "Error while saving map";
  return;
}

size_t Map::getDepth() const
{
  return m_depth;
}

size_t Map::getWidth() const
{
  return m_width;
}

size_t Map::getAirLvl() const
{
  return AIR_LVL;
}

shared_ptr<Tile> Map::getTile(size_t y, size_t x)
{
  if (y >= m_depth || x >= m_width)
    return nullptr;
  return m_map.at(y).at(x);
}

shared_ptr<Tile> Map::changeTile(size_t y, size_t x, shared_ptr<Tile> newTile)
{
  if (y >= m_depth || x >= m_width)
    return nullptr;
  m_map.at(y).at(x) = newTile;
  return newTile;
}
