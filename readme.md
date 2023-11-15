# Context free grammar parser

Note: This was a challenge at one of my university courses (formal languages and compilators)

# How does it work

So, first of all you have to supply the Grammar class with 3 strings representing grammar's nonterminals, terminals and specific productions (all comma separated).
Starting symbol has to be first in nonterminals string.
Productions starts with the nonterminal then an arrow (->) and production separated by vertical line (|).
Resulting object can provide vectorial, list and table representation of given grammar.

## Vectorial representation
In this form, grammar is represented as a vector starting with the start symbol and it's production, next production of the same nonterminal is maked by a vetical line (|) while the begginning of the next nonterminal productions is delimited by hash character (#). The end of representation is marked by dollar sign ($)

TODO: add example

## List representation

In order to represent a grammar as a linked list we'll use the following representation of a node:
```
+-----------+
|     a     |
+-----------+
| b | c | d |
+-----------+
```
The above figure will be used to represent each right member of each production. Letters have the following meaning:
1. **a** - terminal or nonterminal symbol of given grammar (only right members of each production)
2. **b** - pointer or integer
**b** :=
    if (a &isin; alphabet)
    then
        **b** := 0
    else (a &isin; nonterminals)
        **b** := pointer to the head of the first sublist with the same left hand member a
    endif

3. c - pointer or integer
Let **p** and **u** be two statements, thus:
**p : a** is the symbol of the second member in the current production
**u : a** is the last symbol of the second member of all production rules with the same left hand memeber, 
and let **n** - number of rules with the same left hand member,
and let **L** - pointer to the head of the next sublist associated to the production rule with the same lefthand memeber.
Then,
**c** :=
    if **p**
    then
        if **n = 1**
        then 
            **c := 0**
        else
            **c := L**
        endif
    else
        if **u**
        then
            **c := 0**
        else
            **c := -1**
        endif
    endif

4. **d** - pointer or integer
**d** :=
    if (**a** is the last symbol of the right hand member of any production)
    then
        **d := 0**
    else
        **d** is a pointer to the next node of the sublist
    endif


## Table representation

**To be written** FIXME: writte  the section
