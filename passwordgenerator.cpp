#include "passwordgenerator.h"
#include "ui_passwordgenerator.h"

PasswordGenerator::PasswordGenerator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PasswordGenerator)
{
    ui->setupUi(this);


    connect(ui->QPB_generatePassword, &QPushButton::clicked,
            this, &PasswordGenerator::SLOT_generatePasswords);

    connect(ui->QPB_clear, &QPushButton::clicked,
            this, &PasswordGenerator::SLOT_clear);

    connect(ui->QPB_stop, &QPushButton::clicked,
            this, &PasswordGenerator::SLOT_stop);

    connect(ui->QPB_start, &QPushButton::clicked,
            this, &PasswordGenerator::SLOT_start);

    connect(ui->QPB_createStatics, &QPushButton::clicked,
            this, &PasswordGenerator::SLOT_createStatics);

    ui->QSB_minimum_2->setMinimum(2);
    ui->QSB_maximum_2->setMinimum(2);

    ui->QLE_passwordResult->setEnabled(false);

    QLi_c_charsOfPassword.clear();
}

PasswordGenerator::~PasswordGenerator()
{
    delete ui;
}

void PasswordGenerator::SLOT_generatePasswords(){

    QLi_c_charsOfPassword.clear();

    int minimum = ui->QSB_minimum->value(),
        maximum = ui->QSB_maximum->value();


    if(minimum > maximum){
        ui->QSB_maximum->setValue(minimum);
        ui->QLW_listOfPasswords->clear();
        ui->QLW_listOfPasswords->addItem("Error: minimum length bigger ");
        ui->QLW_listOfPasswords->addItem("then maximum length");
        return;
    }

    if(ui->QCB_smallLetters->isChecked())
        QLi_c_charsOfPassword.append(QLi_c_smallLetters);

    if(ui->QCB_capitalLetters->isChecked())
        QLi_c_charsOfPassword.append(QLi_c_capitalLetters);

    if(ui->QCB_numbers->isChecked())
        QLi_c_charsOfPassword.append(QLi_c_numbers);

    if(ui->QCB_specialCharacters->isChecked())
        QLi_c_charsOfPassword.append(QLi_c_specialCharacters);


    if(QLi_c_charsOfPassword.isEmpty()){
        ui->QLW_listOfPasswords->clear();

        ui->QLW_listOfPasswords->addItem("Error: Select at Least one");
        ui->QLW_listOfPasswords->addItem("type of character");

        return;
    }

    ui->QLW_listOfPasswords->clear();

    int numberOfPasswords = ui->QSB_numberOfPasswords->value();
    v_generatePasswords(minimum, maximum, numberOfPasswords);

}

void PasswordGenerator::SLOT_clear(){
    ui->QLW_listOfPasswords->clear();
}

void PasswordGenerator::v_generatePasswords(int minimum, int maximum, int numberOfPasswords){

    int numberOfCharacters = QLi_c_charsOfPassword.size();

    for (int i=0; i<numberOfPasswords; i++){
        int length = QRandomGenerator::global()->bounded(minimum, (maximum+1));        
        QString QS_password;
        QS_password.clear();
        for(int j=0; j<length; j++){
            QS_password.append(
                        QLi_c_charsOfPassword.at(
                            QRandomGenerator::global()->bounded(0, numberOfCharacters)
                            )
                        );
        }
        ui->QLW_listOfPasswords->addItem(QS_password);
    }
}

void PasswordGenerator::SLOT_stop(){

}

