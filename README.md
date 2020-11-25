# Math series generator:
Introduce any sequence and the program will return a matching math sequence. Remember that sequences start in n=0.

## Instructions:
Simply compile the program and then execute it passing the series numbers as arguments. You may also pass 'i' or 'f' instead of a number to use a random integer or float, respectively.

## Examples:
[user@localhost Math_Series]$./executable 2 5 0 -10   
+0.5n³ -5.5n² +8n +2

[user@localhost Math_Series]$./executable 0 1 4 9 16 25   
+1n²

[user@localhost Math_Series]$./executable 1 2 f i  
+4739.95n³ -16947.8n² +12208.8n +1 
(your output will be probably different)

[user@localhost Math_Series]$./executable i i i i  
-7847.5n³ +35158.5n² -37451n +12793 
(your output will be probably different)