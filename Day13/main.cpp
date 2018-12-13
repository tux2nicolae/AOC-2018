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

  char direction{ 0 };
  int cartId{ 0 };

  int intersection{ 2 };
  bool destroyed = false;
  
  // less comparator for sort operations
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
    switch (direction)
    {
    case '^':
      direction = '<';
      break;
    case '<':
      direction = 'v';
      break;
    case 'v':
      direction = '>';
      break;
    case '>':
      direction = '^';
      break;
    default:
      break;
    }
  }

  void turnRight()
  {
    switch (direction)
    {
    case '^':
      direction = '>';
      break;
    case '>':
      direction = 'v';
      break;
    case 'v':
      direction = '<';
      break;
    case '<':
      direction = '^';
      break;
    default:
      break;
    }
  }
};

int main()
{
  ifstream in("D:\\AOC-2018\\Day13\\Day13.in");
  ofstream out("D:\\AOC-2018\\Day13\\Day13.out");
  assert(in.good());
  assert(out.good());

  FStreamReader reader(in);
  auto map = reader.ReadVectorOfWords();

  vector<Cart> carts;

  // read data
  int id = 0;
  for (int i = 0; i < map.size(); i++)
  {
    auto & line = map[i];
    for (int j = 0; j < line.size(); j++)
    {
      auto & c = line[j];

      if (c == '^' || c == 'v')
      {
        Cart cart{ i, j, c, ++id };
        carts.push_back(cart);

        c = '|';
      }
      else if (c == '>' || c == '<')
      {
        Cart cart{ i, j, c, ++id };
        carts.push_back(cart);

        c = '-';
      }
    }
  }

  while (1 < count_if(begin(carts), end(carts), [](auto & cart) { return !cart.destroyed; }))
  {
    sort(begin(carts), end(carts));
    for (auto & cart : carts)
    {
      if (cart.destroyed)
        continue;

      // move forward
      if (cart.direction == '^')
      {
        cart.x -= 1;
      }
      else if (cart.direction == '>')
      {
        cart.y += 1;
      }
      else if (cart.direction == 'v')
      {
        cart.x += 1;
      }
      else if (cart.direction == '<')
      {
        cart.y -= 1;
      }

      assert(map[cart.x][cart.y] != ' ');

      // turn on curves
      if (map[cart.x][cart.y] == '\\')
      {
        if (cart.direction == '^' || cart.direction == 'v')
          cart.turnLeft();
        else if (cart.direction == '>' || cart.direction == '<')
          cart.turnRight();
      }
      else if (map[cart.x][cart.y] == '/')
      {
        if (cart.direction == '^' || cart.direction == 'v')
          cart.turnRight();
        else if (cart.direction == '>' || cart.direction == '<')
          cart.turnLeft();

      }

      // turn on intersections
      else if (map[cart.x][cart.y] == '+')
      {
        cart.intersection++;

        if (cart.intersection % 3 == 0)
          cart.turnLeft();
        else if (cart.intersection % 3 == 2)
          cart.turnRight();
      }

      // resolve collisions
      for (auto & secondCart : carts)
      {
        if (secondCart.destroyed)
          continue;

        if (cart.cartId == secondCart.cartId)
          continue;

        if (cart.x == secondCart.x && cart.y == secondCart.y)
        {
          cart.destroyed = true;
          secondCart.destroyed = true;

          cout << "Collision on : " << cart.y << "," << cart.x << endl;
        }
      }
    }
  }

  auto it = find_if(begin(carts), end(carts), [](auto & cart) { return !cart.destroyed; });
  if (it != end(carts))
  {
    cout << "Last car : " << it->y << "," << it->x << endl;
  }

  return 0;
}
