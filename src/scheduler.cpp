/* @Author
Student Name: <Muhammet Derviş Kopuz>
Student ID : <504201531>
Date: <06/04/2021> */

#include<fstream>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include <sstream>
#include <list>
#include <vector>
#include <math.h>

#include "data_structs.h"

using namespace std;

class Core {
  public:
  string letter;
  int value;

  Core(string letter, int value);
};

Core::Core (string letter1, int value1) {
  letter = letter1;
  value = value1;
}

class Node {
  //string letter;
  //int value;
  vector<Core>* cores;
  int verticeNum;
  bool visited;

  public:
    Node(Core core, int verticeNum);
    Node();
    int getVerticeNum();
    //int getValue();
    //string getLetter();
    bool getVisited();
    void setVisited(bool value);
    Core getCore(int coreNumber);
    void addCore(Core core);
};

Node::Node (Core core, int verticeNum1) {
  cores = new vector<Core>;
  cores->push_back(core);
  verticeNum = verticeNum1;
  visited = false;
}

Node::Node() {
  
}

int Node::getVerticeNum() {
  return verticeNum;
}

bool Node::getVisited() {
  return visited;
}

void Node::setVisited(bool value) {
  visited = value;
}

Core Node::getCore(int coreNum) {
  return cores->at(coreNum);
}

void Node::addCore(Core core) {
  cores->push_back(core);
}

class Graph {
  //Node* vertex;
  //vector<Node>* adj;

  public:
    Node* vertex;
    Graph(Node* vertex);
    void addEdge(Node* src, Node* dest);
    void BFS(Node startVertex);

    vector<Node>* adj;
};

Graph::Graph(Node* vertex1) {
  vertex = vertex1;
  int verticeNum = vertex1->getVerticeNum();
  //adj boyutunu dinamik hale getir
  adj = new vector<Node>[1000];
}

void Graph::addEdge(Node* parent, Node* child) {
  adj[parent->getVerticeNum()].push_back(*child);
}

void Graph::BFS(Node node) {
  
  int verticeNum = node.getVerticeNum();
  //list<bool>* visited = new list<bool>[50];
  //for(int i = 0; i < 50; i++) {
    //visited[i] = false;
  //}

  list<Node> queue;

  //mark current node visited and enqueue
  node.setVisited(true);
  queue.push_back(node);

  list<Node>::iterator i;

  int adjCounter = 0;
  while(!queue.empty()) {
    node = queue.front();
    cout << "Vertice Num: " << node.getVerticeNum() << endl;
    queue.pop_front();

    int adjSize = adj[adjCounter].size();
    //vector<Node> adj = new vector<int>[100];
    for (int i = 0; i != adjSize; ++i) {
      auto test = adj[adjCounter].at(i);
      if(!adj[adjCounter].at(i).getVisited()) {
        adj[adjCounter].at(i).setVisited(true);
        queue.push_back(adj[adjCounter].at(i));
      }
    }

    adjCounter++;

  }
}

bool checkSummationRuleStart(Core operand1, Core operand2, Core result) {
  int carry = 0;
  if ((operand1.value + operand2.value) >= 10) {
    carry = 1;
  }

  if ((operand1.value + operand2.value) == (result.value + 10 * carry)) {
    return true;
  }
  return false;
}

bool checkSummationRule(Core operand1, Core operand2, Core result, int carry1) {
  int carry2 = 0;
  if ((operand1.value + operand2.value + carry1) >= 10) {
    carry2 = 1;
  }

  if ((operand1.value + operand2.value + carry1) == (result.value + 10 * carry2)) {
    return true;
  }
  return false;
}

bool checkSummationRuleEnd(Core operand, int carry) {
  if(operand.value == carry) {
    return true;
  }
  return false;
}

int main(int argc, char* argv[])
{
  const char* filename = "TWO TWO FOUR.txt";
  const string searchMethod = "BFS";
  const string operand1 = "TWO";
  const string operand2 = "TWO";
  const string result = "FOUR";
  //const char* filename = argv[1];

  ifstream file(filename);
  string input;

  Core* newCore = new Core("a",1);
  Node* newNode0 = new Node(*newCore,0);
  Node* newNode1 = new Node(*newCore,1);
  Node* newNode2 = new Node(*newCore,2);
  Node* newNode3 = new Node(*newCore,3);
  Node* newNode4 = new Node(*newCore,4);
  Node* newNode5 = new Node(*newCore,5);
  Node* newNode6 = new Node(*newCore,6);
  Node* newNode7 = new Node(*newCore,7);

  Graph graph(newNode0);
  graph.addEdge(newNode0,newNode1);
  graph.addEdge(newNode0,newNode2);
  graph.addEdge(newNode0,newNode3);
  graph.addEdge(newNode1,newNode6);
  graph.addEdge(newNode1,newNode7);
  graph.addEdge(newNode2,newNode5);
  graph.addEdge(newNode3,newNode4);

  cout << "Breadth First Traversal ";
	cout << "(starting from vertex 0) \n";
	graph.BFS(*newNode0);
  

  if(!file)
  {
    cerr << "Cannot open file" << endl;
    return EXIT_FAILURE;
  }

  vector<int> numbers = {0,1,2,3,4,5,6,7,8,9};
  vector<string> letters = {"T","W","O","F","U","R"};
  //get inputs line by line
  /*
  while(getline(file, input)) {
    cout << input << endl;
    cout << "end of line" << endl;

    istringstream columns(input);
    string column;
    if(numbers.empty()) {
      while(columns >> column) {
        cout << column <<endl;
        numbers.push_back(column);
      }
    } else {
      while(columns >> column) {
        if(column != ".") {
          letters.push_back(column);
        }
        cout << column <<endl;
      }
      cout << numbers.size() << " " << letters.size() <<endl;
    }
  }
  */

  int nodeCount =pow(numbers.size(), letters.size());

  //Core* newCore = new Core("start",1);
  //Node* startNode = new Node(newCore, 0);
  //Graph graph(startNode);
  //graph.adj[0].push_back(*startNode);
  int verticeCounterLetter = 0;
  int verticeCounterNumber = 0;
  int verticeCounterCopy = 0;

  //start node a eklemeler
  for( string letter : letters) {
    for(int i = 0; i < 10; i++) {
      for( int number : numbers) {
        Core* newCore = new Core(letter, number); 
        //Node* newNode = new Node(newCore, verticeCounterNumber);
        //graph.addEdge(graph.vertex, newNode); //Add a new node with every value to parent
        verticeCounterNumber++;

      }
      verticeCounterCopy++;
    }
    verticeCounterLetter++;

  }

  cout << "hello world" << endl;
  
  return EXIT_SUCCESS;
  
}