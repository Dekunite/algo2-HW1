/* @Author
Student Name: <Muhammet Derviş Kopuz>
Student ID : <504201531>
Date: <06/04/2021> */

#include<iostream>
#include <fstream>
//#include<stdlib.h>
//#include <sstream>
#include <list>
#include <vector>
#include <math.h>
#include <algorithm>
//#include <bits/stdc++.h> // for sort()

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
int getPrevCarry (string operand1, string operand2, string result, Node currentNode, int length1, int length2, int minsize);


class Node {

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

class Message {
  public:
    Message(bool success1);
    Message();

    bool success;
    Node* result;
};

Message::Message(bool success1) {
  success = success1;
  result = new Node();
}

Message::Message() {

}

class Graph {

  public:
    Graph(Node* vertex,int lettersSize);
    void addEdge(Node src, Node* dest);
    Node BFS(Node startVertex,string operand1, string operand2, string result, list<string> letters);
    int DFS(Node startVertex,string operand1, string operand2, string result, list<string> letters, Message newMessage);

    Node* vertex;
    vector<Node>* adj;
};

Graph::Graph(Node* vertex1, int lettersSize) {
  vertex = vertex1;
  int verticeNum = vertex1->verticeNum;
  long adjSize = pow(10, lettersSize);
  //adjSize =100000000;
  //adj boyutunu dinamik hale getir
  adj = new vector<Node>[adjSize];
}

void Graph::addEdge(Node parent, Node* child) {
  adj[parent.verticeNum].push_back(*child);
}

Node Graph::BFS(Node node, string operand1, string operand2, string result, list<string> letters) {
  
  int verticeNum = node.verticeNum;

  list<Node> queue;

  //mark current node visited and enqueue
  node.visited = true;
  queue.push_back(node);

  list<Node>::iterator i;

  int adjCounter = 0;
  while(!queue.empty()) {
    node = queue.front();
    queue.pop_front();

    int adjSize = adj[node.verticeNum].size();
    for (int i = 0; i != adjSize; ++i) {
      Node currentNode = adj[node.verticeNum].at(i);
      if(!currentNode.visited) {
        currentNode.visited = true;

        cout << "vertice num: " << currentNode.verticeNum << endl;
        for (int i = 0; i<currentNode.letters->size(); i++) {
          cout << currentNode.letters->at(i) << " " ;
        }
        cout << endl;
        for (int i = 0; i<currentNode.values->size(); i++) {
          cout << currentNode.values->at(i) << " " ;
        }
        cout << endl;

        try {
          if (currentNode.values->at(0) == 9 ) {
            if (currentNode.values->size() > 1) {
              if (currentNode.values->at(1) == 3) {
                if (currentNode.values->size() > 2) {
                  if (currentNode.values->at(2) == 6) {
                    cout <<endl;

                  }
                }
              }
            }
          }
          throw 555;

        } catch (int e) {
          cout << "nope" << endl;
        }

        //aynı sayı kontrolü
        vector<int> temp = *currentNode.values;
        sort(temp.begin(), temp.end());
        vector<int>::iterator valueIterator = unique(temp.begin(), temp.end());
        bool hasDuplicates = !(valueIterator == temp.end());
        if (hasDuplicates) {
          delete currentNode.letters;
          delete currentNode.values;
          continue;
        }

        //not 0 conditions
        if (!checkZeroConditions(operand1, currentNode)) {
          delete currentNode.letters;
          delete currentNode.values;
          continue;
        }

        if (!checkZeroConditions(operand2, currentNode)) {
          delete currentNode.letters;
          delete currentNode.values;
          continue;
        }

        if (!checkZeroConditions(result, currentNode)) {
          delete currentNode.letters;
          delete currentNode.values;
          continue;
        }

        //Check summation rules
        bool passed = checkSummationRuleStart(getLastValue(operand1, currentNode),
                                              getLastValue(operand2, currentNode),
                                              getLastValue(result, currentNode));
        if (!passed) {
          delete currentNode.letters;
          delete currentNode.values;
          continue;
        }

        passed = loopDigits(operand1, operand2, result, currentNode);
        if (!passed) {
          delete currentNode.letters;
          delete currentNode.values;
          continue;
        }
        
        queue.push_back(currentNode);
        cout << "pushed" << endl;
        if (currentNode.letters->size() == letters.size() + 1) {
          cout << "result found" << endl;
          return currentNode;
        }
      }
    }

    adjCounter++;

  }
  return node;
}

int Graph::DFS(Node node, string operand1, string operand2, string result, list<string> letters, Message message) {
 
  int verticeNum = node.verticeNum;

  //mark current node visited and enqueue
  node.visited = true;
  cout << "vertice num: " << node.verticeNum << endl;

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
      vector<int>::iterator valueIterator = unique(temp.begin(), temp.end());
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
        return currentNode.verticeNum;
      }
      int resultVertice = DFS(currentNode, operand1, operand2, result, letters, message);
      if (resultVertice != 0) {
        return resultVertice;
      }
    }
  }
  return 0;
}

