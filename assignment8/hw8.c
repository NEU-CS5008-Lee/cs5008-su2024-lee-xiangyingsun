// name: Xiangying Sun
// email: sun.xiangyi@northeastern.edu


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 200
#define TABLE_SIZE 400  // Define the size of the hash tables

// finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11

// check if a character c is a digit
bool isDigit(char c) {
  if ('0' <= c && c <= '9') {
    return true;
  } else {
    return false;
  }
}

// append character c to string s
void appendChar(char* s, char c) {
  char charToStr[2];           // convert char to string
    charToStr[0] = c;
    charToStr[1] = '\0';          // put NUL to terminate string of one character
    strcat(s, charToStr);
}

// Use linked list for collision
typedef struct Node {
  char city[MAXSTRING];
  int population;
  struct Node* next;
} Node;

Node* createNode(const char* city, int population) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->city, city);
  newNode->population = population;
  newNode->next = NULL;
  return newNode;
}

void insertNode(Node** head, const char* city, int population) {
  Node* newNode = createNode(city, population);
  newNode->next = *head;
  *head = newNode;
}

void freeList(Node* head) {
  Node* current = head;
  Node* nextNode;
  while (current != NULL) {
    nextNode = current->next;
    free(current);
    current = nextNode;
  }
}

// hash function 1: length of the city string (modulo size of table)
int hashFunc1(const char* cityStr) {
  return strlen(cityStr) % TABLE_SIZE;
}

// hash function 2: sum of the character codes (ASCII code) of the city string (modulo size of table)
int hashFunc2(const char* cityStr) {
  int sum = 0;
  for (int i = 0; cityStr[i] != '\0'; i++) {
    sum += cityStr[i];
  }
  return sum % TABLE_SIZE;
}

// hash function 3: product of the first 2 character codes (ASCII code) in city string (modulo size of table)
int hashFunc3(const char* cityStr) {
  if (strlen(cityStr) < 2) {
    return cityStr[0] % TABLE_SIZE; // handle strings with less than 2 characters
  }
  return (cityStr[0] * cityStr[1]) % TABLE_SIZE;
}

