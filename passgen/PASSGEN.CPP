//				 PASSGEN
//			The Random Password Generator
#include <ctype.h>
#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define IN(a,b,c) ( ((a) <= (b)) && ((b) <= (c)) )

enum type
{
  end = 0,
  upper = 1,  //*
  lower = 2,  //*
  numeric = 4,//*
  punc = 8,   //*
  vowel = 16,
  cons = 32
};
typedef type *typep;

const char symbols[] =
//          11111111112222222222333333333344444444445555555555666666666677777
//012345678901234567890123456789012345678901234567890123456789012345678901234

 "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!@#$%&*()+~";
const char vowels[] = "aeiou";
const char consn[] = "bcdfghjklmnpqrstvwxyz";

void help(void);
type *parse(char *s);
char give(type t);
const char *pass(type *tmplate);

void main(int argc, char *argv[])
{
  type *tmpl;
  char ch;

  if (argc !=2)
    help();

  tmpl = parse(argv[1]);
  randomize();

  do
  {
    do
      cout << pass(tmpl) << "\n";
    while (!kbhit());
    getch();
    cout << "\nY for more, N to exit\n";
    ch = getche();
  }
  while (tolower(ch) == 'y');
}

void help(void)
{
  cout << "\nSyntax is\n"
	  "PASSGEN <CONTROL-STRING>\n"
	  "Where CONTROL-STRING is a string of\n"
    "   V - Vowel             C - Consonant\n"
	  "   L - Lowercase         U - Uppercase\n"
	  "   A - Alphabetical      N - Numeric\n"
	  "   M - Lowercase/Numeric Y - Uppercase/Numeric\n"
	  "   O - Alphanumeric      . - Punctuation\n"
    "   1 - L+.   2 - U+.     3 - A+.  4 - N+.\n"
	  "   5 - M+.   6 - Y+.     S - ANY SYMBOL\n";
  exit(0);
}

type *parse(char *s)
{
  type *str;
  int notdone;
  int i;

  str = new type[strlen(s)+1];

  i = 0;
  do
  {
    notdone = 1;
    switch (toupper(s[i]))
    {

      case 'V' : str[i] = vowel;
		 break;
      case 'C' : str[i] = cons;
		 break;
      case 'L' : str[i] = lower;
		 break;
      case 'U' : str[i] = upper;
		 break;
      case 'A' : str[i] = lower | upper;
		 break;
      case 'N' : str[i] = numeric;
		 break;
      case 'M' : str[i] = lower | numeric;
		 break;
      case 'Y' : str[i] = upper | numeric;
		 break;
      case 'O' : str[i] = lower | upper | numeric;
		 break;
      case '.' : str[i] = punc;
		 break;
      case '1' : str[i] = punc  | lower;
		 break;
      case '2' : str[i] = punc  | upper;
		 break;
      case '3' : str[i] = punc  | lower | upper;
		 break;
      case '4' : str[i] = punc  | numeric;
		 break;
      case '5' : str[i] = punc  | lower | numeric;
		 break;
      case '6' : str[i] = punc  | upper | numeric;
		 break;
      case 'S' : str[i] = lower | upper | numeric | punc;
		 break;
      case 0   : str[i] = end;
		 notdone = 0;
		 break;
      default  : cout << "Bad key : " << *str << "\n";
		 help();
		 break;
    };
    i++;
  }
  while (notdone);

  return str;
}

char give(type t)
{
  // 0-25 lower 26-51 upper 52-61 numeric 62-74 punc
  int i;

  if (t == vowel)
    return vowels[random(5)];
  if (t == cons)
    return consn[random(21)];

  do
  {
    i = random(75);
    if ( IN(0,i,25) && (t & lower) == 0 )
       i = -1;
    if ( IN(26,i,51) && (t & upper) == 0 )
       i = -1;
    if ( IN(52,i,61) && (t & numeric) == 0 )
       i = -1;
    if ( IN(62,i,74) && (t & punc) == 0 )
       i = -1;
  }
  while (i == -1);

  return symbols[i];
}

const char *pass(type *tmplate)
{
  static char str[80];
  char *chp;
  chp = str;

  while(*tmplate)
  {
     *chp=give(*tmplate);
     chp++;
     tmplate++;
    };
  *chp = 0 ;
  return str;
}

