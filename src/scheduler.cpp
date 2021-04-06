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
#include <time.h>
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

class Graph {

  public:
    Graph(Node* vertex,int lettersSize);
    void addEdge(Node src, Node* dest);
    Node BFS(Node startVertex,string operand1, string operand2, string result, list<string> letters);
    string DFS(Node startVertex,string operand1, string operand2, string result, list<string> letters);

    Node* vertex;
    vector<Node>* adj;
    int numberOfVisitedNotes;
    int nodesInMemory;
};

Graph::Graph(Node* vertex1, int lettersSize) {
  vertex = vertex1;
  int verticeNum = vertex1->verticeNum;
  long adjSize = pow(10, lettersSize) + 0.5;
  numberOfVisitedNotes = 0;
  nodesInMemory = 0;
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

  while(!queue.empty()) {
    node = queue.front();
    queue.pop_front();

    if (queue.size() > nodesInMemory) {
      nodesInMemory = queue.size();
    }

    int adjSize;
    try{
      adjSize = adj[node.verticeNum].size();
    } catch (...) {
      numberOfVisitedNotes += 10;
      continue;
    }
    for (int i = 0; i != adjSize; ++i) {
      Node currentNode;
      try{
        currentNode = adj[node.verticeNum].at(i);
      } catch (...) {
        numberOfVisitedNotes++;
        continue;
      }
      numberOfVisitedNotes++;
      if(!currentNode.visited) {
        currentNode.visited = true;

        /*
        cout << "vertice num: " << currentNode.verticeNum << endl;
        for (int i = 0; i<currentNode.letters->size(); i++) {
          cout << currentNode.letters->at(i) << " " ;
        }
        cout << endl;
        for (int i = 0; i<currentNode.values->size(); i++) {
          cout << currentNode.values->at(i) << " " ;
        }
        cout << endl;
        */
        

        /*
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
        */

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
        //cout << "pushed" << endl;
        if (currentNode.letters->size() == letters.size() + 1) {
          //cout << "result found" << endl;
          return currentNode;
        }
      }
    }
  }
  return node;
}