bool loopDigits(string operand1, string operand2, string result, Node currentNode) {
  int length1 = operand1.length() - 2 ;
  int length2 = operand2.length() - 2;
  int resultLength = result.length() - 2;

  while (length1 >= 0 && length2 >= 0 && resultLength >= 0) {
    //bir önceki basamaklar toplamı 10 dan büyükse 1 değilse 0
    int carry1 = getValue(string(1, operand1.at(length1 + 1)), currentNode);
    int carry2 =  getValue(string(1, operand2.at(length2 + 1)), currentNode);
    if (carry1 == -9 || carry2 == -9) {
      length1--;
      length2--;
      resultLength--;
      continue;
    }
    int carry = (carry1 + carry2) >= 10 ? 1 : 0;

    int value1 = getValue(string(1, operand1.at(length1)), currentNode);
    int value2 = getValue(string(1, operand2.at(length2)), currentNode);
    int valueR = getValue(string(1, result.at(resultLength)), currentNode);

    bool passed = checkSummationRule(value1, value2, valueR, carry);
    if (!passed) {
      return false;
    }

    length1--;
    length2--;
    resultLength--;

  }

  if(length1 >= 0 && length2 < 0) {
/*
    int carry1 = getValue(string(1, operand1.at(length1 + 1)), currentNode);
    int carry2 =  getValue(string(1, operand2.at(length2 + 1)), currentNode);
    int carry = (carry1 + carry2) >= 10 ? 1 : 0;

    int value1 = getValue(string(1, operand1.at(length1)), currentNode);
    int valueR = getValue(string(1, result.at(resultLength)), currentNode);

    if (!(value1 == -9 || valueR == -9)) {
      if(!((value1 + carry) == valueR)) {
        return false;
      }
    }
    */

    length1--;
    length2--;
    resultLength--;

  }

  if(length2 >= 0 && length1 < 0) {
    /*
    int carry1 = getValue(string(1, operand1.at(length1 + 1)), currentNode);
    int carry2 =  getValue(string(1, operand2.at(length2 + 1)), currentNode);
    int carry = (carry1 + carry2) >= 10 ? 1 : 0;

    int value2 = getValue(string(1, operand2.at(length2)), currentNode);
    int valueR = getValue(string(1, result.at(resultLength)), currentNode);
    
    if (!(value2 == -9 || valueR == -9)) {
      if(!((value2 + carry) == valueR)) {
        return false;
      }
    }
    */

    length1--;
    length2--;
    resultLength--;
  }
  
  

  //ilk basamak kontrol
  if (resultLength == 0) {
    /*
    int pPrevCarry1;
    if (length1 + 3 >= 0) {
      pPrevCarry1 = getValue(string(1, operand1.at(length1 + 3)), currentNode);
    } else {
      pPrevCarry1 = 0;
    }
    int pPrevCarry2;
    if (length2 + 3 >= 0) {
      pPrevCarry2 =  getValue(string(1, operand2.at(length2 + 3)), currentNode);
    } else {
      pPrevCarry2 = 0;
    }
    int pPrevCarry = (pPrevCarry1 + pPrevCarry2) >= 10 ? 1 : 0;

    int prevCarry1;
    if (length1 + 2 >= 0) {
      prevCarry1 = getValue(string(1, operand1.at(length1 + 2)), currentNode);
    } else {
      prevCarry1 = 0;
    }
    int prevCarry2;
    if (length2 + 2 >= 0) {
      prevCarry2 =  getValue(string(1, operand2.at(length2 + 2)), currentNode);
    } else {
      prevCarry2 = 0;
    }
    prevCarry1 += pPrevCarry;
    int prevCarry = (prevCarry1 + prevCarry2) >= 10 ? 1 : 0;
    */

    int carry1;
    if (length1 + 1 >= 0) {
      carry1 = getValue(string(1, operand1.at(length1 + 1)), currentNode);
    } else {
      carry1 = 0;
    }
    int carry2;
    if (length2 + 1 >= 0) {
      carry2 =  getValue(string(1, operand2.at(length2 + 1)), currentNode);
    } else {
      carry2 = 0;
    }
    carry1 += getPrevCarry(operand1, operand2, result, currentNode, length1, length2, max(operand1.size(), operand2.size()));
    int carry = (carry1 + carry2) >= 10 ? 1 : 0;

    if (length1 == 0) {
      carry += (getValue(string(1, operand1.at(length1)), currentNode));
    }

    if (length2 == 0) {
      carry += (getValue(string(1, operand2.at(length2)), currentNode));
    }

    int valueR = getValue(string(1, result.at(resultLength)), currentNode);
    bool passed = checkSummationRuleEnd(valueR, carry);
    if (!passed) {
      return false;
    }
  }

  return true;
}

