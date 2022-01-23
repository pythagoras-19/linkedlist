#include <iostream>
#include <fstream>
#include <string>
#include<stdio.h>
#include<string.h>
#include <vector>
//using namespace std;
/*
Write a program that reads a list of students (first names only) from a file. 
It is possible for the names to be in unsorted order in the file but they have to be placed in sorted order within the linked list.
*/
struct Node
{
	char data[1000]; //content
    //string data;
	Node* next; // next Node
	Node* prev; // previous Node
};
Node* firstAdd(Node* head, char value[])
{
    std::cout << "called firstAdd()" << std::endl;
    Node* newNode = new Node;
    //newNode->data = value;
    strcpy(newNode->data, value);
    newNode->prev = NULL;
    newNode->next = NULL;
    head = newNode;
    return head;
}
Node* addToFront(Node* head, char value[])
{
    std::cout << "called addToFront()" << std::endl;
	Node* newNode = new Node; //allocate memory on heap for a new node
    Node* current;
	//newNode->data = value; // assigning data member of our new node with the value of value
    strcpy(newNode->data, value);
    newNode->prev = NULL; //NEW 11SEP21
    //new 
    head->prev = newNode;
    //endNew
	newNode->next = head; // assigning next member of our new Node to the value of the address of head
	head = newNode; // assigning newNode to head so now our "head" is our newNode
    /*
    for(current = head; current; current = current->next)
    {
        std::cout << current->data << std::endl;
    }
    */
	return head;
}
//coming tail = addToRear(tail, line);
Node* addToRear(Node* tail, char value[])
{
    //std::cout << "tail->data before adding new 'line' to rear =" << tail->data << std::endl;
    //TODO: adding with a tail ptr
    std::cout << "called addToRear()" << std::endl;
    Node* newNode = new Node;
    //newNode->data = value;
    strcpy(newNode->data, value);
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = NULL;
    tail = newNode;
    //std::cout << "tail->data: " << tail->data << std::endl; 
    return tail;
}
//Node* insertInTheMiddle(Node* head, string value)
void insertInTheMiddle(Node* head, char value[])
{
    std::cout << "called insertInTheMiddle()" << std::endl;
    Node* newNode = new Node;
    Node* current = head;
    Node* aliasHead = head;
    while (strcmp(value, current->data) > 0) // while the string is greater than current string, go to next string to compare
    {
        //std::cout << "current->data: "<< current->data << " value: " << value << std::endl;
        current = current->next;
    }
    if(current)
    {
        //std::cout << "here:" << current->data << " " << aliasHead->data << std::endl;
        //std::cout << current->prev << std::endl;
        strcpy(newNode->data,value);
        //std::cout << "good1" << std::endl;
        newNode->next = current;
        //std::cout << "good2" << std::endl;
        newNode->prev = current->prev;
        //std::cout << "good3" << std::endl;
        //new
        current->prev->next = newNode;
        //std::cout << "good4" << std::endl;
        //endnew
        current->prev = newNode;
        //std::cout << "here2" << std::endl;
        
    }
}
//void deleteNode(Node* head, Node* tail, char value[])
Node* deleteNode(Node* head, Node* tail, char value[])
{
    std::cout << "In deleteNode()" << std::endl;
    Node* temp;
	Node* tempy;
	Node* curr = head;
    //std::cout << "curr->data : " << curr->data << " value to delete: " << value << std::endl;
    while (!(strcmp(curr->data, value) == 0)) // find the node that has that value
    {
        //std::cout << "yo curr->data: " << curr->data << std::endl;
        curr = curr->next;
    }
    if (curr) // if curr != NULL --> there  is a node that holds the name we want to delete
    {
        if(curr->prev) // if it isn't a head node
        {
            std::cout << curr->data << std::endl;
            curr->prev->next = curr->next;
        }
        else
        {
            head = curr->next;
        }
        if(curr->next) // if it isn't a tail node
        {
            //std::cout << "curr->next: " << curr->next->data << std::endl;
            //std::cout << "curr->next->prev: " << curr->next->prev->data<<std::endl;
            curr->next->prev = curr->prev;
        }
        else
        {
            tail = curr->prev; 
        }
        std::cout << "deleting : " << curr->data << std::endl;
        delete curr; // deleting node,  new 16 Sep 21 9:56a
    }
    //std::cout << "deleting : " << curr->data << std::endl;
    //delete curr; // deleting node,  new 16 Sep 21 9:56a
    return head;
}
void traverse(Node* head, Node* tail, FILE* fp)
{
    std::cout << "Now writing to file..." << std::endl;
    fp = fopen("output.txt", "w"); // open the file to write to
    for (Node* current = head; current; current = current->next) // Bob -> Jack -> John (head to tail)
    {
        fprintf(fp, "%s", current->data);
        fprintf(fp, "\n");
    }
    fprintf(fp, "=============\n");
    for (Node* current = tail; current; current = current->prev) // John->Jack->Bob (tail to head)
    {
        fprintf(fp, "%s", current->data);
        fprintf(fp, "\n");
    }
    fclose(fp); //close the file we are writing to. Good practice.
}

