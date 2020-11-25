#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

//global definitions:
const float LOW_NUM = -21269;
const float HIGH_NUM = 21269;
const char * const exp_chars[] = { //unicode for superscripts
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












long long factorial(int n) 
{ 
    long long result = 1; 
    //base cases
    if (n == 0) 
        return 1; 
  
    //return error 
    if (n < 0) 
        return -1; 
    for (int i = 2; i < n + 1; ++i) 
        result *= i; 

    return result; 
} 

float _sumX(float *x,int n){ // is always smaller than len(x)
    float result=0;
    for(int i = 0; i<= n-1; i++){
        result += (x[i]*(factorial(n)/factorial(n-i)));
    }

    return result;
}
void fillX(float *x, float *a, int len){
    float value;
    x[0] = a[0];
    for(int n = 1; n < len; n++){ //loops X[i]
        x[n] = (a[n] -_sumX(x, n))/factorial(n);
    }
}



  
long long __getCombinations(int n, int r) { 
    //the function is only defined for r> n 
    if (r > n) 
        return -1; 
  
    if (n == r) 
        return 1; 
  
    if (r == 0) 
        return 1; 
  
    return __getCombinations(n - 1, r - 1) + __getCombinations(n - 1, r); 
} 
  
long long _getStirlingNumber(int r, int n) { 
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
        return __getCombinations(r, 2);
    }
    else{
        return (_getStirlingNumber(r - 1, n - 1) + (r - 1) * _getStirlingNumber(r - 1, n));
    }
} 

void fillCoeficients(float *x, float *coeficients, int len){
    float sum;
    for(int i=0; i< len; i++){
        sum = 0;
        for(int j = len -1; j>=0; j--){
            //cout << (x[j]) << '-' << _getStirlingNumber(j, i) << '-' << ((((i + j) % 2) == 0)? 1: -1) << endl;
            sum += ((x[j]) * _getStirlingNumber(j, i) * ((((i + j) % 2) == 0)? 1: -1));
        }
        coeficients[i] = sum;
    }
}

void _print_superscript(int x){
    if(x >= 10)
       _print_superscript(x / 10);

    int digit = x % 10;

    std::cout << exp_chars[digit];
}

void printResult(float * coeficients, int len){
    int aux, n_digits;

    for (int i = len -1; i >=2; i--){
        if (coeficients[i] != 0){
            cout << ((coeficients[i] >= 0)? '+': '-');
            cout << abs(coeficients[i]) << 'n';
            
            //prints the n exponent
            _print_superscript(i);

            cout << ' ';
        }
        
    }
    //print 1 degree
    if (coeficients[1] != 0){
        cout << ((coeficients[1] >= 0)? '+': '-');
        cout << abs(coeficients[1]) << 'n' << ' ';
    }
    //print 0 degree
    if (coeficients[0] != 0){
        cout << ((coeficients[0] >= 0)? '+': '-');
        cout << abs(coeficients[0]);
    }

    cout << endl;
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

int main(int argc, char *argv[]){
    //generate random seed
    srand(static_cast <unsigned> (time(0)));

    int command;
    //read command


    //main calculation variables
    int num_start_i = 1;//index where numbers start
    int len = argc - num_start_i; //len of number inputs
    float *a = (float*)malloc((len)*sizeof(float));
    float *x = (float*)malloc((len)*sizeof(float));
    float *coeficients = (float*)malloc((len)*sizeof(float));

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
    fillCoeficients(x, coeficients, len);

    printResult(coeficients, len);

    //clean memory
    free(a);
    free(x);
    free(coeficients);
    return 0;
}

