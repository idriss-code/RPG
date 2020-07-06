#include "Capa.h"
#include <cstdio>

Capa::Capa():m_cible(UNIQUE), m_groupe(MONSTRE),m_mana(0)
{

}

Capa::~Capa()
{

}
void Capa::setName(const char*n)
{
    sprintf(m_name,n);
}
