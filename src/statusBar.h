#pragma once

#include "window.h"

/** 
 * @brief Window displaying player's status bar. 
 *  
 * Displays player's health on the left side, depth in the middle
 * and money on the right side.
*/
class StatusBar : public Window
{
public:
/**
 * @brief Construct a new Status Bar object.
 * 
 * @param[in] height height of the StatusBar.
 * @param[in] width Width of the StatusBar.
 * @param[in] startY 'y' coordinate of top left corner.
 * @param[in] startX 'x' coordinate of top left corner.
 */
  StatusBar(int height, int width, int startY, int startX);

  StatusBar(const StatusBar& statusBar) = delete;

  StatusBar operator = (const StatusBar& statusBar) = delete;

  /** @brief Display description to the values shown. (eg. "depth:") */
  void displayDescrition();

  /**
   * @brief Display given number as player's health.
   * 
   * @param[in] num  value to be displayed as player's health.
   */
  void displayHealth(int num);

  /**
   * @brief Display given number as player's money.
   * 
   * @param[in] num  value to be displayed as player's money.
   */
  void displayMoney(size_t num);

  /**
   * @brief Display given number as player's depth.
   * 
   * @param[in] num  value to be displayed as the depth player is at.
   */
  void displayDepth(size_t num);

private:
  /** @var m_hpPos 'x' axis coordinate where hp should be displayed. */
  /** @var m_moneyPos 'x' axis coordinate where money should be displayed. */
  /** @var m_depthPos 'x' axis coordinate where depth should be displayed. */
  size_t m_hpPos, m_moneyPos, m_depthPos;
};