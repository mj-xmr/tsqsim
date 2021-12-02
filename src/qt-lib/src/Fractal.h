#ifndef FRACTAL_H
#define FRACTAL_H


class Fractal
{
    public:
        Fractal(const QVector<double> & time, int idx, int numBars, double value, bool broken, bool touched);
        virtual ~Fractal();

        const QVector<double> & GetData() const;
        const QVector<double> & GetTime() const;
        bool IsBroken() const {return m_broken; };
        bool IsTouched() const {return m_touched; };
        double GetValue() const { return m_value; };


    protected:
    private:

        QVector<double> m_time;
        QVector<double> m_data;
        bool m_broken;
        bool m_touched;
        double m_value;

        static const int m_numBars;
};

#endif // FRACTAL_H
