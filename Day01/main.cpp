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
#include <optional>
#include <numeric>

using namespace std;

int main()
{
  ifstream in("D:\\AOC-2018\\Day1\\Day1.in");
  ofstream out("D:\\AOC-2018\\Day1\\Day1.out");

  vector<int> v;

  int s = 0,n = 0;
  while (in >> n)
  {
    s += n;
    v.push_back(n);
  }

  out << s << endl;

  // part 2

  s = 0;

  optional<int> found;
  unordered_map<int, bool> frequency;

  while(!found)
  {
    for (auto & n : v)
    {
      s += n;

      if (frequency[s] && !found)
      {
        found = s;
        break;
      }

      frequency[s] = true;
    }
  }


  int a[][4] = { {1, 2, 3, 4}, {5, 6, 7, 8} };


  vector<vector<int>> x;
  auto sum = accumulate(begin(x), end(x), 0, [](int s, const vector<int> & y){
    return s + accumulate(begin(y), end(y),  0);
  });



  out << *found << endl;

  return 0;
}
