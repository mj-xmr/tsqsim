#ifndef MINMAX_H
#define MINMAX_H

struct MinMax
{
    MinMax();
    MinMax(float a, float b);
    virtual ~MinMax();
    bool IsZero() const;
    float Diff() const;

    float min, max;
};

#endif // MINMAX_H
