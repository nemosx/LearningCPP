#include <iostream>
#include <map>
#include <vector>
#include <utility>

struct Node {
  char id;

  Node(char);

  bool
  operator< (const Node& rhs) const;
};

class Graph {

  public:

    Graph() = default;

    const std::vector<Node>&
    getAdjacentNodes(const Node& n) const;

    void
    insertEdge(const Node& src, const Node& dest);

    friend std::ostream&
    operator<<(std::ostream&, const Graph &);

  private:
    std::map<Node, std::vector<Node>> mAdjacencyMap;
};

Node::Node(char c) : id(c) {
}

bool
Node::operator<(const Node& rhs) const {
  return id < rhs.id;
}

std::ostream&
operator<<(std::ostream& os, const Node& n) {
  return (os << n.id);
}

const std::vector<Node>&
Graph::getAdjacentNodes(const Node& n) const {
  return mAdjacencyMap.at(n);
}

void
Graph::insertEdge(Node const & src, Node const & dest) {
  mAdjacencyMap.try_emplace(src);
  mAdjacencyMap.try_emplace(dest);
  mAdjacencyMap[src].push_back(dest);
}

std::ostream&
operator<<(std::ostream &os, const Graph& g) {
  for (const auto & [src, adjacentNodes] : g.mAdjacencyMap) {
    os << src << "=>";
    bool firstItem = true;
    
    for(auto & node : adjacentNodes) {
      if (!firstItem) {
        os << ',';
      }
      os << node;
      firstItem = false;
    }
    os << '\n';
  }
  return os;
}


void
dfsTraversal(const Graph& g, const Node& start) {
  auto neighbors = g.getAdjacentNodes(start);
  for (auto n : neighbors) {
    dfsTraversal(g, n);
  }
  std::cout<< "Finished exploring: " << start << std::endl;
}

int main() {
  Graph g;

  g.insertEdge('a', 'b');
  g.insertEdge('b', 'c');
  g.insertEdge('b', 'd');
  g.insertEdge('d', 'e');
  g.insertEdge('c', 'h');

  std::cout << g << '\n';

  const auto neighbors = g.getAdjacentNodes({'a'}); 
  std::cout<< "Adjacent Nodes to 'a' are: ";
  for (auto n : neighbors) {
    std::cout << ' ' <<  n;
  }
  std::cout << std::endl;

  dfsTraversal(g, {'a'});
}
