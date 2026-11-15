1. Trie Building Results

Include a summary of your results in the table below. In support of your answers, include screenshot of the output of your program in the appendix section (at the end of the report).

| Input file |  | Number of words | Standard Trie Build \#operations | BST-based Trie  Build \#operations | Standard Trie space | BST-based Trie space |
| :---- | :---: | :---: | ----- | ----- | ----- | :---: |
| **test.txt** | **26** |  | **283** | **643** | **1872** | **216** |
| **test2.txt** | **69** |  | **759** | **2012** | **4628** | **534** |
| **tale.txt** | **1002** |  | **9410** | **32705** | **49374** | **5697** |
| **words\_ alpha.txt** | **370103** |  | **5920416** | **74113215** | **26723034** | **3083427** |

**Reflection 1**: Explain why the two Tries require different amount of time to be built, and use different amounts of space. Were the observed results consistent with the theoretical expectations?

The two tries require different amounts of time and space to be built because of the nature of their lookups. When the standard Trie is being built, it simply goes from the root and looks up the index of the respective letter being inserted (0-25) or simply traverses to that same index if it's already there. That also accounts for its larger space cost, as each node must have an array of 26 child pointers for each letter, regardless of whether the letter exists or not. On the other side, with a BST-based Trie, it only has the letters it needs, meaning a whole lot less space is being used. But that also means when looking up, more comparisons are being done, as the Trie may have to look through many letters just to find the spot where the given word should be inserted. The results above do align with the theoretical expectations.

2. Autocomplete Results

Include a summary of the autocomplete results below. In support of your answers, include screenshot of the output of your program in the appendix section (at the end of the report).

For the files tale.txt and words-alpha.txt, fill the table for specific queries. In addition, find and list results for 

1. No-match query  
2. high-branching query (a prefix whose Trie node has many possible next characters, usually resulting in many auto-complete choices)  
3. low-branching query (a prefix with only a few possible continuations and a small auto-complete subtree)  
4. complete-word prefix (a complete word in the Trie that is also a prefix of one or more longer words).

| Query in file tale.txt | Number of results | \#operations Standard search  | \#operations BST-based search  | \#operations Standard auto-complete  | \#operations BST-based auto-complete  |
| :---- | ----- | ----- | ----- | ----- | ----- |
| re | **10** | **2** | **20** | **1757** | **277** |
| fr | **3** | **2** | **13** | **353** | **62** |
| No-match query (z) | **0** | **1** | **12** | **1** | **12** |
| High-branching query (s) | **48** | **1** | **14** | **5995** | **899** |
| Low-branching query (ba) | **2** | **2** | **9** | **218** | **38** |
| Complete-word prefix (ever) | **3** | **4** | **17** | **193** | **42** |
|   |  |  |  |  |  |
|  **Query** in file words-alpha.txt | **Number of results** | **\#operations Standard search**  | **\#operations BST-based search**  | **\#operations Standard auto-complete**  | **\#operations BST-based auto-complete**  |
| abac | **24** | **4** | **13** | **1381** | **214** |
| miser | **25** | **5** | **151** | **1652** | **392** |
| No-match query (zz) | **0** | **2** | **49** | **2** | **49** |
| High-branching query (s) | **38764** | **1** | **60** | **2838970** | **420645** |
| Low-branching query (xyr) | **6** | **3** | **98** | **570** | **179** |
| Complete-word prefix (please) | **9** | **6** | **106** | **438** | **167** |

**Reflection 2**: Both Trie implementations should return exactly the same auto-complete strings for every query. Explain how the characteristics of each query \- such as its length, branching factor, and whether it is itself a complete word \- affected the operation counts and auto-complete performance of the standard Trie and the BST-based Trie. Were the observed results consistent with the theoretical expectations? Did one implementation consistently outperform the other for auto-complete? If not, explain why.

For each query, its characteristics would influence the auto-complete in slightly different ways. The length of the query itself didn’t have much influence compared to other aspects, only really being impactful when there was a no-match query, as the operations for standard auto-complete would be dictated by its length. Much more impactful is branching, being the main factor influencing the number of operations done. Because of the nature of a standard Trie, it’d need to search each and every one of its 26 children to ensure there isn’t anything there, whereas a BST-based Trie only has 3 children at any given node, which, while it may still require many comparisons, not nearly as many since it contains only the letters needed. Completion of the word also followed a similar pattern, the only real difference being the initial search of the query being faster on a standard Trie. Regardless, it can be seen that for auto-complete operations, the BST-based Trie consistently outperformed the standard Trie, likely because of the reason mentioned prior, where from any given query, we’d only need to check the branching paths of 3 children nodes at worst case to find words for auto-completion, whereas a standard Trie needs to check 26\. The only case where this fact is different is when there is no matching query, which makes sense because a standard Trie can do one set of lookups and find nothing, but the BST-based Trie would need to go check its children to make sure the words aren’t hidden deep down.

3. Search-all Results

This section corresponds to results from **Case 2**. Include a summary of your results in the table below. In support of your answers, include screenshot of the output of your program in the appendix section (at the end of the report).

| Input file |  | Number of strings searched | Standard Trie Build \#operations | Standard Trie  Search-all \#operations | BST-based Trie  Build \#operations   | BST-based Trie  Search-all  \#operations  |
| :---- | :---: | :---- | ----- | ----- | ----- | ----- |
| **test.txt** | **26** |  | **283** | **139** | **643** | **372** |
| **test2.txt** | **69** |  | **759** | **403** | **2012** | **1199** |
| **tale.txt** | **1002** |  | **9410** | **5612** | **32705** | **20408** |
| **words\_ alpha.txt** | **370103** |  | **5920416** | **3864798** | **74113215** | **52966212** |

**Reflection 3**: For the same input file, which out of the standard Trie and the BST-based Trie required more operations to search every string? Explain the difference using the number of characters searched, the number of child comparisons or array lookups.

For every input file, the BST-based Trie required more operations to search every single string. This can easily be explained by the nature of lookups in each Trie. The standard trie only has to do a single operation for each letter and since each word we are looking for does exist, it will take as many characters in the word in operations for the standard Trie. However, a BST-based Trie will eventually have to look at branching children to find some characters, meaning that it will have to check a few more additional characters here and there to find a given word. The exact number depends on the structure of the Trie, but it is guaranteed that the left and right children will be traversed and several nodes checked and skipped, which adds up to more operations overall.

**Reflection 4**: Building the Trie and searching all input strings are different workloads, even though both process the same collection of strings. Compare their measured operation counts and explain which one is higher and why. 

Building the Trie is always going to result in more operations because the Trie must insert and assign values to new nodes. So, whereas searching all input strings only requires lookups and checks for end\_of\_word, inserting also requires inserting nodes where they are needed. These additional operations are what make the building operations higher than search. 

4. Appendix

In this section, include the output of your program (copy-paste or screenshots) to support your answers in previous sections.