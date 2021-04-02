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
#include <algorithm>
#include <bits/stdc++.h> // for sort()

#include "data_structs.h"

using namespace std;

//Forward Declerations
class Node;
bool checkZeroConditions(string operand1, Node currentNode);
bool checkSummationRuleStart(int operand1, int operand2, int result);
int getLastValue(string operand1, Node currentNode);
int getValue(string letter, Node currentNode);
bool loopDigits(string operand1, string operand2, string result, Node currentNode);
bool checkSummationRule(int operand1, int operand2, int result, int carry1);
bool checkSummationRuleEnd(int operand, int carry);

class Node {
  //string letter;
  //int value;

  public:
    Node(string letter, int value, int verticeNum);
    Node();

    vector<string>* letters;
    vector<int>* values;
    int verticeNum;
    bool visited;
    };

Node::Node (string letter, int value, int verticeNum1) {
  letters = new vector<string>;
  letters->push_back(letter);
  values = new vector<int>;
  values->push_back(value);
  verticeNum = verticeNum1;
  visited = false;
}

Node::Node() {
  letters = new vector<string>;
  values = new vector<int>;
  visited = false;
}

class Graph {
  //Node* vertex;
  //vector<Node>* adj;

  public:
    Graph(Node* vertex,int lettersSize);
    void addEdge(Node src, Node* dest);
    void BFS(Node startVertex,string operand1, string operand2, string result, list<string> letters);
    void DFS(Node startVertex,string operand1, string operand2, string result, list<string> letters);

    Node* vertex;
    vector<Node>* adj;
};

Graph::Graph(Node* vertex1, int lettersSize) {
  vertex = vertex1;
  int verticeNum = vertex1->verticeNum;
  long adjSize = pow(10, lettersSize);
  adjSize =100000000;
  //adj boyutunu dinamik hale getir
  adj = new vector<Node>[adjSize];
}

void Graph::addEdge(Node parent, Node* child) {
  adj[parent.verticeNum].push_back(*child);
}

void Graph::BFS(Node node, string operand1, string operand2, string result, list<string> letters) {
  
  int verticeNum = node.verticeNum;
  //list<bool>* visited = new list<bool>[50];
  //for(int i = 0; i < 50; i++) {
    //visited[i] = false;
  //}

  list<Node> queue;

  //mark current node visited and enqueue
  node.visited = true;
  queue.push_back(node);

  list<Node>::iterator i;

  int adjCounter = 0;
  while(!queue.empty()) {
    node = queue.front();
    //cout << "Vertice Num: " << node.verticeNum << endl;
    //cout << "Letters Num: " << node.letters << endl;
    queue.pop_front();

    int adjSize = adj[node.verticeNum].size();
    //vector<Node> adj = new vector<int>[100];
    for (int i = 0; i != adjSize; ++i) {
      Node currentNode = adj[node.verticeNum].at(i);
      if(!currentNode.visited) {
        currentNode.visited = true;
        //cout << currentNode.verticeNum << endl;

        cout << "vertice num: " << currentNode.verticeNum << endl;
        for (int i = 0; i<currentNode.letters->size(); i++) {
          cout << currentNode.letters->at(i) << " " ;
        }
        cout << endl;
        for (int i = 0; i<currentNode.values->size(); i++) {
          cout << currentNode.values->at(i) << " " ;
        }
        cout << endl;

        //aynı sayı kontrolü
        vector<int> temp = *currentNode.values;
        sort(temp.begin(), temp.end());
        auto valueIterator = unique(temp.begin(), temp.end());
        bool hasDuplicates = !(valueIterator == temp.end());
        if (hasDuplicates) {
          continue;
        }

        //not 0 conditions
        if (!checkZeroConditions(operand1, currentNode)) {
          continue;
        }

        if (!checkZeroConditions(operand2, currentNode)) {
          continue;
        }

        if (!checkZeroConditions(result, currentNode)) {
          continue;
        }

        //Check summation rules
        bool passed = checkSummationRuleStart(getLastValue(operand1, currentNode),
                                              getLastValue(operand2, currentNode),
                                              getLastValue(result, currentNode));
        if (!passed) {
          continue;
        }

        passed = loopDigits(operand1, operand2, result, currentNode);
        if (!passed) {
          continue;
        }
        
        /*
        cout << currentNode.verticeNum << endl;
        for (int i = 0; i<currentNode.letters->size(); i++) {
          cout << currentNode.letters->at(i) << " " ;
        }
        cout << endl;
        for (int i = 0; i<currentNode.values->size(); i++) {
          cout << currentNode.values->at(i) << " " ;
        }
        */

        queue.push_back(currentNode);
        cout << "pushed" << endl;
        if (currentNode.letters->size() == letters.size() + 1) {
          cout << "result found" << endl;
          break;
        }
      }
    }

    adjCounter++;

  }
}