void PasswordGenerator::SLOT_start(){

    ui->QLW_listOfPasswords_2->clear();

    QLi_c_charsOfPassword.clear();

    int minimum = ui->QSB_minimum_2->value(),
        maximum = ui->QSB_maximum_2->value();


    if(minimum > maximum){
        ui->QSB_maximum_2->setValue(minimum);
        ui->QLW_listOfPasswords_2->addItem("Error: minimum length bigger ");
        ui->QLW_listOfPasswords_2->addItem("then maximum length");
        return;
    }

    QString QS_yourPassword = ui->QLE_yourPassword->text();

    int length = QS_yourPassword.size();

    if( ! (length >= minimum &&
           length <= maximum)
            ){
        ui->QLW_listOfPasswords_2->addItem("Error: password impossible ");
        ui->QLW_listOfPasswords_2->addItem("to figure out because ");
        ui->QLW_listOfPasswords_2->addItem(" ...");
        ui->QLW_listOfPasswords_2->addItem("the lenght of your password is");
        ui->QLW_listOfPasswords_2->addItem(QString::number(length));

        ui->QSB_minimum_2->setValue(length);
        ui->QSB_maximum_2->setValue(length);

        return;
    }

    if(ui->QCB_smallLetters_2->isChecked())
        QLi_c_charsOfPassword.append(QLi_c_smallLetters);

    if(ui->QCB_capitalLetters_2->isChecked())
        QLi_c_charsOfPassword.append(QLi_c_capitalLetters);

    if(ui->QCB_numbers_2->isChecked())
        QLi_c_charsOfPassword.append(QLi_c_numbers);

    if(ui->QCB_specialCharacters_2->isChecked())
        QLi_c_charsOfPassword.append(QLi_c_specialCharacters);

    if(QLi_c_charsOfPassword.isEmpty()){
        ui->QLW_listOfPasswords_2->clear();
        ui->QLW_listOfPasswords_2->addItem("Error: ");
        ui->QLW_listOfPasswords_2->addItem("Error: Select at Least one");
        ui->QLW_listOfPasswords_2->addItem("type of character");
        return;
    }

    for (int i=0; i<length; i++){
        bool charOK = false;
        for (auto n: QLi_c_charsOfPassword)
            if(n == QS_yourPassword.at(i)){
                charOK = true;
                break;
            }
        if(!charOK){
            ui->QLW_listOfPasswords_2->clear();
            ui->QLW_listOfPasswords_2->addItem("Error: password impossible ");
            ui->QLW_listOfPasswords_2->addItem("to find out");
            ui->QLW_listOfPasswords_2->addItem("invalid char");

            return;
        }
    }

    QS_password = QS_yourPassword;

    v_findOutPassword(minimum, maximum);

}

void PasswordGenerator::v_findOutPassword(int minimum, int maximum){

    QET_control.start();

    QLi_QS_passwords_interface_2.clear();

    int numberOfCharacters = QLi_c_charsOfPassword.size();

    for (int length=minimum; length<=maximum; length++){

        QList<uint8_t> QLi_control;
        QLi_control.clear();
        for(int i=0; i<length; i++){
            QLi_control.append(0);
        }

        bool bOk = false;

        int n=0;

        while (!bOk){

            n++;

            QString QS_passwordTest = "";

            for(int i=0; i<length; i++){
                QS_passwordTest.append(
                            QLi_c_charsOfPassword.at(
                                QLi_control.at(i)));
            }

            if(QLi_QS_passwords_interface_2.size() < 20)
                QLi_QS_passwords_interface_2.append(QS_passwordTest);

            if(n >=10000){
                ui->QLW_listOfPasswords_2->clear();
                ui->QLW_listOfPasswords_2->addItems(QLi_QS_passwords_interface_2);

                qApp->processEvents();
                this->repaint();

                QLi_QS_passwords_interface_2.clear();
                n=0;
            }

            if(QS_passwordTest == QS_password){
                QString QS_timeOfProcess;
                double time = QET_control.nsecsElapsed();


                if(time < 1e3){ /// ns
                    int time_nsec = static_cast<int>(time);
                    QS_timeOfProcess = "Time of process: "+ QString::number(time_nsec) +" nsec";
                }
                else if(time < 1e6){ /// us
                    time /= 1e3;

                    QS_timeOfProcess = "Time of process: "+ QString::number(time, 'f', 2) +" usec";
                }
                else if(time < 1e9){ /// ms
                    time /= 1e6;

                    QS_timeOfProcess = "Time of process: "+ QString::number(time, 'f', 2) +" msec";

                }
                else if(time < 60*1e9){ /// s
                    time /= 1e9;

                    QS_timeOfProcess = "Time of process: "+ QString::number(time, 'f', 2) +" sec";

                }

                else if(time < 3600*1e9){ /// min + sec
                    time /= 1e9;
                    int time_sec = static_cast<int>(time) % 60;
                    int time_min = static_cast<int>(time) / 60;

                    QS_timeOfProcess =
                            "Time of process: "+ QString::number(time_min) +" min "+ QString::number(time_sec)+ " sec";

                }
                else if(time < 86400*1e9){ /// h + min
                    time /= 1e9;
                    time /= 60;

                    int time_min = static_cast<int>(time) % 60;
                    int time_h = static_cast<int>(time) / 60;

                    QS_timeOfProcess =
                            "Time of process: "+ QString::number(time_h) +" h "+ QString::number(time_min)+ " min";


                } else { /// day + h
                    time /= 1e9;
                    time /= 3600;

                    int time_h = static_cast<int>(time) % 24;
                    int time_day = static_cast<int>(time) / 24;

                    QS_timeOfProcess =
                            "Time of process: "+ QString::number(time_day) +" days "+ QString::number(time_h)+ " h";

                }
                ui->QLE_passwordResult->setText(QS_passwordTest);

                ui->QLW_listOfPasswords_2->clear();
                ui->QLW_listOfPasswords_2->addItem("Your Passwor is:");
                ui->QLW_listOfPasswords_2->addItem(QS_passwordTest);
                ui->QLW_listOfPasswords_2->addItem(" ");
                ui->QLW_listOfPasswords_2->addItem("Time of Process: ");
                ui->QLW_listOfPasswords_2->addItem(QS_timeOfProcess);

                return;
            }
            for (int i=length-1; i>=0; i--){

                uint8_t n = QLi_control.at(i);

                if(n == numberOfCharacters-1){
                    if(i==0)
                        bOk = true;
                    else {
                        QLi_control.replace(i, 0);
                    }
                }
                else{
                    QLi_control.replace(i, n+1);
                    break;
                }
            }
        }
    }
}

