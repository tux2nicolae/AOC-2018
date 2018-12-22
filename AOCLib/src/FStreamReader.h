#pragma once

/**
 * Advent of code 2018
 * @author : Nicolae Telechi
 */
class FStreamReader
{
public:
  /**
   * Input stream
   */
  FStreamReader(ifstream & aIn);

  vector<int> ReadVector();
  vector<string> ReadVectorOfWords();

  vector<vector<int>> ReadMatrix();
  vector<vector<int>> ReadMatrixOfDigits();
  vector<vector<string>> ReadMatrixOfWords();

private:
  ifstream & mFileStream;

  vector<int> ReadLineAsVectorOfDigits();
  vector<string> ReadLineAsVectorOfWords();
};