void Graph::DFS(Node node, string operand1, string operand2, string result, list<string> letters) {
 
  int verticeNum = node.verticeNum;

  //mark current node visited and enqueue
  node.visited = true;
  cout << node.verticeNum << " ";

  list<Node>::iterator* i;

  // Recur for all the vertices adjacent to this vertex
	int adjSize = adj[node.verticeNum].size();
  for (int i = 0; i != adjSize; ++i) {
    Node currentNode = adj[node.verticeNum].at(i);
    if(!currentNode.visited) {
      cout << "vertice num: " << currentNode.verticeNum << endl;
      for (int i = 0; i<currentNode.letters->size(); i++) {
        cout << currentNode.letters->at(i) << " " ;
      }
      cout << endl;
      for (int i = 0; i<currentNode.values->size(); i++) {
        cout << currentNode.values->at(i) << " " ;
      }
      cout << endl;

      //aynı sayı kontrolü
      vector<int> temp = *currentNode.values;
      sort(temp.begin(), temp.end());
      auto valueIterator = unique(temp.begin(), temp.end());
      bool hasDuplicates = !(valueIterator == temp.end());
      if (hasDuplicates) {
        continue;
      }

      //not 0 conditions
      if (!checkZeroConditions(operand1, currentNode)) {
        continue;
      }

      if (!checkZeroConditions(operand2, currentNode)) {
        continue;
      }

      if (!checkZeroConditions(result, currentNode)) {
        continue;
      }

      //Check summation rules
      bool passed = checkSummationRuleStart(getLastValue(operand1, currentNode),
                                            getLastValue(operand2, currentNode),
                                            getLastValue(result, currentNode));
      if (!passed) {
        continue;
      }

      passed = loopDigits(operand1, operand2, result, currentNode);
      if (!passed) {
        continue;
      }

      cout << "pushed" << endl;
      if (currentNode.letters->size() == letters.size() + 1) {
        cout << "result found" << endl;
        break;
      }
      DFS(currentNode, operand1, operand2, result, letters);
    }
  }
}

bool loopDigits(string operand1, string operand2, string result, Node currentNode) {
  int length1 = operand1.length() - 2 ;
  int length2 = operand2.length() - 2;
  int resultLength = result.length() - 2;

  while (length1 >= 0 && length2 >= 0 && resultLength >= 0) {
    //bir önceki basamaklar toplamı 10 dan büyükse 1 değilse 0
    int carry = (getValue(string(1, operand1.at(length1 + 1)), currentNode) + getValue(string(1, operand2.at(length2 + 1)), currentNode)) >= 10 ? 1 : 0;

    int value1 = getValue(string(1, operand1.at(length1)), currentNode);
    int value2 = getValue(string(1, operand2.at(length1)), currentNode);
    int valueR = getValue(string(1, result.at(resultLength)), currentNode);

    bool passed = checkSummationRule(value1, value2, valueR, carry);
    if (!passed) {
      return false;
    }

    length1--;
    length2--;
    resultLength--;

  }

  //ilk basamak kontrol
  if (resultLength == 0) {
    int carry = (getValue(string(1, operand1.at(length1 + 1)), currentNode) + getValue(string(1, operand2.at(length2 + 1)), currentNode)) > 10 ? 1 : 0;

    int valueR = getValue(string(1, result.at(resultLength)), currentNode);
    bool passed = checkSummationRuleEnd(valueR, carry);
    if (!passed) {
      return false;
    }
  }

  return true;
}

