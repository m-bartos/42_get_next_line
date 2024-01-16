# 42_get_next_line
This project is about programming a function that returns a line read from a file descriptor.

## Description
* Repeated calls (e.g., using a loop) to get_next_line() function will read from the text file pointed to by the file descriptor, one line at a time.
* Function is returning the line that was read. If there is nothing else to read or if an error occurs, it returns NULL.
* Function works as expected both when reading a file and also when reading from the standard input.
* Returned line includes the terminating \n character, except if the end of the file was reached and does not end with a \n character.
* This get_next_line() function can manage multiple file descriptors at the same time. For example, if you can read from the file descriptors 3, 4 and 5, you should be able to read from a different fd per call without losing the reading thread of each file descriptor or returning a line from another fd. It means that you should be able to call get_next_line() to read from fd 3, then fd 4, then 5, then once again 3, once again 4, and so forth.
* The get_next_line() has undefined behaviour if the file pointed to by the file descriptor changed since the last call whereas read() didn’t reach the end of the file.
* We also consider that get_next_line() has undefined behaviour when reading a binary file.
* By default the BUFFER_SIZE for reading is set to 10. However, you can change it when compiling with the `-D BUFFER_SIZE=42` flag or it can be changed inside the header files.

## What I learned during this project
* I learned about and implemented static variables
* I got more familiar with string handling (dividing one string into two strings, freeing allocated memory, etc.)