int main () {

  char inputLine[MAXSTRING];   // temporary string to hold input line
  char cityStr[MAXSTRING];     // city name
  int  lineNum;                // line number (city rank)
  int  popInt;                 // population
  int  state;                  // FSM state
  int  nextChar;               // index of next character in input string
  char temp[MAXSTRING];        // temp string to build up extracted strings from input characters
  
  // Initialize hash tables
  Node* hashTable1[TABLE_SIZE] = {NULL};
  Node* hashTable2[TABLE_SIZE] = {NULL};
  Node* hashTable3[TABLE_SIZE] = {NULL};
 
  FILE* fp;
  fp = fopen("pop.csv","r");

  if (fp != NULL) {
    fgets(inputLine, MAXSTRING, fp); // prime the pump for the first line

    // ***** BEGIN FINTITE STATE MACHINE *****
    
    // STARTSTATE: digit -> S1
    // S1: digit -> S1; , -> S2
    // S2: " -> S3
    // S3: !" -> S3; " -> S4
    // S4: , -> S5
    // S5: " -> S6; ( -> ACCEPTSTATE
    // S6: digit -> S6; , -> S6; " -> ACCEPTSTATE; 
    // ACCEPTSTATE: done!
    // else go to ERRORSTATE
    //
    while (feof(fp) == 0){

      nextChar = 0;
      state = STARTSTATE; 
      strcpy(temp,"");       // temp = ""

      if (nextChar >= strlen(inputLine)){
        // if no input string then go to ERRORSTATE
        state = ERRORSTATE;
      } 

      while ((state != ERRORSTATE) && (state != ACCEPTSTATE)) {
        switch (state) {
          case STARTSTATE:
            // look a digit to confirm a valid line
            if (isDigit(inputLine[nextChar])) {
              state = S1;
              appendChar(temp, inputLine[nextChar]);
            } else {
              state = ERRORSTATE;
            }  
            break;

          case S1:
            if (isDigit(inputLine[nextChar])) {
              appendChar(temp, inputLine[nextChar]);
            } else if (inputLine[nextChar] == ',') {
              state = S2;
              lineNum = atoi(temp);  // convert temp to line number
              strcpy(temp, "");      // reset temp
            } else {
              state = ERRORSTATE;
            }
            break;

          case S2:
            if (inputLine[nextChar] == '"') {
              state = S3;
            } else {
              state = ERRORSTATE;
            }
            break;

          case S3:
            if (inputLine[nextChar] != '"') {
              appendChar(temp, inputLine[nextChar]);
            } else {
              state = S4;
              strcpy(cityStr, temp); // copy temp to cityStr
              strcpy(temp, "");      // reset temp
            }
            break;

          case S4:
            if (inputLine[nextChar] == ',') {
              state = S5;
            } else {
              state = ERRORSTATE;
            }
            break;

          case S5:
            if (inputLine[nextChar] == '"') {
              state = S6;
            } else if (inputLine[nextChar] == '(') {
              popInt = 0;           // if '(' then population is 0
              state = ACCEPTSTATE;
            } else {
              state = ERRORSTATE;
            }
            break;

          case S6:
            if (isDigit(inputLine[nextChar])) {
              appendChar(temp, inputLine[nextChar]);
            } else if (inputLine[nextChar] == ',') {
              // do nothing, continue in S6
            } else if (inputLine[nextChar] == '"') {
              state = ACCEPTSTATE;
              popInt = atoi(temp);  // convert temp to population
              strcpy(temp, "");     // reset temp
            } else {
              state = ERRORSTATE;
            }
            break;
            
          case ACCEPTSTATE:
            // nothing to do - we are done!
            break;
            
          default:
            state = ERRORSTATE;
            break;
        } // end switch

        // advance input
        nextChar++;
	
      }	// end while state machine loop

      // ***** END FINITE STATE MACHINE *****
	  

      // Insert the parsed data into hash tables
      int index1 = hashFunc1(cityStr);
      int index2 = hashFunc2(cityStr);
      int index3 = hashFunc3(cityStr);

      insertNode(&hashTable1[index1], cityStr, popInt);
      insertNode(&hashTable2[index2], cityStr, popInt);
      insertNode(&hashTable3[index3], cityStr, popInt);


      // get next line
      fgets(inputLine, MAXSTRING, fp);
      
    } // end while file input loop
    

    fclose(fp);

    // Print hash tables for verification
    printf("***** HASH TABLE 1 *****\n\n====================\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("TABLE[%d]: \n", i);

        Node* current = hashTable1[i];
        if (current != NULL) {
            while (current != NULL) {
                printf("key/value: [%s] / [%d]\n", current->city, current->population);
                current = current->next;
            }
        }
        printf("\n");
    }
    printf("====================\n\n\n");

    printf("***** HASH TABLE 2 *****\n\n====================\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("TABLE[%d]: \n", i);

        Node* current = hashTable2[i];
        if (current != NULL) {
            while (current != NULL) {
                printf("key/value: [%s] / [%d]\n", current->city, current->population);
                current = current->next;
            }
        }
        printf("\n");
    }
    printf("====================\n\n\n");

    printf("***** HASH TABLE 3 *****\n\n====================\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("TABLE[%d]: \n", i);

        Node* current = hashTable3[i];
        if (current != NULL) {
            while (current != NULL) {
                printf("key/value: [%s] / [%d]\n", current->city, current->population);
                current = current->next;
            }
        }
        printf("\n");
    }
    printf("====================\n\n\n");

    // Free memory used by hash tables
    for (int i = 0; i < TABLE_SIZE; i++) {
        freeList(hashTable1[i]);
        freeList(hashTable2[i]);
        freeList(hashTable3[i]);
    }
  
  }
  else{
    printf("File not found!\n");
  }
  return 0;
}
