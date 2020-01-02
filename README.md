# csc411-a6
Implementing a Universal Machine (simple Virtual Machine)  

This assignment was based on a problem found in the [ICFP programming contest 2006](http://fileformats.archiveteam.org/wiki/Universal_Machine_(ICFP_programming_contest_2006)).  

This repo also represents our work improving our Universal Machine using a profiler using Valgrind's Callgrind.  
The steps we used to improve the Universal Machine are as follows (more details in labnotes.pdf): 

1. Compile with optimization (01 and 02)
2. Remove bitpack module and replace with inlined and specialized getu function
3. Inline parser and instructions modules
4. Removed repetitive pointer dereference  
5. Only load the program segment when needed
6. Replaced Hanson Array's with our specialized arrays
7. Use uintptr to get around mallocing/freeing in Hanson's stack
8. Removed needless asserts
9. Every module is inlined, removed more repeated pointer dereferences
10. Replaced arr_clone's loop with memcpy
11. Wrote our own sequence data structure to replace Hanson's
12. Wrote our own stack to replace Hanson's
13. Tweaked alignment of structs
