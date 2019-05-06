/*
 * Chris Alves
 * Quick Password Encrypter
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 20
#define TAB_LEN 44
#define CODE_LEN 250

const char CHARSET[]=  "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 .,;!-'?";

//Prototypes
void menu();
void setChoice(int choice, int *case1, int *case2, char table[TAB_LEN][TAB_LEN], char *key);
void seeder(char tab[TAB_LEN][TAB_LEN]);
void keyword(char *key);
void encrypt(char tab[TAB_LEN][TAB_LEN], char *key);
void decrypt(char tab[TAB_LEN][TAB_LEN], char *key);

void getChar(char *str, int len);
int getInput(void);
int getPosition(const char *str, const char c);

//Main
int main()
{
 
    char tabula[TAB_LEN][TAB_LEN];
    char keyword[CODE_LEN];
    int choice;
    int case1= 0;
    int case2= 0;
 
    system("clear");
    menu();
    
    while(1)
    {
       printf("\n> ");
        choice= getInput();
        setChoice(choice, &case1, &case2, tabula, keyword);
    }

    return 0;
}

//Creates a menu
void menu()
{
    printf("\n  QUICK PASSWORD ENCRYPTER\n ~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    printf(" 1. Enter a random number seed to generate the Tabula Recta \n");
    printf(" 2. Enter the Keyword \n");
    printf(" 3. Enter a message to encrypt \n");
    printf(" 4. Enter a message to decrypt \n");
    printf(" 5. Exit the program \n\n");
}

//Functions of menu
void setChoice(int choice, int *case1, int *case2, char table[TAB_LEN][TAB_LEN], char *key)
{
    switch(choice)
    {
      case 1:
        seeder(table);
        while(*case1 == 0)
            ++*case1;
        break;
      case 2:
        keyword(key);
        while(*case2 == 0)
            ++*case2;
        break;
      case 3:
        if (*case1 && *case2)
            encrypt(table, key);
        else
        {
            printf("\nMake sure you have entered a random number and keyword");
            printf("\nPress enter to refresh...");
            getInput();
        }
        break;
      case 4:
        if (*case1 && *case2)
            decrypt(table, key);
        else
        {
            printf("\nMake sure you have entered a random number and keyword");
            printf("\nPress enter to refresh...");
            getInput();
        }
        break;
      case 5:
        printf("Program exited successfully\n");
        exit(EXIT_SUCCESS);
        break;
      default:
        printf("\nInvalid Option");
        printf("\nPress enter to refresh...");
        getInput();
        break;
    }
  
}

//Seeder Funtion
void seeder(char tab[TAB_LEN][TAB_LEN])
{
    printf("Input number: ");
//Impliment seeding function here
    int input= 0;
    input= getInput();
    srandom(input);

    printf("\nSeed: %d\n", input);
//Fills initial tabula recta row to help when adding randomly generated numbers backwards
    int i;
    for(i= 0; i < TAB_LEN; i++)
        tab[0][i]= CHARSET[i];

//Shuffles the first row
    int o;
    int index;
    for (o= TAB_LEN - 1; o > 0; o--)
    {
        char temp;
        index= random()%(o+1);
        temp= tab[0][index];
        tab[0][index]= tab[0][o];
        tab[0][o]= temp;
    }

//Shifts next row to left by 1, repeats
    int j;
    int k;
    for (j= 1; j < TAB_LEN; j++)
    {
        for(k= 0; k < TAB_LEN; k++)
        {
            tab[j][k] = tab[j-1][k+1];
        }
        tab[j][TAB_LEN-1]= tab[j-1][0];
    }
}

//Keyword function
void keyword(char *key)
{
    printf("Input keyword: ");
//Get keyword and make it all caps
    getChar(key, MAX_LEN);
    int keylen;
    keylen= strlen(key);
    int i;
    for(i = 0; i < keylen; i++)
        key[i]= toupper(key[i]);
    
    printf("\nKeyword: %s\n", key);

//Extend the keyword
    for(i= 0; i < CODE_LEN - keylen; i++)
               key[keylen+i]= key[i];
}

//Encrypter function
void encrypt(char tab[TAB_LEN][TAB_LEN], char *key)
{
    printf("Input plaintext: ");
//Get plaintext and make it all caps
    char plain[CODE_LEN];
    getChar(plain, CODE_LEN);
    int plainlen;
    plainlen= strlen(plain);
   
    char code[CODE_LEN];
    int i;
    for(i = 0; i < plainlen; i++)
        plain[i]= toupper(plain[i]);
    printf("\nMessage: %s\n", plain);

//Encryption Loop
    int letter;
    int row= 0;
    int col= 0;
    for(letter= 0; letter <= plainlen; letter++)
    {
        row= getPosition(CHARSET, key[letter]);
        col= getPosition(CHARSET, plain[letter]);
        code[letter]= tab[row][col];
         if(letter == plainlen)
            code[letter]= '\0';
    }
    printf("Encryption: %s\n", code);
}

//Decrypter function
void decrypt(char tab[TAB_LEN][TAB_LEN], char *key)
{
    printf("Input garbage: ");
//Get Secret message
    char secret[CODE_LEN];
    getChar(secret, CODE_LEN);
    int secretlen;
    secretlen= strlen(secret);
    char message[CODE_LEN];

//Makes secret message all caps just in case user manually enters
    int i;
    for(i = 0; i < secretlen; i++)
        secret[i]= toupper(secret[i]);
    printf("\nEncryption: %s\n", secret);

//Decryption Loop
    int letter;
    int row= 0;
    int col= 0;
    for(letter= 0; letter <= secretlen; letter++)
    {
        row= getPosition(CHARSET, key[letter]);
        col= getPosition(tab[row], secret[letter]);
        message[letter]= CHARSET[col];
        if(letter == secretlen)
            message[letter]= '\0';
    }
    printf("Message: %s\n", message);
}

//Gets input from the user
void getChar(char *str, int len)
{
    fgets(str, len, stdin);
    char *pos;
    pos= strchr(str, '\n');
    if(pos != NULL)
        *pos= '\0';
}

//Gets number from user
int getInput(void)
{
   char input[MAX_LEN];
   int result;
   fgets(input, MAX_LEN, stdin);
   sscanf(input,"%d", &result);
   return result;
}

//Finds the location of a char in a string and returns it as an int
int getPosition(const char *str, const char c)
{
  int retVal = -1;
  char *pos = strchr(str, c);

  if (pos != NULL)
  {
    retVal = pos - str;
  }

  return retVal;
}
