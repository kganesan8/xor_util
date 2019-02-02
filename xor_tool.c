#include "xor_tool.h"

void xor_encrypt(unsigned char *key, unsigned char *data, int *datalen, int keylen, int shift)
{
        int i,j;
        unsigned int keyvalue;
	char temp;

        if ( key == NULL)
        {
                printf("The input key pointer is null");
                exit(EXIT_FAILURE);
        }

        if ( data == NULL)
        {
                printf("The input data pointer is null");
                exit(EXIT_FAILURE);
        }

        for( i = 0; i < *datalen; i++ )
        {
                if ( ((i % keylen) == 0) && i != 0 )
                {
                        rotate_left(key,keylen,shift);

                }
		
		if ( *datalen < keylen)
		{
			for ( j = 0; j < keylen; j++ )
			{
				if ( j == (keylen-1))
				{
                			data[j] = data[j]^key[j%keylen];
				}
				else
				{
					temp = data[j];
                                        data[j] = 0x00;
                                        data[j] = data[j]^key[j%keylen];
                                        data[j+1] = temp;
                                        *datalen += 1;
					
				}
			}
			break;
		}
		else
		{
			if ( (*datalen % keylen) != 0 )
			{
				if ( i == ( *datalen - ( *datalen % keylen) ) )
				{
					
					memmove(data+i+(keylen-(*datalen % keylen)), data+i,(*datalen % keylen));
		 			memset(data+i, 0, (keylen-(*datalen % keylen)));
					*datalen += (keylen-(*datalen % keylen));
			
					for ( j = 0; j < keylen; j++ )
                        		{
                                        		data[i+j] = data[i+j]^key[j%keylen];

                                	}

					break;
				}
				else
				{
					data[i] = data[i]^key[i%keylen];
				}
			}
			else
			{
				data[i] = data[i]^key[i%keylen];
			}
		}
        }

}

int get_ls_mask(int shift)
{
        switch (shift)
        {
        case 0:
                return 0x00;
        case 1:
                return 0x80;
        case 2:
                return 0xC0;
        case 3:
                return 0xE0;
        case 4:
                return 0xF0;
        case 5:
                return 0xF8;
        case 6:
                return 0xFC;
        case 7:
                return 0xFE;
        default:
                printf("\n Shift outside of range 0-7, so returning 0x00");
                return 0x00;
        }
}


void rotate_left(unsigned char* key, int key_len, int shift)
{
        unsigned char temp = 0x00, temp2 = 0x00, temp3 = 0x00;
        int k;

        if ( key != NULL )
        {
                temp3 = key[0];
        }
        else
        {
                exit(EXIT_FAILURE);
        }

        for (k = (key_len-1); k >= 0; k--)
        {
                if (k == (key_len-1))
                {
                        temp = key[k];
                        key[k] <<= shift;
                        key[k] |= ((temp3 & get_ls_mask(shift)) >> (8 - shift));
                }
                else
                {
                        temp2 = key[k];
                        key[k] <<= shift;
                        key[k] |= ((temp & get_ls_mask(shift)) >> (8 - shift));
                        temp = temp2;
                }
        }
}