void PasswordGenerator::SLOT_createStatics(){

    ui->QLW_listOfPasswords_2->clear();

    QLi_c_charsOfPassword.clear();

    int minimum = ui->QSB_minimum_2->value(),
        maximum = ui->QSB_maximum_2->value();


    if(minimum > maximum){
        ui->QSB_maximum_2->setValue(minimum);
        ui->QLW_listOfPasswords_2->addItem("Error: minimum length bigger ");
        ui->QLW_listOfPasswords_2->addItem("then maximum length");
        return;
    }

    QString QS_yourPassword = ui->QLE_yourPassword->text();

    int length = QS_yourPassword.size();

    if( ! (length >= minimum &&
           length <= maximum)
            ){
        ui->QLW_listOfPasswords_2->addItem("Error: password impossible ");
        ui->QLW_listOfPasswords_2->addItem("to figure out because ");
        ui->QLW_listOfPasswords_2->addItem(" ...");
        ui->QLW_listOfPasswords_2->addItem("the lenght of your password is");
        ui->QLW_listOfPasswords_2->addItem(QString::number(length));

        ui->QSB_minimum_2->setValue(length);
        ui->QSB_maximum_2->setValue(length);

        return;
    }

    if(ui->QCB_smallLetters_2->isChecked())
        QLi_c_charsOfPassword.append(QLi_c_smallLetters);

    if(ui->QCB_capitalLetters_2->isChecked())
        QLi_c_charsOfPassword.append(QLi_c_capitalLetters);

    if(ui->QCB_numbers_2->isChecked())
        QLi_c_charsOfPassword.append(QLi_c_numbers);

    if(ui->QCB_specialCharacters_2->isChecked())
        QLi_c_charsOfPassword.append(QLi_c_specialCharacters);

    if(QLi_c_charsOfPassword.isEmpty()){
        ui->QLW_listOfPasswords_2->clear();
        ui->QLW_listOfPasswords_2->addItem("Error: ");
        ui->QLW_listOfPasswords_2->addItem("Error: Select at Least one");
        ui->QLW_listOfPasswords_2->addItem("type of character");
        return;
    }

    for (int i=0; i<length; i++){
        bool charOK = false;
        for (auto n: QLi_c_charsOfPassword)
            if(n == QS_yourPassword.at(i)){
                charOK = true;
                break;
            }
        if(!charOK){
            ui->QLW_listOfPasswords_2->clear();
            ui->QLW_listOfPasswords_2->addItem("Error: password impossible ");
            ui->QLW_listOfPasswords_2->addItem("to find out");
            ui->QLW_listOfPasswords_2->addItem("invalid char");

            return;
        }
    }

    QS_password = QS_yourPassword;

    v_generateStatics(minimum, maximum);

}


