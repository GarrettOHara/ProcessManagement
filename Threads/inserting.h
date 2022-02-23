/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | Februrary 2022
 **/
#ifndef INSERTING_H_                             /* INCLUDE GUARD */
#define INSERTING_H_ 

namespace inserting{
    void* insert(void*);
}


#endif                                           // DICTTREE_H_

/**

#ifndef INSERTING_H_                             // INCLUDE GUARD
#define INSERTING_H_ 

class inserting {
    public:
        inserting();
        ~inserting();

    public:                                        // PUBLIC FIELDS
        void* insert(void*);
        static void* insert(void*){
            return reinterpret_cast<inserting*>(void*)->insert();
        }
};

#endif                                           // DICTTREE_H_







class inserting {
  public:
    static void* start(void* instance) {
        return static_cast<inserting*>(instance)->insert(instance);
    }                                       // PRIVATE FIELDS

  public:                                        // PUBLIC FIELDS
    void* insert(void*);
};


 **/