#pragma once

#include "window.h"

#include <ncurses.h>

/** @brief Class representing game object displayable in a Window. */

class Entity
{
public:
  Entity();

  /**
   * @brief Construct a new Entity object
   * 
   * @param[in] icon icon that will be displayed in game as this Entity.
   * @param[in] posY 'y' coordinate.
   * @param[in] posX 'x' coordinate.
   */
  Entity(chtype icon, int posY, int posX);

  /**
   * @brief Display this Entity at its coordinates in a given Window.
   * 
   * @param[out] win Window in which this Entity should be displayed.
   */
  void display(Window& win) const;

  /**
   * @brief Get the coordinates of this Entity.
   * 
   * @returns pair (posY, posX)  pair of cooridnates.
   */
  pair<size_t, size_t> getPos() const;

protected:
  /** @var chtype that will be displayed in Window as this Entity */
  chtype m_icon;

  /** @var m_posY 'y' coordinate  */
  /** @var m_posX 'x' coordinate  */
  size_t m_posY, m_posX;
};
