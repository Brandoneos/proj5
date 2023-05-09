/*
Author: BRANDON KIM
DATE: 4/11/2023
Course: CS 251

Description: This file(priorityqueue.h) includes the priorityqueue class with the NODE structure.
This class has functions used to be similar to an actual priority queue data structure
but modified to include duplicates.

*/

/// @file priorityqueue.h
///
///
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

#pragma once

#include <iostream>

#include <sstream>

#include <set>

using namespace std;

template < typename T >
  class priorityqueue {
    private: struct NODE {
      int priority; // used to build BST
      T value; // stored data for the p-queue
      bool dup; // marked true when there are duplicate priorities
      NODE * parent; // links back to parent
      NODE * link; // links to linked list of NODES with duplicate priorities
      NODE * left; // links to left child
      NODE * right; // links to right child
    };
    NODE * root; // pointer to root node of the BST
    int size; // # of elements in the pqueue
    NODE * curr; // pointer to next item in pqueue (see begin and next)
    //  can/should add private member functions to help out

    void deleteLinks(NODE * current) {
      while (current != nullptr) {
        NODE * next = current -> link;
        delete current;
        size--;
        current = next;
      }
    }

    bool _linkEqual(NODE * mycur, NODE * othercur) const {
      NODE * current = mycur;
      NODE * currentO = othercur;
      if (mycur -> dup != othercur -> dup) {
        return false;
      } else if (mycur -> dup == false) {
        return true;
      }
      while (current != nullptr && currentO != nullptr) {
        if (current -> priority != currentO -> priority || current -> value != currentO -> value || current -> dup != currentO -> dup) {
          return false;
        }
        current = current -> link;
        currentO = currentO -> link;
      }
      if (current != nullptr || currentO != nullptr) {
        return false;
      } else {
        return true;
      }
    }
    bool _equal(NODE * mycur, NODE * othercur) const {
      if (mycur == nullptr && othercur == nullptr) {
        return true;
      } else if (mycur == nullptr) {
        return false;
      } else if (othercur == nullptr) {
        return false;
      } else {
        if ((mycur -> priority == othercur -> priority) && (mycur -> value == othercur -> value) && (_linkEqual(mycur, othercur)) && (_equal(mycur -> left, othercur -> left)) && (_equal(mycur -> right, othercur -> right))) {
          return true;
        } else {
          return false;
        }
      }
    }

    void inOrderFindMinForCurr(NODE * cur) {

      if (cur == nullptr) {
        return;
      } else {
        if (cur -> left != nullptr) {
          inOrderFindMinForCurr(cur -> left);
        } else {
          curr = cur;
        }
      }
    }
    void inOrderToString(NODE * cur, ostream & output) {
      if (cur == nullptr) {
        return;
      } else {
        inOrderToString(cur -> left, output);
        output << cur -> priority << " value: " << cur -> value << "\n";
        if (cur -> dup == true) {

          NODE * curLink = cur -> link;
          while (curLink != nullptr) {
            output << curLink -> priority << " value: " << curLink -> value << "\n";
            curLink = curLink -> link;
          }
        }
        inOrderToString(cur -> right, output);
      }
    }
    void postOrderClear(NODE * cur) {
      if (cur == nullptr) {
        return;
      } else {
        postOrderClear(cur -> left);
        postOrderClear(cur -> right);

        NODE * temp = cur;
        if (cur -> dup == true) {
          NODE * currentN = cur -> link;
          deleteLinks(currentN);
        }
        delete temp;
        size--;
      }
      root = nullptr;

    }
    void preOrderAssignment2(NODE * rootThis, NODE * rootOther) {

      if (rootOther == nullptr) {
        rootThis = nullptr;
      } else {
        enqueue(rootOther -> value, rootOther -> priority);
        if (rootThis == nullptr) {
          rootThis = root;
        }
        if (rootOther -> dup == true) {
          NODE * current = rootOther -> link;
          while (current != nullptr) {
            enqueue(current -> value, current -> priority);
            current = current -> link;
          }
        }
        preOrderAssignment2(rootThis, rootOther -> left);
        preOrderAssignment2(rootThis, rootOther -> right);

      }
    }

    public:
      //
      // default constructor:
      //
      // Creates an empty priority queue.
      // O(1)
      //

      priorityqueue() {
        root = nullptr;
        size = 0;
        curr = nullptr; //for begin and next

      }

    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue & operator = (const priorityqueue & other) {
      this -> clear();

      if (other.root == nullptr) { //edge case of passing in empty pq
        this -> root = nullptr;
        return * this;
      }

      preOrderAssignment2(this -> root, other.root);

      return * this;

    }

    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
      //post order traversal in order to delete the root node last.

      postOrderClear(root); //calls recursive function

    }

    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
      //Only called at the very end of program
      clear(); //call clear to properly delete pq

    }

    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    void enqueue(T value, int priority) {

      NODE * newNode = new NODE();
      newNode -> priority = priority;
      newNode -> value = value;

      newNode -> left = nullptr;
      newNode -> right = nullptr;

      newNode -> dup = false; //false for now, will change in the search if duplicates are found in tree
      //insert function
      NODE * prev = nullptr;
      NODE * cur = root;
      //1). search, will find duplicate
      while (cur != nullptr) {
        if (priority == cur -> priority) {
          if (cur -> dup == true) {
            while (cur -> link != nullptr) {
              cur = cur -> link; //go to the end of the linked list
            }
            cur -> link = newNode;
            newNode -> dup = true;
            newNode -> parent = prev;
            newNode -> link = nullptr;
          } else { //first duplicate node
            cur -> dup = true;
            newNode -> dup = true;
            cur -> link = newNode;
            newNode -> link = nullptr;
            newNode -> parent = prev;
          }
          //found key, make duplicates linked list
          size++;
          return;
        }
        if (priority < cur -> priority) { //go left
          prev = cur;
          cur = cur -> left;
        } else { //go right
          prev = cur;
          cur = cur -> right;
        }
      }

      //2). not found through search, so add node to tree
      if (prev == nullptr) {
        root = newNode;
        newNode -> parent = nullptr; //delete maybe
      } else if (priority < prev -> priority) {
        prev -> left = newNode;
        newNode -> parent = prev;
      } else {
        prev -> right = newNode;
        newNode -> parent = prev;
      }
      size++;
      return;

    }
    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T dequeue() {

      //1). locate node to delete

      NODE * nodeToDelete = root;
      NODE * nodePLink;
      while (nodeToDelete -> left != nullptr) {
        nodeToDelete = nodeToDelete -> left;
      }
      //If nodeTodelete has dups case
      if (nodeToDelete -> dup == true) {
        nodePLink = nodeToDelete -> link;
        if (nodePLink -> link == nullptr) {
          nodePLink -> dup = false;
        }
        if (nodeToDelete == root) {
          nodePLink -> left = nodeToDelete -> left;
          nodePLink -> right = nodeToDelete -> right;
          nodePLink -> parent = nullptr;
          root = nodePLink;
        } else {
          nodePLink -> left = nodeToDelete -> left;
          nodePLink -> right = nodeToDelete -> right;
          nodePLink -> parent = nodeToDelete -> parent;
          if (nodeToDelete == nodeToDelete -> parent -> left) {
            nodeToDelete -> parent -> left = nodePLink;
          } else {
            nodeToDelete -> parent -> right = nodePLink;
          }
        }
        //nodeToDelete doesn't have dups case, and has right subtree
      } else if (nodeToDelete -> right != nullptr) {
        nodePLink = nodeToDelete -> right;

        if (nodeToDelete == root) {
          nodePLink -> parent = nullptr;
          root = nodePLink;
        } else {
          nodePLink -> parent = nodeToDelete -> parent;
          if (nodeToDelete == nodeToDelete -> parent -> left) {
            nodeToDelete -> parent -> left = nodePLink;
          } else {
            nodeToDelete -> parent -> right = nodePLink;
          }
        }

      } else { //doesn't have right subtree case, makes it the left most node, the min.
        if (nodeToDelete == root) {
          root = nullptr;
        } else {
          if (nodeToDelete == nodeToDelete -> parent -> left) { //update values
            nodeToDelete -> parent -> left = nullptr;
          } else {
            nodeToDelete -> parent -> right = nullptr;
          }
        }
      }
      T value1 = nodeToDelete -> value;
      delete nodeToDelete;
      size--;
      return value1;

    }

    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
      return size;
    }

    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    // curr is pointer to next item in pq
    void begin() {
      inOrderFindMinForCurr(root);
      //should update curr to be the first node
    }

    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T & value, int & priority) {
      if (curr == nullptr) {
        return false;
      }
      value = curr -> value;
      priority = curr -> priority;

      if (curr -> dup == true) {
        if (curr -> link != nullptr) {
          curr = curr -> link;
          return true;
        } else {
          //else set the curr back to the original node
          if (curr -> parent == nullptr) {
            //root duplicates
            curr = root;
          } else if (curr -> parent -> priority > curr -> priority) {
            curr = curr -> parent -> left;
          } else {
            curr = curr -> parent -> right;
          }

        }
        //else its at the end of linked list
        //goes to next if statement
      }

      if (curr -> right != nullptr) { //if right subtree is not empty
        inOrderFindMinForCurr(curr -> right);
      } else { //its one of the ancestors
        NODE * current = curr;
        // NODE* parent1;
        while (current != root) {
          if (current -> parent -> left == current) {
            curr = current -> parent;
            return true;
          }
          current = current -> parent;
        }
        curr = nullptr;
        return false;
      }
      return true;

    }

    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
      //in order traversal
      string str = "";
      stringstream ss(str);
      inOrderToString(root, ss);
      return ss.str();

    }

    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T peek() {

      NODE * current = root;
      while (current -> left != nullptr) {
        current = current -> left;
      } //go to left most node, which is lowest priority
      T valueOut = current -> value;
      return valueOut;

    }

    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator == (const priorityqueue & other) const {
      return _equal(root, other.root);
    }

    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void * getRoot() {
      return root;
    }
  };