# OS_Assignment1
Operating Systems Fall 2021, programming assignment #1.

Code largely taken from lectures by professor, as well as the github repository https://gist.github.com/walchko/6d211a2dc8b2f5158642fb2fd65cf295 .
Used as a template for adding integers into shared memory, and then displaying all of those integers at the end.

In the terminal, run 'gcc producer.c -pthread -lrt -o producer', then 'gcc consumer.c -pthread -lrt -o consumer', then './producer & ./consumer &', as designated by the OS Assignment instructions. It displays the empty shared memory, then the filled shared memory (in a type I do not understand), then displays the integers added to the shared memory. The program does not close after that is printed, and Ctrl+C must be pressed to close it.
