// MSGS.CPP
#include "msgs.h"

typedef char *chp;

int msgs::load(char *in)
{
  if (strings)                    // If there is anything allocated,
    return 1;                     //    DON'T DO IT TWICE!!

  int count;
  char *ptr;

// Count #'s

  count = 0U;
  ptr = in;
  while (*ptr)
  {
    if (*ptr == '#')
      ++count;
    ++ptr;
  }

// Initialize strings.

  top = count - 1;
  strings = new chp[top + 1];

  ptr = in;
  for(int i = 0; i <= top; ++i)
  {
    strings[i] = ptr;
    while((*ptr) && (*ptr != '#'))
      ++ptr;

    if (! ptr)
      break;

    *ptr = '\0';
    ++ptr;
  }
  return 0;
}

msgs::~msgs(void)
{
  if (strings)
    delete [] strings;
}


