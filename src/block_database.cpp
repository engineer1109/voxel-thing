#include <block_database.hpp>

#include <stdexcept>
#include <ctype.h>
#include <iostream>

#include <utils.hpp>

BlockInfo BlockDatabase::get(BlockType type) {
  if (blocks.find(type) != blocks.end()) {
    return blocks.at(type);
  }

  return blocks[fallback];
}

void BlockDatabase::read(std::ifstream& file) {
  std::string line;

  // consume meta information
  while (getline(file, line)) {
    if (isSeparator(line, '=')) break;

    if (isEmpty(line)) continue;

    ParsedLine pair = parsedLine(line);

    if (pair.key == "version") {
      version = stoi(pair.val);
    } else if (pair.key == "fallback") {
      fallback = (BlockType) stoi(pair.val);
    } else if (pair.key == "air") {
      air = (BlockType) stoi(pair.val);
    } else {
      throw std::runtime_error("parsing block db. unknown key: " + pair.key);
    }
  }

  // build block database
  while (true) {
    BlockInfo info;

    while (getline(file, line)) {
      if (isSeparator(line)) break;
      if (isEmpty(line)) continue;

      ParsedLine pair = parsedLine(line);

      if (pair.key == "id") {
        info.id = stoi(pair.val);
      } else if (pair.key == "name") {
        info.name = pair.val;
      } else if (pair.key == "color") {
        info.color = stringToVec4(pair.val);
      } else if (pair.key == "description") {
        info.description = pair.val;
      } else if (pair.key == "solid") {
        info.description = (pair.val == "true");
      } else {
        throw std::runtime_error("invalid attribute");
      }
    }

    // TODO: clean this up. should have a function to check the validity of the BlockInfo.
    if (info.name.length() > 0) {
      blocks[info.id] = info;
    }

    if (file.peek() == EOF) {
      break;
    }
  }
}

ParsedLine BlockDatabase::parsedLine(std::string line) {
  std::string key = untilSpace(line);
  line = eatSpace(line);
  std::string val = untilNewline(line);

  return ParsedLine{key, val};
}

bool BlockDatabase::isEmpty(std::string line) {
  for (int i = 0; line[i]; i++) {
    if (!isspace(line[i])) {
      return false;
    }
  }

  return true;
}

bool BlockDatabase::isSeparator(std::string line, char c) {
  for (int i = 0; i < 2; i++) {
    if (!line[i] || line[i] != c) {
      return false;
    }
  }

  return true;
}

std::string BlockDatabase::untilSpace(std::string& line) {
  std::string s;

  for (int i = 0; line[i]; i++) {
    char c = line[i];
    if (isblank(c)) {
      line.erase(0, i);
      break;
    }

    s += c;
  }

  return s;
}

std::string BlockDatabase::untilNewline(std::string& line) {
  std::string s;

  for (int i = 0; line[i]; i++) {
    char c = line[i];
    if (c == '\n') {
      line.erase(0, i);
      break;
    }

    s += c;
  }

  return s;
}

std::string BlockDatabase::eatSpace(std::string line) {
  for (int i = 0; line[i]; i++) {
    char c = line[i];
    if (!isspace(c)) {
      line.erase(0, i);
      break;
    }
  }

  return line;
}

glm::vec4 BlockDatabase::stringToVec4(std::string str) {
  glm::vec4 p;

  std::string v = untilSpace(str);
  p.x = rgbToGl(stoi(v));

  str = eatSpace(str);

  v = untilSpace(str);
  p.y = rgbToGl(stoi(v));

  str = eatSpace(str);

  v = untilSpace(str);
  p.z = rgbToGl(stoi(v));

  str = eatSpace(str);

  v = untilSpace(str);
  p.w = stoi(v);

  return p;
}
