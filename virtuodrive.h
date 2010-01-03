#ifndef VIRTUODRIVE_H
#define VIRTUODRIVE_H


class virtuodrive
{
    public:
        virtuodrive();
        virtual ~virtuodrive();
        void SetGain(double gain);
        void SetAmount(double amount);
        float forSample(float in);
        double forSample(double in);
    private:
        double m_gain;
        double m_amount;
        double k;
};

#endif // VIRTUODRIVE_H
