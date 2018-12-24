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
#include <unordered_set>
#include <assert.h>
#include <queue>
#include <stack>
#include <numeric>
#include <set>
#include <regex>
#include <iterator>
#include <locale>
#include <functional>

using namespace std;

std::vector<std::string> Explode(const std::string & str, char separator)
{
  std::vector<std::string> result;

  std::istringstream stream(str);
  for (std::string token; std::getline(stream, token, separator); )
  {
    result.push_back(std::move(token));
  }

  return result;
}

//----------------------------------------------------------------------------

struct Group
{
  enum class Type
  {
    imune,
    infection
  };

  Type type{};
  int units{};
  int unitHitPoints{};

  unordered_set<string> imunities;
  unordered_set<string> weaknesees;

  int damage{};
  string target;
  int initiative{};

  bool dead{ false };

  int GetEffectivePower() const
  {
    return units * damage;
  }

  int GetAtackDamage(const Group& defending) const
  {
    if(defending.imunities.count(target) > 0)
      return 0;

    if (defending.weaknesees.count(target) > 0)
      return GetEffectivePower() * 2;
    
    return GetEffectivePower();
  }

  static bool InitiativeOrder(const Group& first, const Group& second)
  {
    return first.initiative > second.initiative;
  }

  static bool EfectivePowerOrder(const Group& first, const Group& second)
  {
    if (first.GetEffectivePower() > second.GetEffectivePower())
      return true;
    else if (first.GetEffectivePower() == second.GetEffectivePower())
      return InitiativeOrder(first, second);

    return false;
  }
};

void ParseGroupInfo(const string & str, Group & gr)
{
  smatch match;
  regex_match(str, match, regex("(.*) units each with (.*) hit points (.*)with an attack that does (.*) (.*) damage at initiative (.*)"));
  assert(match.size() == 7);

  // 1
  gr.units = stoi(match[1]);

  // 2
  gr.unitHitPoints = stoi(match[2]);

  // 3
  if (string expresion = match[3]; !expresion.empty())
  {
    auto sBegin = expresion.find('(') + 1;
    auto sEnd = expresion.find(')');
    assert(sBegin != string::npos);
    assert(sEnd != string::npos);

    for (auto & ex : Explode(expresion.substr(sBegin, sEnd - sBegin), ';'))
    {
      if (string toFind = "weak to ";  ex.find(toFind) != string::npos)
      {
        ex = ex.substr(toFind.length());
        ex.erase(remove(ex.begin(), ex.end(), ' '), ex.end());

        auto weaknesees = Explode(ex, ',');
        copy(begin(weaknesees), end(weaknesees), inserter(gr.weaknesees, gr.weaknesees.end()));
      }
      else if (string toFind = "immune to ";  ex.find(toFind) != string::npos)
      {
        ex = ex.substr(toFind.length());
        ex.erase(remove(ex.begin(), ex.end(), ' '), ex.end());

        auto imunities = Explode(ex, ',');
        copy(begin(imunities), end(imunities), inserter(gr.imunities, gr.imunities.end()));
      }
    }
  }

  // 4
  gr.damage = stoi(match[4]);

  // 5
  gr.target = match[5];

  // 6
  gr.initiative = stoi(match[6]);
}

void UpdateAtackTarget(unordered_map<Group *, Group *> & atackTargets, Group & atacker, Group & defender)
{
  if (atacker.type == defender.type)
    return;

  // no atack damage or the defender is already chosen by another one
  if (atacker.GetAtackDamage(defender) == 0 ||
    find_if(begin(atackTargets), end(atackTargets), [&](auto & target) { return target.second == &defender; }) != atackTargets.end())
  {
    return;
  }

  if (atackTargets[&atacker] == nullptr)
  {
    atackTargets[&atacker] = &defender;
    return;
  }

  // change existing target
  if (atacker.GetAtackDamage(*atackTargets[&atacker]) < atacker.GetAtackDamage(defender))
  {
    atackTargets[&atacker] = &defender;
  }
  else if (atacker.GetAtackDamage(*atackTargets[&atacker]) == atacker.GetAtackDamage(defender))
  {
    // tie by largest efective power
    if (atackTargets[&atacker]->GetEffectivePower() < defender.GetEffectivePower())
    {
      atackTargets[&atacker] = &defender;
    }
    else if (atackTargets[&atacker]->GetEffectivePower() == defender.GetEffectivePower())
    {
      // tie by largest initiative
      if (atackTargets[&atacker]->initiative < defender.initiative)
      {
        atackTargets[&atacker] = &defender;
      }
    }
  }
};

//----------------------------------------------------------------------------

int main()
{
  ifstream in("C:\\Users\\Telechi\\Desktop\\Day24.in");
  ifstream in2("C:\\Users\\Telechi\\Desktop\\Day24_2.in");
  assert(in.good());
  assert(in2.good());

  int id = 0;
  string line;

  // imune system
  vector<Group> groups;
  while (getline(in, line))
  {
    auto & imuneGroup = groups.emplace_back();
    imuneGroup.type = Group::Type::imune;

    ParseGroupInfo(line, imuneGroup);
  }

  // infection
  while (getline(in2, line))
  {
    auto & infectionGroup = groups.emplace_back();
    infectionGroup.type = Group::Type::infection;

    ParseGroupInfo(line, infectionGroup);
  }

  int boost = 34; // on 33 enters an infinite loop
  vector<Group> battleGroups;

  do
  {
    // boost
    battleGroups.clear();
    transform(begin(groups), end(groups), back_inserter(battleGroups), [&](const auto & group) {
      Group boosted(group);

      if (boosted.type == Group::Type::imune)
        boosted.damage += boost;
      
      return move(boosted);
    });


    while (count_if(begin(battleGroups), end(battleGroups), [](auto & group) {return !group.dead && group.type == Group::Type::imune; }) > 0 &&
      count_if(begin(battleGroups), end(battleGroups), [](auto & group) {return !group.dead && group.type == Group::Type::infection; }) > 0 )
    {
      // target sellection
      unordered_map<Group *, Group *> atackTargets;

      sort(begin(battleGroups), end(battleGroups), Group::EfectivePowerOrder);
      for (auto & atacker : battleGroups)
      {
        if (atacker.dead)
          continue;

        for (auto & defender : battleGroups)
        {
          if (defender.dead)
            continue;

          UpdateAtackTarget(atackTargets, atacker, defender);
        }
      }

      // prepare atack order
      vector<pair<Group *, Group *>> atackOrder;
      copy(begin(atackTargets), end(atackTargets), back_inserter(atackOrder));

      sort(begin(atackOrder), end(atackOrder), [](auto & a, auto & b) {
        return Group::InitiativeOrder(*a.first, *b.first);
      });

      // ataaaaaaaack !!!!!!
      for (auto atack : atackOrder)
      {
        auto & atacker = *atack.first;
        auto & defender = *atack.second;

        if (atacker.dead)
          continue;

        auto atackDamage = atacker.GetAtackDamage(defender);
        defender.units -= atackDamage / defender.unitHitPoints;

        if (defender.units <= 0)
          defender.dead = true;
      }
    }

    int winningPoints = 0;
    for (auto & group : battleGroups)
      winningPoints += group.dead ? 0 : group.units;

    std::cout << winningPoints << endl;
    boost+=1;

  } while (count_if(begin(battleGroups), end(battleGroups), [](auto & group) {return !group.dead && group.type == Group::Type::infection; }) > 0);
  
  return 0;
}
