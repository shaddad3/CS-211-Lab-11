/*

Create the sentinel node at the beginning of main() and then implement functions
appendNumber( )  and deleteNumber( ).

The sentinel node should always be there at the beginning of the list,
with a data value of -1.  This sentinel Node should not be displayed whenever
you print the list.

 */
#include <stdio.h>  // For printf and scanf
#include <stdlib.h> // For malloc

typedef struct Node *NodePtr; // Make:  NodePtr to be a synonym for: struct Node *
struct Node {
  int data;      // The data stored at the node
  NodePtr pNext; // Pointer to the next node
};

//------------------------------------------------------------
// Display the list.  We've supplied this version so your output
// will match the expected test cases.
void displayList(NodePtr pHead) {
  printf("List is: ");
  while (pHead != NULL) {
    // Don't print the sentinel Node value
    if (pHead->data != -1) {
      printf("%d ", pHead->data);
    }
    pHead = pHead->pNext;
  }
  printf("\n");
} // end displayList()

///--------------------------------------------------------------
// Append number at the end of the list.  Add the parameters
// and the code needed to implement this function.
void appendNumber(NodePtr *pHead, NodePtr *pTail, int number) {
  //allocate space for the node, then initialize it
	NodePtr pTemp;
  pTemp = malloc( sizeof( struct Node));
  pTemp->data = number;
  pTemp->pNext = NULL;

  if ((*pHead)->pNext == NULL) { //no nodes other then sentinel
    // at the start, list is: pHead --> -1 / NULL <-- pTail
    (*pHead)->pNext = pTemp;
    (*pTail) = pTemp;
    //now: list is: pHead --> -1 --> pTemp <-- pTail
  }
    
	else { //at least one node on the list other than sentinel
    //at start, list is: pHead --> -1 --> # / NULL <--pTail
    (*pTail)->pNext = pTemp;
    (*pTail) = pTemp;
    //now: list is: pHead --> -1 --> # --> pTemp <--pTail
  }
  
} // end appendNumber()

//--------------------------------------------------------------
// Delete the first (non-sentinel) Node on the list and return the
// number that was in it. Add the parameters and the code needed to
// implement this function.
int deleteNumber(NodePtr *pHead) {
  // Sanity check: Ensure there is at least one Node on the list.
  // This is supplied so your code matchess the test cases.
  if ((*pHead)->pNext == NULL) {
    // Non-displayed sentinel node at front of list does not point to
    //   any valid data Node, so list is empty.
    printf("Sorry, can't delete from an empty list.");
    return -1;
  }

  //delete the first non sentinal node on the list:
  NodePtr pDelete = (*pHead)->pNext;
  int value = (*pHead)->pNext->data;
  (*pHead)->pNext = (*pHead)->pNext->pNext;
  free(pDelete);
  
  return value;
} // end deleteNumber()

//--------------------------------------------------------------
// Consider: For input of 1 3 5 -1, what is the output?
int main() {
  // Create a sentinel Node(which is the pHead) at list beginning, initialize it
  NodePtr pHead;
  pHead = malloc( sizeof( struct Node));
  pHead->data = -1;
  pHead->pNext = NULL;
  // and make both head and tail point to it.
  NodePtr pTail = pHead;

  // ---------------------------------------------------
  // The code below this point should remain unchanged.
  int number = 0;        // Used to store numbers read in
  char menuOption = ' '; // Store user input menu option

  // Loop to allow adding and deleting list values.
  while (menuOption != 'x') {
    printf("Menu: \n");
    printf("  a n  to add value n to the list \n");
    printf("  d    to delete value from the list \n");
    printf("  x    to exit program \n");
    printf("Your choice: ");
    scanf(" %c", &menuOption);

    // Handle menu options
    switch (menuOption) {
    case 'x':
      return 0; // Exit program
      break;
    case 'a':
      scanf("%d", &number);					// Read in the number to be added
      appendNumber(&pHead, &pTail, number);				// Append to end of list
      break;
    case 'd':
      number = deleteNumber(&pHead); 			// Delete from end of list
      if (number != -1) {
        printf("Deleted %d\n", number);
      }
      break;
    default:
      printf("Invalid menu option.  Retry. \n");
      continue;
    }

    printf("\n");
    displayList(pHead);
  }

  return 0; // return value to keep C++ happy
} // end main()