#include <iostream>
#include <cstring>
#include <cmath>
#include <cassert>


//global definitions:
constexpr float LOW_NUM = -21269;
constexpr float HIGH_NUM = 21269;
const char* EXP_CHARS[] = { //unicode for superscripts
    "\u2070",
    "\u00b9",
    "\u00b2",
    "\u00b3",
    "\u2074",
    "\u2075",
    "\u2076",
    "\u2077",
    "\u2078",
    "\u2079",
};

long long factorial(int n) { 
    long long result = 1; 
    //base cases
    if (n == 0) 
        return 1; 
  
    //error
    assert(n >= 0);

    for (int i = 2; i < n + 1; ++i) 
        result *= i; 

    return result; 
} 

float sumX(float *x,int n){ // is always smaller than len(x)
    float result=0;
    for(int i = 0; i<n; i++){
        result += (x[i]*(factorial(n)/factorial(n-i)));
    }

    return result;
}
void fillX(float *x, float *a, int len){
    x[0] = a[0];
    for(int n = 1; n < len; n++){ //loops X[i]
        x[n] = (a[n] -sumX(x, n))/factorial(n);
    }
}


long long getCombinations(int n, int r) { 
    //the function is only defined for r> n 
    assert(r <= n);
  
    if (n == r) 
        return 1; 
  
    if (r == 0) 
        return 1; 
  
    return getCombinations(n - 1, r - 1) + getCombinations(n - 1, r); 
} 
  
long long getStirlingNumber(int r, int n) { 
    if (r == n) 
        return 1; 

    //the function is only defined for n> r, but in our program we need 0
    if (n > r) 
        return 0; 
  
    if (n == 0) 
        return 0; 
  
    if (n == 1) 
        return factorial(r - 1); 
  
    if (r - n == 1){
        return getCombinations(r, 2);
    }

    return (getStirlingNumber(r - 1, n - 1) + (r - 1) * getStirlingNumber(r - 1, n));

} 

void fillCoefficients(float *x, float *coefficients, int len){
    float sum;
    for(int i=0; i< len; i++){
        sum = 0;
        for(int j = len -1; j>=0; j--){
            
            sum += ((x[j]) * getStirlingNumber(j, i) * ((((i + j) % 2) == 0)? 1: -1));
        }
        coefficients[i] = sum;
    }
}

void print_superscript(int x){
    if(x >= 10)
       print_superscript(x / 10);

    int digit = x % 10;

    std::cout << EXP_CHARS[digit];
}

void printResult(float * coefficients, int len){
    int aux, n_digits;

    for (int i = len -1; i >=2; i--){
        if (coefficients[i] != 0){
            std::cout << ((coefficients[i] >= 0)? '+': '-');
            std::cout << std::fabs(coefficients[i]) << 'n';
            
            //prints the n exponent
            print_superscript(i);

            std::cout << ' ';
        }
        
    }
    //print 1 degree
    if (coefficients[1] != 0){
        std::cout << ((coefficients[1] >= 0)? '+': '-');
        std::cout << std::fabs(coefficients[1]) << 'n' << ' ';
    }
    //print 0 degree
    if (coefficients[0] != 0){
        std::cout << ((coefficients[0] >= 0)? '+': '-');
        std::cout << std::fabs(coefficients[0]);
    }

    std::cout << std::endl;
}

float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

float randomInt(int a, int b) {
    return a + rand() % (( b + 1 ) - a);
}

int main(int argc, const char *argv[]){
    //generate random seed
    srand(static_cast <unsigned> (time(0)));

    int command;
    //read command

    //main calculation variables
    int num_start_i = 1;//index where numbers start
    int len = argc - num_start_i; //len of number inputs
    float* a = (float*)malloc((len)*sizeof(float));
    float* x = (float*)malloc((len)*sizeof(float));
    float* coefficients = (float*)malloc((len)*sizeof(float));

    float input_aux;
    for (int i = num_start_i; i <= (argc - num_start_i); i++){
        if(strcmp(argv[i], "f") == 0){ // generate random float
            input_aux = randomFloat(LOW_NUM, HIGH_NUM);
        }
        else if (strcmp(argv[i], "i") == 0){ // generate random int
            input_aux = randomInt(LOW_NUM, HIGH_NUM);
        }
        else{
            input_aux = atof(argv[i]);
        }

        a[i - num_start_i] = input_aux;
    }

    fillX(x, a, len);
    fillCoefficients(x, coefficients, len);

    printResult(coefficients, len);

    //clean memory
    free(coefficients);
    free(x);
    free(a);
    return 0;
}

