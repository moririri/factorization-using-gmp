#include<stdio.h>
#include<gmp.h>
#include<limits.h>

#define NUM 10

void f(mpz_ptr n, mpz_t temp);
void abs_num(mpz_ptr n, mpz_t num1, mpz_t num2);

/*global*/
mpz_t P;

void f(mpz_ptr n, mpz_t temp){
	mpz_t num[2];
	int i=0;

	for(i=0;i<2;i++){
		mpz_init(num[i]);
	}

	mpz_set(num[0], temp);
	mpz_powm_ui(num[1], num[0], 2, P);
	mpz_add_ui(num[1], num[1], 1);
	mpz_mod(n, num[1], P);
	//mpz_set(n, num[1]);

	for(i=0;i<2;i++){
		mpz_clear(num[i]);
	}
}

void abs_num(mpz_ptr n, mpz_t num1, mpz_t num2){
	mpz_t temp1;
	mpz_t num[2];
	int flag=0, i=0;

	mpz_init(temp1);

	for(i=0;i<2;i++){
		mpz_init(num[i]);
	}

	mpz_set(num[0], num1);
	mpz_set(num[1], num2);

	flag=mpz_cmp(num[0], num[1]);

	if(flag < 0){ // num[0] < num[1]
		mpz_set(temp1, num[0]);
		mpz_set(num[0], num[1]);
		mpz_set(num[1], temp1);
	}

	mpz_sub(n, num[0], num[1]);

	mpz_clear(temp1);

	for(i=0;i<2;i++){
		mpz_clear(num[i]);
	}

}


int main(){
	mpz_t temp;
	mpz_t temp1;
	mpz_t temp2;
	mpz_t center;

	int flag=0;
	unsigned long int temp3=2;

	mpz_init(temp);
	mpz_init(temp1);
	mpz_init(temp2);
	mpz_init(center);
	mpz_init(P);

	gmp_scanf("%Zd", &P);

LABEL:

	//mpz_set_str(P, Prime, NUM);
	mpz_set_ui(temp1, temp3); //temp1 is 1.
	f(temp, temp1); //temp is 2.


	for(;;){
		f(temp1, temp1);
		f(temp, temp);
		f(temp, temp);
		abs_num(center, temp1, temp);
		mpz_gcd(center, center, P);
		flag=mpz_cmp_ui(center, 1);
		if(flag!=0){
			break;
		}
	}

	mpz_cdiv_q(temp2, P, center);

	if((mpz_cmp_ui(center, 1)==0) || (mpz_cmp_ui(temp2, 1)==0)){
		temp3=temp3+1;
		goto LABEL;
	}
	else if(temp3 == UINT_MAX){
		printf("rho method is failed.\n");
		return 1;
	}
	else{
		gmp_printf("%Zd: %Zd %Zd\n",P,center,temp2);	
	}

	mpz_clear(temp);
	mpz_clear(temp1);
	mpz_clear(temp2);
	mpz_clear(center);
	mpz_clear(P);
	return 0;
}
