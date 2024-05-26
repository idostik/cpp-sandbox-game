#include "enemy.h"

#define ENEMY_DAMAGE 10
#define ENEMY_REWARD 70

Enemy::Enemy(size_t posY, size_t posX, chtype icon, int hitPoints)
{
  m_icon = icon; 
  m_hitPoints = hitPoints;
  m_posY = posY;
  m_posX = posX;
  m_solid = true;
  m_climbable = false;
}

Enemy::Enemy(ifstream& ifs, size_t posY, size_t posX)
{
  // dummy and noskipws in case icon is ' ' (empty space)
  char icon, dummy;
  int hitPoints;

  ifs >> noskipws >> dummy >> icon >> skipws >> hitPoints;
  if (!ifs.good())
    throw invalid_argument("failed to load enemy");
  m_posY = posY;
  m_posX = posX;
  m_icon = icon;
  m_hitPoints = hitPoints;
  m_solid = true;
  m_climbable = false;
}
  
bool Enemy::activate(Map& mp, Player& p, MainWindow& win)
{
  if (m_hitPoints > 0)
  {
    p.changeHealth(-ENEMY_DAMAGE);
    m_hitPoints--;
    return false;
  }
  p.changeMoney(ENEMY_REWARD);
  return true;
}

void Enemy::serialize(ofstream& ofs) const
{
  //ORDER: type, icon, hitPoints
  ofs << "E\n" << static_cast<char>(m_icon) << " " << m_hitPoints << endl; 

  if (!ofs.good())
    throw "Error while saving";
  return;
}

shared_ptr<Tile> Enemy::clone() const
{
  return make_shared<Enemy> (*this);
}