//				WORDLIST.H
#ifndef WORDLIST_H
#define WORDLIST_H

typedef char *charp;

class wordlist
{
private:
  char **words;
  int topwords;
  int nextword;
public:
  wordlist(int maxwords);
  int full(void)
  {
    return (nextword > topword);
  }
  int nwords(void)
  {
    return nextword;
  };
  int addword(const char *word);
  void sort(void);
  const char *operator[](int n);
  int changeword(int n, const char *word);
  int load(char *file);
  int save(char *file);
  ~wordlist();
};

#endif
