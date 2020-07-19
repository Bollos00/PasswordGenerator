#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QMainWindow>
#include <QList>
#include <QDebug>
#include <QString>
#include <QRandomGenerator>
#include <QElapsedTimer>
#include <QApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class PasswordGenerator; }
QT_END_NAMESPACE

class PasswordGenerator : public QMainWindow
{
    Q_OBJECT


public:
    PasswordGenerator(QWidget *parent = nullptr);
    ~PasswordGenerator();

private:

    void generatePasswords(const uchar& minimum,
                           const uchar& maximum,
                           const uchar& numberOfPasswords,
                           const QVector<char>& charAlowed);

    Ui::PasswordGenerator *ui;

    const QList<char> smallLetters =
    {'a',  'b',  'c',  'd',  'e',
     'f',  'g',  'h',  'i',  'j',
     'k',  'l',  'm',  'n',  'o',
     'p',  'q',  'r',  's',  't',
     'u',  'v',  'w',  'x',  'y',
     'z'};

    const QList<char> capitalLetters =
    {'A',  'B',  'C',  'D',  'E',
     'F',  'G',  'H',  'I',  'J',
     'K',  'L',  'M',  'N',  'O',
     'P',  'Q',  'R',  'S',  'T',
     'U',  'V',  'W',  'X',  'Y',
     'Z'};

    const QList<char> numbers =
    {'0',  '1',  '2',  '3',  '4',
     '5', '6',  '7',  '8',  '9'};

    const QList<char> specialCharacters =
    {'!',  '\"',  '#',  '$',   '%',
     '&',  '\'',  '(',  ')',   '*',
     '+',  ',',   '-',  '.',   '/',
     ':',  ';',   '<',  '=',   '>',
     '?',  '@',   '[',  '\\',  ']',
     '^',  '_',   '`',  '{',   '|',
     '}',  '~',   ' '};

private slots:
    void SLOT_generatePasswords();
    void SLOT_clear();
};
#endif // PASSWORDGENERATOR_H
