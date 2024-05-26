#include "game.h"

#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>

#define BOARD_WIDTH 50
#define BOARD_HEIGHT 30
#define PLAYER_ICON '@'
#define PLAYER_START_X 4
#define PLAYER_START_Y 0
#define MAX_HEALTH 100
#define SLEEP_AFTER_DEATH 800 //in miliseconds
#define GRAVITY_INTERVAL 200 //in miliseconds
#define FALL_TRESHOLD 1 //how far can player fall without recieving damage
#define MIN_WIDTH 30
#define MIN_HEIGHT 15

Game::Game()
{
  initscr();
  refresh();
  cbreak();
  noecho();
  curs_set(0);
  m_hasEnded = false;

  //center gameBoard
  int maxY, maxX;
  getmaxyx(stdscr, maxY, maxX);
  if (maxY < BOARD_HEIGHT || maxX < BOARD_WIDTH)
    throw invalid_argument("Terminal size is too small");
  int boardStartY = maxY/2 - BOARD_HEIGHT/2;
  int boardStartX = maxX/2 - BOARD_WIDTH/2;

  m_mainWin = make_shared<MainWindow> (BOARD_HEIGHT, BOARD_WIDTH, boardStartY, boardStartX);
  m_statusWin = make_shared<StatusBar> (1, BOARD_WIDTH, boardStartY + BOARD_HEIGHT, boardStartX);
  m_map = make_shared<Map> (BOARD_HEIGHT, BOARD_WIDTH);
  m_player = make_shared<Player> (PLAYER_START_Y, PLAYER_START_X, PLAYER_ICON, m_mainWin, m_map, MAX_HEALTH);

  m_mainWin->displayHelp();
  m_mainWin->redraw();
}

Game::~Game()
{
  endwin();
}

void Game::start()
{
  //wait for user to press something before continuing
  m_mainWin->inputChar();
  m_mainWin->clear();

  m_statusWin->displayDescrition();
  m_statusWin->redraw();
  m_map->print(*m_mainWin);
  m_player->display(*m_mainWin);
  m_mainWin->redraw();
}

void Game::gameOver()
{
  m_statusWin->clear();
  m_statusWin->redraw();

  m_mainWin->displayGameOverScr();
  m_mainWin->redraw();
  char input;
  // wait for the user to press space
  do
  {
   input = m_mainWin->inputChar(); 
  } while (input != ' ');
  
  //reset the game
  m_map->generate();
  m_map->print(*m_mainWin);
  m_player->reset();
  m_player->display(*m_mainWin);
  m_statusWin->displayDescrition();
  m_statusWin->displayHealth(m_player->getHealth());
  m_statusWin->redraw();
  m_mainWin->redraw();
}

bool Game::hasEnded() const
{
  return m_hasEnded;
}

void Game::proccesInput()
{
  flushinp();
  int input = m_mainWin->inputChar();

  switch(input)
  {
    case KEY_UP:
      m_player->move(Direction::UP);
      break;
    case KEY_RIGHT:
      m_player->move(Direction::RIGHT);
      break;
    case KEY_LEFT:
      m_player->move(Direction::LEFT);
      break;
    case KEY_DOWN:
      m_player->move(Direction::DOWN);
      break;
    case 'w':
      m_player->mine(Direction::UP);
      break;
    case 'd':
      m_player->mine(Direction::RIGHT);
      break;
    case 's':
      m_player->mine(Direction::DOWN);
      break;
    case 'a':
      m_player->mine(Direction::LEFT);
      break;
    case 't':
      m_player->placeLadder();
      break;
    case 'm':
      proccesMenuInput();
  } 
}

