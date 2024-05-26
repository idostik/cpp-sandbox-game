
#include <ncurses.h>
#include <iostream>

#include "game.h"

using namespace std;

#ifndef TEST

int main() 
{
  try
  {
    Game game;
    game.start();
    game.update();
    
    while (!game.hasEnded())
    {
      game.proccesInput();
      game.update();
    }
    return 0;
  }
  catch (const exception& ex)
  {
    endwin();
    cout << "\nERROR: " << ex.what() << endl;
    return 1;
  }
}

#endif
