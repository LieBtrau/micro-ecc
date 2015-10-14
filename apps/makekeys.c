#if !TARGET_LPC11XX

#include "uECC.h"
#include "Base64.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void vli_print(uint8_t *p_vli)
{
    unsigned i;
    for(i=0; i<uECC_BYTES-1; ++i)
    {
        printf("0x%02X, ", (unsigned)p_vli[i]);
    }
    printf("0x%02X", (unsigned)p_vli[i]);
}

int randfd;

int getRandomBytes(uint8_t *p_dest, unsigned p_size)
{
    if(read(randfd, p_dest, p_size) != (int)p_size)
    {
        printf("Failed to get random bytes.\n");
    }
}

int main(int argc, char **argv)
{
    unsigned l_num = 1;
    unsigned i, j;
    
    if(argc > 1)
    {
        l_num = strtoul(argv[1], NULL, 10);
    }
    
    randfd = open("/dev/urandom", O_RDONLY);
    if(randfd == -1)
    {
        printf("No access to urandom\n");
        return -1;
    }
    
    uint8_t l_private[uECC_BYTES];
    uint8_t l_public[uECC_BYTES*2];
    uint8_t base64enc[uECC_BYTES*4];
    
    for(i=0; i<l_num; ++i)
    {
	uECC_set_rng(&getRandomBytes);
	uECC_make_key(l_public, l_private);
	
	base64_encode(base64enc, l_private, uECC_BYTES);
        printf("Private_key_%u= \"", i);
        printf(base64enc);
        printf("\";\n");
        printf("uint8_t private_%u[NUM_ECC_DIGITS] = {", i);
        vli_print(l_private);
        printf("};\n");


 	base64_encode(base64enc, l_public, uECC_BYTES*2);
        printf("Public_key_%u= \"", i);
        printf(base64enc);
        printf("\";\n");

        printf("uint8_t public_%u[2*NUM_ECC_DIGITS] = {", i);
        vli_print(l_public);
        vli_print(l_public+uECC_BYTES);
        printf("};\n\n");
    }
    
    return 0;
}

#endif /* !TARGET_LPC11XX */
