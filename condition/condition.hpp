#ifndef CONDITION_HPP
#define CONDITION_HPP

class condition_t
{
public:
    condition_t();
    virtual ~condition_t();

    virtual bool evaluate(bool &error);
};

#endif // CONDITION_HPP
