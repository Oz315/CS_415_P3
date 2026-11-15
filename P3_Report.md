1. Trie Building Results

Include a summary of your results in the table below. In support of your answers, include screenshot of the output of your program in the appendix section (at the end of the report).

| Input file            |Number of words | Standard Trie Build \#operations | BST-based Trie  Build \#operations | Standard Trie space | BST-based Trie space |
|:----------------------|:--------------:|----------------------------------|------------------------------------|---------------------|:--------------------:|
| **test.txt**          |     **26**     | **283**                          | **643**                            | **1872**            |       **216**        |
| **test2.txt**         |     **69**     | **759**                          | **2012**                           | **4628**            |       **534**        |
| **tale.txt**          |    **1002**    | **9410**                         | **32705**                          | **49374**           |       **5697**       |
| **words\_ alpha.txt** |   **370103**   | **5920416**                      | **74113215**                       | **26723034**        |     **3083427**      |

**Reflection 1**: Explain why the two Tries require different amount of time to be built, and use different amounts of space. Were the observed results consistent with the theoretical expectations?

The two tries require different amounts of time and space to be built because of the nature of their lookups. When the standard Trie is being built, it simply goes from the root and looks up the index of the respective letter being inserted (0-25) or simply traverses to that same index if it's already there. That also accounts for its larger space cost, as each node must have an array of 26 child pointers for each letter, regardless of whether the letter exists or not. On the other side, with a BST-based Trie, it only has the letters it needs, meaning a whole lot less space is being used. But that also means when looking up, more comparisons are being done, as the Trie may have to look through many letters just to find the spot where the given word should be inserted. The results above do align with the theoretical expectations.

2. Autocomplete Results

Include a summary of the autocomplete results below. In support of your answers, include screenshot of the output of your program in the appendix section (at the end of the report).

For the files tale.txt and words-alpha.txt, fill the table for specific queries. In addition, find and list results for 

1. No-match query  
2. high-branching query (a prefix whose Trie node has many possible next characters, usually resulting in many auto-complete choices)  
3. low-branching query (a prefix with only a few possible continuations and a small auto-complete subtree)  
4. complete-word prefix (a complete word in the Trie that is also a prefix of one or more longer words).

| Query in file tale.txt            | Number of results     | \#operations Standard search     | \#operations BST-based search     | \#operations Standard auto-complete     | \#operations BST-based auto-complete     |
|:----------------------------------|-----------------------|----------------------------------|-----------------------------------|-----------------------------------------|------------------------------------------|
| re                                | **10**                | **2**                            | **20**                            | **1757**                                | **277**                                  |
| fr                                | **3**                 | **2**                            | **13**                            | **353**                                 | **62**                                   |
| No-match query (z)                | **0**                 | **1**                            | **12**                            | **1**                                   | **12**                                   |
| High-branching query (s)          | **48**                | **1**                            | **14**                            | **5995**                                | **899**                                  |
| Low-branching query (ba)          | **2**                 | **2**                            | **9**                             | **218**                                 | **38**                                   |
| Complete-word prefix (ever)       | **3**                 | **4**                            | **17**                            | **193**                                 | **42**                                   |
|                                   |                       |                                  |                                   |                                         |                                          |
| **Query** in file words-alpha.txt | **Number of results** | **\#operations Standard search** | **\#operations BST-based search** | **\#operations Standard auto-complete** | **\#operations BST-based auto-complete** |
| abac                              | **24**                | **4**                            | **13**                            | **1381**                                | **214**                                  |
| miser                             | **25**                | **5**                            | **151**                           | **1652**                                | **392**                                  |
| No-match query (zz)               | **0**                 | **2**                            | **49**                            | **2**                                   | **49**                                   |
| High-branching query (s)          | **38764**             | **1**                            | **60**                            | **2838970**                             | **420645**                               |
| Low-branching query (xyr)         | **6**                 | **3**                            | **98**                            | **570**                                 | **179**                                  |
| Complete-word prefix (please)     | **9**                 | **6**                            | **106**                           | **438**                                 | **167**                                  |

