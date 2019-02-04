#include "xor_tool.h"

int main(int argc , char *argv[])
{

	int k, count = 0;
	int keyfilesize;
	int datasize;
	int keysize, size_delta;
	unsigned char *keyfile = NULL;
	unsigned char *data = NULL;
        unsigned char *key = NULL;
	FILE *keyfileptr;
        
	/* Parse the input arguments for invalid case */

	if ( argc != 4 )
	{
		printf("Invalid arguments! Please read the readme.txt for instructions to use this tool!\n");
		exit(EXIT_FAILURE);
	}
	
	if ( strcmp("-k", argv[1]) != 0 )
	{
		printf("Unknown argument option:%s\n",argv[1]);
		exit(EXIT_FAILURE);
	}
	else
	{	
		keyfile = argv[2];
	}

	if ( strcmp("", argv[3]) == 0 )
        {
                printf("Input data is empty\n");
                exit(EXIT_FAILURE);
        }

	/* Read the key file from input file */

	keyfileptr = fopen(keyfile,"rb");

	if ( keyfileptr == NULL)
	{
		printf("can't open the keyfile, please check whether file exists \n");
		exit(EXIT_FAILURE);
	}

	if ( fseeko(keyfileptr, 0, SEEK_END) != 0 )
	{
		printf("can't set the keyfile to end  \n");
                exit(EXIT_FAILURE);
	}
	
        keyfilesize = ftello(keyfileptr);
	
	if ( fseeko(keyfileptr, 0, SEEK_SET) != 0 )
        {
                printf("can't set the keyfile to start \n");
                exit(EXIT_FAILURE);
        }
	
	keysize = keyfilesize-1;
	
	if(keysize == 0)
	{
        	printf("The key is empty, please input key in keyfile\n");
		exit(EXIT_FAILURE);
	}

	key = (unsigned char*) malloc(sizeof(unsigned char)*(keysize+1));

	if ( key == NULL )
	{
		printf("\n Couldn't allocate memory on heap");
                exit(EXIT_FAILURE);
	}

        while (!feof(keyfileptr)) 
	{
	       	fscanf(keyfileptr,"%c",&key[count++]);
	}
 
	key[keysize] = '\0';
	
	fclose(keyfileptr);

	/* copy the data to char array */

	datasize = strlen(argv[3]);

	if ( (datasize % keysize) == 0)
	{
        	data = (unsigned char*) malloc(sizeof(unsigned char)*(datasize+1));
		size_delta = 0;
	}
	else
	{
		if ( datasize < keysize )
		{
			size_delta = (keysize - datasize);
		}
		else
		{
			size_delta = (keysize - ( datasize % keysize));
			
		}
		data = (unsigned char*) malloc(sizeof(unsigned char)*(datasize+1+size_delta));
	}
  
	if ( data != NULL )
	{
	        strcpy(data,argv[3]);
	}
	else
	{
		free(key);
		printf("\n Couldn't allocate memory on heap");
		exit(EXIT_FAILURE);
	}
	
	/* Call encrypt with rotate shift value 1*/
	xor_encrypt(key, data, &datasize, keysize, size_delta, 1);

	printf("Encrypted output data: ");

	for ( k = 0; k < datasize; k++ )
	{      
		if ( (k % keysize) == 0 )
			printf("  ");
		printf("%02x", data[k]);
	}
	printf("\n");
       
	/* Free the heap memory used */
	free(data);
	free(key);

	return 0;

}

