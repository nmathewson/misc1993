//			        WORDLIST.CPP
#include <string.h>
#include <fstream.h>
#include "wordlist.h"

wordlist::wordlist(int maxwords)
{
  if (maxwords < 0)
    maxwords *= -1;
  words=new charp[maxwords];
  topword=maxwords-1;
  nextword=0;
}

int wordlist::addword(const char *word)
{
  if (full())
    return -1;

  words[nextword]=new char[strlen(word)+1];
  strcpy(words[nextword], word);
  nextword++;
  return 0;
}

void wordlist::sort(void)
{
  int flag, i;
  char *c;

  if (nextword < 2)
    return;

  do
   {
    flag = 0;
    for(i=0; i < (nextword-1); i++)
      if (strcmp(words[i],words[i+1]) > 0)
      {
        flag = 1;
        c = words[i];
        words[i]=words[i+1];
        words[i+1]=c;
      };
   }
  while (flag == 1);
}

const char *wordlist::operator[](int n)
{
  if (n>=nextword)
    return NULL;
  return words[n];
}

int wordlist::changeword(int n, const char *word)
{
  if (n>=nextword)
    return -1;

  delete [] (words[n]);
  words[n] = new char[strlen(word)+1];
  strcpy(words[n],word);
  return 0;
}

int wordlist::load(char *file)
{
  char buffer[81];

  ifstream in(file);
  if (in.bad())
    return -1;

  do
   {
    in.get(buffer,80).get();
    if (strlen(buffer))
      addword(buffer);
   }
  while ((! in.eof()) && (! in.bad()));

  if (in.bad())
    return -1;

  in.close();

  return 0;
}

int wordlist::save(char *file)
{
  ofstream out(file);
  if (out.bad())
    return -1;

  for(int i = 0; i < nextword; i++)
    out << words[i] << "\n";

  if (out.bad())
    return -1;

  out.close();

  return 0;
}


wordlist::~wordlist()
{
  int i;
  for(i=0; i<nextword; i++)
    delete [] words[i];
  delete [] words;
}