**Reflection 2**: Both Trie implementations should return exactly the same auto-complete strings for every query. Explain how the characteristics of each query \- such as its length, branching factor, and whether it is itself a complete word \- affected the operation counts and auto-complete performance of the standard Trie and the BST-based Trie. Were the observed results consistent with the theoretical expectations? Did one implementation consistently outperform the other for auto-complete? If not, explain why.

For each query, its characteristics would influence the auto-complete in slightly different ways. The length of the query itself didn’t have much influence compared to other aspects, only really being impactful when there was a no-match query, as the operations for standard auto-complete would be dictated by its length. Much more impactful is branching, being the main factor influencing the number of operations done. Because of the nature of a standard Trie, it’d need to search each and every one of its 26 children to ensure there isn’t anything there, whereas a BST-based Trie only has 3 children at any given node, which, while it may still require many comparisons, not nearly as many since it contains only the letters needed. Completion of the word also followed a similar pattern, the only real difference being the initial search of the query being faster on a standard Trie. Regardless, it can be seen that for auto-complete operations, the BST-based Trie consistently outperformed the standard Trie, likely because of the reason mentioned prior, where from any given query, we’d only need to check the branching paths of 3 children nodes at worst case to find words for auto-completion, whereas a standard Trie needs to check 26\. The only case where this fact is different is when there is no matching query, which makes sense because a standard Trie can do one set of lookups and find nothing, but the BST-based Trie would need to go check its children to make sure the words aren’t hidden deep down.

3. Search-all Results

This section corresponds to results from **Case 2**. Include a summary of your results in the table below. In support of your answers, include screenshot of the output of your program in the appendix section (at the end of the report).

| Input file            | Number of strings searched | Standard Trie Build \#operations | Standard Trie  Search-all \#operations | BST-based Trie  Build \#operations | BST-based Trie  Search-all  \#operations |
|:----------------------|:---------------------------|----------------------------------|----------------------------------------|------------------------------------|------------------------------------------|
| **test.txt**          | **26**                     | **283**                          | **139**                                | **643**                            | **372**                                  |
| **test2.txt**         | **69**                     | **759**                          | **403**                                | **2012**                           | **1199**                                 |
| **tale.txt**          | **1002**                   | **9410**                         | **5612**                               | **32705**                          | **20408**                                |
| **words\_ alpha.txt** | **370103**                 | **5920416**                      | **3864798**                            | **74113215**                       | **52966212**                             |

**Reflection 3**: For the same input file, which out of the standard Trie and the BST-based Trie required more operations to search every string? Explain the difference using the number of characters searched, the number of child comparisons or array lookups.

For every input file, the BST-based Trie required more operations to search every single string. This can easily be explained by the nature of lookups in each Trie. The standard trie only has to do a single operation for each letter and since each word we are looking for does exist, it will take as many characters in the word in operations for the standard Trie. However, a BST-based Trie will eventually have to look at branching children to find some characters, meaning that it will have to check a few more additional characters here and there to find a given word. The exact number depends on the structure of the Trie, but it is guaranteed that the left and right children will be traversed and several nodes checked and skipped, which adds up to more operations overall.

**Reflection 4**: Building the Trie and searching all input strings are different workloads, even though both process the same collection of strings. Compare their measured operation counts and explain which one is higher and why. 

Building the Trie is always going to result in more operations because the Trie must insert and assign values to new nodes. So, whereas searching all input strings only requires lookups and checks for end\_of\_word, inserting also requires inserting nodes where they are needed. These additional operations are what make the building operations higher than search. 

 4. Space and Time Complexity Comparison

The standard Trie and BST-based Trie have a tradeoff between time and space. In both Case 1 and Case 2, the standard Trie generally required fewer operations for building and searching. For the standard Trie, finding the next character is faster because each node has an array with a position for every possible letter. This means searching for a word mainly depends on the number of characters in the word, since each character can be accessed directly. For example, in Case 1 with `words_alpha.txt`, the standard Trie took 5,920,416 operations to build, while the BST-based Trie took 74,113,215 operations. In Case 2, searching all of the words took 3,864,798 operations for the standard Trie compared to 52,966,212 operations for the BST-based Trie.

