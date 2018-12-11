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

int value[20];

struct Node
{
  int count{};
  int visited{};
  int metadatas{};
  vector<int> childs;

  int nr{};
};

stack<Node> st;

int readNode(istream & in)
{
  int node = 0;
  int metadatacount = 0;

  in >> node >> metadatacount;

  vector<int> childValues(node, 0);
  st.push({ node, 0, metadatacount, childValues, 0 });

  while (!st.empty())
  {
    auto & data = st.top();
    if(data.visited < data.count)
    {
      in >> node >> metadatacount;

      vector<int> childValues(node, 0);
      st.push({ node, 0, metadatacount, move(childValues), data.visited++ });
    }
    else
    {
      vector<int> metadatas;
      for (int i = 0; i < data.metadatas; i++)
      {
        int x;
        in >> x;

        metadatas.push_back(x);
      }
 
      int value = 0;
      if (!data.count)
      {
        for (auto & metaDataId : metadatas)
          value += metaDataId;
      }
      else
      {
        for (auto & metaDataId : metadatas)
        {
          if (metaDataId != 0 && (metaDataId - 1) < data.count)
          {
            value += data.childs[(metaDataId - 1)];
          }
        }
      }

      st.pop();
      if (!st.empty())
      {
        auto & parent = st.top();
        parent.childs[data.nr] = value;
      }
      else
      {
        return value;
      }
    }    
  }

  return 0;
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
