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
