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
  string OpCode{};
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

  unordered_map<string, unique_ptr<baseop>> operationMap;
  operationMap["addr"] = make_unique<addr>();
  operationMap["addi"] = make_unique<addi>();
  operationMap["mulr"] = make_unique<mulr>();
  operationMap["muli"] = make_unique<muli>();
  operationMap["banr"] = make_unique<banr>();
  operationMap["bani"] = make_unique<bani>();
  operationMap["borr"] = make_unique<borr>();
  operationMap["bori"] = make_unique<bori>();
  operationMap["setr"] = make_unique<setr>();
  operationMap["seti"] = make_unique<seti>();
  operationMap["gtir"] = make_unique<gtir>();
  operationMap["gtri"] = make_unique<gtri>();
  operationMap["gtrr"] = make_unique<gtrr>();
  operationMap["eqir"] = make_unique<eqir>();
  operationMap["eqri"] = make_unique<eqri>();
  operationMap["eqrr"] = make_unique<eqrr>();

  long long ip = 4;
  vector<long long> registers(6, 0);

  // part 2
  // registers[0] = 1;

  Operation input;
  vector<Operation> operations;

  while (in >> input.OpCode >> input.A >> input.B >> input.C)
    operations.push_back(input);

  // part 1
  while (true)
  {
    auto & operation = operations[registers[ip]];
    operationMap[operation.OpCode]->Execute(operation, registers);

    registers[ip]++;
    if (registers[ip] >= operations.size())
    {
      registers[ip] = 0;
      break;
    }
  }

  cout << registers[0] << endl;

  // part 2
  int s = 0;
  int nr = 10551287;
  for (int i = 1; i <= 10551287; i++)
  {
    if (nr % i == 0)
      s += i;
  }

  cout << s;
  return 0;
}
