/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | January 2022
 **/
#ifndef DICTTREE_H_                              /* INCLUDE GUARD */
#define DICTTREE_H_ 
#include <iostream>

class dicttree {
  private:                                       // PRIVATE FIELDS
    static const int size = 27;
    dicttree *character[size];
    bool isWord;

    int BFS(dicttree*);
    int DFS(dicttree*);
    int DFS(dicttree*, int);
   
  public:                                        // PUBLIC FIELDS
    dicttree(bool isWord = false);               // CONSTRUCTOR
    ~dicttree();                                 // DESCTRUCTOR    

    void setword(bool);
    bool  getword();
    void insertme(std::string);                  // FUNCTION PROTOTYPE
    int  searchme(std::string);                  // FUNCTION PROTOTYPE
};

#endif                                           // DICTTREE_H_
