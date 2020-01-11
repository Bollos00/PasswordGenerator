#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QMainWindow>
#include <QList>
#include <QDebug>
#include <QString>
#include <QRandomGenerator>
#include <QElapsedTimer>
#include <QApplication>

#include "stdlib.h"



QT_BEGIN_NAMESPACE
namespace Ui { class PasswordGenerator; }
QT_END_NAMESPACE

struct number{

    int power = 0;

    double value = 0;
};


class PasswordGenerator : public QMainWindow
{
    Q_OBJECT


public:
    PasswordGenerator(QWidget *parent = nullptr);
    ~PasswordGenerator();

    void v_generatePasswords(int minimum, int maximum, int numberOfPasswords);

    void v_findOutPassword(int minimum, int maximum);

    void v_generateStatics(int minimum, int maximum);

private slots:
    void SLOT_generatePasswords();
    void SLOT_clear();

    void SLOT_start();
    void SLOT_stop();

    void SLOT_createStatics();

private:
    Ui::PasswordGenerator *ui;
    const QList<char> QLi_c_smallLetters = {'a',  'b',  'c',  'd',  'e',
                                             'f',  'g',  'h',  'i',  'j',
                                             'k',  'l',  'm',  'n',  'o',
                                             'p',  'q',  'r',  's',  't',
                                             'u',  'v',  'w',  'x',  'y',
                                             'z'};

    const QList<char> QLi_c_capitalLetters = {'A',  'B',  'C',  'D',  'E',
    'F',  'G',  'H',  'I',  'J',
    'K',  'L',  'M',  'N',  'O',
    'P',  'Q',  'R',  'S',  'T',
    'U',  'V',  'W',  'X',  'Y',
    'Z'};

    const QList<char> QLi_c_numbers = {'0',  '1',  '2',  '3',  '4',
                                       '5', '6',  '7',  '8',  '9'};

    const QList<char> QLi_c_specialCharacters = {'!',  '\"',  '#',  '$',   '%',
                                                 '&',  '\'',  '(',  ')',   '*',
                                                 '+',  ',',   '-',  '.',   '/',
                                                 ':',  ';',   '<',  '=',   '>',
                                                 '?',  '@',   '[',  '\\',  ']',
                                                 '^',  '_',   '`',  '{',   '|',
                                                 '}',  '~',   ' '};

    QList<char> QLi_c_charsOfPassword;

    QElapsedTimer QET_control;

    QString QS_password;

    QList<QString> QLi_QS_passwords_interface_2;


};
#endif // PASSWORDGENERATOR_H
