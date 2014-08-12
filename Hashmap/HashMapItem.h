#ifndef HASHMAPITEM_H
#define HASHMAPITEM_H

#include <iostream>
#include <string>

template<typename T>
struct HashMapItem 
{
    //HashMapItem() : nextItem(nullptr), key(""){
    HashMapItem() {
        std::cout << "Default Constructing..." << std::endl;
    };
    HashMapItem(std::string k, T val) : nextItem(nullptr), key(k), value(val) {
        std::cout << "Constructing: " << key << std::endl;
    };
    HashMapItem(const HashMapItem& c)
    {
        std::cout << "Copy constructor called: " << key << std::endl;
    }


    ~HashMapItem(){      
        /*if (!key.empty())
            std::cout << "Destructing: " << key << std::endl;
        else
            std::cout << "Destructing... " << std::endl;*/
    };
    HashMapItem* nextItem;    
    T value;
    //char* key; //so this is 4 bytes. how does it know how much to allocate?
    std::string key; //so this is 4 bytes. how does it know how much to allocate?

    //Any allocation function for a class T is a static member (even if not explicitly declared static).
    //
    //There is a difference between the "new" keyword and an operator new:
    //  MyClass *x = new MyClass;
    //There are actually two things that happen--memory allocation and object construction; 
    //the new keyword is responsible for both. One step in the process is to call operator new in order to allocate memory; 
    //the other step is to actually invoke the constructor. 
    //Operator new lets you change the memory allocation method, but does not have any responsibility for calling the constructor. 
    //That's the job of the new keyword.        


    static void* operator new (std::size_t count, HashMapItem<T>* memoryPool, int slot){
        
        //constructor has been called by now, right? or no, because this is suppose to get the memory for the constructor?
        std::cout << "new called!" << std::endl;
        //memoryPool[slot] = this;
       // T foobar; //baaad
        return nullptr;
    };

    void* operator new  (std::size_t count, void* ptr)
    {
        std::cout << "new placement called!" << std::endl;
        //memoryPool[slot] = this;
        ptr = this;
        ++ptr; //ok, now how do I allocate to the pool???
        // T foobar; //baaad
        return nullptr;
    }


    //so my problem was that key2 wasn't being allocated well.
};

#endif