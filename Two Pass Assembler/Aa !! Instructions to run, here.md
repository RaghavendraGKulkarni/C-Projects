The project converts an assembly level program to an object code using two passes.
1) Pass 01 :- Generation of SYMTAB, detection of invalid opcodes, allocation of addresses to the instructions and generation of Intermediate file.
2) Pass 02 :- Detection of any invalid operand in the instruction and object code generation.
Instructions :-
1) The assembly level program is to be loaded in the file sic.txt
2) The opcodes with their codes are to be loaded in the file Optab.txt
3) The symbol table is printed in the file Symtab.txt after pass 01 and a message is printed on the console.
4) The file Intermediate File.txt will be loaded with the intermediate code after pass 01 by the program.
5) Pass 02 scans the file Intermediate File.txt and refering to the files Optab.txt and Symtab.txt, generates the Object code and loads it in the file Object Code File.txt.
