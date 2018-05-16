# TextGen
A pseudo-random text generator using Markov modelling.

## To Use
There are two options:
### Use the executable
Input the complete filename (with a "\_inp.txt" extension, which will be replaced by a "\_out.txt" extension). 
Note, the filename must be in the current directory as the executable.

### Build from source
Compile MarkovChains.cpp, and run the executable, as above.
C++ 11 options must be enabled while compiling. In gcc, do: 
```bash
gcc -std=c++11 MarkovChains.cpp"
```

This is a C++ implementation for this [assignment](http://www.cs.princeton.edu/courses/archive/spring17/cos126/assignments/markov.html), a part of Princeton University's CS course - COS126.
