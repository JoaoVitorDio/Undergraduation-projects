# Software Projects - Graduation 

### What is this repository?

It is a repository of exercises and some project solutions *mainly, in the C language* developed by the student João Vitor D. during the course **Bachelor of Information Systems** at the [Institute of Mathematical and Computer Science](https://www.icmc. usp.br/ "Institute of Mathematical and Computer Science") of **[Universidade de São Paulo](https://www5.usp.br/ "Universidade de São Paulo")**.

### Why?

In the technology market, it is very interesting for those who want to grow within it that their evolution is relevant, constant, and of course, that their steps are documented.

At the same time, so that opportunities can appear and find themselves, whether for the individual or for potential initiatives that have a demand for a particular professional, it is necessary for those involved to leave “digital footprints", that is, show the world who you are, what you do, and how you do it.
**So**... I tried to document my path through the technology career here. (At least when it comes to academic projects)

### How is it organized?

~~Assuming already familiarity with github:~~:
The repository is divided by subjects (there is no repository for each subject in the course, as not all of them are aimed at software development). 

In the directory [Introduction to Computer Science 1](https://github.com/JoaoVitorDio/Projetos-em-C-Graduacao-/tree/master/Introdu%C3%A7%C3%A3o%20%C3%A0%20Ci%C3%AAncia%20da%20Computa%C3%A7%C3%A3o%201), there're the first steps of a student who definitely knew absolutely nothing about programming, let alone C. The exercises are in ascending order of progress. course and consequent learning of new tools and methods. ~~Yes, the first exercises are embarrassing, but they are no less important for that! Without them, I wouldn't be here, so let them public!~~ There is no directory for classes 1 to 7 because they were lectures and theoretical classes, in pseudocode and introduction to concepts, such as variables, compilers, assemblers, workflows code and the basics of the logic involved in programming.

At the end of Introduction to Computer Science 1 and the beginning of the second semester - (Algorithms and Data Structures + Introduction to Computer Science 2 courses) - I started using a [cloud-based Unix environment for development](https://ide.cs50.io/ "cloud-based Unix environment for development"), as well as more interesting tools to debug and monitor the functioning of *-ggdb and Valgrind-* codes and consequently closer contact with the `command line` and the like.

### How do I use any of the solutions?

As much as the projects developed so far, for the most part, do not have great practical and commercial application, they were super important and some were considerably challenging from the point of view of **development of the logic of organizing the information and elaborating a sequence of steps that makes meaning to a machine** (which is super relevant in my opinion, since, unfortunately ~~or fortunately~~), life is not like this:

![b9d6de8262241bf9ac45ea28360a426f](https://user-images.githubusercontent.com/60077147/93294909-3d287880-f7c2-11ea-9b07-211c1b823d98.jpg)


Some have uses in mathematics, such as the algorithm for calculating the root of newton, or the "prime number printer", or even the program that generates the fibonacci sequence. Some - in the struct and file management part, for example - are small management systems.

If you are interested in executing any of the solutions presented here, it is necessary to compile the `.c code` (in the case of single file programs. Some require linking and use of the CMake tool - The makefile will be in the same directory as the file and more below is the explanation of how it works).

To do this, if you have already installed gcc and the development packages, just follow the guide...:

    if (file.c == Single file in directory())
    {
    printf("Type in your linux terminal, inside the directory where the program was downloaded:\n");
    $ gcc program_name.c -o program_name
    printf("An executable file will magically appear in the current directory: 'program_name'\n");
    printf("To run it
