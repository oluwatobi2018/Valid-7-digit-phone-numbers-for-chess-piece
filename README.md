# Valid-7-digit-phone-numbers-for-chess-piece
We will calculate the number of valid phone numbers of certain length by the movement of knight and bishop on a keypad.
The properties of the phone number:

The phone number starts with some digits by input.

The phone number should not contain special characters.

The length of the phone number should be a value by input.

## Algorithm

I use factory pattern to create two movement methods. The main idea is to create a path denoting all the possible next digits of a certain digit. Recursive method is used, which will not handle big test cases. DP or Cache method should be used. Bishop movement is complex and difficult to combine four direction cases into one function.  

## Usage
The console will get the following lines:
1. movement mode either "knight" or "bishop"
2. length of phone number
3. start digits
4. keypad rows
5. keypad columns
6. each line will be a row of keypad

For example:
(1)

knight

2

1 2 3 4 5 6 7 8 9

4

3

1 2 3

4 5 6

7 8 9

? 0 #

It will return 18

(2)

bishop

2

1 2 3 4 5

4

3

1 2 3

4 5 6

7 8 9

? 0 #

It will return 12







# telephone-numbers-by-chess-moves (scala)

## Summary
Scala solution for the coding puzzle for generating n-digit numbers using a phone keypad in which subsequent keys are defined by possible moves of a chess piece 

The original problem was described in [Generate 10-digit number using a phone keypad
](https://stackoverflow.com/questions/2893470/generate-10-digit-number-using-a-phone-keypad). 

The code that is given here, generalizes the problem in two ways: 
  - instead of 10 digits, telephone numbers of any length can be counted
  - all chess pieces can be used to define valid combinations

You can run the code by entering `sbt test` in directory `telephone-numbers-by-chess-moves`. This requires cloning this repository first.
There is no `main`-method defined, so `sbt run` will not work!
  
## Problem Description

Imagine a knight (the chess piece) is put on the field "1" of regular telephone keypad (as shown below). How many different telephone numbers of length *n* (*n* being any natural number, i.e. 1,2,3 ...) can be dialed?

```
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+
| 4 | 5 | 6 |
+---+---+---+
| 7 | 8 | 9 |
+---+---+---+
    | 0 |
    +---+
```
For example, if *n = 3*, starting at 1, with a knight we can dial the numbers 

| count | telephone number |
| ----: | ---------------: |
|     1 |              160 |
|     2 |              161 |
|     3 |              167 |
|     4 |              181 |
|     5 |              183 |

For all 10 possible starting positions (0, 1, ... 9) the result for 3-digit phone numbers is (as produced by the code):

```
chess piece: Knight
start position:  0, length:   3, number of telephone-numbers:                                  6
start position:  1, length:   3, number of telephone-numbers:                                  5
start position:  2, length:   3, number of telephone-numbers:                                  4
start position:  3, length:   3, number of telephone-numbers:                                  5
start position:  4, length:   3, number of telephone-numbers:                                  6
start position:  5, length:   3, number of telephone-numbers:                                  0
start position:  6, length:   3, number of telephone-numbers:                                  6
start position:  7, length:   3, number of telephone-numbers:                                  5
start position:  8, length:   3, number of telephone-numbers:                                  4
start position:  9, length:   3, number of telephone-numbers:                                  5
	  total number of telephone-numbers with length    3:                                 46
``` 

## Code
The code has been tested based on Scala version 1.12.5 but no specific features of this version are used, so it should also work with older and (hopefully) also newer versions of the language.

For the algorithm to work for larger numbers, a tail-recursive method is used. This makes to code a little more complicated, but also a lot faster!
Since the number of numbers are computed based on `BigInt`s, rather large values for length of telephone numbers can be used.
