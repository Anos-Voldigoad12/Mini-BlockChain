# MINI BLOCKCHAIN #
## Goal ##
The goal of this project is to explore the fundamental concept of blockchain as a data strucure.
## Concept ##
A blockchain is a kind of linked list. The only difference between it and the linked list is that, unlike a linked list, each node in a blockchain stores the hash of its previous node. So as a result if one node gets tampered, the  we can detect that by looking at its next node.
## Organization of the Project ##
1. bins      - Contains all the executable files
  1. mini_blockchain.out     : Executable for debian linux distros 
2. lib       - Contains the header files created for this project
  1. mini_blockchain_lib_i.h : Contains functions used by the driver program to interface with the block chain
  2. mini_blockchain_lib.h   : Contains functions used by mini_blockchain_lib_i.h 
3. src       - Contains the source code of the driver program
  1. mini_blockchain_src.c   : Source code for the driver program
4. nodes     - Contains the previously created nodes
5. last.data - Contains the data of the last node
## The block_node Structure ##
```C
typedef struct block_node
{
	unsigned char phash[EVP_MAX_MD_SIZE];
	int data; 
}block_node;
```
## mini_blockchain_lib.h Functions ##
1. ```void sha256_Node(block_node* node, unsigned char* hash)```: To generate SHA 256 Hash of a node
2. ```int isPrevOf(block_node* n1, block_node* n2)```: To check if node n1 is previous to node n2
3. ```void print_SHA256(const unsigned char* hash)```: To print SHA 256 Hash
4. ```void printNode(block_node* node)```: To print the contents of a Node
5. ```int file_exists(const char *filename)```: To check if a file exists
6. ```void pack_and_save_node(const block_node* node, const char* filename)```: To pack a node and save it to a file
7. ```void unpack_node(block_node* node, const char* filename)```: To unpack a node file and load it to a node address
## mini_blockchain_lib_i.h Functions ##
1. ```void viewNodeFile(const char* filename)```: To Print the data stored in a node file
2. ```int setLastNodeFile(const char* filename)```: To Set the Last Node of the block chain
3. ```void createNodeFile(int data, const char* filename)```: To Add a new Node to the block chain
4. ```void validateNodeFiles(const char* filename, const char* filename2)```: To check for Integrity between two nodes
## Compiling the Code ##
```Bash
gcc lib/mini_blockchain_lib.h
gcc lib/mini_blockchain_lib_i.h
gcc src/mini_blockchain_src.c -lssl -lcrypto -o bins/<executable_name>
```
**Note: Don't forget to install open ssl in your system before running these commands.** 
## Running the Program ##
To create a new block chain, make sure to delete the last.dat file first and then use: 
```Bash
./bins/<executable_name>
```
## Sample Use Case ##
Suppose there's a big and sensitive data that you have but you dont want to keep the whole thing with you.
In this case you can create 10 nodes and give 5 of your friends the odd numbered nodes i.e., nodes 1,3,5,7 and 9.
Whenever you need the entire data you can ask your friends for the nodes, when supplied you can check for the integrity of:
1. Node 1 using Node 2
2. Node 3 using Node 4  or 2 
3. Node 5 using Node 6  or 4
4. Node 7 using Node 8  or 6
5. Node 9 using Node 10 or 8