int main()
{
    Node* current = new Node;
    Node* head = NULL;
    Node* tail = NULL;

    int i = 0;
    char line[1000];
    //char line[30];
    char deleteWord[] = "delete";

    //ifstream inFS;
    FILE *inputFile;
    //inFS.open("input.txt");
    FILE *fp;
    fp = fopen("input.txt", "r");
    //add jill, jim, and john to the linked list
    if (fp != NULL)
    {
        while (fscanf(fp,"%s",line) != EOF)
        //while (fgets(line, 60, fp))
        {
            //std::cout << "line is: " << line << std::endl;
            if (strcmp(line, deleteWord) == 0)
            {
                //fgets(line, 60, fp); // read the word we want to delete
                fscanf(fp,"%s", line);
                std::cout << "new 'line' after delete: " << line << std::endl;
                //call delete with new word 
                //deleteNode(head, tail, line);
                //std::cout << "first for loop: " << std::endl;
                /*21SEP21
                for(current = head; current; current = current->next)
                {
                    std::cout << current->data << std::endl;
                }
                */
                if(head) // if someone accidently tried to delete before firstAdd() executed
                {
                    head = deleteNode(head, tail, line); // 
                }
                //head = deleteNode(head, tail, line); // 
            }
            else if(head == NULL)//(!head) // if head is NULL (EMPTY LINKEDLIST)
            {
                //head = addToFront(head, line);
                //tail = add(tail, line);
                head = firstAdd(head,line);
                tail = head;
                //std::cout << "head->data : " << head->data << std::endl << "tail->data : " << tail->data << std::endl;
            }
            //TODO: deal with delete
            else if (strcmp(line, head->data) < 0)//(line < head->data)
            {
                std::cout << "addToFront() called with: " << line << std::endl;
                head = addToFront(head,line); // add to the FRONT of list
            }
            else if (strcmp(line, tail->data) > 0) //(line > tail->data) // line that is greater than tail->data, so add to end of list
            {
                std::cout << "addToRear() called with: " << line << std::endl;
                tail = addToRear(tail, line);
            }
            else //somewhere in the middle
            {
                std::cout << "insertInTheMiddle() called with: " << line << std::endl;
                insertInTheMiddle(head, line);   
                //std::cout << "lol" << std::endl;
                /*21SEP21
                for(current = head; current; current = current->next)
                {
                    std::cout << current->data << std::endl;
                }
                */
            }
        }
    }
    else std::cout << "Unable to open file." << std::endl;
    //current = head;
    //std::cout << "In last for loop: " << std::endl;
    /*
    for(current = head; current; current = current->next)
    {
        std::cout << current->data << std::endl;
    }
    */
    fclose(fp); // close the file we are reading from
    /*
    At the end of the program, traverse through the contents of the linked list in both ascending and descending order, using the doubly linked list, 
    and write the contents into the file output.txt. For example, given the above list, here is the sample display:
    */
    traverse(head, tail, fp);
    return 0;
}
//Graveyard
/*
 for (size_t i = 0; i < names.size(); i++)
    {
        if(names[i] <= names[i+1])
        {
            head = add(head, names[i]);
            headNode = names[i];
        }
        else if (names[i] > names[i+1])
        {
            head = add(head, names[i+1]);
            headNode = names[i+1];
        }
    }
    //for (i = 0; i < names.size(); i++)
    //{
    //     cout << names[i] << endl;
    //}
    //cout << "names.size() = " << names.size() << endl; // size is 7
    //string headNode = "wahsup";
    
    //in insert middle
     // for(; current; current = current->next)
    // {
    //     if (value < current->data)
    //     {
    //         //newNode->data = value;
    //         strcpy(newNode->data,value);
    //         newNode->next = current;
    //         newNode->prev = current->prev;
    //         current->prev = newNode;
    //     }
        
    // }

*/