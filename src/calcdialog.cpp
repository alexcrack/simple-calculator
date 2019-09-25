#include "calcdialog.h"
#include "ui_calcdialog.h"

CalcDialog::CalcDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CalcDialog)
{
    ui->setupUi(this);

    setLcdFont();
    setupButtons();

    alu = new Alu();
    alu->setScreen(ui->lineEdit);
}

CalcDialog::~CalcDialog()
{
    delete ui;
}

void CalcDialog::setLcdFont()
{
    int id = QFontDatabase::addApplicationFont(":/fonts/fonts/digital-7 (mono italic).ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    QFont font(family, 42);

    ui->lineEdit->setFont(font);
    ui->lineEdit->setMinimumHeight(64);
    ui->lineEdit->setTextMargins(6, 0, 6, 6);
}

void CalcDialog::setupButtons()
{
    // Setup digits buttons
    int digit = 0;
    addDigitButton(digit++, 4, 0);
    for (int row = 3; row >= 1; --row) {
        for (int col = 0; col <= 2; col++) {
            addDigitButton(digit++, row, col);
        }
    }

    // Setup operations buttons
    addOperationButton(ui->btnPlus, Alu::Op::Plus);
    addOperationButton(ui->btnMinus, Alu::Op::Minus);
    addOperationButton(ui->btnMultiply, Alu::Op::Multiply);
    addOperationButton(ui->btnDivision, Alu::Op::Divide);
    addOperationButton(ui->btnPercent, Alu::Op::Percent);
    addOperationButton(ui->btnEqual, Alu::Op::Equal);

    // Service buttons
    connect(ui->btnC, &QPushButton::clicked, this, [=]() {
        alu->clean();
    });
    connect(ui->btnAC, &QPushButton::clicked, this, [=]() {
        alu->cleanAll();
    });

    connect(ui->btnPoint, &QPushButton::clicked, this, [=]() {
        alu->setPartial();
    });

    connect(ui->btnPlusMinus, &QPushButton::clicked, this, [=]() {
        alu->changeSign();
    });

    connect(ui->btnBracketOpen, &QPushButton::clicked, this, [=]() {
        alu->openBracket();
    });

    connect(ui->btnBracketClose, &QPushButton::clicked, this, [=]() {
        alu->closeBracket();
    });
}

void CalcDialog::addDigitButton(int digit, int row, int col)
{
    QPushButton *btn = new QPushButton(this);
    btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    btn->setText(QString("%1").arg(digit));

    ui->gridLayout->addWidget(btn, row, col, 1, digit == 0 ? 2 : 1);

    btn->setShortcutEnabled(true);
    btn->setShortcut(QString::number(digit));

    connect(btn, &QPushButton::clicked, this, [=]() {
        alu->addDigit(digit);
    });
}

void CalcDialog::addOperationButton(QPushButton *btn, Alu::Op operation)
{
    connect(btn, &QPushButton::clicked, this, [=]() {
        alu->addOperation(operation);
    });
}
