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
  long long OpCode{};
  long long A{};
  long long B{};
  long long C{};
};

class baseop
{
public:
  virtual ~baseop() {};
  virtual void Execute(const Operation & op, vector<long long> & registers) = 0;

  bool found{ false };
};

// addition
class addr : public baseop
{
public:
  ~addr() {};
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = registers[op.A] + registers[op.B];
  }
};

class addi : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = registers[op.A] + op.B;
  }
};

// multiplication
class mulr : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = registers[op.A] * registers[op.B];
  }
};


class muli : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = registers[op.A] * op.B;
  }
};

// bitwise and
class banr : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = registers[op.A] & registers[op.B];
  }
};

class bani : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = registers[op.A] & op.B;
  }
};

// bitwise or
class borr : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = registers[op.A] | registers[op.B];
  }
};

class bori : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = registers[op.A] | op.B;
  }
};

// assignment
class setr : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = registers[op.A];
  }
};

class seti : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = op.A;
  }
};

// greather-than
class gtir : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = (op.A > registers[op.B]);
  }
};

class gtri : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = (registers[op.A] > op.B);
  }
};

class gtrr : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = (registers[op.A] > registers[op.B]);
  }
};

// equality testing
class eqir : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = (op.A == registers[op.B]);
  }
};

class eqri : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = (registers[op.A] == op.B);
  }
};

class eqrr : public baseop
{
public:
  void Execute(const Operation & op, vector<long long> & registers) override
  {
    registers[op.C] = (registers[op.A] == registers[op.B]);
  }
};

//----------------------------------------------------------------------------

int main()
{
  ifstream in("D:\\AOC-2018\\Day19\\Day19.in");
  ofstream out("D:\\AOC-2018\\Day19\\Day19.out");
  assert(in.good());
  assert(out.good());

  vector<unique_ptr<baseop>> operationMap;
  operationMap.push_back(make_unique<addr>());
  operationMap.push_back(make_unique<addi>());
  operationMap.push_back(make_unique<mulr>());
  operationMap.push_back(make_unique<muli>());
  operationMap.push_back(make_unique<banr>());
  operationMap.push_back(make_unique<bani>());
  operationMap.push_back(make_unique<borr>());
  operationMap.push_back(make_unique<bori>());
  operationMap.push_back(make_unique<setr>());
  operationMap.push_back(make_unique<seti>());
  operationMap.push_back(make_unique<gtir>());
  operationMap.push_back(make_unique<gtri>());
  operationMap.push_back(make_unique<gtrr>());
  operationMap.push_back(make_unique<eqir>());
  operationMap.push_back(make_unique<eqri>());
  operationMap.push_back(make_unique<eqrr>());

  long long ip = 4;
  vector<long long> registers(6, 0);

  // part 2
  registers[0] = 1;

  string instuction;
  long long a, b, c;

  unordered_map<string, long long> pos;
  pos["addr"] = 0;
  pos["addi"] = 1;
  pos["mulr"] = 2;
  pos["muli"] = 3;
  pos["banr"] = 4;
  pos["bani"] = 5;
  pos["borr"] = 6;
  pos["bori"] = 7;
  pos["setr"] = 8;
  pos["seti"] = 9;
  pos["gtir"] = 10;
  pos["gtri"] = 11;
  pos["gtrr"] = 12;
  pos["eqir"] = 13;
  pos["eqri"] = 14;
  pos["eqrr"] = 15;

  vector<Operation> operations;
  while (in >> instuction >> a >> b >> c)
  {
    Operation input;

    input.OpCode = pos[instuction];
    input.A = a;
    input.B = b;
    input.C = c;

    operations.push_back(input);
  }

  // part 1;
  // while (true)
  // {
  //   auto & operation = operations[registers[ip]];
  //   // cout << registers[ip] << endl;
  // 
  //   operationMap[operation.OpCode]->Execute(operation, registers);
  // 
  //   registers[ip]++;
  //   if (registers[ip] >= operations.size())
  //   {
  //     registers[ip] = 0;
  //     break;
  //   }
  // }

  int s = 0;

  // part 2
  int nr = 10551287;
  for (int i = 1; i <= 10551287; i++)
  {
    if (nr % i == 0)
      s+=i;
  }

  // part 1
  // cout << registers[0] << endl;

  // part 2
  cout << s;

  return 0;
}
