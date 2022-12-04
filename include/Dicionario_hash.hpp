#ifndef DICIONARIO_HASH
#define DICIONARIO_HASH
#include "Verbete.hpp"

class Dicionario_Hash{
    private:


    public:
        Dicionario_Hash();
        Dicionario_Hash * criaDic(int n);
        Dicionario_Hash(Dicionario_Hash *dic, Verbete * it);
};

#endif