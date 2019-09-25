#ifndef ALU_H
#define ALU_H

#include <QString>
#include <QLineEdit>
#include <QThread>
#include <QtMath>

class Alu
{
public:
    enum Op {
        NoOp,
        Plus,
        Minus,
        Divide,
        Multiply,
        Percent,
        Equal
    };

    struct Stack {
        double accumulator;
        double operand;
        Op operation;

        explicit Stack() : accumulator(0), operand(0), operation(Op::NoOp) {}
        Stack operator =(const Stack &stack) {
            accumulator = stack.accumulator;
            operand = stack.accumulator;
            operation = stack.operation;

            return *this;
        }
    };

    Alu();
    ~Alu();

    void setScreen(QLineEdit *lcdScreen);

    void addDigit(int digit);
    void addOperation(Op operation);


public slots:
    void clean();
    void cleanAll();
    void setPartial();
    void changeSign();
    void openBracket();
    void closeBracket();

private:
    QLineEdit *lcd;

    double memory;
    double accumulator;
    double operand;
    Op currentOperation;
    bool waitOperand = true;
    bool isPartial = false;

    QVector<Stack> bracketsStack;

    QString screenBuffer;

    void updateScreen();
    void calculate();
    void calculatePercent();

};

#endif // ALU_H
