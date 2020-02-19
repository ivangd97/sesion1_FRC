#ifndef CONTROLFRAME_H
#define CONTROLFRAME_H


class ControlFrame
{
protected:
    unsigned char S;
    unsigned char D;
    unsigned char C;
    unsigned char NT;

public:
    ControlFrame();
    ControlFrame(int value);
    //void setAtribute(char value, int attribute);
   // char getAtribute(int attribute);

    void setC(unsigned char value);
    void setD(unsigned char value);
    void setS(unsigned char value);
    void setNT(unsigned char value);


    unsigned char getC();
    unsigned char getD();
    unsigned char getS();
    unsigned char getNT();


};

#endif // CONTROLFRAME_H
