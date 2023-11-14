# Context free grammar parser
Note: This was a challenge at one of my university courses (formal languages and compilators)

# How does it work
So, first of all you have to supply the Grammar class with 3 strings representing grammar's nonterminals, terminals and specific productions (all comma separated).
Starting symbol has to be first in nonterminals string.
Productions starts with the nonterminal then an arrow (->) and production separated by vertical line (|).
Resulting object can provide vectorial, list and table representation of given grammar.

## Vectorial representation
In this form, grammar is represented as a vector starting with the start symbol and it's production, next production of the same nonterminal is maked by a vetical line (|) while the begginning of the next nonterminal productions is delimited by hash character (#). The end of representation is marked by dollar sign ($)

## List representation
**To be written**

## Table representation
**To be written**