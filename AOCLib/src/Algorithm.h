#pragma once

/**
 * Advent of code 2018
 * @author : Nicolae Telechi
 */
namespace AOC
{
  int Fibonaci(int n, int modulo);
  vector<bool> Eratosthenes(int n);


  struct Coordonate
  {
    int x{ 0 };
    int y{ 0 };

    bool operator < (const Coordonate& second) const
    {
      if (x < second.x)
        return true;
      else if (x == second.x)
        return y < second.y;

      return false;
    }
  };

  pair<vector<vector<int>>, set<int>> Lee(const vector<Coordonate> & aCoordonates, vector<vector<int>> & aMap);


  tuple<int, int, int> SubsequenceOfLargestSum(const vector<int> & sequence);

  vector<string> Explode(const string & str, char separator);

  //--------------------------------------------------------------------------
  // implementation details

  namespace detail
  {
    vector<int> GetPartialSums(const vector<int> & sequence);

    vector<vector<int>> MultiplyMatrix(const vector<vector<int>> & first, 
      const vector<vector<int>> & second, int modulo);

    vector<vector<int>> FibonaciMatrix(int n, int modulo);
  }
}
