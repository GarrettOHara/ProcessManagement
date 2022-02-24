#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

static int local_reader(char const* filename){
    ifstream file(filename);
    string line;
    int interal_count = 0;

    if(file.is_open()){
        while (getline(file,line)){
            interal_count+= line.length()+1; // strlen(line.c_str())
        }
    }
    file.close();
    return interal_count;
}

static int read_all_bytes(char const* filename){
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    return pos;
}

static int byte_reader(char const* filename){
    std::ifstream input(filename, std::ios::binary);

    std::vector<char> bytes(
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));

    input.close();
    return bytes.size();
}

int main(){
    const char* file = "./Resources/dictionarysource.txt";
    vector<char>v;
    cout << read_all_bytes(file) << endl;
    cout << byte_reader(file) << endl;    
    cout << local_reader(file) << endl;
    return 0;
}