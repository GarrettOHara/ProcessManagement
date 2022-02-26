/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | January 2022
 **/
#ifndef DICTTREE_H_                              // INCLUDE GUARD
#define DICTTREE_H_ 
#include <iostream>
#define CHILDREN 27

class dicttree {
  private:                                       // PRIVATE FIELDS
    static const int size = CHILDREN;            // NODE CHILDREN SIZE
    dicttree *character[size];                   // NODE POINTERS 
    bool isWord;                                 // DICTIONARY WORD

    int BFS(dicttree*);                          // BSF ITERATIVE
    int DFS(dicttree*);                          // DFS RECURSIVE
    int DFS(dicttree*, int);                     // DFS ITERATIVE
   
  public:                                        // PUBLIC FIELDS
    dicttree(bool isWord = false);               // CONSTRUCTOR
    ~dicttree();                                 // DESCTRUCTOR    

    void setword(bool);                          // SETTER
    bool getword();                              // GETTER
    void insertme(std::string);                  // FUNCTION PROTOTYPE
    int  searchme(std::string);                  // FUNCTION PROTOTYPE
};

#endif                                           // DICTTREE_H_
