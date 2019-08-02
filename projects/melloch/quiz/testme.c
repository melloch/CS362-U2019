#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    //Returns random char character
    char pool[9] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'}; 
    char randomChar = rand() % 9;
    return pool[randomChar];
}

char *inputString()
{
    //Randomly reorders the letters r-e-s-e-t
    char pool[5] = "reset";
    char s[6];
    int sInt[6];
    int i, j;
    for(i = 0; i < 5; i++){
          sInt[i] = rand() % 5;
          j = 0;
            while(j < i){
              if(sInt[j] == sInt[i]){
                sInt[i] = rand() % 5;
                j = 0;
              }
              else 
                j++;
            }
          }
    for(i = 0; i < 5; i++)
      s[i] = pool[sInt[i]];

    s[5] = '\0';

    return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    //printf("%c\n", inputChar());
    return 0;
}