#include <iostream>
#include <map>
#include <vector>
#include <utility>

struct Node {
  char id;
  bool operator< (const Node& rhs) const {
    return this->id < rhs.id;
  }
};

class Graph {

  private:
    std::map<Node, std::vector<Node> > mAdjacencyMap;
    
  public:
    Graph() {
    
    }; 
    
    void insertNode(Node n) {
      std::vector<Node> neighbors;
      std::pair<Node, std::vector<Node> > keyValuePair = std::make_pair(n, neighbors);
      mAdjacencyMap.insert(keyValuePair);
    }

    std::vector<Node> getAdjacentNodes(Node n) {
      return mAdjacencyMap[n];
    }

    /*
     How can I avoid an extra copy here? Without assigning neighbors back, it didn't work..
    */
    void insertEdge(std::pair<Node, Node> edge) {
      std::vector<Node> neighbors = mAdjacencyMap[edge.first];
      neighbors.emplace_back(edge.second);
      mAdjacencyMap[edge.first] = neighbors;
    }

    void printGraph() {
      for (std::map<Node, std::vector<Node> >::iterator it = mAdjacencyMap.begin(); it != mAdjacencyMap.end(); ++it) {
	std::cout << it->first.id << "->";
        for (auto neighbor : it->second) {
          std::cout << neighbor.id << ',';
        }
        std::cout << '\n';
      }
    }
};

int main() {
  Node a = {'a'};
  Node b = {'b'};
  Node c = {'c'};
  
  Graph g;

  g.insertNode(a);
  g.insertNode(b);
  g.insertNode(c);

  std::pair<Node, Node> edge = std::make_pair(a, b);
  std::pair<Node, Node> edge2 = std::make_pair(a, c);
  std::pair<Node, Node> edge3 = std::make_pair(b, c);

  g.insertEdge(edge); 
  g.insertEdge(edge2);
  g.insertEdge(edge3);
  
  g.printGraph();

  std::vector<Node> neighbors = g.getAdjacentNodes(a);

  std::cout << "Adjacent Nodes " << neighbors[0].id << neighbors[1].id << std::endl;
}
