#include "alu.h"

Alu::Alu()
    : memory(0), accumulator(0), operand(0), currentOperation(Op::NoOp)
{

}

void Alu::setScreen(QLineEdit *lcdScreen)
{
    lcd = lcdScreen;
}

void Alu::clean()
{
    operand = 0;

    updateScreen();
}

void Alu::cleanAll()
{
    clean();
    accumulator = 0;
    memory = 0;
    currentOperation = Op::NoOp;
    isPartial = false;

    updateScreen();
}

void Alu::setPartial()
{
    isPartial = true;
}

void Alu::changeSign()
{
    operand = -operand;

    updateScreen();
}

void Alu::addDigit(int digit)
{
    if (waitOperand) {
        operand = isPartial ? (digit / 10) : digit;
        waitOperand = false;
    } else {
        operand = isPartial ? operand / 10 + digit / 10 : operand * 10 + digit;
    }

    updateScreen();
}

void Alu::addOperation(Op operation)
{
    if (operation == Op::Equal) {
        calculate();
        currentOperation = Op::NoOp;
        operand = accumulator;
        waitOperand = false;
    } else if (operation == Op::Percent) {
        calculatePercent();
        currentOperation = Op::NoOp;
        operand = accumulator;
        waitOperand = false;
    } else {
        currentOperation = operation;
        accumulator = operand;
        waitOperand = true;
    }

    updateScreen();
}

void Alu::openBracket()
{
    Stack stack;
    stack.accumulator = accumulator;
    stack.operand = operand;
    stack.operation = currentOperation;

    bracketsStack.push_front(stack);

    accumulator = 0;
    currentOperation = Op::NoOp;
    waitOperand = true;

    updateScreen();
}

void Alu::closeBracket()
{
    calculate();

    Stack stack(bracketsStack.takeFirst());

    operand = accumulator;
    accumulator = stack.operand;
    currentOperation = stack.operation;

    updateScreen();
}

void Alu::calculate()
{
    if (currentOperation == Op::NoOp) return;

    switch (currentOperation) {
    case Op::Plus: {
        accumulator = accumulator + operand;
        break;
    }
    case Op::Minus: {
        accumulator = accumulator - operand;
        break;
    }
    case Op::Multiply: {
        accumulator = accumulator * operand;
        break;
    }
    case Op::Divide: {
        accumulator = accumulator / operand;
    }
    }
}

void Alu::calculatePercent()
{
    if (currentOperation == Op::NoOp) return;

    switch (currentOperation) {
    case Op::Plus: {
        accumulator = accumulator + (accumulator * operand / 100);
        break;
    }
    case Op::Minus: {
        accumulator = accumulator - (accumulator * operand / 100);
        break;
    }
    case Op::Multiply: {
        accumulator = accumulator * (accumulator * operand / 100);
        break;
    }
    case Op::Divide: {
        accumulator = accumulator / (accumulator * operand / 100);
    }
    }
}

void Alu::updateScreen()
{
    lcd->setText(QString::number(operand, 'g', 12));
}

