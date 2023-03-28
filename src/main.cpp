#include <cassert>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

struct Entity {
  std::string name;
  float health;
  float dmg;
  float speed;
  float def;
  Entity(const std::string &n = "Entity")
      : name(n), health(10.f), dmg(1.f), speed(10.f), def(5.f){};
};

void hashInsert(std::vector<std::pair<std::string, Entity>> &map,
                const Entity &val) {
  std::pair<std::string, Entity> pair;
  pair.first = val.name;
  pair.second = val;

  size_t hash = 0;
  for (size_t i = 0; i < pair.first.size(); ++i) {
    hash += (int)pair.first.size();
  };
  hash = map.size() % hash;
  // Check for collision
  if (map[hash].second.name != "Entity") {
    while (map[hash].second.name != "Entity") {
      std::cout << "Collision at [" << hash << "]...\n";
      hash++;
      // wrap around if hash(i) reached the size of map
      if (hash == map.capacity()) {
        hash = 0;
      };
    };
  };

  std::cout << "Inserted \"" << pair.first << "\" at index: " << hash << "\n";
  map[hash] = pair;
};

Entity hashGet(std::vector<std::pair<std::string, Entity>> &map,
               const std::string &key) {
  size_t hash = 0;
  for (size_t i = 0; i < key.size(); ++i) {
    hash += (int)key[i];
  };
  hash = map.size() % hash;

  assert(hash < map.size());

  size_t searchOrigin = hash;
  while (map[hash].second.name != key) {
    hash++;

    // wrap around
    if (hash == map.size()) {
      hash = 0;
    };

    // fully searched through the map
    if (hash == searchOrigin) {
      Entity e;
      std::cout << "WARN: Key \"" << key << "\" not found in map!!!\n";
      return e;
    };
  };
  std::cout << "Key \"" << key << "\" found at [" << hash << "]\n";
  return map[hash].second;
};

Entity vecGet(std::vector<Entity> &vec, const std::string key) {
  for (const auto &v : vec) {
    if (v.name == key)
      return v;
  };
  std::cout << "WARN: Key \"" << key << "\" not found in vector!!!\n";
  return Entity();
};

#define HASH_MAP_CAP 1024

int main(int argc, char *argv[]) {
  std::vector<std::pair<std::string, Entity>> hashMap(HASH_MAP_CAP);
  Entity e1("Momoyon");
  Entity e2("Ahmed");
  Entity e3("Your Mom");
  Entity e4("Bob");
  Entity e5("Jeff");
  Entity e6("Ali");
  Entity e7("Ahmed");
  Entity e8("Mendes");
  Entity e9("Harry");
  Entity e10("Axel");

  hashInsert(hashMap, e1);
  hashInsert(hashMap, e2);
  hashInsert(hashMap, e3);
  hashInsert(hashMap, e4);
  hashInsert(hashMap, e5);
  hashInsert(hashMap, e6);
  hashInsert(hashMap, e7);
  hashInsert(hashMap, e8);
  hashInsert(hashMap, e9);
  hashInsert(hashMap, e10);
  std::vector<Entity> vec(HASH_MAP_CAP);
  vec.push_back(e1);
  vec.push_back(e2);
  vec.push_back(e3);
  vec.push_back(e4);
  vec.push_back(e5);
  vec.push_back(e6);
  vec.push_back(e7);
  vec.push_back(e8);
  vec.push_back(e9);
  vec.push_back(e10);

  std::string key = "Ali";

  std::cout << "----------------HASH MAP--------------------------\n";

  auto tp1 = std::chrono::system_clock::now();

  hashGet(hashMap, key);

  auto tp2 = std::chrono::system_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(tp2 - tp1);

  float dt = duration.count() / 1000.f;
  std::cout << "Retrieving took " << dt << "s\n";

  std::cout << "-----------------VECTOR-------------------\n";

  tp1 = std::chrono::system_clock::now();

  vecGet(vec, key);

  tp2 = std::chrono::system_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(tp2 - tp1);

  dt = duration.count() / 1000.f;
  std::cout << "Retrieving took " << dt << "s\n";

  return 0;
}
