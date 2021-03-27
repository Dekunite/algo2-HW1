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
    int getVerticeNum();
    int getValue();
    string getLetter();
};

Node::Node(string letter, int value, int verticeNum) {
  this->letter = letter;
  this->value = value;
  this->verticeNum = verticeNum;
}

int Node::getVerticeNum() {
  return this->verticeNum;
}

string Node::getLetter() {
  return this->letter;
}

int Node::getValue() {
  return this->value;
}

class Graph {
  Node numberOfVertices;
  list<Node>* adj;

  public:

    Graph(Node numberOfVertices);
    void addEdge(Node src, Node dest);
    void BFS(Node startVertex);
};

Graph::Graph(Node numberOfVertices) {
  this->numberOfVertices = numberOfVertices;
  int verticeNum = numberOfVertices.getVerticeNum();
  adj = new list<Node>[verticeNum];
}

void Graph::addEdge(Node parent, Node child) {
  adj[parent.getVerticeNum()].push_back(child);
}

void Graph::BFS(Node node) {
  
  int verticeNum = node.getVerticeNum();
  bool* visited = new bool[verticeNum];
  for(int i = 0; i < verticeNum; i++) {
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
        queue.push_back(adj[node.getVerticeNum()].begin());
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

  Node newNode = Node("asda",2,2);

  Graph graph(newNode);
  graph.addEdge(0,1);
  graph.addEdge(0,2);
  graph.addEdge(0,3);
  graph.addEdge(1,4);
  graph.addEdge(1,5);
  graph.addEdge(2,6);
  graph.addEdge(3,7);

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