The downside of the standard Trie is its space usage. Every node reserves space for 26 child pointers even when most of them are not being used. The BST-based Trie only stores the links that it needs, so it uses much less space. In Case 1 with `words_alpha.txt`, the standard Trie used 26,723,034 pointer units while the BST-based Trie only used 3,083,427 pointer units. This same difference could also be seen with the smaller files. Therefore, even though both structures grow based on the number of characters and nodes stored, the standard Trie has a much larger space cost because of the 26 pointers stored at every node.

The BST-based Trie saves space, but it usually requires more comparisons to find a character. Instead of going directly to an array position, it may have to move through different nodes before finding the correct character. This explains why its build and normal search operation counts were higher. In Case 1, this could be seen with searches such as `miser`, where the standard Trie required 5 operations while the BST-based Trie required 151 operations.

However, autocomplete showed an advantage of the BST-based Trie. When searching through all possible completions, the standard Trie may have to check all 26 child positions at each node, including positions that are empty. The BST-based Trie only follows the child links that actually exist. For example, in Case 1, the `s` query in `words_alpha.txt` required 2,838,970 autocomplete operations in the standard Trie but only 420,645 operations in the BST-based Trie. This shows that even though the standard Trie was faster for directly searching a prefix, the BST-based Trie could require fewer operations when exploring a large autocomplete subtree.

The Case 2 results also showed that the standard Trie was faster when searching every word in the input file. This happened for all four files that were tested. For `test.txt`, the standard Trie used 139 search operations compared to 372 for the BST-based Trie. For `test2.txt`, it used 403 compared to 1,199. For `tale-1.txt`, it used 5,612 compared to 20,408. The largest difference was with `words_alpha.txt`, where the standard Trie used 3,864,798 operations while the BST-based Trie used 52,966,212 operations.

Overall, the standard Trie favors faster direct searching at the cost of much more memory, while the BST-based Trie favors saving memory at the cost of additional comparisons during building and searching. The autocomplete results also show that neither structure is better in every situation. The standard Trie performed better for direct searches and searching all words, while the BST-based Trie used much less memory and could perform better when traversing autocomplete results. The better choice depends on whether faster direct lookups or lower space usage and more efficient traversal of existing children is more important.


5. Appendix: In this section, include the output of your program (copy-paste or screenshots) to support your answers in previous sections.

Case 1:
sgarcia@blue:~/cs415/CS_415_P3$ ./main tale-1.txt 1
Time taken to build the standard Trie is 9410 operations and space occupied by it is 49374 pointer units
Time taken to build the BST based Trie is 32705 operations and space occupied by it is 5697 pointer units

Enter search string:re
Time taken to search in the standard Trie is 2 operations
Auto-complete results using standard Trie are: received, recently, recognised, relate, removing, requisition, restalong, retinue, revelations, revolution
Time taken to find auto-complete results in the standard Trie is 1757 operations

Time taken to search in the BST based Trie is 20 operations
Auto-complete results using BST based Trie are: received, recently, recognised, relate, removing, requisition, restalong, retinue, revelations, revolution
Time taken to find auto-complete results in the BST based Trie is 277 operations


(To quit type '0') Enter search string: fr
Time taken to search in the standard Trie is 2 operations
Auto-complete results using standard Trie are: framework, france, from
Time taken to find auto-complete results in the standard Trie is 353 operations

Time taken to search in the BST based Trie is 13 operations
Auto-complete results using BST based Trie are: framework, france, from
Time taken to find auto-complete results in the BST based Trie is 62 operations


(To quit type '0') Enter search string: z
Time taken to search in the standard Trie is 1 operations
Auto-complete results using standard Trie are: 
Time taken to find auto-complete results in the standard Trie is 1 operations

Time taken to search in the BST based Trie is 12 operations
Auto-complete results using BST based Trie are: 
Time taken to find auto-complete results in the BST based Trie is 12 operations


(To quit type '0') Enter search string: s
Time taken to search in the standard Trie is 1 operations
Auto-complete results using standard Trie are: sack, saturday, sawn, scarcely, search, season, security, sentencing, set, settled, seven, seventyfive, she, sheltered, shield, short, shot, sight, silently, sister, sixpence, sixty, small, smoothness, snipped, snuffed, so, some, southcott, spending, spirits, spiritual, spring, st, stand, state, stir, stopped, strange, stringing, subjects, sublime, such, sufferer, superlative, supernaturally, suspicion, swallowing
Time taken to find auto-complete results in the standard Trie is 5995 operations

