#ifndef COMBATALEATOIRE_H
#define COMBATALEATOIRE_H


class CombatAleatoire
{
    public:
        CombatAleatoire();
        CombatAleatoire(int Min, int Max);
        virtual ~CombatAleatoire();

        void incrStep();
        bool testCombat() const;
        void reset();


    protected:

    private:

        unsigned int m_butStep;
        unsigned int m_minStep;
        unsigned int m_maxStep;
        unsigned int m_currentStep;
};

#endif // COMBATALEATOIRE_H
