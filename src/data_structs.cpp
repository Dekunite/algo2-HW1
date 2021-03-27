/* @Author
Student Name: <Muhammet Derviş Kopuz>
Student ID : <504201531>
Date: <13/01/2021> */

#include <iostream>
#include "data_structs.h"

using namespace std;

void Stack::init() {
  head= NULL;
}

void Stack::close() {

  Subtask* subtask;
  while (head)
  {
    subtask = head;
    head = head->next;
    delete subtask;
  } 
}

void Stack::push(Subtask* in) {

  Subtask* newSubtask = new Subtask;
  newSubtask->name = in->name;
  newSubtask->duration = in->duration;
  newSubtask->next = head;
  head = newSubtask;
  
}

Subtask* Stack::pop() {

  Subtask* topSubtask;
  topSubtask = head;
  head = head->next;
  return topSubtask;
  
}

bool Stack::isEmpty() {

  return (head == NULL);
}


void Queue::init() {

  head = NULL;
  tail = NULL;
}

void Queue::close() {

  Process* process;
  while (head)
  {
    process = head;
    head = head->next;
    delete process;
  }
}

void Queue::queue(Process* in) {
  
  Process* newProcess = new Process;
  newProcess->name = in->name;
  newProcess->arrival_time = in->arrival_time;
  newProcess->deadline = in->deadline;
  newProcess->task_count = in->task_count;
  newProcess->priority = in->priority;
  newProcess->task_stack = in->task_stack;
  newProcess->next = NULL;

  if (isEmpty()) //first element
  {
    tail = newProcess;
    head = tail;
  } else
  {
    tail->next = newProcess;
    tail = newProcess;
  }
  
}

Process* Queue::dequeue() {

  Process* process;

  process = head;
  head = head->next;
  if (head == NULL)
    tail = NULL;

  return process;
  
}

bool Queue::isEmpty() {
  return (head == NULL);
}

Process* Queue::front() {
  return (head);  
}

void MultiQueue::init() {

  queues[0].init();
  queues[1].init();
  queues[2].init();

}

void MultiQueue::close() {
  
  queues[0].close();
  queues[1].close();
  queues[2].close();

}


void MultiQueue::queue(Process* in) {
  
  Process* newProcess = new Process;
  newProcess->name = in->name;
  newProcess->arrival_time = in->arrival_time;
  newProcess->deadline = in->deadline;
  newProcess->task_count = in->task_count;
  newProcess->priority = in->priority;
  newProcess->task_stack = in->task_stack;
  newProcess->next = NULL;

  if (newProcess->priority == 1)
  {
    queues[0].queue(newProcess);
  } else if (newProcess->priority == 2)
  {
    queues[1].queue(newProcess);
  } else if (newProcess->priority == 3)
  {
    queues[2].queue(newProcess);
  }
}
Process* MultiQueue::dequeue(int priority) {
  
  Process* process;

  if (priority == 1)
  {
    process = queues[0].dequeue();
  } else if (priority == 2)
  {
    process = queues[1].dequeue();
  } else if (priority == 3)
  {
    process = queues[2].dequeue();
  }

  return process;  
}

bool MultiQueue::isEmpty() {
  if (queues[0].isEmpty() && queues[1].isEmpty() && queues[2].isEmpty())
  {
    return true;
  } else
  {
    return false;
  }
}


Process* MultiQueue::front(int priority) {
  
  Process* process;
  
  if (priority == 1)
  {
    process = queues[0].front();
  } else if (priority == 2)
  {
    process = queues[1].front();
  } else if (priority == 3)
  {
    process = queues[2].front();
  }

  return process;
}