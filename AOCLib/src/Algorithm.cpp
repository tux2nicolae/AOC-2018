/**
 * Advent of code 2018
 * @author : Nicolae Telechi
 */
#include "stdafx.h"
#include "Algorithm.h"

int AOC::Fibonaci(int n, int modulo)
{
  if (n == 0)
    return 0;

  auto fibonaciMatrix = detail::FibonaciMatrix(n - 1, modulo);
  return fibonaciMatrix[1][1];
}

std::vector<bool> AOC::Eratosthenes(int n)
{
  vector<bool> sieve;
  sieve.resize(n + 1); // + 1 for n

  for (int i = 2; i <= sqrt(n); i++)
  {
    while (sieve[i]) i++;

    for (int j = i * i; j <= n; j += i)
      sieve[j] = true;
  }

  return sieve;
}

pair<vector<vector<int>>, set<int>> AOC::Lee(const vector<Coordonate> & aCoordonates, vector<vector<int>> & aMap)
{
  set<int> infinitePoints;

  vector<vector<int>> distances;
  distances.resize(aMap.size());
  for (auto & line : distances)
    line.resize(aMap[0].size());
  
  queue<Coordonate> unvisited;
  for (const auto & startingPoint : aCoordonates)
    unvisited.push(startingPoint);

  auto isInBoundary = [&](const Coordonate & to)-> bool
  {
    return !(to.x < 0 || to.y < 0 || to.x >= aMap.size() || to.y >= aMap[0].size());
  };

  // run
  while (!unvisited.empty())
  {
    auto from = unvisited.front();
    unvisited.pop();

    if (aMap[from.x][from.y] == -1)
      continue;

    static const int directionX[4] = { -1,  0, 1, 0 };
    static const int directionY[4] = { 0,  1, 0, -1 };

    for (int i = 0; i < 4; ++i)
    {
      Coordonate to;
      to.x = from.x + directionX[i];
      to.y = from.y + directionY[i];

      if (!isInBoundary(to))
      {
        infinitePoints.insert(aMap[from.x][from.y]);
        continue;
      }

      if (aMap[to.x][to.y])
      {
        if(distances[to.x][to.y] == distances[from.x][from.y] + 1 && aMap[from.x][from.y] != aMap[to.x][to.y])
          aMap[to.x][to.y] = -1;

        continue;
      }

      aMap[to.x][to.y] = aMap[from.x][from.y];
      distances[to.x][to.y] = distances[from.x][from.y] + 1;

      unvisited.push(to);
    }
  }

  return { distances, infinitePoints };
}

tuple<int, int, int> AOC::SubsequenceOfLargestSum(const vector<int> & sequence)
{
  assert(sequence.size() > 1);

  // reserve +1 for a dummy element 0 witch will make our live easier, this will make
  // begin and end to point on the correct positions
  vector<int> sums;
  sums.reserve(sequence.size() + 1);
  sums.push_back(0);

  std::partial_sum(sequence.begin(), sequence.end(),
    back_inserter(sums));

  int smax = std::numeric_limits<int>::min();
  int smaxbegin = 0, smaxend = 0;

  for (int beg = 0, end = 1; end < sums.size(); ++end)
  {
    if (sums[end] - sums[beg] > smax)
    {
      smax = sums[end] - sums[beg];
      smaxbegin = beg;
      smaxend = end;
    }

    // longest or shortest <=
    if (sums[end] < sums[beg])
      beg = end;
  }

  return make_tuple(smax, smaxbegin, smaxend);
}

std::vector<std::string> AOC::Explode(const std::string & str, char separator)
{
  std::vector<std::string> result;

  std::istringstream stream(str);
  for (std::string token; std::getline(stream, token, separator); )
  {
    result.push_back(std::move(token));
  }

  return result;
}

namespace AOC::detail
{
  vector<int> GetPartialSums(const vector<int> & sequence)
  {
    vector<int> sums;
    sums.reserve(sequence.size());

    std::partial_sum(sequence.begin(), sequence.end(),
      back_inserter(sums));

    return sums;
  }

  vector<vector<int>> MultiplyMatrix(const vector<vector<int>> & first, const vector<vector<int>> & second, int modulo)
  {
    assert(first.size() != 0);
    assert(first.size() == second.size());
    assert(first[0].size() == second[0].size());

    for (int i = 0; i < first.size(); ++i)
    {
      assert(first[i].size() == first[0].size());
      assert(second[i].size() == first[0].size());
    }

    //------------------------------------------------------------------------

    size_t matrixSize = first.size();
    vector<vector<int>> temp;

    temp.resize(matrixSize);
    for (auto & row : temp)
      row.resize(matrixSize);

    for (int i = 0; i < matrixSize; i++)
    {
      for (int j = 0; j < matrixSize; j++)
      {
        for (int k = 0; k < matrixSize; k++)
        {
          temp[i][j] = ((((long long)first[i][k] * second[k][j]) % modulo) + temp[i][j]) % modulo;
        }
      }
    }

    return temp;
  }

  vector<vector<int>> FibonaciMatrix(int n, int modulo)
  {
    static const vector<vector<int>> kFibonaci{ {0, 1}, {1, 1} };

    if (n == 0)
    {
      return { {1, 0}, {0, 1} };
    }
    else if (n == 1)
    {
      return kFibonaci;
    }

    auto result = FibonaciMatrix(n / 2, modulo);
    if (n % 2 == 0)
    {
      return MultiplyMatrix(result, result, modulo);
    }
    else
    {
      return MultiplyMatrix(MultiplyMatrix(result, result, modulo), kFibonaci, modulo);
    }
  }
}
