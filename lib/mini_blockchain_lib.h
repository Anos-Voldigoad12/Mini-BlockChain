#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <sys/stat.h>

typedef struct block_node
{
	unsigned char phash[EVP_MAX_MD_SIZE];
	int data; 
}block_node;

void sha256_Node(block_node* node, unsigned char* hash); //To generate SHA 256 Hash of a node
int isPrevOf(block_node* n1, block_node* n2); //To check if node n1 is previous to node n2
void print_SHA256(const unsigned char* hash); //To print SHA 256 Hash
void printNode(block_node* node); //To print the contents of a Node
int file_exists(const char *filename); //To check if a file exists
void pack_and_save_node(const block_node* node, const char* filename); //To pack a node and save it to a file
void unpack_node(block_node* node, const char* filename); //To unpack a node file and load it to a node address

void sha256_Node(block_node* node, unsigned char* hash)
{
	EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(mdctx,EVP_sha256(),NULL);
	EVP_DigestUpdate(mdctx,node->phash,EVP_MD_size(EVP_sha256()));
	EVP_DigestUpdate(mdctx,&node->data,sizeof(int));
	EVP_DigestFinal_ex(mdctx,hash,NULL);
	EVP_MD_CTX_free(mdctx);
}
int isPrevOf(block_node* n1, block_node* n2)
{
	size_t hash_len = EVP_MD_size(EVP_sha256());
	unsigned char hash[hash_len];
	sha256_Node(n1,hash);
	size_t i;
	for(i=0;i<hash_len;i++)
	{
		if(hash[i]!=n2->phash[i])
			return 0;
	}
	return 1;
}
void print_SHA256(const unsigned char* hash)
{
	size_t hash_len = EVP_MD_size(EVP_sha256());
	size_t i;
	for(i=0;i<hash_len;i++)
	{
		printf("%02x",hash[i]);
	}
	printf("\n");
}
void printNode(block_node* node)
{
	printf("Data: %d\n",node->data);
	printf("Previous Node Hash: "); print_SHA256(node->phash);
	printf("\n");
}
int file_exists(const char *filename)
{
	struct stat buffer;
	return (stat (filename,&buffer))==0;
}
void pack_and_save_node(const block_node* node, const char* filename)
{
	FILE *file = fopen(filename,"wb");
	if(file==NULL)
	{
		perror("Error Opening File...\n");
		return;
	}
	fwrite(node,sizeof(block_node),1,file);
	fclose(file);
}
void unpack_node(block_node* node, const char* filename)
{
	FILE *file = fopen(filename,"rb");
	if(file==NULL)
	{
		perror("Error Opening File...\n");
		return;
	}
	fread(node,sizeof(block_node),1,file);
	fclose(file);
}