void PasswordGenerator::v_generateStatics(int minimum, int maximum){


    QET_control.start();

    number numberOfPossiblePasswords;

    int numberOfCharacters = QLi_c_charsOfPassword.size();

    for (int length=minimum; length<=maximum; length++){
        numberOfPossiblePasswords.value += pow(numberOfCharacters, length);
    }

    {
        bool b_aux = false;

        while(!b_aux){

            if(numberOfPossiblePasswords.value >= 0 &&
               numberOfPossiblePasswords.value < 1000){
                b_aux = true;
            }
            else{
                numberOfPossiblePasswords.value /= pow(10, 3);
                numberOfPossiblePasswords.power += 3;
            }

        }
    }


    QLi_QS_passwords_interface_2.clear();

    int length = maximum;

    QList<uint8_t> QLi_control;
    QLi_control.clear();
    for(int i=0; i<length; i++){
        QLi_control.append(0);
    }

    bool bOk = false;

    int n = 0;
    int k = 0;

    while (!bOk && k <=30*10000){

        n++;
        k++;

        QString QS_passwordTest = "";

        for(int i=0; i<length; i++){
            QS_passwordTest.append(
                        QLi_c_charsOfPassword.at(
                            QLi_control.at(i)));
        }

        if(QLi_QS_passwords_interface_2.size() < 20)
            QLi_QS_passwords_interface_2.append(QS_passwordTest);

        if(n >=10000){
            ui->QLW_listOfPasswords_2->clear();
            ui->QLW_listOfPasswords_2->addItems(QLi_QS_passwords_interface_2);

            qApp->processEvents();
            this->repaint();

            QLi_QS_passwords_interface_2.clear();
            n=0;
        }

        if(QS_passwordTest == QS_password)
            break;

        for (int i=length-1; i>=0; i--){

            uint8_t n = QLi_control.at(i);

            if(n == numberOfCharacters-1){
                if(i==0)
                    bOk = true;
                else {
                    QLi_control.replace(i, 0);
                }
            }
            else{
                QLi_control.replace(i, n+1);
                break;
            }
        }
    }

    QString QS_numberOfCharacters = "number of Characters: "+ QString::number(numberOfCharacters),

            QS_numberOfPossiblePasswords =
            "number of Possible Passwords: " +
            QString::number(numberOfPossiblePasswords.value, 'f', 3) + " E" +
            QString::number(numberOfPossiblePasswords.power),

            QS_timeEstimeted = "";


    double timeEstimeted = QET_control.nsecsElapsed()*
            numberOfPossiblePasswords.value*
            pow(10, numberOfPossiblePasswords.power)/
            k;


    if(timeEstimeted < 1e3){ /// ns
        int time_nsec = static_cast<int>(timeEstimeted);
        QS_timeEstimeted = "time Estimeted: "+ QString::number(time_nsec) +" nsec";
    }
    else if(timeEstimeted < 1e6){ /// us
        timeEstimeted /= 1e3;

        QS_timeEstimeted = "time Estimeted: "+ QString::number(timeEstimeted, 'f', 2) +" usec";
    }
    else if(timeEstimeted < 1e9){ /// ms
        timeEstimeted /= 1e6;

        QS_timeEstimeted = "time Estimeted: "+ QString::number(timeEstimeted, 'f', 2) +" msec";

    }
    else if(timeEstimeted < 60*1e9){ /// s
        timeEstimeted /= 1e9;

        QS_timeEstimeted = "time Estimeted: "+ QString::number(timeEstimeted, 'f', 2) +" sec";

    }

    else if(timeEstimeted < 3600*1e9){ /// min + sec
        timeEstimeted /= 1e9;
        int time_sec = static_cast<int>(timeEstimeted) % 60;
        int time_min = static_cast<int>(timeEstimeted) / 60;

        QS_timeEstimeted =
                "time Estimeted: "+ QString::number(time_min) +" min "+ QString::number(time_sec)+ " sec";

    }
    else if(timeEstimeted < 86400*1e9){ /// h + min
        timeEstimeted /= 1e9;
        timeEstimeted /= 60;

        int time_min = static_cast<int>(timeEstimeted) % 60;
        int time_h = static_cast<int>(timeEstimeted) / 60;

        QS_timeEstimeted =
                "time Estimeted: "+ QString::number(time_h) +" h "+ QString::number(time_min)+ " min";


    } else { /// day + h
        timeEstimeted /= 1e9;
        timeEstimeted /= 3600;

        int time_h = static_cast<int>(timeEstimeted) % 24;
        int time_day = static_cast<int>(timeEstimeted) / 24;

        QS_timeEstimeted =
                "time Estimeted: "+ QString::number(time_day) +" days "+ QString::number(time_h)+ " h";

    }

    QS_timeEstimeted.append(" (max)");

    ui->QLW_listOfPasswords_2->clear();
    ui->QLW_listOfPasswords_2->addItem("Statics: ");
    ui->QLW_listOfPasswords_2->addItem("");
    ui->QLW_listOfPasswords_2->addItem(QS_numberOfCharacters);
    ui->QLW_listOfPasswords_2->addItem(QS_numberOfPossiblePasswords);
    ui->QLW_listOfPasswords_2->addItem(QS_timeEstimeted);

}











