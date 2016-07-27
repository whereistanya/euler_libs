#include <fstream>
#include <iostream>
#include <sstream>

#include "grid.h"

using namespace std;

Node::Node() {}

Node::Node(int _x, int _y) {
  x = _x;
  y = _y;
}
Node::Node(const Node& n) {
  x = n.x;
  y = n.y;
}

bool Node::operator==(const Node& n) const {
  return ((n.x == x) && (n.y == y));
}
bool Node::operator!=(const Node& n) const {
  return (!(n.x == x) || !(n.y == y));
}

bool Node::operator < (const Node& n) const {
  if (n.x < x) {
    return true;
  }
  if ((n.x == x) && (n.y < y)) return true;
  return false;
}

ostream& operator<<(ostream& os, const Node& n) {
  os << "[" << n.x << ", " << n.y << "]";
  return os;
}

Grid::Grid(int h, int w) {
  maxheight = h;
  maxwidth = w;
  data = new int[h * w];
  for (int i = 0; i < maxheight * maxwidth; i++) {
      data[i] = 0;
  }
}

Grid::~Grid() {
  delete[] data;
}

// If there's any change of this being out of bounds, use get() instead
int Grid::operator()(int i, int j) {
  int d = -1;
  if (InBounds(i, j)) {
    d = data[i + j * maxwidth];
  }
  return d;
}

int Grid::operator()(Node n) {
  int d = -1;
  if (InBounds(n.x, n.y)) {
    d = data[n.x + n.y * maxwidth];
  }
  return d;
}

int Grid::get(int i, int j) {
  if (InBounds(i, j)) {
    return data[i + j * maxwidth];
  }
  else {
    cout << "ERROR: " << i << ", " << j << " is out of bounds" << endl;
    return -1;
  }
}

int Grid::get(Node n) {
  return get(n.x, n.y);
}

bool Grid::set(int i, int j, int value) {
  if (InBounds(i, j)) {
   data[i + j * maxwidth] = value;
   return true;
  } else {
    cout << "ERROR: " << i << ", " << j << " is out of bounds" << endl;
    return false;
  }
}
bool Grid::ok(int i, int j) {
  return InBounds(i, j);
}
int Grid::width() {
  return maxwidth;
}

int Grid::height() {
  return maxheight;
}

bool Grid::InBounds(int i, int j) {
  if ((i < 0) || (j < 0)) {
    //cout << "ERROR: " << i << ", " << j << " is out of bounds" << endl;
    return false;
  }
  if ((i >= maxheight) || (j >= maxwidth)) {
    //cout << "ERROR: " <<i << ", " << j << " is out of bounds" << endl;
    return false;
  }
  return true;
}
