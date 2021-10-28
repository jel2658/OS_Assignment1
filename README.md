# OS_Assignment1
Operating Systems Fall 2021, programming assignment #1. By Justin Labrie.

Code largely taken from lectures by professor, as well as the github repository https://gist.github.com/walchko/6d211a2dc8b2f5158642fb2fd65cf295 .
Used as a template for adding integers into shared memory, and then displaying all of those integers at the end.

In the terminal, run 'gcc producer.c -pthread -lrt -o producer', then 'gcc consumer.c -pthread -lrt -o consumer', then './producer & ./consumer &', as designated by the OS Assignment instructions. It displays the empty shared memory, then the filled shared memory (in a type I do not understand), then displays the integers added to the shared memory. The program does not close after that is printed, and Ctrl+C must be pressed to close it.

After having looked at a variety of different examples, including the aforementioned github, I have concluded that there is very little I can do in the way of customizing this program to be less copy-pasted. I have changed what is stored in the shared memory, and attempted syntax changes more in line with the professor's code, but ultimately I am not knowledgable enough to do much else. I'm willing to take whatever penalty might come of this, because the lectures have not gone over specific code pertaining to this project anyway and I wouldn't be able to do it on my own. Given the requirements of the project, I also believe there will be little difference between classmates' projects and mine as well, but I haven't looked at any of theirs.
