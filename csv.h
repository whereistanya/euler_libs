#include <fstream>
#include <sstream>
#include "grid.h"

using namespace std;

bool FilenameToArray(string filename, Grid& grid) {

  ifstream ifs;
  ifs.open(filename.c_str());
  if (!ifs.is_open()) {
    cout << "ERROR: Can't open file " << filename << endl;
    return false;
  }
  string line, node;
  stringstream ss;
  int i = 0;
  // csv to array strip newlines
  while (getline(ifs, line)) {
    int j = 0;
    ss << line;
    while (getline(ss, node, ',')) {
      if (node[node.length() - 1] == '\r') {
        node.resize(node.size() - 1);
      }
      if (grid.ok(i, j)) {
        grid.set(i, j, atoi(node.c_str()));
        j++;
      } else {
        return false;
      }
    }
    i++;
    ss.clear();
  }
  return true;
}
