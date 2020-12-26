#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define N 3

void felma_sub(mpz_ptr num);

void felma_sub(mpz_ptr num){
    mpz_set_ui(num, 1);

}

int main(){
    mpz_t a[N];

    for(int i=0 ; i<N ; i++){
        mpz_init(a[i]);
    }

    felma_sub(a[0]);

    gmp_printf("a[0]=%Zd\n",a[0]);

    for(int i=0 ; i<N ; i++){
        mpz_clear(a[i]);
    }
    return 0;
}
