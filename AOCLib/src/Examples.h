#pragma once

/**
 * Advent of code 2018
 * @author : Nicolae Telechi
 */

//----------------------------------------------------------------------------
// Heap

/*

auto heapComparator = [](int left, int right) { return left < right; };
priority_queue<int, vector<int>, decltype(heapComparator)> heap(heapComparator);

priority_queue<int, vector<int>, greater<int>> minHeap;
priority_queue<int, vector<int>, less<int>> maxHeap;

minHeap.push(10); minHeap.top(); minHeap.pop();

*/

//----------------------------------------------------------------------------
// General

/*

---------------------------------------------------

auto [min, max] = minmax(data.begin(), data.end())

---------------------------------------------------

vector<vector<int>> temp;

temp.resize(matrixSize);
for (auto & row : temp)
  row.resize(matrixSize);

---------------------------------------------------

str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x)
{
  return std::isspace(x);
});

---------------------------------------------------

vector<vector<int>> map;
map.resize(500);
for (auto & line : map)
  line.resize(500);

*/
