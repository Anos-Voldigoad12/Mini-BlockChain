#include "mini_blockchain_lib.h"

void viewNodeFile(const char* filename); //To Print the data stored in a node file
int setLastNodeFile(const char* filename); //To Set the Last Node of the block chain
void createNodeFile(int data, const char* filename); //To Add a new Node to the block chain
void validateNodeFiles(const char* filename, const char* filename2); //To check for Integrity between two nodes

void viewNodeFile(const char* filename)
{
	block_node n1;
	if(file_exists(filename))
	{
		unpack_node(&n1,filename);
		printf("Node Data: %d\n",n1.data);
	}
	else
		printf("%s does not exist!\n",filename);
}
int setLastNodeFile(const char* filename)
{
	block_node n1;
	if(file_exists(filename))
	{
		unpack_node(&n1,filename);
		pack_and_save_node(&n1,"last.dat");
		return 1;
	}
	else
	{
		return 0;
	}
}
void createNodeFile(int data, const char* filename)
{
	char *filename2 = "last.dat";
	unsigned char hash[EVP_MD_size(EVP_sha256())];
	block_node n1,n2;
	n2.data = data;
	
	if(file_exists(filename2))
	{
		unpack_node(&n1,filename2);
		sha256_Node(&n1,hash);
		strcpy(n2.phash,hash);
		pack_and_save_node(&n2,filename);
		pack_and_save_node(&n2,filename2);
	}
	else
	{
		strcpy(n2.phash,"\0");
		pack_and_save_node(&n2,filename);
		pack_and_save_node(&n2,filename2);
	}		
}
void validateNodeFiles(const char* filename, const char* filename2)
{
	block_node n1,n2;
	if( file_exists(filename) && file_exists(filename2) )
	{
		unpack_node(&n1,filename);
		unpack_node(&n2,filename2);
		if(isPrevOf(&n1,&n2))
    		printf("\nCongrats! Data Integrity Guaranted!\n");
    	else
    		printf("\nFailure! Data Tampered!\n");
	} 
	else if( !file_exists(filename) )
		printf("%s does not exist!\n",filename);
	else if( !file_exists(filename2) )
		printf("%s does not exist!\n",filename2);
	else
		printf("%s and %s does not exist!\n",filename,filename2);
}