string Graph::DFS(Node node, string operand1, string operand2, string result, list<string> letters) {
 
  int verticeNum = node.verticeNum;

  //mark current node visited and enqueue
  node.visited = true;
  //cout << "vertice num: " << node.verticeNum << endl;

  int errors = 0;
  // Recur for all the vertices adjacent to this vertex
  int adjSize;
  try{
    adjSize = adj[node.verticeNum].size();
  } catch (...) {
    numberOfVisitedNotes += 10;
  }
  for (int i = 0; i != adjSize; ++i) {
    Node currentNode;
    try{
      currentNode = adj[node.verticeNum].at(i);
      numberOfVisitedNotes++;
    } catch (...) {
      numberOfVisitedNotes++;
      continue;
    }
    if(!currentNode.visited) {
      //cout << "vertice num: " << currentNode.verticeNum << endl;
      
      /*
      for (int i = 0; i<currentNode.letters->size(); i++) {
        cout << currentNode.letters->at(i) << " " ;
      }
      cout << endl;
      for (int i = 0; i<currentNode.values->size(); i++) {
        cout << currentNode.values->at(i) << " " ;
      }
      cout << endl;
      */
      

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

      //cout << "pushed" << endl;
      if (currentNode.letters->size() == letters.size() + 1) {
        //cout << "result found" << endl;
        string verticeAndI = to_string(node.verticeNum);
        verticeAndI.append("+");
        verticeAndI.append(to_string(i));
        return verticeAndI;
      }
      string resultVertice = DFS(currentNode, operand1, operand2, result, letters);
      if (resultVertice != "0") {
        return resultVertice;
      }
    }
  }
  return "0";
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

    length1--;
    length2--;
    resultLength--;

  }

  if(length2 >= 0 && length1 < 0) {

    length1--;
    length2--;
    resultLength--;
  }
  
  

  //ilk basamak kontrol
  if (resultLength == 0) {

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

  //letter checker
  /*
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
      delete newNode;
    }
    break;
  }

  //graph.BFS(*startNode);

  layerCount++;
  string poppedLetter = letters.front();
  letters.pop_front();
  int bir = 1;

  for (list<string>::iterator letter = letters.begin(); letter!= letters.end(); ++letter) {
    for(int k = 0; k<bir; k++) { //graph.adj[adjCounter].size()
      for(int i = 0; i < 10; i++) { //i 8 e düşecek
        for(vector<int>::iterator number = numbers.begin(); number!= numbers.end(); ++number) {
          //cout << graph.adj[adjCounter].at(i).letters->back() <<endl;
          try {
            //cout << *letter << ": " << *number <<endl;
            Node* newNode = cloneNode(graph.adj[adjCounter].at(i));
            newNode->verticeNum = verticeCounterNumber; 
            newNode->letters->push_back(*letter);
            newNode->values->push_back(*number);
            //cout << "vertice num: " << newNode->verticeNum << endl;
/*
            for (int i = 0; i<newNode->letters->size(); i++) {
              cout << newNode->letters->at(i) << " " ;
            }
            cout << endl;
            for (int i = 0; i<newNode->values->size(); i++) {
              cout << newNode->values->at(i) << " " ;
            }
            cout << endl;
            */

            //aynı sayı kontrolü
            vector<int> temp = *newNode->values;
            sort(temp.begin(), temp.end());
            vector<int>::iterator valueIterator = unique(temp.begin(), temp.end());
            bool hasDuplicates = !(valueIterator == temp.end());
            if (hasDuplicates) {
              //delete currentNode.letters;
              //delete currentNode.values;
              delete newNode;
              verticeCounterNumber++;
              //cout << "deleted"<< endl;
              continue;
            }


            //cout << "added" <<endl;
            graph.addEdge(graph.adj[adjCounter].at(i), newNode); //Add a new node with every value to parent
            //delete newNode->letters;
            //delete newNode->values;
            delete newNode;

            verticeCounterNumber++;
            continue;

          } catch (...) {
            verticeCounterNumber++;
            continue;
          }
          


        }
      }
      adjCounter++;
    }
    bir *= 10;
  }

  Node resultNode; 
  string dfsResult;
  const clock_t begin_time = clock();
  if (searchMethod == "BFS") {
    resultNode = graph.BFS(*startNode, operand1, operand2, result, letters);

    /*
    cout << "vertice num: " << resultNode.verticeNum << endl;
    for (int i = 0; i<resultNode.letters->size(); i++) {
      cout << resultNode.letters->at(i) << " " ;
    }
    cout << endl;
    for (int i = 0; i<resultNode.values->size(); i++) {
      cout << resultNode.values->at(i) << " " ;
    }
    cout << endl;
    */
  } else if (searchMethod == "DFS") {
    dfsResult = graph.DFS(*startNode, operand1, operand2, result, letters);
    string verticeNum = dfsResult.substr(0, dfsResult.find("+"));
    //cout << verticeNum <<endl;
    dfsResult.erase(0, dfsResult.find("+")+1);
    //cout << dfsResult <<endl;
    //int dfsResultParent = (dfsResult - onda)/10;
    resultNode = graph.adj[stoi(verticeNum)].at(stoi(dfsResult));

    //cout << "vertice num: " << resultNode.verticeNum << endl;
    
    /*
    for (int i = 0; i<resultNode.letters->size(); i++) {
      cout << resultNode.letters->at(i) << " " ;
    }
    cout << endl;
    for (int i = 0; i<resultNode.values->size(); i++) {
      cout << resultNode.values->at(i) << " " ;
    }
    cout << endl;
    */
    
  }
  float finalTime = float( clock () - begin_time ) /  CLOCKS_PER_SEC;

  letters.push_front(poppedLetter);

  writeToFile(letters, numbers, resultNode, outputFileName);

  cout << "Algorithm: " << searchMethod << endl;
  cout << "Number of the visited nodes: " << graph.numberOfVisitedNotes << endl;
  cout << "Maximum number of nodes kept in the memory: " << graph.nodesInMemory << endl;
  cout << "Running time: " << finalTime << " seconds" << endl;
  cout << "Solution: ";
  for (int i = 0; i<resultNode.letters->size(); i++) {
    if (i == resultNode.letters->size() - 1) {
      cout << resultNode.letters->at(i) << ": " << resultNode.values->at(i);
      continue;
    }
      cout << resultNode.letters->at(i) << ": " << resultNode.values->at(i) << ", ";
  }

  cin>> input;
  
  return 0;
  
}