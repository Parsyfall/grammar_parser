#ifndef GRAMMAR_H
#define GRAMMAR_H
#include <string>
#include <vector>
#include <map>

class Grammar {
    struct Node {
        int index = 0;
        std::string a = "";
        Node* b = nullptr;
        Node* c = nullptr;
        Node* d = nullptr;

        Node(int index, std::string a) : index(index), a(a){};
    };

    std::vector<std::string> N, sigma; // N and Sigma are vectors of elements
    std::string S;                     // Starting element
    std::multimap<std::string, std::string> Prod; // Productions

    // Crutch to be abel to point somehow to -1 (algorithm requirement)
    Node minusOne = Node(-1, "-1");

  public:
    // Comma separated terminals, nonterminals and production rules
    Grammar(std::string nonterm, std::string term, std::string prod);

    /*
    Prints to console table form of current Grammar
    */
    void tableRepresentation();
    /*
    Returns a multimap where:
        keys - terminals
        values - vector of nodes representing key production
        each node contain an index, string 'a' (nonterminal/terminal), and 3
    node pointers - 'b', 'c', 'd'
    */
    std::multimap<std::string, std::vector<Node>> getListForm() noexcept;
    /*
    Returns a vector of 3 elements:
        1st -  nonterminals
        2nd - terminals
        3rd - productions
    */
    std::vector<std::string> getVectorialForm() noexcept;

  private:
    // Utility functions

    void vectorialRepresentation();
    void listRepresantation();
    std::vector<std::string> split(std::string, char delimiter);
    std::multimap<std::string, std::string>
    make_production(std::vector<std::string> prod);

    // Representations cache

    std::vector<std::string> vecForm;
    std::multimap<std::string, std::vector<Node>> listForm;
};

#endif