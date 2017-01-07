#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*notes: 
 * error catching is very basic. play nice
 * not optimized for efficiency
 */

void printUsage()
{
	printf("Usage: gmath [dvrs|et|gcd|lcm|pf] [args...]\n");
	exit(1);
}

//helper method: converts the integers specified by user into an array of integers to use
int * get_int_args(int argc, char *argv[]){
	int * tmp = malloc(sizeof(int) * argc-2);
	for (int i = 0; i < argc-2; i++){;
		tmp[i] = atoi(argv[i+2]);
	}
	return tmp;
}

//prints all numbers from 1 to divide_num that divide divide_num
/*void print_divisors(int divide_num){
	for (int i = 1; i <= divide_num/2; i++){
		if (divide_num % i == 0){
			printf("%d\n", i);
		}
	}
	printf("%d\n", divide_num);
}*/

//faster print_divisors, but prints out of numerical order
void print_divisors(int divide_num){
	int incr = divide_num % 2 == 0 ? 1 : 2;
	int r = sqrt(divide_num);
	for (int i = 1; i <= r; i+=incr){
		if (divide_num % i == 0){
			printf("%d\n", i);
			if (i != r) printf("%d\n", divide_num/i);
		}
	}
}

//prints number positive integers less than n that are relatively prime to n
void print_euler_totient(int n){
	int total = 0;
	int tmp_gcd;
	if (n == 1) total = 1;
	for (int i = 1; i < n; i++){ // i is positive integer less than n to test
		tmp_gcd = 1;
		//calculate gcd of i and n, store in tmp_gcd
		for (int j = 1; j <= i; j++){
			if (i % j == 0 && n % j == 0) tmp_gcd = j;
		}
		if (tmp_gcd == 1) total++;
	}
	printf("%d\n", total);
}

//prints the greatest common denominator of list
void print_gcd(int * list, int size){
	//find smallest in list
	int tmp_gcd = INT_MAX;
	for (int i = 0; i < size; i++){
		if (list[i] < tmp_gcd){
			tmp_gcd = list[i];
		}
	}

	//from smallest to 1, print first number that divides everything in list
	char divided_everything = 0;
	while (tmp_gcd > 1){
		for (int i = 0; i < size; i++){
			if (list[i] % tmp_gcd != 0){ //does not divide
				break;
			}
			if (i == size-1) divided_everything = 1; //got to final spot in list without hitting break => tmp_gcd divides all entries
		}
		if (divided_everything) break;
		tmp_gcd--;
	}
	printf("%d\n", tmp_gcd);
	free(list);
}

//prints the least common multiple of list
void print_lcm(int * list, int size){
	//find largest in list, store in tmp_lcm
	int tmp_lcm = INT_MIN;
	for (int i = 0; i < size; i++){
		if (list[i] > tmp_lcm){
			tmp_lcm = list[i];
		}
	}

	//find max possible (to define upper search bound)
	int max_possible = 0;
	if (size > 0) max_possible = list[0];
	for (int i = 1; i < size; i++){
		max_possible *= list[i];
	}

	//search from largest in list to max possible, print first number everything in list divides
	char everything_divides = 0;
	while(tmp_lcm < max_possible){
		for (int i = 0; i < size; i++){
			if (tmp_lcm % list[i] != 0) break; //element does not divide tmp_lcm
			if (i == size-1) everything_divides = 1;
		}
		if (everything_divides) break;
		tmp_lcm++;
	}
	printf("%d\n", tmp_lcm);
	free(list);
}

//returns smallest prime larger than p
int get_next_prime(int p){
	if (p < 2) return 2;
	if (p == 2) return 3;
	while(p>0){
		p++;
		for (int i = 2; i <= p/2; i++){ //test if p is prime
			if (p % i == 0) break;
			if (i == (p/2)) return p; 
		}
	}
	return -1; //should not get here
}

//prints prime factorization of n
void print_prime_factorization(int n){
	int p = 2, pow = 0, rem = n; //p: current prime to check; pow: power of p; rem: remainder of n after being divided by previously checked p values
	//Algorithm is basically check whether n is divisible by each prime in increasing order. When n is divisible by that prime, increase power of that prime and divide by that prime again until no longer divisble. Move onto higher primes until finished.
	while (p <= rem){
		while (rem % p == 0) {
			rem = rem/p;
			pow++;
		}
		if (pow != 0) {
			printf("%d^%d\n", p, pow);
		}
		pow = 0;
		p = get_next_prime(p);
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2){
		printUsage();
		return 1;
	}

	if (strncmp(argv[1], "dvrs", 4) == 0){
		print_divisors(atoi(argv[2]));
	} 
	else if (strncmp(argv[1], "et", 2) == 0){
		print_euler_totient(atoi(argv[2]));
	} 
	else if (strncmp(argv[1], "gcd", 3) == 0){
		print_gcd(get_int_args(argc, argv), argc-2);
	} 
	else if (strncmp(argv[1], "lcm", 3) == 0){
		print_lcm(get_int_args(argc, argv), argc-2);
	}
	else if (strncmp(argv[1], "pf", 2) == 0){
		print_prime_factorization(atoi(argv[2]));
	}
	else {
		printUsage();
		return 2;
	}
	return 0;
}
