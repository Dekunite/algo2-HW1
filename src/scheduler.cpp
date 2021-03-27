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

#include "data_structs.h"

using namespace std;

class Node {
  string letter;
  int value;
  int verticeNum;

  public:
    Node(string letter, int value, int verticeNum);
    Node();
    int getVerticeNum();
    int getValue();
    string getLetter();
};

Node::Node(string letter1, int value1, int verticeNum1) {
  letter = letter1;
  value = value1;
  verticeNum = verticeNum1;
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

class Graph {
  Node numberOfVertices;
  list<Node>* adj;

  public:

    Graph(Node* numberOfVertices);
    void addEdge(Node src, Node dest);
    void BFS(Node startVertex);
};

Graph::Graph(Node* numberOfVertices) {
  this->numberOfVertices = *numberOfVertices;
  int verticeNum = numberOfVertices->getVerticeNum();
  adj = new list<Node>[1000];
}

void Graph::addEdge(Node parent, Node child) {
  adj[parent.getVerticeNum()].push_back(child);
}

void Graph::BFS(Node node) {
  
  int verticeNum = node.getVerticeNum();
  bool* visited = new bool[50];
  for(int i = 0; i < 50; i++) {
    visited[i] = false;
  }

  list<Node> queue;

  //mark current node visited and enqueue
  visited[node.getVerticeNum()] = true;
  queue.push_back(node);

  list<Node>::iterator i;

  while(!queue.empty()) {
    node = queue.front();
    cout << "letter: " << node.getLetter() << endl;
    cout << "Vertice Num: " << node.getVerticeNum() << endl;
    cout << "value: " << node.getValue() << endl;
    queue.pop_front();

    int adjSize = adj->size();
    for(int i = 0; i < adjSize; i++) {

      if(!visited[i]) {
        visited[i] = true;
        queue.push_back(node);
      }
    }

  }
}

int main(int argc, char* argv[])
{
  const char* filename = "TWO TWO FOUR.txt";
  //const char* filename = argv[1];

  ifstream file(filename);
  string input;

  Node* newNode = new Node("asda",2,0);
  Node* newNode0 = new Node("asda",2,0);
  Node* newNode1 = new Node("asda",2,1);
  Node* newNode2 = new Node("asda",2,2);
  Node* newNode3 = new Node("asda",2,3);
  Node* newNode4 = new Node("asda",2,4);
  Node* newNode5 = new Node("asda",2,5);
  Node* newNode6 = new Node("asda",2,6);
  Node* newNode7 = new Node("asda",2,7);

  Graph graph(newNode0);
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

  if(!file)
  {
    cerr << "Cannot open file" << endl;
    return EXIT_FAILURE;
  }

  while(getline(file, input)) {
    cout << input << endl;
    cout << "end of line" << endl;

    istringstream columns(input);
    string column;
    while(columns >> column) {
      cout << column <<endl;
    }
  }

  cout << "hello world" << endl;
  
  return EXIT_SUCCESS;
  
}