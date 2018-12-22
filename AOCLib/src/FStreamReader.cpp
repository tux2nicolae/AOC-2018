/**
 * Advent of code 2018
 * @author : Nicolae Telechi
 */
#include <stdafx.h>
#include "FStreamReader.h"


FStreamReader::FStreamReader(ifstream & aIn) 
  : mFileStream(aIn)
{
  assert(mFileStream.good());
}

vector<int> FStreamReader::ReadVector()
{
  vector<int> ret;

  int n = 0;
  while (mFileStream >> n)
    ret.push_back(n);

  return ret;
}

vector<string> FStreamReader::ReadVectorOfWords()
{
  vector<string> ret;

  string line;
  while (getline(mFileStream, line))
    ret.push_back(line);

  return ret;
}

vector<vector<int>> FStreamReader::ReadMatrix()
{
  vector<vector<int>> ret;

  string line;
  while (getline(mFileStream, line))
  {

    vector<int> row;
    std::istringstream ss(line);

    int n = 0;
    while (ss >> n)
      row.push_back(n);

    if (!row.empty())
      ret.push_back(row);
  }

  return ret;
}

vector<std::vector<int>> FStreamReader::ReadMatrixOfDigits()
{
  vector<std::vector<int>> ret;

  while (mFileStream.good())
  {
    auto lineOfDigits = ReadLineAsVectorOfDigits();
    if (!lineOfDigits.empty())
      ret.push_back(lineOfDigits);
  }

  return ret;
}

std::vector<std::vector<string>> FStreamReader::ReadMatrixOfWords()
{
  vector<std::vector<string>> ret;

  while (mFileStream.good())
  {
    auto lineOfWords = ReadLineAsVectorOfWords();
    if (!lineOfWords.empty())
      ret.push_back(lineOfWords);
  }

  return ret;
}

vector<int> FStreamReader::ReadLineAsVectorOfDigits()
{
  vector<int> ret;

  string line;
  if (!getline(mFileStream, line))
    return ret;

  std::istringstream ss(line);

  char n = 0;
  while (ss >> n)
  {
    if ('0' <= n && n <= '9')
      ret.push_back(n - '0');
  }

  return ret;
}

vector<string> FStreamReader::ReadLineAsVectorOfWords()
{
  vector<string> ret;

  string line;
  if (!getline(mFileStream, line))
    return ret;

  std::istringstream ss(line);

  string word;
  while (ss >> word)
    ret.push_back(word);

  return ret;
}
