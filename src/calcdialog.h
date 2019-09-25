#ifndef CALCDIALOG_H
#define CALCDIALOG_H

#include <QDialog>
#include <QFontDatabase>
#include "alu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CalcDialog; }
QT_END_NAMESPACE

class CalcDialog : public QDialog
{
    Q_OBJECT

public:
    CalcDialog(QWidget *parent = nullptr);
    ~CalcDialog();

private:
    Ui::CalcDialog *ui;
    Alu *alu;

    void setLcdFont();
    void setupButtons();
    void addDigitButton(int digit, int row, int col);

    void addOperationButton(QPushButton *btn, Alu::Op operation);
};
#endif // CALCDIALOG_H
