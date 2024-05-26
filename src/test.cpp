#include "game.h"

#include <iostream>
#include <ncurses.h>

using namespace std;

#ifdef TEST

int main(void)
{
  Game game;

  try 
  {
    game.save("tests/save01.txt");
  }
  catch(const exception& ex)
  {
    return 1;
  }
  try
  {
    game.load("tests/nonexisting.txt");
    return 1;
  }
  catch(const exception& ex)
  {
  }
  try
  {
    game.save("tests/save02.txt");
  }
  catch(const exception& ex)
  {
    return 1;
  }
  try 
  {
    game.load("tests/broken01.txt");
    return 1;
  }
  catch(const exception& ex)
  {
  }
  try
  {
    game.load("tests/save04.txt");
  }
  catch(const std::exception& e)
  {
    return 1;
  }
  try
  {
    game.save("tests/save05.txt");
  }
  catch(const std::exception& e)
  {
    return 1;
  }
  try
  { 
    game.load("tests/broken02.txt");
    return 1;
  }
  catch(const exception& ex)
  {
  }
  try
  { 
    game.load("tests/broken03.txt");
    return 1;
  }
  catch(const exception& ex)
  {
  }
  try
  { 
    game.load("tests/broken04.txt");
    return 1;
  }
  catch(const exception& ex) 
  {
  }
  try 
  {
    game.save("tests/save03.txt");
  }
  catch(const exception& ex)
  {
    return 1;
  }
  try 
  {
    game.load("tests/broken05.txt");
    return 1;
  }
  catch(const exception& ex)
  {
  }
  try 
  {
    game.load("tests/broken06.txt");
    return 1;
  }
  catch(const exception& ex)
  {
  }
  try 
  {
    game.load("tests/broken07.txt");
    return 1;
  }
  catch(const exception& ex)
  {
  }
  try
  {
    game.load("tests/broken08.txt");
    return 1;
  }
  catch(const exception& ex)
  {
  }
  try 
  {
    game.load("tests/broken09.txt");
    return 1;
  }
  catch(const exception& ex)
  {
  }
  try 
  {
    game.load("tests/broken10.txt");
    return 1;
  }
  catch(const exception& ex)
  {
  }
  try
  { 
    //file doesn't exist
    game.load("tests/lasodfasfahfalfhaskjfhaslkjfhaslkjfhaskljfhalskjfh.txt");
    return 1;
  }
  catch(const exception& ex)
  {
  }
  try
  {
    game.load("nonexisting/broken01.txt");
    return 1;
  }
  catch(const std::exception& ex)
  {
  }
  try
  {
    game.load("tests/broken11.txt");
    return 1;
  }
  catch(const std::exception& ex)
  {
  }
  try
  {
    game.load("tests/broken12.txt");
    return 1;
  }
  catch(const std::exception& ex)
  {
  }
  try
  {
    game.load("tests/broken13.txt");
    return 1;
  }
  catch(const std::exception& ex)
  {
  }
  try
  {
    game.load("tests/broken14.txt");
    return 1;
  }
  catch(const std::exception& ex)
  {
  }
  try
  {
    game.load("tests/broken15.txt");
    return 1;
  }
  catch(const std::exception& ex)
  {
  }
  try
  {
    game.save("tests/save06.txt");
  }
  catch(const std::exception& ex)
  {
    return 1;
  }
  try
  {
    game.load("tests/broken16.txt");
    return 1;
  }
  catch(const std::exception& ex)
  {
  }
  try
  {
    game.load("tests/broken17.txt");
    return 1;
  }
  catch(const std::exception& ex)
  {
  }
  try
  {
    game.load("tests/save06.txt");
  }
  catch(const std::exception& ex)
  {
    return 1;
  }
  try
  {
    game.load("tests/broken18.txt");
    return 1;
  }
  catch(const std::exception& ex)
  {
  }
  try
  {
    game.load("tests/broken19.txt");
    return 1;
  }
  catch(const std::exception& ex)
  {
  }
  try
  {
    game.load("tests/broken20.txt");
    return 1;
  }
  catch(const std::exception& ex)
  {
  }
  
  endwin();
  cout << "Tests successful" << endl;
  return 0;
}

#endif