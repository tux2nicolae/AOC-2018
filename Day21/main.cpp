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
#include <bitset>

using namespace std;

#include "../AOCLib/src/Algorithm.h"
#include "../AOCLib/src/Math.h"
#include "../AOCLib/src/Time.h"
#include "../AOCLib/src/FStreamReader.h"
#include "../AOCLib/src/FStreamWriter.h"
#include "../AOCLib/src/Examples.h"

using namespace AOC;

bool showLog = false;

struct Operation
{
  string OpCode{};
  int A{};
  int B{};
  int C{};
};

class baseop
{
public:
  virtual ~baseop() {};
  virtual void Execute(const Operation & op, vector<int> & registers) = 0;

  bool found{ false };
};

// addition
class addr : public baseop
{
public:
  ~addr() {};
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] + registers[op.B];

    if (showLog)
      cout << "r" << op.C << "=" << "r" << op.A <<  "+" << "r" << op.B;
  }
};

class addi : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] + op.B;

    if (showLog)
      cout << "r" << op.C << "=" << "r" << op.A << "+" << op.B;
  }
};

// multiplication
class mulr : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] * registers[op.B];

    if (showLog)
      cout << "r" << op.C << "=" << "r" << op.A << "*" << "r" << op.B;
  }
};


class muli : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] * op.B;

    if (showLog)
      cout << "r" << op.C << "=" << "r" << op.A << "*" << op.B;
  }
};

// bitwise and
class banr : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] & registers[op.B];

    if (showLog)
      cout << "r" << op.C << "=" << "r" << op.A << "&" << "r" << op.B;
  }
};

class bani : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] & op.B;

    if (showLog)
      cout << "r" << op.C << "=" << "r" << op.A << "&" << op.B;
  }
};

// bitwise or
class borr : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] | registers[op.B];

    if (showLog)
      cout << "r" << op.C << "=" << "r" << op.A << "|" << "r" << op.B;
  }
};

class bori : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A] | op.B;

    if (showLog)
      cout << "r" << op.C << "=" << "r" << op.A << "|" << op.B;
  }
};

// assignment
class setr : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = registers[op.A];

    if (showLog)
      cout << "r" << op.C << "=" << "r" << op.A;
  }
};

class seti : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = op.A;

    if (showLog)
      cout << "r" << op.C << "=" << op.A;
  }
};

// greather-than
class gtir : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = (op.A > registers[op.B]);

    if (showLog)
      cout << "r" << op.C << "=" << op.A << ">" << "r" << op.B;
  }
};

class gtri : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = (registers[op.A] > op.B);

    if (showLog)
      cout << "r" << op.C << "=" << "r" << op.A << ">" << op.B;
  }
};

class gtrr : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = (registers[op.A] > registers[op.B]);

    if (showLog)
      cout << "r" << op.C << "=" << "r" << op.A << ">" << "r" << op.B;
  }
};

// equality testing
class eqir : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = (op.A == registers[op.B]);

    if (showLog)
      cout << "r" << op.C << "=" << op.A << "==" << "r" << op.B;
  }
};

class eqri : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = (registers[op.A] == op.B);

    if (showLog)
      cout << "r" << op.C << "=" << "r" << op.A << "==" << op.B;
  }
};

class eqrr : public baseop
{
public:
  void Execute(const Operation & op, vector<int> & registers) override
  {
    registers[op.C] = (registers[op.A] == registers[op.B]);

    if (showLog)
      cout << "r" << op.C << "=" << "r" << op.A << "==" << "r" << op.B;
  }
};

// this program is only for my input
int program()
{
  // alloc on heap
  auto found = make_unique<bitset<16777215>>();

  int r0 = 0;
  int r4 = 0;

  int lastValue = 0;
  while (true)
  {
    int r3 = r4 | 65536;
             r4 = 12670166;

    for (; r3; r3 /= 256)
    {
      r4 += r3 & 255;

      r4 &= 16777215;
      r4 *= 65899;
      r4 &= 16777215;
    }

    // return the last value before finding a cycle
    if (found->test(r4))
      return lastValue;

    lastValue = r4;
    found->set(r4);
  }

  return lastValue;
}

//----------------------------------------------------------------------------

int main()
{
  ifstream in("D:\\AOC-2018\\Day21\\Day21.in");
  ofstream out("D:\\AOC-2018\\Day21\\Day21.out");
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

  int ip = 1;
  vector<int> registers(6, 0);

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

    // part 1, break on first solution
    if (registers[ip] == 28)
    {
      // the 28 instruction on my input was "eqrr 4 0 2" may defer for other inputs 
      cout << registers[4] << endl;
      break;
    }
  }

  // part 2
  cout << program() << endl;
  return 0;
}
