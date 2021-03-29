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

class Node {
  string letter;
  int value;
  int verticeNum;
  bool visited;

  public:
    Node(string letter, int value, int verticeNum);
    Node();
    int getVerticeNum();
    int getValue();
    string getLetter();
    bool getVisited();
    void setVisited(bool value);
};

Node::Node(string letter1, int value1, int verticeNum1) {
  letter = letter1;
  value = value1;
  verticeNum = verticeNum1;
  visited = false;
}

Node::Node() {
  
}

int Node::getVerticeNum() {
  return verticeNum;
}

string Node::getLetter() {
  return letter;
}

int Node::getValue() {
  return value;
}

bool Node::getVisited() {
  return visited;
}

void Node::setVisited(bool value) {
  visited = value;
}

class Graph {
  Node numberOfVertice;
  //vector<Node>* adj;

  public:

    Graph(Node numberOfVertice);
    void addEdge(Node src, Node dest);
    void BFS(Node startVertex);

    vector<Node>* adj;
};

Graph::Graph(Node numberOfVertice) {
  this->numberOfVertice = numberOfVertice;
  int verticeNum = numberOfVertice.getVerticeNum();
  //adj boyutunu dinamik hale getir
  adj = new vector<Node>[1000];
}

void Graph::addEdge(Node parent, Node child) {
  adj[parent.getVerticeNum()].push_back(child);
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
    cout << "letter: " << node.getLetter() << endl;
    cout << "Vertice Num: " << node.getVerticeNum() << endl;
    cout << "value: " << node.getValue() << endl;
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

bool checkSummationRuleStart(Node operand1, Node operand2, Node result) {
  int carry = 0;
  if ((operand1.getValue() + operand2.getValue()) >= 10) {
    carry = 1;
  }

  if ((operand1.getValue() + operand2.getValue()) == (result.getValue() + 10 * carry)) {
    return true;
  }
  return false;
}

bool checkSummationRule(Node operand1, Node operand2, Node result, int carry1) {
  int carry2 = 0;
  if ((operand1.getValue() + operand2.getValue() + carry1) >= 10) {
    carry2 = 1;
  }

  if ((operand1.getValue() + operand2.getValue() + carry1) == (result.getValue() + 10 * carry2)) {
    return true;
  }
  return false;
}

bool checkSummationRuleEnd(Node operand, int carry) {
  if(operand.getValue() == carry) {
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

  /*
  Node* newNode = new Node("asda",2,0);
  Node* newNode0 = new Node("a",2,0);
  Node* newNode1 = new Node("b",2,1);
  Node* newNode2 = new Node("c",2,2);
  Node* newNode3 = new Node("d",2,3);
  Node* newNode4 = new Node("e",2,4);
  Node* newNode5 = new Node("f",2,5);
  Node* newNode6 = new Node("g",2,6);
  Node* newNode7 = new Node("h",2,7);

  Graph graph(*newNode0);
  graph.addEdge(*newNode0,*newNode1);
  graph.addEdge(*newNode0,*newNode2);
  graph.addEdge(*newNode0,*newNode3);
  graph.addEdge(*newNode1,*newNode4);
  graph.addEdge(*newNode1,*newNode5);
  graph.addEdge(*newNode2,*newNode6);
  graph.addEdge(*newNode3,*newNode7);

  cout << "Breadth First Traversal ";
	cout << "(starting from vertex 0) \n";
	graph.BFS(*newNode0);
  */

  if(!file)
  {
    cerr << "Cannot open file" << endl;
    return EXIT_FAILURE;
  }

  vector<string> numbers;
  vector<string> letters;
  //get inputs line by line
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

  int nodeCount =pow(numbers.size(), letters.size());
  Node* startNode = new Node("start",0,0);
  Graph graph(*startNode);
  graph.adj[0].push_back(*startNode);
  int verticeCounterLetter = 0;
  int verticeCounterNumber = 0;
  int verticeCounterCopy = 0;

  for( string letter : letters) {
    for(int i = 0; i < graph.adj[0].size(); i++) {
      for( string number : numbers) {
        graph.addEdge(graph.adj[verticeCounterCopy].at(i), *new Node(letter, stoi(number), verticeCounterNumber)); //Add a new node with every value to parent
        verticeCounterNumber++;

      }
      verticeCounterCopy++;
    }
    verticeCounterLetter++;

  }

  cout << "hello world" << endl;
  
  return EXIT_SUCCESS;
  
}