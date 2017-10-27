#ifndef BLOCK_DATABASE_H
#define BLOCK_DATABASE_H

#include <string>
#include <map>
#include <fstream>

#include <glm/glm.hpp>

typedef int BlockType;

struct BlockInfo {
  int id;
  std::string name;
  glm::vec4 color;
  std::string description;
  bool solid;
};

struct ParsedLine {
  std::string key;
  std::string val;
};

class BlockDatabase {
  public:
    BlockInfo get(BlockType type);

    void read(std::ifstream& file);

    BlockType air;

    std::map<BlockType,BlockInfo> blocks;
  private:
    int version;
    BlockType fallback;


    ParsedLine parsedLine(std::string line);

    bool isEmpty(std::string);
    bool isSeparator(std::string line, char c = '-');

    std::string untilSpace(std::string& line);
    std::string untilNewline(std::string &line);
    std::string eatSpace(std::string line);

    glm::vec4 stringToVec4(std::string str);
};

#endif
