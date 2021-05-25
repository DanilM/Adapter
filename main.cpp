#include <QCoreApplication>
#include <cmath>
#include <QDebug>


class Target
{
public:
    virtual ~Target() = default;
    virtual int Request() const
    {
        return 5;
    }
};

class Adaptee
{
public:
    int SpecificRequest() const
    {
        return 101;
    }
};

class Adapter: public Target, public Adaptee
{
public:
    int translateBinyriToDecimal(int binary) const
    {
        int leftBorder = 10;
        int rightBorder = 1;
        int power = 0;
        int decimal = 0;
        while(rightBorder < binary)
        {
            decimal += ((binary % leftBorder)/rightBorder) * pow(2, power);
            rightBorder*=10;
            leftBorder*=10;
            ++power;
        }
        return decimal;
    }

    Adapter(){};
    int Request() const override
    {
        int toTranslateNumber = SpecificRequest();
        return translateBinyriToDecimal(toTranslateNumber);
    }
};

void ClientCode(Target* target)
{
    qDebug() << target->Request();
}


int main()
{
    Target *target = new Target;
    ClientCode(target);

    Adaptee *adaptee = new Adaptee;

    qDebug() << adaptee->SpecificRequest();

    Adapter* adapter = new Adapter;
    ClientCode(adapter);

    delete target;
    delete adaptee;
    delete adapter;

    return 0;
}
