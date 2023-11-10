#include "../lib/mini_blockchain_lib_i.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayOptionsMenu()
{
	printf("====================\n");
	printf("       OPTIONS      \n");
	printf("====================\n");
	printf("1. Set Last Node\n");
	printf("2. Create First Node\n");
	printf("====================\n");
	printf("\n");
	printf("Choice: ");
}
void displayMainMenu()
{
	printf("================================\n");
	printf("             MENU               \n");
	printf("================================\n");
	printf("1. Create New Node\n");
	printf("2. Validate Link Between 2 Nodes\n");
	printf("3. View Node\n");
	printf("================================\n");
	printf("\n");
	printf("Choice: ");
}
void main()
{
	char s[10];
	int choice, data;
	char filename[20], filename2[20];
	while(1)
	{
		displayMainMenu(); scanf("%d",&choice);
		printf("\n");
		switch(choice)
		{
			case 1:
				if(file_exists("last.dat"))
				{
					printf("Data: "); scanf("%d",&data);
					fflush(stdin);
					printf("Node FileName: "); scanf("%s",filename);
					fflush(stdin);
					
					createNodeFile(data,filename);
					printf("NodeFile %s Created!\n",filename);
					
				}
				else
				{
					displayOptionsMenu(); scanf("%d",&choice);
					printf("\n");
					switch(choice)
					{
						case 1:
							printf("Node FileName: ");
							fflush(stdin);
							scanf("%s",filename);
							fflush(stdin);
							if(setLastNodeFile(filename))
								printf("%s Set as Last Node!\n",filename);
							else
								printf("%s Does Not Exist!\n",filename);
							break;
						case 2:
							printf("Data: "); scanf("%d",&data);
							fflush(stdin);
							printf("Node FileName: ");
							scanf("%s",filename);
							printf("%s\n",filename);
							createNodeFile(data,filename);
							printf("NodeFile %s Created!\n",filename);
							break;
						default:
							printf("Invalid Choice!\n");
					}
				}
				break;
			case 2:
				fflush(stdin);
				printf("Node-1 FileName: "); scanf("%s",filename);
				fflush(stdin);
				printf("Node-2 FileName: "); scanf("%s",filename2);
				validateNodeFiles(filename, filename2);
				break;
			case 3:
				fflush(stdin);
				printf("Node FileName: "); scanf("%s",filename);
				viewNodeFile(filename);
				break;
			default: 
				printf("Invalid Choice!\n");
		} 
		printf("\nDo you wish to continue? ");
		fflush(stdin);
		scanf("%s",s);
		fflush(stdin);
		if( s[0]=='y' || s[0]=='Y' )
			continue;
		else
			break;
	}
}

