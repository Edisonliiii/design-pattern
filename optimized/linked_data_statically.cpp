#include <iostream>

/**
 * @brief
 * the addr of array elements are constant expression
 *
 */

struct treenode {
  char const* name;
  treenode* left;
  treenode* right;
} tree[] = {
    {"D", &tree[1], &tree[2]}, {"B", &tree[3], &tree[4]},
    {"F", &tree[5], nullptr},  {"A", nullptr, nullptr},
    {"C", nullptr, nullptr},   {"E", nullptr, nullptr},
};

struct cyclenode {
  char const* name;
  cyclenode* next;
};

extern cyclenode first;
cyclenode forth = {"4", &first};
cyclenode third = {"3", &forth};
cyclenode second = {"2", &third};
cyclenode first = {"1", &second};