Time taken to search in the BST based Trie is 14 operations
Auto-complete results using BST based Trie are: sack, saturday, sawn, scarcely, search, season, security, sentencing, set, settled, seven, seventyfive, she, sheltered, shield, short, shot, sight, silently, sister, sixpence, sixty, small, smoothness, snipped, snuffed, so, some, southcott, spending, spirits, spiritual, spring, st, stand, state, stir, stopped, strange, stringing, subjects, sublime, such, sufferer, superlative, supernaturally, suspicion, swallowing
Time taken to find auto-complete results in the BST based Trie is 899 operations


(To quit type '0') Enter search string: ba
Time taken to search in the standard Trie is 2 operations
Auto-complete results using standard Trie are: ball, battles
Time taken to find auto-complete results in the standard Trie is 218 operations

Time taken to search in the BST based Trie is 9 operations
Auto-complete results using BST based Trie are: ball, battles
Time taken to find auto-complete results in the BST based Trie is 38 operations


(To quit type '0') Enter search string: ever
Time taken to search in the standard Trie is 4 operations
Auto-complete results using standard Trie are: ever, every, everything
Time taken to find auto-complete results in the standard Trie is 193 operations

Time taken to search in the BST based Trie is 17 operations
Auto-complete results using BST based Trie are: ever, every, everything
Time taken to find auto-complete results in the BST based Trie is 42 operations


(To quit type '0') Enter search string: 0
Done!

sgarcia@blue:~/cs415/CS_415_P3$ ./main test.txt 1
Time taken to build the standard Trie is 283 operations and space occupied by it is 1872 pointer units
Time taken to build the BST based Trie is 643 operations and space occupied by it is 216 pointer units

Enter search string:0
Done!

sgarcia@blue:~/cs415/CS_415_P3$ ./main test2.txt 1
Time taken to build the standard Trie is 759 operations and space occupied by it is 4628 pointer units
Time taken to build the BST based Trie is 2012 operations and space occupied by it is 534 pointer units

Enter search string:0
Done!


sgarcia@blue:~/cs415/CS_415_P3$ ./main words_alpha.txt 1
Time taken to build the standard Trie is 5920416 operations and space occupied by it is 26723034 pointer units
Time taken to build the BST based Trie is 74113215 operations and space occupied by it is 3083427 pointer units

Enter search string:abac
Time taken to search in the standard Trie is 4 operations
Auto-complete results using standard Trie are: abac, abaca, abacas, abacate, abacaxi, abacay, abaci, abacinate, abacination, abacisci, abaciscus, abacist, aback, abacli, abacot, abacterial, abactinal, abactinally, abaction, abactor, abaculi, abaculus, abacus, abacuses
Time taken to find auto-complete results in the standard Trie is 1381 operations

Time taken to search in the BST based Trie is 13 operations
Auto-complete results using BST based Trie are: abac, abaca, abacas, abacate, abacaxi, abacay, abaci, abacinate, abacination, abacisci, abaciscus, abacist, aback, abacli, abacot, abacterial, abactinal, abactinally, abaction, abactor, abaculi, abaculus, abacus, abacuses
Time taken to find auto-complete results in the BST based Trie is 214 operations


(To quit type '0') Enter search string: miser
Time taken to search in the standard Trie is 5 operations
Auto-complete results using standard Trie are: miser, miserabilia, miserabilism, miserabilist, miserabilistic, miserability, miserable, miserableness, miserably, miseration, miserdom, misere, miserected, miserere, misereres, miserhood, misericord, misericorde, misericordia, miseries, miserism, miserliness, miserly, misers, misery
Time taken to find auto-complete results in the standard Trie is 1652 operations

Time taken to search in the BST based Trie is 151 operations
Auto-complete results using BST based Trie are: miser, miserabilia, miserabilism, miserabilist, miserabilistic, miserability, miserable, miserableness, miserably, miseration, miserdom, misere, miserected, miserere, misereres, miserhood, misericord, misericorde, misericordia, miseries, miserism, miserliness, miserly, misers, misery
Time taken to find auto-complete results in the BST based Trie is 392 operations


