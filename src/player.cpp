#include "player.h"
#include "block.h"

#include <cmath>

#define PICKAXE_PRICE 40
#define HEALTH_PRICE 30
#define PICKAXE_PRICE_COEFICIENT 2.2
#define STARTING_PICKAXE_LVL 1
#define STARTING_MONEY 0

Player::Player(int y, int x, chtype c, shared_ptr<MainWindow> win, shared_ptr<Map> mp, int maxHealth)
  : Entity(c, y, x),  m_win(win), m_map(mp), m_maxHealth(maxHealth), m_health(maxHealth),
    m_pickaxeLvl(STARTING_PICKAXE_LVL), m_money(STARTING_MONEY)
{
}

Player::Player(ifstream& ifs, shared_ptr<MainWindow> win, shared_ptr<Map> mp)
{
  //order in file: posY, posX, icon, maxHealth, health, pickaxeLvl, money
  int posY, posX, maxHealth, health;
  char icon;
  size_t pickaxeLvl, money;

  ifs >> posY >> posX >> icon >> maxHealth >> health >> pickaxeLvl >> money;
  if (!ifs.good())
    throw invalid_argument("Save data are invalid");
  m_win = win;
  m_map = mp;
  m_posY = posY;
  m_posX = posX;
  m_icon = icon;
  m_maxHealth = maxHealth;
  m_health = health;
  m_pickaxeLvl = pickaxeLvl;
  m_money = money;
}

void Player::serialize(ofstream& ofs) const
{
  //ORDER: type, posY, posX, icon, maxHealth, health, pickaxeLvl, money
  ofs << "P\n" << m_posY << " " << m_posX << " " << static_cast<char>(m_icon) << " "
  << m_maxHealth << " " << m_health << " " << m_pickaxeLvl << " " << m_money << endl; 

  if (!ofs.good())
    throw "Error while saving";
  return;
}

void Player::reset()
{
  m_posY = m_posX = 1;
  m_health = m_maxHealth;
  m_pickaxeLvl = 1; 
  m_money = 0;
}

bool Player::move(Direction dir)
{
  //display the tile player is standing on
  m_map->getTile(m_posY, m_posX)->display(*m_win);

  shared_ptr<Tile> neighbour = nullptr;
  switch (dir)  
  {
    case Direction::LEFT:
      neighbour = m_map->getTile(m_posY, m_posX - 1);
      if (!neighbour || neighbour->isSolid())
        return false;
      m_posX -= 1;
      break;
    case Direction::RIGHT:
      neighbour = m_map->getTile(m_posY, m_posX + 1);
      if (!neighbour || neighbour->isSolid())
        return false;
      m_posX += 1;
      break;
    case Direction::UP:
      neighbour = m_map->getTile(m_posY - 1, m_posX);
      if (!neighbour || !neighbour->isClimbable()) 
        return false;
      m_posY -= 1;
      break;
    case Direction::DOWN:
      neighbour = m_map->getTile(m_posY + 1, m_posX);
      if (!neighbour || neighbour->isSolid())
        return false;
      m_posY += 1;
      break;
    default:
      return false;
  }
  display(*m_win);
  return true;
}

void Player::mine(Direction dir)
{
  shared_ptr<Tile> toMine = nullptr;
  switch(dir)
  {
    case Direction::UP:
      toMine = m_map->getTile(m_posY - 1, m_posX);
      if (toMine && toMine->activate(*m_map, *this, *m_win))
        m_map->changeTile(m_posY - 1, m_posX, make_shared<Block> (m_posY - 1, m_posX))->display(*m_win);
      break;
    case Direction::DOWN:
      toMine = m_map->getTile(m_posY + 1, m_posX);
      if (toMine && toMine->activate(*m_map, *this, *m_win))
        m_map->changeTile(m_posY + 1, m_posX, make_shared<Block> (m_posY + 1, m_posX))->display(*m_win);
      break;
    case Direction::RIGHT:
      toMine = m_map->getTile(m_posY, m_posX + 1);
      if (toMine && toMine->activate(*m_map, *this, *m_win))
        m_map->changeTile(m_posY, m_posX + 1, make_shared<Block> (m_posY, m_posX + 1))->display(*m_win);
      break;
    case Direction::LEFT:
      toMine = m_map->getTile(m_posY, m_posX - 1);
      if (toMine && toMine->activate(*m_map, *this, *m_win))
        m_map->changeTile(m_posY, m_posX - 1, make_shared<Block> (m_posY, m_posX - 1))->display(*m_win);
      break;
  }
}

bool Player::placeLadder() const
{
  auto above = m_map->getTile(m_posY - 1, m_posX);
  if(!above || above->isSolid())
    return false;
  m_map->changeTile(m_posY - 1, m_posX, make_shared<Block> (m_posY - 1, m_posX, BlockType::LADDER))->display(*m_win);
  return true;
}

bool Player::shouldFall()
{
  auto underneath = m_map->getTile(m_posY, m_posX);
  //check if player is on a ladder
  if (underneath && underneath->isClimbable())
    return false;

  auto below = m_map->getTile(m_posY + 1, m_posX);
  if (below && !below->isSolid())
    return true;
  return false;
}

void Player::changeHealth(int change)
{
  m_health += change;
}

void Player::changeMoney(int change)
{
  m_money += change;
}

bool Player::upgradePickaxe()
{
  size_t pickaxePrice = getPickaxePrice();
  if (m_money < pickaxePrice)
    return false;  
  m_pickaxeLvl++;
  m_money -= pickaxePrice;
  return true;
}

bool Player::refillHealth()
{
  if (m_money < HEALTH_PRICE)
    return false;  
  m_health = m_maxHealth;
  m_money -= HEALTH_PRICE;
  return true;
}

int Player::getHealth() const
{
  return m_health;
}

size_t Player::getMoney() const
{
  return m_money;
}

size_t Player::getPickaxeLvl() const
{
  return m_pickaxeLvl;
}

size_t Player::getPickaxePrice() const
{
  return PICKAXE_PRICE * pow(PICKAXE_PRICE_COEFICIENT, m_pickaxeLvl);
}

size_t Player::getHealthPrice() const
{
  return HEALTH_PRICE;
}
