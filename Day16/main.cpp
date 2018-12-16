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


struct Operation 
{
  int OpCode{};
  int A{};
  int B{};
  int C{};
};

class baseop
{
public:
  virtual ~baseop() {};
  virtual void Execute(const Operation & op, vector<int> & registers) = 0;
  
  bool found{false};
};

// addition
class addr : public baseop
{
public:
  ~addr() {};
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] + registers[op.B];
  }
};

class addi : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] =  registers[op.A] + op.B;
  }
};

// multiplication
class mulr : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] * registers[op.B];
  }
};


class muli : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] * op.B;
  }
};

// bitwise and
class banr : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] & registers[op.B];
  }
};

class bani : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] & op.B;
  }
};

// bitwise or
class borr : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] | registers[op.B];
  }
};

class bori : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] | op.B;
  }
};

// assignment
class setr : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A];
  }
};

class seti : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = op.A;
  }
};

// greather-than
class gtir : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = (op.A > registers[op.B]);
  }
};

class gtri : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = (registers[op.A] > op.B);
  }
};

class gtrr : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = (registers[op.A] > registers[op.B]);
  }
};

// equality testing
class eqir : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = (op.A == registers[op.B]);
  }
};

class eqri : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = (registers[op.A] == op.B);
  }
};

class eqrr : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = (registers[op.A] == registers[op.B]);
  }
};


//----------------------------------------------------------------------------

int main()
{
  ifstream in("D:\\AOC-2018\\Day16\\Day16.in");
  ofstream out("D:\\AOC-2018\\Day16\\Day16.out");
  assert(in.good());
  assert(out.good());

  FStreamReader reader(in);
  auto map = reader.ReadMatrix();

  vector<unique_ptr<baseop>> operations;
  operations.push_back(make_unique<addr>());
  operations.push_back(make_unique<addi>());
  operations.push_back(make_unique<mulr>());
  operations.push_back(make_unique<muli>());
  operations.push_back(make_unique<banr>());
  operations.push_back(make_unique<bani>());
  operations.push_back(make_unique<borr>());
  operations.push_back(make_unique<bori>());
  operations.push_back(make_unique<setr>());
  operations.push_back(make_unique<seti>());
  operations.push_back(make_unique<gtir>());
  operations.push_back(make_unique<gtri>());
  operations.push_back(make_unique<gtrr>());
  operations.push_back(make_unique<eqir>());
  operations.push_back(make_unique<eqri>());
  operations.push_back(make_unique<eqrr>());

  unordered_map<int, baseop *> operationMap;

  bool partOneCounted = false;
  int partOneCount = 0;
  while(16 != count_if(begin(operationMap), end(operationMap), [](auto & op) {return nullptr != op.second; }))
  {
    for (int i = 0; i < map.size(); i += 3)
    {
      const auto & registers = map[i];

      Operation input;
      input.OpCode = map[i + 1][0];
      input.A = map[i + 1][1];
      input.B = map[i + 1][2];
      input.C = map[i + 1][3];

      const auto & expected = map[i + 2];

      // part 1
      if (!partOneCounted)
      {
        int operationsCount = 0;
        for (auto & operation : operations)
        {
          auto tempRegisters = registers;
          operation->Execute(input, tempRegisters);

          if (equal(begin(tempRegisters), end(tempRegisters), begin(expected), end(expected)))
          {
            operationsCount++;
          }
        }

        if (operationsCount >= 3)
          partOneCount++;
      }

      // part 2
      baseop * op = nullptr;
      if(!operationMap[input.OpCode])
      {
        int machOperations = 0;
        for (auto & operation : operations)
        {
          if(operation->found)
            continue;

          auto tempRegisters = registers;
          operation->Execute(input, tempRegisters);

          if(equal(begin(tempRegisters), end(tempRegisters), begin(expected), end(expected)))
          {
            op = operation.get();
            machOperations++;
          }
        }

        if (machOperations == 1)
        {
          operationMap[input.OpCode] = op;
          op->found = true;
        }
      }
    }

    partOneCounted = true;
  }

  cout << partOneCount << endl;

  ifstream in2("D:\\AOC-2018\\Day16\\Day16_part2.in");
  assert(in2.good());
 
  FStreamReader reader2(in2);
  auto program = reader2.ReadMatrix();

  vector<int> registers(4, 0);
  for (auto & instruction : program)
  {
    Operation input;
    input.OpCode = instruction[0];
    input.A = instruction[1];
    input.B = instruction[2];
    input.C = instruction[3];

    operationMap[input.OpCode]->Execute(input, registers);
  }

  cout << registers[0] << endl;

  return 0;
}
