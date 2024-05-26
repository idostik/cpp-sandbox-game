#include "tile.h"

#define DEFAULT_ENEMY_ICON 'X'
#define DEFAULT_ENEMY_HP 3

/** @brief Class reperesenting Enemy that can hurt Player */
class Enemy : public Tile
{
public:

  /**
   * @brief Construct a new Enemy object.
   * 
   * @param[in] posY 'y' coordinate.
   * @param[in] posX 'x' coordinate.
   * @param[in] icon icon that will be displayed in game as this Enemy.
   * @param[in] hitPoints health.
   */
  Enemy(size_t posY, size_t posX, chtype icon = DEFAULT_ENEMY_ICON, int hitPoints = DEFAULT_ENEMY_HP);

  /**
   * @brief Construct a new Enemy object from file stream
   * 
   * @param[in] ifs file stream to read from.
   * @param[in] posY 'x' coordinate.
   * @param[in] posX 'y' coordinate.
   * @throws invalidArgument if error occurs while readin from file stream.
   */
  Enemy(ifstream& ifs, size_t posY, size_t posX);

  /**
   * @brief Hit Enemy, deal damage to Player.
   * Give Player reward after activation with no remaining hitPoints.
   * 
   * @param[in] mp Map in which this Enemy is.
   * @param[in, out] p Player that hit this Enemy.
   * @param[out] win MainWindow in which everything is displayed.
   * @returns true if Enemy has no m_hitpoints left (<= 0).
   */
  bool activate(Map& mp, Player& p, MainWindow& win) override;

  /**
   * @brief Serialize into output file stream.
   * 
   * @param[out] ofs file stream in which to serealize.
   * @throws invalidArgument if error occurs while writing to the file stream.
   */
  void serialize(ofstream& ofs) const override;

  /**
   * @returns shared_ptr to a copy of this Enemy.
   */
  virtual shared_ptr<Tile> clone() const override;

private:
  /** @var health. */
  int m_hitPoints;
};