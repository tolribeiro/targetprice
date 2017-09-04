# Coding Puzzle

## Description:

A restaurant has its menu items listed on a `.csv` file following the structure: the fist line contains the target price and the following data values are menu items you could buy. 

The program should then find a combination of dishes that has a total of exactly the target price. If there is no solution found, then the program should print that there is no combination of dishes that is equal to the target price. Below is an example of how the program works:

### Input

The file `input.csv` contains the following information:

`Target price,$2.75

mixed fruit,$2.15
french fries,$2.60
gum,$0.25
coke,$1.50
cookie,$2.75
fries,$1.25`

### Output

Then it prints possible all the combinations from the menu items that sums up to a target:

`Option 1:
-----------
coke - $1.50
fries - $1.25
-----------
Total: $2.75

Option 2:
-----------
cookie - $2.75
-----------
Total: $2.75`

### Instructions

To run the program, go on terminal and type:

`./main input.csv`