int getPrevCarry (string operand1, string operand2, string result, Node currentNode, int length1, int length2, int maxsize) {
  int pPrevCarry = 0;
  int i = maxsize;
  for (int k = 0; k<maxsize; k++) {
    int pPrevCarry1;
    if (length1 + i >= 0) {
      pPrevCarry1 = getValue(string(1, operand1.at(length1 + i)), currentNode);
    } else {
      pPrevCarry1 = 0;
    }
    int pPrevCarry2;
    if (length2 + i >= 0) {
      pPrevCarry2 =  getValue(string(1, operand2.at(length2 + i)), currentNode);
    } else {
      pPrevCarry2 = 0;
    }
    pPrevCarry1 += pPrevCarry;
    pPrevCarry = (pPrevCarry1 + pPrevCarry2) >= 10 ? 1 : 0;
    i--;

  }
  return pPrevCarry;
}

int getValue(string letter, Node currentNode) {
  for (int k = 0; k < currentNode.letters->size(); k++) {
    if (letter == currentNode.letters->at(k)) {
      return currentNode.values->at(k);
    }
  }
  return -9;
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
  return -9;
}

bool checkSummationRuleStart(int operand1, int operand2, int result) {
  if (operand1 == -9 || operand2 == -9 || result == -9) {
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
  if (operand1 == -9 || operand2 == -9 || result == -9) {
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
  if (operand == -9) {
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

void writeToFile(list<string> letters, vector<int> numbers, Node resultNode, string fileName) {
  ofstream outputFileName(fileName);
  outputFileName << "\t";

  for(vector<int>::iterator number = numbers.begin(); number!= numbers.end(); ++number) {
    if (number == numbers.end()-1) {
      outputFileName << *number;
      outputFileName << "\n";
      continue;
    }
    outputFileName << *number << "\t";
  }

  int letterCounter = 0;
  for (list<string>::iterator letter = letters.begin(); letter!= letters.end(); ++letter) {
    outputFileName << *letter ;
    int value = resultNode.values->at(letterCounter);
    for (int i = 0; i < value; i++) {
      outputFileName << "\t" << ".";
    }
    outputFileName << "\t" << "1";
    int remainder = 9 - value;
    if (remainder == 0) {
      outputFileName << "\n";
    }
    for (int k = 0; k < remainder; k++) {
      if (k == remainder -1) {
        outputFileName << "\t" << "." << "\n";
        continue;
      }
      outputFileName << "\t" << ".";
    }
    letterCounter++;
  }

}

void pushLetters(string input) {
  list<string> letters;
  for (int i = 0; i < input.size(); i++) {
    letters.push_back(string(1,input.at(i)));
  }

}

int main(int argc, char* argv[])
{
  const char* filename = "TWO TWO FOUR.txt";
  const string searchMethod = "BFS";

  const string operand1 = "TWO";
  const string operand2 = "TWO";
  const string result = "FOUR";
  const string outputFileName = "output";
/*
  const string operand1 = "DOWN";
  const string operand2 = "WWW";
  const string result = "ERROR";
  */

 /*
  const string searchType = argv[1];
  const string operand1 = argv[2];
  const string operand2 = argv[3];
  const string result = argv[4];
  const string outputFileName = argv[5];
  */
 list<string> letters;
 //add operand1 letters
 for (int i = 0; i < operand1.size(); i++) {
   bool contains = false;
   for (list<string>::iterator letter = letters.begin(); letter!= letters.end(); ++letter) {
     if (string(1,operand1.at(i)) == *letter) {
       contains = true;
     }
   }

    if (!contains) {
      letters.push_back(string(1,operand1.at(i)));
    }
  }

  //add operand2 letters
  for (int i = 0; i < operand2.size(); i++) {
   bool contains = false;
   for (list<string>::iterator letter = letters.begin(); letter!= letters.end(); ++letter) {
     if (string(1,operand2.at(i)) == *letter) {
       contains = true;
     }
   }

    if (!contains) {
      letters.push_back(string(1,operand2.at(i)));
    }
  }

  //add result letters
  for (int i = 0; i < result.size(); i++) {
   bool contains = false;
   for (list<string>::iterator letter = letters.begin(); letter!= letters.end(); ++letter) {
     if (string(1,result.at(i)) == *letter) {
       contains = true;
     }
   }

    if (!contains) {
      letters.push_back(string(1,result.at(i)));
    }
  }

  /* letter checker
  list<string>::iterator ok;
  for (ok = letters.begin(); ok!= letters.end(); ++ok) {
    cout << *ok <<endl;
  }
  */

/*
  cout << "operator1: " << operator1 << endl;
  cout << "operator2: " << operator2 << endl;
  cout << "operator3: " << operator3 << endl;
  cout << "operator3: " << outputFileName << endl;
  */

  //ifstream file(filename);
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

  //Distinct harfleri bul ve pushla!!!!!!!!!!!

  vector<int> numbers;
  numbers.push_back(0);
  numbers.push_back(1);
  numbers.push_back(2);
  numbers.push_back(3);
  numbers.push_back(4);
  numbers.push_back(5);
  numbers.push_back(6);
  numbers.push_back(7);
  numbers.push_back(8);
  numbers.push_back(9);
  
  /*
  list<string> letters;
  letters.push_back("T");
  letters.push_back("W");
  letters.push_back("O");
  letters.push_back("F");
  letters.push_back("U");
  letters.push_back("R");
  */
  
  
 /*
  list<string> letters;
  letters.push_back("S");
  letters.push_back("E");
  letters.push_back("N");
  letters.push_back("D");
  letters.push_back("M");
  letters.push_back("O");
  letters.push_back("R");
  letters.push_back("Y");
  */

 /*
  list<string> letters;
  letters.push_back("D");
  letters.push_back("O");
  letters.push_back("W");
  letters.push_back("N");
  letters.push_back("E");
  letters.push_back("R");
  */
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

  Node* startNode = new Node("start", 0, 0);
  Graph graph(startNode, letters.size());
  int verticeCounterNumber = 1;
  int layerCount = 0;
  int adjCounter = 0;

  //start node a eklemeler
  for (list<string>::iterator letter = letters.begin(); letter!= letters.end(); ++letter) {
    for(vector<int>::iterator number = numbers.begin(); number!= numbers.end(); ++number) {
      Node* newNode = new Node(*letter, *number, verticeCounterNumber);
      graph.addEdge(*graph.vertex, newNode); //Add a new node with every value to parent
      verticeCounterNumber++;
    }
    break;
  }

  //graph.BFS(*startNode);

  layerCount++;
  string poppedLetter = letters.front();
  letters.pop_front();

  for (list<string>::iterator letter = letters.begin(); letter!= letters.end(); ++letter) {
    for(int k = 0; k<layerCount; k++) { //graph.adj[adjCounter].size()
      for(int i = 0; i < 10; i++) {
        for(vector<int>::iterator number = numbers.begin(); number!= numbers.end(); ++number) {
          //cout << graph.adj[adjCounter].at(i).letters->back() <<endl;
          
          Node* newNode = cloneNode(graph.adj[adjCounter].at(i));
          newNode->verticeNum = verticeCounterNumber;
          newNode->letters->push_back(*letter);
          newNode->values->push_back(*number);
          

          graph.addEdge(graph.adj[adjCounter].at(i), newNode); //Add a new node with every value to parent
          //delete newNode->letters;
          //delete newNode->values;
          delete newNode;

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

  Node resultNode; 
  int dfsResult;
  if (searchMethod == "BFS") {
    resultNode = graph.BFS(*startNode, operand1, operand2, result, letters);

    cout << "vertice num: " << resultNode.verticeNum << endl;
    for (int i = 0; i<resultNode.letters->size(); i++) {
      cout << resultNode.letters->at(i) << " " ;
    }
    cout << endl;
    for (int i = 0; i<resultNode.values->size(); i++) {
      cout << resultNode.values->at(i) << " " ;
    }
    cout << endl;
  } else if (searchMethod == "DFS") {
    Message* newMessage = new Message(false);
    newMessage->success = false;

    dfsResult = graph.DFS(*startNode, operand1, operand2, result, letters, newMessage);
    int onda = dfsResult%10;
    int dfsResultParent = (dfsResult - onda)/10;
    resultNode = graph.adj[dfsResultParent].at(onda - 1);

    cout << "vertice num: " << resultNode.verticeNum << endl;
    
    for (int i = 0; i<resultNode.letters->size(); i++) {
      cout << resultNode.letters->at(i) << " " ;
    }
    cout << endl;
    for (int i = 0; i<resultNode.values->size(); i++) {
      cout << resultNode.values->at(i) << " " ;
    }
    cout << endl;
    
  }

  letters.push_front(poppedLetter);

  writeToFile(letters, numbers, resultNode, outputFileName);

  cout << "hello world" << endl;
  cin>> input;
  
  return 0;
  
}