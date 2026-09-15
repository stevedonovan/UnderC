// import2.h
// testing the import of classes w/ virtual methods

#ifndef __UNDERC__
#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif
#else
#define EXPORT
#ifdef _WIN32
#lib import2.dll
#else
#lib examples/import/libimport2.so
#endif
#endif

class EXPORT Base {
protected:
  int a;
public:
  Base();
  Base(int _a);
  ~Base();
  virtual void method1();
  virtual int val();
  virtual void set(int _a);
  virtual int sum(int x);
};

class EXPORT Derived: public Base {
public:
  Derived();
  ~Derived();
  virtual int sum(int);
};

EXPORT Base *return_base();
EXPORT Base *return_derived();

#ifdef __UNDERC__  
#lib 
#endif

