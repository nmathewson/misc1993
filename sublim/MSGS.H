// msgs class. For SUBLIM

#ifndef MSGS_H
#define MSGS_H

#define RANGE(x,y,z)  (x < y) ? ((y < z) ? y : z ) : x

class msgs
{
public:
  const char *operator[](int n)             // Access to message #n
  {
    return strings[RANGE(0, n, top)];
  }              
  int n(void)
  {
    return top + 1;
  }
  msgs(void) : top(0), strings(0)
  {
  }
  int load(char *in);
  ~msgs(void);
protected:
  int top;
  char **strings;
};

#endif

