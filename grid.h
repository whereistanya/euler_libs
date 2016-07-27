#ifndef H_GRID
#define H_GRID

using namespace std;

struct Node {
  // give access to private members for printing
  friend ostream &operator<<( ostream &out, const Node& n);
  Node();
  Node(int _x, int _y);
  Node(const Node& n);
  bool operator==(const Node& n) const;
  bool operator!=(const Node& n) const;
  bool operator < (const Node& n) const;
  int x;
  int y;
};

ostream& operator<<(ostream& os, const Node& n);

class Grid {
public:
  Grid(int h, int w);
  ~Grid();
  int operator()(int i, int j);
  int operator()(Node n);
  int get(int i, int j);
  int get(Node n);
  bool set(int i, int j, int value);
  bool ok(int i, int j);
  int width();
  int height();

private:
  bool InBounds(int i, int j);
  int* data;
  int maxwidth;
  int maxheight;
};

#endif
