#include "CombatAleatoire.h"
#include "../util/benrandom.h"


CombatAleatoire::CombatAleatoire(): m_minStep(1*33),m_maxStep(10*33)
{

    //ctor
}

CombatAleatoire::CombatAleatoire(int Min, int Max): m_minStep(Min),m_maxStep(Max),m_currentStep(0)
{

    //ctor
}

CombatAleatoire::~CombatAleatoire()
{
    //dtor
}

void CombatAleatoire::reset()
{
    m_currentStep=0;
    m_butStep=random(m_maxStep,m_minStep);
}

bool CombatAleatoire::testCombat() const
{
    if (m_currentStep>=m_butStep){
            return true;
        }else{
            return false;
        }
}

void CombatAleatoire::incrStep()
{
    m_currentStep++;
    if (m_currentStep>m_maxStep)m_currentStep=0;
}
