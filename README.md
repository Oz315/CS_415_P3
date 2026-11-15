Oscar Huitron-Gonzalez and Shakira Garcia

Gen AI Disclosure-

Gen AI tool I used: ChatGPT
The conceptual questions I asked:
- “What does a high-branching prefix mean for autocomplete?”
- “Why does a standard Trie usually use more memory than a BST-based Trie?”
- “Why can a standard Trie be faster even though it takes up more space?”
- “How do the length of the prefix and the number of autocomplete results affect the operation count?”
- “Why can the number of operations for building the Trie be different from searching all the words?”

How the responses influenced your design or analysis:
The responses mainly helped me understand and analyze the differences between the standard Trie and the BST-based Trie.
They helped me understand why the standard Trie uses more memory because it keeps space for all possible child pointers, while
the BST-based Trie only stores the branches that are needed. They also helped me understand why the standard Trie can be faster for normal searching
because it can directly access a child, while the BST-based Trie may need several comparisons.

The responses also helped me analyze the autocomplete results. I understood that longer prefixes can require more search operations,
while prefixes with many possible completions can require more autocomplete operations because a larger part of the Trie has to be explored.
The explanation of high-branching prefixes helped me understand why queries such as 's' had much larger autocomplete operation counts than prefixes
with only a few results. Finally, the responses helped me explain why building the Trie required a different number of operations than searching all of the words. 
Building includes creating and connecting nodes, while searching uses the structure that has already been created. I used these explanations to help interpret my program's 
results and write the reflection and complexity comparison sections of the report.


Instructions to run the code:

Run the program from the project directory on Blue.

### Case 1 – Trie Building and Auto-Complete

Use the following format:

```bash
./main <input_file> 1
```

Examples:

```bash
./main test.txt 1
./main test2.txt 1
./main tale-1.txt 1
./main words_alpha.txt 1
```

After the Trie is built, enter a prefix when prompted to test the auto-complete feature.

Enter:

```text
0
```

to quit the program.

### Case 2 – Search All Strings

Use the following format:

```bash
./main <input_file> 2
```

Examples:

```bash
./main test.txt 2
./main test2.txt 2
./main tale-1.txt 2
./main words_alpha.txt 2
```

Case 2 builds both Trie implementations and searches all strings from the selected input file.