void Game::proccesMenuInput()
{
  m_mainWin->openMenu();
  while (true)
  {
    string input = m_mainWin->inputStr();
    stringstream iss(input);
    string command, argument;
    iss >> command >> argument;

    if (command == "upgrade-pickaxe" && argument.empty())
    {
      if (m_player->getPos().first > m_map->getAirLvl())
        m_mainWin->menuOutput("You need to be above ground to buy!");
      else if (!m_player->upgradePickaxe())
        m_mainWin->menuOutput("Not enough money. Costs: " + to_string(m_player->getPickaxePrice()));
      else
      {
        m_mainWin->menuOutput("Pikaxe upgraded!");
        m_statusWin->displayMoney(m_player->getMoney());
        m_statusWin->redraw();
      }
    }
    else if (command == "quit" && argument.empty())
    {
      m_hasEnded = true;
      return;
    }
    else if (command == "return" && argument.empty())
    {  
      m_mainWin->closeMenu();
      m_map->print(*m_mainWin);
      return;
    }
    else if (command == "refill-health" && argument.empty())
    {
      if (m_player->getPos().first > m_map->getAirLvl())
        m_mainWin->menuOutput("You need to be above ground to buy stuff!");
      else if (!m_player->refillHealth())
        m_mainWin->menuOutput("Not enough money. Costs: " + to_string(m_player->getHealthPrice()));
      else
      {
        m_mainWin->menuOutput("Health refilled!");
        m_statusWin->displayMoney(m_player->getMoney());
        m_statusWin->displayHealth(m_player->getHealth());
        m_statusWin->redraw();
      }
    }
    else if (command == "save" && !argument.empty())
    {
      try
      {
        save(argument);
        m_mainWin->menuOutput("Game saved!");
      }
      catch(const exception& ex)
      {
        m_mainWin->menuOutput(ex.what());
      }
    }
    else if (command == "load" && !argument.empty())
    {
      try
      {
        load(argument);
        m_mainWin->openMenu();
        m_mainWin->menuOutput("Game loaded!");
      }
      catch(const exception& ex)
      {
        m_mainWin->menuOutput(ex.what());
      }
    }
    else
      m_mainWin->menuOutput("Wrong input");

    m_mainWin->resetInput();
  }
}

void Game::update()
{
  if (m_hasEnded)
    return;
  //display health first in case player takes damage right before falling
  m_statusWin->displayHealth(m_player->getHealth());
  m_statusWin->redraw();

  //gravity
  int fallDamage = -FALL_TRESHOLD;
  while (m_player->shouldFall())
  {
    m_player->move(Direction::DOWN);
    m_player->display(*m_mainWin);
    m_mainWin->redraw();
    m_statusWin->displayDepth(m_player->getPos().first);
    m_statusWin->redraw();
    fallDamage++;
    //delay makes the fall continuous and not instant
    this_thread::sleep_for(chrono::milliseconds(GRAVITY_INTERVAL));
  }
  if (fallDamage > 0)
    m_player->changeHealth(-fallDamage);

  //update status bar
  m_statusWin->displayDepth(m_player->getPos().first);
  m_statusWin->displayHealth(m_player->getHealth());
  m_statusWin->displayMoney(m_player->getMoney());

  m_player->display(*m_mainWin);

  m_mainWin->redraw();
  m_statusWin->redraw();

  if (m_player->getHealth() <= 0)
    gameOver();
}

void Game::save(const string& fileName) const
{
  ofstream ofs(fileName);
  if (!ofs.good())
    throw invalid_argument("Failed to write");

  ofs << BOARD_HEIGHT << " " << BOARD_WIDTH << endl;

  m_map->serialize(ofs);
  m_player->serialize(ofs);
}

void Game::load(const string& fileName)
{
  ifstream ifs(fileName);
  if (!ifs.good())
    throw invalid_argument("Failed to open file");
  size_t height, width;
  height = width = 0;
  ifs >> height >> width;

  if (!ifs.good() || height < MIN_HEIGHT || width < MIN_WIDTH)
    throw invalid_argument("Save data are invalid");

  int maxY, maxX;
  getmaxyx(stdscr, maxY, maxX);
  int boardStartY = maxY/2 - height/2;
  int boardStartX = maxX/2 - width/2;

  auto newBoard = make_shared<MainWindow> (height, width, boardStartY, boardStartX);
  auto newStatusBar = make_shared<StatusBar> (1, width, boardStartY + height, boardStartX);
  auto newMap = make_shared<Map> (ifs, height, width);

  string word = "";
  ifs >> word;
  if (word != "P" || !ifs.good())
    throw invalid_argument("Save data are invalid");

  auto newPlayer = make_shared<Player> (ifs, newBoard, newMap);

  m_mainWin->clear();
  m_mainWin->redraw();
  m_statusWin->clear();
  m_statusWin->redraw();

  m_map = newMap;
  m_player = newPlayer;
  m_mainWin = newBoard;
  m_statusWin = newStatusBar;

  m_statusWin->displayDescrition();
  m_statusWin->displayMoney(m_player->getMoney());
  m_statusWin->displayHealth(m_player->getHealth());
  m_statusWin->redraw();
  m_mainWin->redraw();
}
