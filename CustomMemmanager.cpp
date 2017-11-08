#include <sys/types.h> 
#include <bits/stdc++.h>

using namespace std;


class MemoryManager//our custom Memory Manager
{ 
  struct FreeStore //This Is our Custom Struct To link up Free Blocks like a Linked list
    {
     FreeStore *next;//Each is connected to the next using the next Pointer
    }; 
  void expandPoolSize ();//This Function Expands the Pool of our blocks by adding more Free Variables 
  void cleanUp ();//We clean up the Free Pool using this function
  FreeStore* freeStoreHead; //This pointer is Points to the Root Of out Free blocks's Linked List
  public:
    MemoryManager () { 
      freeStoreHead = 0;//Initialise to null or 0
      expandPoolSize ();//Call the Function
      }
    virtual ~MemoryManager () { 
      cleanUp ();//Called in Constructor
      }
    virtual void* allocate(size_t);//Alocate a Block (i.e a Compex Object to A Block)
    virtual void   free(void*);//Makes the FreeStoreHead Point To The Current Object block and Change the next of the Complex Block to point To the Next Free Bock
  };
 
MemoryManager gMemoryManager;
 
class Complex 
  {
  public:
    Complex (double a, double b): r (a), c (b) {}
    inline void* operator new(size_t);
    inline void   operator delete(void*);
  private:
    double r; // Real Part
    double c; // Complex Part
  };

  inline void* MemoryManager::allocate(size_t size)
  {
  if (0 == freeStoreHead)//If No Free Space Avaialable
    expandPoolSize ();
 
  FreeStore* head = freeStoreHead;//We Give the Allocation to The FreeStorehead Pointer and Make FreeStoreHead Forward
  freeStoreHead = head->next;
  return head;
  }
 
inline void MemoryManager::free(void* deleted)//Take the Pointer of the Block to Delete
  {
    //Note this Deleted will be the root of our new FreeStore Linked List
  FreeStore* head = static_cast <FreeStore*> (deleted);//Basically We change the Deleted Type to FreeStore*
  head->next = freeStoreHead;//Change next Pointer of this block to point to The next Free one
  freeStoreHead = head;//Make the change of FreeStore to the Deleted block;
  }
 
void* Complex::operator new (size_t size) 
  {
  return gMemoryManager.allocate(size);//When New is Called We execute the Allocate Function of the Memorymanger
  }
 
void Complex::operator delete (void* pointerToDelete)
  {
  gMemoryManager.free(pointerToDelete);//When free is Called We execute the Allocate Function of the Memorymanger
  }


  #define POOLSIZE 32
 
void MemoryManager::expandPoolSize ()
  {
  size_t size = (sizeof(Complex) > sizeof(FreeStore*)) ? //Basically we Define A size for our Blocks which is The maximum of the Complex And FreeStore
    sizeof(Complex) : sizeof(FreeStore*);
  FreeStore* head = reinterpret_cast <FreeStore*> (new char[size]);//1 Char=1 Byte ,so we Store A Block Of Size ="size " and have a root pointer Attached to it
  freeStoreHead = head;//Root=That
 
  for (int i = 0; i < POOLSIZE; i++) {//This Loops creates Blocks and Links Them .
    head->next = reinterpret_cast <FreeStore*> (new char [size]);
    head = head->next;
    }
 
  head->next = 0;
  }
 
void MemoryManager::cleanUp()
  {
  FreeStore* nextPtr = freeStoreHead;//Cleans up from the FreeStoreHead From the Root 
  for (; nextPtr; nextPtr = freeStoreHead) {
    freeStoreHead = freeStoreHead->next;
    delete [] nextPtr; // remember this was a char array
    }
  }

  int main(int argc, char* argv[]) 
  {
    auto t = clock();
  Complex* array[1000];
  for (int i = 0;i  <  5000; i++) {
    for (int j = 0; j  <  1000; j++) {
      array[j] = new Complex (i, j);
      }
    for (int j = 0; j  <  1000; j++) {
      delete array[j];
      }
    }
    t = clock()-t;
    cout<<"It took us "<<((float)t)/CLOCKS_PER_SEC<<" secs"<<endl;
  return 0;
  }
