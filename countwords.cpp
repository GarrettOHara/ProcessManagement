/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | January 2022
 **/
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include "dicttree.h"

using namespace std;

struct thread_arg {
    string file_path;
    dicttree root;
} insert_thread, search_thread;

void static print_tokens(vector<string> tokens){
    for(int i = 0; i < tokens.size(); i++){
        cout << tokens[i] << endl;
    }
}

/* READ IN TEXT FILE AND TOKENIZE INTO STRINGS
 * INSERT BOOLEAN DETERMINES TO INSERT OR SEARCH WORD IN TRIE */
void static read_file(dicttree* root, const char* path, bool insert){
  ifstream file(path);
  string line;
  string temp = "";

  if(file.is_open()){
    while (getline(file,line)){
        char delimiters[] = " \n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
        char* token = strtok (&line[0], delimiters);
        while(token != NULL){
            if(insert)
                root->insertme(token);
            else{
                int count = root->searchme(token);
                cout << token << " " << count << endl;
            }
            token = strtok (NULL, delimiters);
        }
    }
    file.close();
  }
  return;
}

int main(int argc, char *argv[]){
  const string err = "\n\nExiting program...\n";
  try{

    if(argc != 3)
    throw("Invalid amount of arguments");

    const char *dict_path = argv[1];
    const char *text_path = argv[2];
    
    dicttree* root = new dicttree();

    /**
     * instantiate dicttree node on the stack,
     * pass it in by pointer along with the file
     * itself (dictionary file)
     * 
     * create a stuct that contains the 
     * node and a string variable which is a
     * realative path to the file we need to read
     * open
     * 
     * then pass the struct to the thread
     * from there we can open the file up and 
     * read it in, inserting or searching each
     * token from the file on our stack instantiated node
     */

    read_file(root, dict_path, true);
    read_file(root, text_path, false);

  } catch(const char* msg){
    cout << msg << 
    "\n\nPlease supply 2 exceptions:" <<
    "\n  - Path to dictionary"  <<
    "\n  - Path to sample text" <<
    err << endl;
  } catch ( const exception& e ) {
    cerr << "ERROR: " << e.what() << err << endl;
  } catch (...) {
    cout << "Exception occurred";
  }
  return 0;
}
