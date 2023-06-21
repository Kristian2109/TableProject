# TableProject
Course project for Second Semester

### Important notes ###
- I've removed the type checking because we could have IP addresses or ID numbers which doesn't belong to any partycular format.
- Max sizes:
  + columns: 30
  + rows: 10000
  + len value: 256 ( 255 without the terminating null )

### Structure
1. We have a Row which is a vector from strings
2. Table which has rows and other attributes that contribute to the logic
3. System which handles the commands given by the user

### Functionalities

1. Load data from csv file with "open" command
-  We remove the double quotes in the end and begin of the value if it is a string.
-  If we have an invalid format like (Year"). The program wouldn't load the content. 

2. Print the data in the following format
    
| R1C1 | R1C2 | ....... | R1 Last column | 

3. Close the opened file, without autosaving

4. Saving
- We place a backslash after every symbol double quotes (").

5. Editing
- We raise an error if the value is bigger than 100 symbols. It wouldn't be saved.

6. Formulas
-  Almost like in your document.
-  If the value in the cell is empty or not a number, we set it to zero
-  Division by zero not possible
-  If the output is too large, we use the default log like: 1.54e10
-  Also, the precision is the default of the console
-  The power function can work only with whole numbers, but if we put a value with decimal lower than our EPSILON value (0.0000001), it would handle the power as a whole number. Else it will print "Invalid format".
