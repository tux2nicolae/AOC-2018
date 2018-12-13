#define _CRT_SECURE_NO_WARNINGS

/**
 * Advent of code 2018
 * @author : Nicolae Telechi
 */
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <assert.h>
#include <queue>
#include <stack>
#include <numeric>
#include <set>

using namespace std;

#include "../AOCLib/src/Algorithm.h"
#include "../AOCLib/src/Math.h"
#include "../AOCLib/src/Time.h"
#include "../AOCLib/src/FStreamReader.h"
#include "../AOCLib/src/FStreamWriter.h"
#include "../AOCLib/src/Examples.h"

using namespace AOC;

//----------------------------------------------------------------------------

struct Cart
{
  int x{0};
  int y{0};

  int cartId = 0;

  char direction = 0;
  int intersection = -1;

  bool destroyed = false;
  
  bool operator < (const Cart& second) const
  {
    if (x < second.x)
      return true;
    else if (x == second.x)
      return y < second.y;

   return false;
  }

  void turnLeft()
  {
    if (direction == 0)
      direction = 3;
    else if (direction == 3)
      direction = 2;
    else if (direction == 2)
      direction = 1;
    else if (direction == 1)
      direction = 0;
  }

  void turnRight()
  {
    if (direction == 0)
      direction = 1;
    else if (direction == 1)
      direction = 2;
    else if (direction == 2)
      direction = 3;
    else if (direction == 3)
      direction = 0;
  }
};

vector<Cart> carts;

int main()
{
  ifstream in("D:\\AOC-2018\\Day13\\Day13.in");
  ofstream out("D:\\AOC-2018\\Day13\\Day13.out");
  assert(in.good());
  assert(out.good());

  FStreamReader reader(in);
  auto map = reader.ReadVectorOfWords();

  int id = 0;
  for (int i = 0; i < map.size(); i++)
  {
    auto & line = map[i];
    for (int j = 0; j < line.size(); j++)
    {
      auto & c = line[j];

      if (c == '^')
      {
        Cart cart;
        cart.x = i;
        cart.y = j;
        cart.direction = 0;
        cart.cartId = ++id;
        carts.push_back(cart);

        c = '|';
      }

      if (c == '>')
      {
        Cart cart;
        cart.x = i;
        cart.y = j;
        cart.direction = 1;
        cart.cartId = ++id;
        carts.push_back(cart);

        c = '-';
      }

      if (c == 'v')
      {
        Cart cart;
        cart.x = i;
        cart.y = j;
        cart.direction = 2;
        cart.cartId = ++id;
        carts.push_back(cart);

        c = '|';
      }


      if (c == '<')
      {
        Cart cart;
        cart.x = i;
        cart.y = j;
        cart.direction = 3;
        cart.cartId = ++id;
        carts.push_back(cart);

        c = '-';
      }
    }
  }

  for(int i = 0; carts.size() > 1; ++i)
  {
    sort(begin(carts), end(carts));
    for(auto & cart : carts)
    {
      if(cart.destroyed)
        continue;

      // move forward
      if (cart.direction == 0)
      {
        cart.x -= 1;
      }
      else if (cart.direction == 1)
      {
        cart.y += 1;
      }
      else if (cart.direction == 2)
      {
        cart.x += 1;
      }
      else if (cart.direction == 3)
      {
        cart.y -= 1;
      }

      if (map[cart.x][cart.y] == ' ')
      {
        return 0;
      }

      // resolve curves
      if (map[cart.x][cart.y] == '\\')
      {

        if (cart.direction == 0 || cart.direction == 2)
          cart.turnLeft();
        else if (cart.direction == 1 || cart.direction == 3)
          cart.turnRight();

      } else if (map[cart.x][cart.y] == '/')
      {

        if (cart.direction == 0 || cart.direction == 2)
          cart.turnRight();
        else if (cart.direction == 1 || cart.direction == 3)
          cart.turnLeft();

      }
      // turn on intersections
      else if(map[cart.x][cart.y] == '+')
      {
        cart.intersection++;

        if (cart.intersection % 3 == 0)
          cart.turnLeft();
        else if (cart.intersection % 3 == 2)
          cart.turnRight();
      }



      // resolve conflicts
      for (auto & secondCart : carts)
      {
        if(secondCart.destroyed)
          continue;

        if(cart.cartId == secondCart.cartId)
          continue;

        if (cart.x == secondCart.x && cart.y == secondCart.y)
        {
          cart.destroyed = true;
          secondCart.destroyed = true;

          cout << "Colision on : " << cart.x << "," << cart.y;
        }
      }
    }

    int nr = 0;
    for (auto & cart : carts)
    {
      if (!cart.destroyed)
        nr++;
    }

    if (nr < 2)
      break;
  }

  return 0;
}
