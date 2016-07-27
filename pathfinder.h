#include <iostream>
#include <map>
#include <set>
#include "grid.h"

using namespace std;

int Estimate(Node n, Grid& grid) {
  int distance = (grid.height() - n.x) + (grid.width() - n.y);
  return distance;
}

int GetPathCost(Node& start, set<Node>& targets, Grid& grid,
                void neighbour_function(Node& n, set<Node>& neighbours, Grid& grid)) {
  // Find the minimal path sum from start to finish
  map<Node, int> g_score, h_score, f_score;
  set<Node> closedset;
  set<Node> openset;
  set<Node> neighbours;
  map<Node, Node> came_from;

  g_score[start] = grid.get(start);
  h_score[start] = Estimate(start, grid);
  f_score[start] = g_score[start] + h_score[start];

  openset.insert(start);

  while (! openset.empty()) {
    Node current = *openset.begin();
    for (set<Node>::const_iterator it = openset.begin(); it != openset.end(); ++it) {
      if (f_score[*it] < f_score[current]) {
        current = *it;
      }
    }
    if (targets.find(current) != targets.end()) {
      cout << "Found target" << endl;
      int sum = 0;
      while (current != start) {
        cout << grid(current) << " ";
        sum += grid(current);
        current = came_from[current];
      }
      cout << grid(current) << endl;
      sum += grid(current);

      return sum;
    }
    openset.erase(current);
    closedset.insert(current);
    neighbours.clear();
    neighbour_function(current, neighbours, grid);
    for (set<Node>::const_iterator it = neighbours.begin(); it != neighbours.end(); ++it) {
      Node neighbour = *it;
      // if neighbour is in closedset
      if (closedset.find(neighbour) != closedset.end()) {
        continue;
      }
      int tentative_g_score = g_score[current] + grid.get(neighbour);
      bool tentative_is_better;
      // if neighbout not in openset
      if (openset.find(neighbour) == openset.end()) {
        openset.insert(neighbour);
        h_score[neighbour] = Estimate(neighbour, grid);
        tentative_is_better = true;
      } else if (tentative_g_score < g_score[neighbour]) {
        tentative_is_better = true;
      } else {
        tentative_is_better = false;
      }

      if (tentative_is_better == true) {
        came_from[neighbour] = current;
        g_score[neighbour] = tentative_g_score;
        f_score[neighbour] = g_score[neighbour] + h_score[neighbour];
      }
    }
  }
  cout << "Tried all available nodes." << endl;
  return -1;
}

