// 				Misspell.cpp

#include <stdlib.h>
#include <fstream.h>
#include <ctype.h>
#include <string.h>

struct  entry_t
{
  char first;
  char next;
};

const entry_t table[] =
{
  { 'e', '\0' },    // a
  { 'd', '\0' },    // b
  { 'k', '\0' },    // c
  { 't', '\0' },    // d
  { 'a', '\0' },    // e
  { 'p', 'h'  },    // f
  { 'j', '\0' },    // g
  { '\0', '\0'},    // h
  { 'e', '\0' },    // i
  { 'g', '\0' },    // j
  { 'c', '\0' },    // k
  { 'l', 'l'  },    // l
  { 'm', '\0' },    // m
  { 'n', '\0' },    // n
  { 'a', '\0' },    // o
  { 'f', '\0' },    // p
  { 'k', 'w'  },    // q
  { 'r', 'r'  },    // r
  { 'z', '\0' },    // s
  { 'd', '\0' },    // t
  { 'o', 'o'  },    // u
  { 'f', '\0' },    // v
  { 'u', '\0' },    // w
  { 'c', '\0' },    // x
  { 'i', '\0' },    // y
  { 's', '\0' }     // z
};

void getfact(int &factor);
int parse(int &factor, char *f);
void misspell(ifstream &in, ofstream &out, int fact);
void help(void);

int main(int argc, char *argv[])
{
  char filein[14];
  char fileout[14];
  int factor;

  cout << "\nMisspell V 2.0\n";			// Message

  if ((argc<3)||(argc>4))           // Arguments in bounds?
     help();                        // If not, show help

  strncpy(filein,argv[1],12); 			// set filenames
  strncpy(fileout,argv[2],12);
  filein[12]=fileout[12]= '\0';
  strupr(filein);
  strupr(fileout);

  if (argc==3)                      // if 2 args, input manually
    getfact(factor);

  if (argc==4)                                  // if 3 args, parse
    parse(factor, argv[3]);

  cout << "Misspelling " << filein << "\n"
          "         to " << fileout
       << "\nChanging 1 letter out of " << factor << "\n\n";

  ifstream in(filein);				// open filein
  if (in.bad())
   {
    cout << "\nERROR: Could not open " << filein << "\n";
    exit(2);
   };

  ofstream out(fileout);			// open fileout
  if (out.bad())
   {
    cout << "\nERROR: Could not open " << fileout << "\n";
    exit(2);
   };

  randomize();
  misspell(in,out,factor);

  in.close();
  out.close();

  cout << "\nThrough misspelling.\n";

  return 0;
}

void getfact(int &factor)
{
  char buffer[6];

  cout << "1 out of N characters will be misspelled. (5óNó1000)\nEnter N: ";
  do
   {
    cin.getline(buffer,5);
    factor=atoi(buffer);
    if ((factor<5) || (factor > 1000))
       cout << "Bad input.  (5óNó1000)\nEnter N: ";
   }
  while ((factor<5) || (factor > 1000));
}

int parse(int &factor, char *f)
{
  factor = atoi(f);
  if ((factor<5) || (factor>1000))
   {
    cout << "Factor out of range.\n";
    exit(1);
   };

  return factor;
}

void misspell(ifstream &in, ofstream &out, int fact)
{
  char ch, next;
  int index, lower;

  while (! in.eof())
  {
    ch = in.get();
    if ((random(fact) != 0) || ! isalpha(ch))
    {
      out.put(ch);
      cout.put(ch);
    }
    else
    {
      lower = islower(ch);
      index = tolower(ch) - 'a';
      ch = table[index].first;
      next = table[index].next;
      if (! lower)
      {
        ch   = toupper(ch);
        next = toupper(next);
      };
      if (ch)
      {
        out.put(ch);
        cout.put(ch);
      };
      if (next)
      {
        out.put(next);
        cout.put(next);
      };
    };    // if ((random...
  };    // while ( ! in...

}


void help(void)
{
  cout << "Format is\n"
	  "MISSPELL FILEIN FILEOUT [FACTOR]\n"
	  "Where FACTOR is between 5 and 1000\n";
  exit(1);
}