(To quit type '0') Enter search string: zz
Time taken to search in the standard Trie is 2 operations
Auto-complete results using standard Trie are: 
Time taken to find auto-complete results in the standard Trie is 2 operations

Time taken to search in the BST based Trie is 49 operations
Auto-complete results using BST based Trie are: 
Time taken to find auto-complete results in the BST based Trie is 49 operations


(To quit type '0') Enter search string: s
Time taken to build the standard Trie is 5920416 operations and space occupied by it is 26723034 pointer units
Time taken to build the BST based Trie is 74113215 operations and space occupied by it is 3083427 pointer units

Enter search string:Time taken to search in the standard Trie is 1 operations
Time taken to find auto-complete results in the standard Trie is 2838970 operations

Time taken to search in the BST based Trie is 60 operations
Time taken to find auto-complete results in the BST based Trie is 420645 operations


(To quit type '0') Enter search string: Done!

(To quit type '0') Enter search string: xyr
Time taken to search in the standard Trie is 3 operations
Auto-complete results using standard Trie are: xyrichthys, xyrid, xyridaceae, xyridaceous, xyridales, xyris
Time taken to find auto-complete results in the standard Trie is 570 operations

Time taken to search in the BST based Trie is 98 operations
Auto-complete results using BST based Trie are: xyrichthys, xyrid, xyridaceae, xyridaceous, xyridales, xyris
Time taken to find auto-complete results in the BST based Trie is 179 operations


(To quit type '0') Enter search string: please
Time taken to search in the standard Trie is 6 operations
Auto-complete results using standard Trie are: please, pleased, pleasedly, pleasedness, pleaseman, pleasemen, pleaser, pleasers, pleases
Time taken to find auto-complete results in the standard Trie is 438 operations

Time taken to search in the BST based Trie is 106 operations
Auto-complete results using BST based Trie are: please, pleased, pleasedly, pleasedness, pleaseman, pleasemen, pleaser, pleasers, pleases
Time taken to find auto-complete results in the BST based Trie is 167 operations


(To quit type '0') Enter search string: 0
Done!

Case 2:

sgarcia@blue:~/cs415/CS_415_P3$ ./main test.txt 2
Time taken to build the standard Trie is 283 operations and space occupied by it is 1872 pointer units
Time taken to build the BST based Trie is 643 operations and space occupied by it is 216 pointer units

Total words searched: 26
Words found in standard Trie: 26
Time taken to search all strings in the standard Trie is 139 operations
Words found in BST based Trie: 26
Time taken to search all strings in the BST based Trie is 372 operations
Done!

sgarcia@blue:~/cs415/CS_415_P3$ ./main test2.txt 2
Time taken to build the standard Trie is 759 operations and space occupied by it is 4628 pointer units
Time taken to build the BST based Trie is 2012 operations and space occupied by it is 534 pointer units

Total words searched: 69
Words found in standard Trie: 69
Time taken to search all strings in the standard Trie is 403 operations
Words found in BST based Trie: 69
Time taken to search all strings in the BST based Trie is 1199 operations
Done!

sgarcia@blue:~/cs415/CS_415_P3$ ./main tale-1.txt 2
Time taken to build the standard Trie is 9410 operations and space occupied by it is 49374 pointer units
Time taken to build the BST based Trie is 32705 operations and space occupied by it is 5697 pointer units

Total words searched: 1002
Words found in standard Trie: 1002
Time taken to search all strings in the standard Trie is 5612 operations
Words found in BST based Trie: 1002
Time taken to search all strings in the BST based Trie is 20408 operations
Done!

sgarcia@blue:~/cs415/CS_415_P3$ ./main words_alpha.txt 2
Time taken to build the standard Trie is 5920416 operations and space occupied by it is 26723034 pointer units
Time taken to build the BST based Trie is 74113215 operations and space occupied by it is 3083427 pointer units

Total words searched: 370103
Words found in standard Trie: 370103
Time taken to search all strings in the standard Trie is 3864798 operations
Words found in BST based Trie: 370103
Time taken to search all strings in the BST based Trie is 52966212 operations
Done!
