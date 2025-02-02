#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

const long long  prime_base = 31;
const long long  M          = 1e9 + 7;


bool is_prime(long n){
    /*skipping the multiple of 2 and 3*/
    if(n %2 == 0 || n%3 == 0) return false;

    for(int i = 5 ;i*i<=n;i+=6){
        if(n%i == 0 || n%(i+2) == 0) return false;
    }

    return true;
}

int size_of_table(int expected_keys_count){
    int N = 2*expected_keys_count + 1;
    
    /*definitly thge table size will be more than 8 so i will not
     not check base case
    */

   while(is_prime(N)){
        N += 2;
   }

   return N;
}

int hashvalue_of_key(char* key){
    int hash = 0;
    for(char* c = key;*c != '\0';++c){
        hash = ((hash*prime_base)%M + *c)%M;
    }
    return hash;
}

int main(){
    printf("prime %d\n %lld,%lld\n %d\n",size_of_table(64),prime_base,M,hashvalue_of_key("Radha"));
}