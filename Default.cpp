 #include <sys/types.h> 
#include <bits/stdc++.h>

using namespace std;
class Complex 
  {
  public:
    Complex (double a, double b): r (a), c (b) {}
   // inline void* operator new(size_t);
    //inline void   operator delete(void*);
  private:
    double r; // Real Part
    double c; // Complex Part
  };

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
    cout<<"It took us "<<b((float)t)/CLOCKS_PER_SEC<<" secs"<<endl;
  return 0;
  }
