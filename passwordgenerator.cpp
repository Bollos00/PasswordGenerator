#include "passwordgenerator.h"
#include "ui_passwordgenerator.h"

#define qRand QRandomGenerator::global()

PasswordGenerator::PasswordGenerator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PasswordGenerator)
{
    ui->setupUi(this);

    {
        QPalette darkPalette;
        darkPalette.setColor (QPalette::BrightText,      Qt::red);
        darkPalette.setColor (QPalette::WindowText,      Qt::white);
        darkPalette.setColor (QPalette::ToolTipBase,     Qt::white);
        darkPalette.setColor (QPalette::ToolTipText,     Qt::white);
        darkPalette.setColor (QPalette::Text,            Qt::white);
        darkPalette.setColor (QPalette::ButtonText,      Qt::white);
        darkPalette.setColor (QPalette::HighlightedText, Qt::black);
        darkPalette.setColor (QPalette::Window,          QColor (53, 53, 53));
        darkPalette.setColor (QPalette::Base,            QColor (25, 25, 25));
        darkPalette.setColor (QPalette::AlternateBase,   QColor (53, 53, 53));
        darkPalette.setColor (QPalette::Button,          QColor (53, 53, 53));
        darkPalette.setColor (QPalette::Link,            QColor (42, 130, 218));
        darkPalette.setColor (QPalette::Highlight,       QColor (42, 130, 218));

        qApp->setPalette(darkPalette);
    }

    connect(ui->QPB_generatePassword, &QPushButton::clicked,
            this, &PasswordGenerator::SLOT_generatePasswords);

    connect(ui->QPB_clear, &QPushButton::clicked,
            this, &PasswordGenerator::SLOT_clear);

    ui->QPTE_listOfPasswords->setLineWrapMode(QPlainTextEdit::NoWrap);
    ui->QPTE_listOfPasswords->setWordWrapMode(QTextOption::NoWrap);
}

PasswordGenerator::~PasswordGenerator()
{
    delete ui;
}

void PasswordGenerator::SLOT_generatePasswords()
{
    const uchar
            minimum = ui->QSB_minimum->value(),
            maximum = ui->QSB_maximum->value();


    if(minimum > maximum){
        ui->QSB_maximum->setValue(minimum);
        ui->QPTE_listOfPasswords->setPlainText("Error: minimum length bigger "
                                               "than maximum length");
        return;
    }

    QVector<char> charAlowed = QVector<char>();

    if(ui->QCB_smallLetters->isChecked())
        charAlowed.append(smallLetters.toVector());

    if(ui->QCB_capitalLetters->isChecked())
        charAlowed.append(capitalLetters.toVector());

    if(ui->QCB_numbers->isChecked())
        charAlowed.append(numbers.toVector());

    if(ui->QCB_specialCharacters->isChecked())
        charAlowed.append(specialCharacters.toVector());


    if(charAlowed.isEmpty())
    {
        ui->QPTE_listOfPasswords->setPlainText("Error: Select at Least one"
                                               "type of character");

        return;
    }

    ui->QPTE_listOfPasswords->clear();

    generatePasswords(minimum, maximum, ui->QSB_numberOfPasswords->value(), charAlowed);

}

void PasswordGenerator::SLOT_clear()
{
    ui->QPTE_listOfPasswords->clear();
}

void PasswordGenerator::generatePasswords(const uchar& minimum,
                                          const uchar& maximum,
                                          const uchar& numberOfPasswords,
                                          const QVector<char>& charAlowed)
{
    const uchar numberOfCharacters = charAlowed.size();

    for (uchar i=0; i<numberOfPasswords; i++)
    {
        uchar length = qRand->bounded(minimum, (maximum+1));

        QString QS_password = "";
        QS_password.reserve(length);

        for(uchar j=0; j<length; j++)
        {
            QS_password.append(
                        charAlowed.at(
                            qRand->bounded(0, numberOfCharacters)
                            )
                        );
        }
        ui->QPTE_listOfPasswords->appendPlainText(QS_password);
        ui->QPTE_listOfPasswords->appendPlainText("\n");
    }
}
