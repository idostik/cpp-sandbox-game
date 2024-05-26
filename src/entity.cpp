#include "entity.h"

Entity::Entity()
  : m_icon(' '), m_posY(0), m_posX(0)
{
}

Entity::Entity(chtype icon, int posY, int posX)
  : m_icon(icon), m_posY(posY), m_posX(posX)
{
}

void Entity::display(Window& win) const
{
  win.drawAt(m_posY, m_posX, m_icon);
}

pair<size_t, size_t> Entity::getPos() const
{
  return pair(m_posY, m_posX);
}