int getValue(string letter, Node currentNode) {
  for (int k = 0; k < currentNode.letters->size(); k++) {
    if (letter == currentNode.letters->at(k)) {
      return currentNode.values->at(k);
    }
  }
  return -1;
}

bool checkZeroConditions(string operand1, Node currentNode) {
  //int operand1Length = operand1.length();
  //for (int i = 0; i < operand1Length - 2; i++) { //W 0 olmama sebebi var mı?
  for (int i = 0; i < 1; i++) {
    string letter = string(1, operand1.at(i));
    for (int k = 0; k < currentNode.letters->size(); k++) {
      if (letter == currentNode.letters->at(k)) {
        if(currentNode.values->at(k) == 0) {
          return false;
        }
      }
    }
  }
  return true;
}

int getLastValue(string operand1, Node currentNode) {
  int length = operand1.size();
  string lastLetter = string(1,operand1.at(length-1));

  for (int k = 0; k < currentNode.letters->size(); k++) {
    if (lastLetter == currentNode.letters->at(k)) {
      return currentNode.values->at(k);
    }
  }
  return -1;
}

bool checkSummationRuleStart(int operand1, int operand2, int result) {
  if (operand1 == -1 || operand2 == -1 || result == -1) {
    return true;
  }

  int carry = 0;
  if ((operand1 + operand2) >= 10) {
    carry = 1;
  }

  if (((operand1 + operand2) == (result + 10 * carry))) {
    return true;
  }
  return false;
}

bool checkSummationRule(int operand1, int operand2, int result, int carry1) {
  if (operand1 == -1 || operand2 == -1 || result == -1) {
    return true;
  }

  int carry2 = 0;
  if ((operand1 + operand2 + carry1) >= 10) {
    carry2 = 1;
  }

  if ((operand1 + operand2 + carry1) == (result + 10 * carry2)) {
    return true;
  }
  return false;
}

bool checkSummationRuleEnd(int operand, int carry) {
  if (operand == -1) {
    return true;
  }

  if(operand == carry) {
    return true;
  }
  return false;
}

Node* cloneNode(Node parent) {
  Node* newNode = new Node();
  *newNode->letters = *parent.letters;
  *newNode->values = *parent.values;
  newNode->visited = false;

  return newNode;
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
  */

  if(!file)
  {
    cerr << "Cannot open file" << endl;
    return EXIT_FAILURE;
  }

  vector<int> numbers = {0,1,2,3,4,5,6,7,8,9};
  //list<string> letters = {"T","W","O","F","U","R"};
  list<string> letters = {"S","E","N","D","M","O","R","Y"};
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
  Node* startNode = new Node("start", 0, 0);
  Graph graph(startNode, letters.size());
  //graph.adj[0].push_back(*startNode);
  int verticeCounterNumber = 1;
  int layerCount = 0;
  int adjCounter = 0;

  //start node a eklemeler
  for( string letter : letters) {
    for( int number : numbers) {
      Node* newNode = new Node(letter, number, verticeCounterNumber);
      graph.addEdge(*graph.vertex, newNode); //Add a new node with every value to parent
      verticeCounterNumber++;
    }
    break;
  }

  //graph.BFS(*startNode);

  layerCount++;
  letters.pop_front();

  for( string letter : letters) {
    for(int k = 0; k<layerCount; k++) { //graph.adj[adjCounter].size()
      for(int i = 0; i < 10; i++) {
        for( int number : numbers) {
          //cout << graph.adj[adjCounter].at(i).letters->back() <<endl;
          Node* newNode = cloneNode(graph.adj[adjCounter].at(i));
          newNode->verticeNum = verticeCounterNumber;
          newNode->letters->push_back(letter);
          newNode->values->push_back(number);
          graph.addEdge(graph.adj[adjCounter].at(i), newNode); //Add a new node with every value to parent
          verticeCounterNumber++;

        }
      }
      adjCounter++;
    }
    if (layerCount == 0) {
      layerCount = 1;
    }
    layerCount *= 10;
  }

  graph.BFS(*startNode, operand1, operand2, result, letters);
  //graph.DFS(*startNode, operand1, operand2, result, letters);

  cout << "hello world" << endl;
  
  return EXIT_SUCCESS;
  
}