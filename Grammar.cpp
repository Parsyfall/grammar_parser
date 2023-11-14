#include "Grammar.h"
#include <algorithm>
#include <iostream>

void Grammar::vectorialRepresentation() {
    std::string term, nonterm, prod;

    // Assemble  nonterminals
    for (auto it = N.begin(); it != N.end(); ++it) {
        term.append(*it);
    }
    term.append("$");
    vecForm.push_back(term);

    // Assemble  terminals
    for (auto it = sigma.begin(); it != sigma.end(); ++it) {
        nonterm.append(*it);
    }
    nonterm.append("$");
    vecForm.push_back(nonterm);

    // Assemble  productions
    std::string last;
    for (auto it = Prod.begin(); it != Prod.end(); ++it) {
        // Get the nonterminal of the production
        if (it->first != last) {
            prod.append(it->first);
        }
        // Append right-hand
        prod.append(it->second);

        // Mark the end of curent production
        if (std::next(it, 1) != Prod.end() &&
            it->first != std::next(it, 1)->first) {
            prod.append("#");
        } else {
            prod.append("|");
        }
        last = it->first;
    }
    prod.append("#$");
    vecForm.push_back(prod);
}

void Grammar::tableRepresentation() {
    if (listForm.empty()) {
        listRepresantation();
    }

    std::string line = "\n|-----+-----+-----+-----+-----|\n";
    std::string sep2 = "  |  ";
    std::string sep1 = " |  ";
    std::cout << "      |  a  |  b  |  c  |  d  |";
    for (auto it = listForm.begin(); it != listForm.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            std::cout << line;
            std::cout << "|  " << it2->index << (it2->index > 9 ? sep1 : sep2);
            std::cout << it2->a << sep2;
            if (it2->b == nullptr) {
                std::cout << 0 << sep2;
            } else {
                std::cout << it2->b->index << (it2->b->index > 9 ? sep1 : sep2);
            }
            if (it2->c == nullptr) {
                std::cout << 0 << sep2;
            } else {
                std::cout << it2->c->index
                          << (it2->c->index > 9 || it2->c->index == -1 ? sep1
                                                                       : sep2);
            }
            if (it2->d == nullptr) {
                std::cout << 0 << sep2;
            } else {
                std::cout << it2->d->index << (it2->d->index > 9 ? sep1 : sep2);
            }
        }
    }
    std::cout << "\n|" << std::string(29, '-') << "|\n"
              << "\n\n\n";
}

void Grammar::listRepresantation() {

    // std::multimap<std::string, std::vector<Node>> listForm;
    std::vector<Node> cell;
    int _index = 1;

    // Build representation
    for (auto it = Prod.begin(); it != Prod.end(); ++it) {
        for (size_t i = 0; i < it->second.length(); ++i, ++_index) {
            Node node(_index, std::string(1, it->second[i]));
            cell.push_back(node);
        }
        listForm.insert({it->first, cell});
        cell.clear();
    }

    /*--------------------- Completing cells ---------------------------*/

    for (auto it = listForm.begin(); it != listForm.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {

            /*--------------------- Complete 'b' ---------------------------*/

            // Check if 'a' is a terminal
            if (std::find(sigma.begin(), sigma.end(), it2->a) != sigma.end()) {
                it2->b = nullptr; // b  = 0
            } else {
                // 'a' is a nonterminal
                std::string token = it2->a;
                auto range = listForm.equal_range(token);
                // 'b' point to the first node of the first 'sublist' with the
                // same lhs 'a'
                it2->b = &range.first->second[0];
            }
        }
    }

    for (auto it = listForm.begin(); it != listForm.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            /*--------------------- Complete 'c' ---------------------------*/

            if (it2 == it->second.begin()) {
                if (std::next(it, 1) == listForm.end() ||
                    std::next(it, 1)->first != it->first) {
                    // Current node it's the last node of all 'sublists' with
                    // the same lhs member
                    it2->c = nullptr;
                } else {
                    // point to the next 'sublist' with the same lhs member
                    it2->c = &(std::next(it, 1)->second[0]);
                }

            } else {
                std::string token = it->first;
                auto range = listForm.equal_range(token);
                //  'c' = 0, if current production is the last rhs element of
                //  all production with the same lfs member
                if (std::next(range.second,-1) == it &&
                    it2 == std::next(it->second.end(), -1)) {
                    it2->c = nullptr;
                } else {
                    // Otherwise 'c' = -1
                    it2->c = &minusOne;
                }
            }
        }
    }

    for (auto it = listForm.begin(); it != listForm.end(); ++it) {
        /*--------------------- Complete 'd' ---------------------------*/

        for (size_t i = 0; i < it->second.size(); ++i) {
            // 'd' = 0, in case it's the last rhs element of a prodution
            if (&it->second[i] == &it->second[it->second.size() - 1]) {
                it->second[i].d = nullptr;
            } else {
                // Otherwise it points to the next element in 'sublist'
                it->second[i].d = &it->second[i + 1];
            }
        }
    }
}

/**
                term and nonterm - string of comma separated values
                prod - string of comma or/and pipe separated productions, where
right arrow '->' sparate nonterminals by it's production/s
**/
Grammar::Grammar(std::string nonterm, std::string term, std::string prod) {
    S = nonterm[0];
    sigma = split(term, ',');
    N = split(nonterm, ',');

    std::vector<std::string> temp_P = split(prod, ',');
    Prod = make_production(temp_P);
}

std::multimap<std::string, std::string>
Grammar::make_production(std::vector<std::string> prod) {
    std::multimap<std::string, std::string> result;
    std::vector<std::string> productions;

    // Iterate through unfinished production vector using iterator (because I
    // have learned about them so i'll use them)
    for (auto it = prod.begin(); it != prod.end(); ++it) {
        // Get position of first char in the right-hand part of productions
        size_t start = it->find("->") + 2;

        // split right-hand productions by pipe char '|'
        productions = split(it->substr(start), '|');
        for (auto it2 = productions.begin(); it2 != productions.end(); ++it2) {
            // Make pairs
            result.insert({it->substr(0, start - 2), *it2});
        }
    }

    return result;
}

std::vector<std::string> Grammar::split(std::string str, char delimiter) {
    // std::cout << "Spliting: " << str << "\n";
    // Start and end of the token substring
    int start = 0, end = str.find(delimiter);
    std::string token;
    std::vector<std::string> result;

    while (end != std::string::npos) {
        token = str.substr(start, end - start);
        // std::cout << "Token is: " << token << "\n";
        // start = end + 1;
        str.erase(str.begin(), str.begin() + end + 1);
        end = str.find(delimiter);
        result.push_back(token);
        start = 0;
    }

    // include in result vector the last substring which have no delimiter at
    // it's end or if there were no delimiter at all
    result.push_back(str);
    return result;
}

std::multimap<std::string, std::vector<Grammar::Node>>
Grammar::getListForm() noexcept {
    if (listForm.empty()) {
        listRepresantation();
    }
    return listForm;
}
std::vector<std::string> Grammar::getVectorialForm() noexcept {
    if (vecForm.empty()) {
        vectorialRepresentation();
    }
    return vecForm;
}