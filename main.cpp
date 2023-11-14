#include "Grammar.h"

int main() {
    Grammar g("R,X,S,T", "a,b,e", "R->XRX|S,S->aTb|bTa,T->XTX|X|e,X->a|b");
    g.tableRepresentation();
}