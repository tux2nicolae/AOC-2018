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

int s = 0;

bool readNode(istream & in)
{
  int node = 0;
  int metadatacount = 0;

  in >> node >> metadatacount;

  for (int i = 0; i < node; i++)
    readNode(in);

  for (int j = 0; j < metadatacount; j++)
  {
    int metadata;
    in >> metadata;

    s += metadata;
  }

  return s;
}

int main()
{
  ifstream in("D:\\AOC-2018\\Day8\\Day8.in");
  ofstream out("D:\\AOC-2018\\Day8\\Day8.out");

  assert(in.good());
  assert(out.good());

  readNode(in);

  return 0;
}
