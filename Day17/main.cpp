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

int main()
{
  ifstream in("D:\\AOC-2018\\Day17\\Day17.in");
  ifstream in2("D:\\AOC-2018\\Day17\\Day17_part2.in");
  ofstream out("D:\\AOC-2018\\Day17\\Day17.out");
  assert(in.good());
  assert(in2.good());
  assert(out.good());

  vector<vector<char>> map(2000, vector<char>(2000, '.'));

  int mini = 999999;
  int maxi = 0;

  int a, b, c;
  while (in >> a >> b >> c)
  {
    for (int i = b; i <= c ; i++)
    {
      map[i][a] = '#';

      mini = std::min(mini, i);
      maxi = std::max(maxi, i);
    }
  }

  while (in2 >> a >> b >> c)
  {
    for (int j = b; j <= c; j++)
    {
      map[a][j] = '#';

      mini = std::min(mini, a);
      maxi = std::max(maxi, a);
    }
  }

  Coordonate water{ 0, 500 };
  stack<Coordonate> st;

  st.push(water);

  while (!st.empty())
  {
    Coordonate current = st.top();
    if (current.x >= maxi || map[current.x + 1][current.y] == '|')
    {
      map[current.x][current.y] = '|';

      st.pop();
      continue;
    }
    
    // fall down
    if (map[current.x + 1][current.y] == '.')
    {
      Coordonate down{ current.x + 1, current.y };
      map[down.x][down.y] = '~';

      st.push(down);
      continue;
    }
    
    // fall left
    bool fallLeftRight = false;
    if (map[current.x][current.y - 1] == '.')
    {
      Coordonate left{ current.x, current.y - 1 };
      map[left.x][left.y] = '~';

      st.push(left);
      fallLeftRight = true;
    }

    // fall right
    if (map[current.x][current.y + 1] == '.')
    {
      Coordonate right{ current.x, current.y + 1 };
      map[right.x][right.y] = '~';

      st.push(right);
      fallLeftRight = true;
    }

    if(fallLeftRight)
      continue;

    if (map[current.x + 1][current.y] == '|' ||
      map[current.x][current.y - 1] == '|' ||
      map[current.x][current.y + 1] == '|')
    {
      map[current.x][current.y] = '|';
     
      int i = 1;
      while (map[current.x][current.y + i] == '~') { map[current.x][current.y + i] = '|'; i++; };

      i = 1;
      while (map[current.x][current.y - i] == '~') { map[current.x][current.y - i] = '|'; i++; };

      st.pop();
      continue;
    }

    st.pop();
  }

  int s = 0, part2 = 0;
  for (int i = mini; i <= maxi ; i++)
  {
    for (int j = 0; j < 2000; j++)
    {
      if (map[i][j] == '~' || map[i][j] == '|')
        s++;

      if (map[i][j] == '~')
        part2++;
    }
  }

  FStreamWriter writer(out);
  writer.WriteMatrix(map);

 
  cout << s << " " << part2;

  return 0;
}
