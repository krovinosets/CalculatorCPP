#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"

#define MAX_LEN 1024

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *NumsButtons[10] = {ui->PB_0, ui->PB_1, ui->PB_2, ui->PB_3, ui->PB_4, ui->PB_5, ui->PB_6, ui->PB_7, ui->PB_8, ui->PB_9};
    for(QPushButton *button : NumsButtons){
        connect(button, SIGNAL(clicked()), this, SLOT(on_PB_numspace_clicked()));
        connect(button, SIGNAL(clicked()), this, SLOT(on_PB_clicked()));
    }
    QPushButton *FuncButtons[5] = {/*ui->PB_ac, ui->PB_del, ui->PB_fin,*/ ui->PB_dot, ui->PB_dev, ui->PB_mult, ui->PB_minus, ui->PB_plus};
    for(QPushButton *button : FuncButtons){
        connect(button, SIGNAL(clicked()), this, SLOT(on_PB_funcspace_clicked()));
        connect(button, SIGNAL(clicked()), this, SLOT(on_PB_clicked()));
    }
    QPushButton *UniqButtons[6] = {ui->PB_ac, ui->PB_del, ui->PB_mc, ui->PB_Mplus, ui->PB_Mminus};
    for(QPushButton *button : UniqButtons){
        connect(button, SIGNAL(clicked()), this, SLOT(on_PB_clicked()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PB_clicked()
{
    QLabel *outputForm = this->ui->LB_output;
    int len = outputForm->text().length();
    if(len < MAX_LEN){
        QWidget *sawc = this->ui->SAWC_var;
        int cal = 409 + ((len > 17) ? len - 17 : 0) * 24;
        sawc->setMinimumWidth(cal);
        outputForm->setGeometry(outputForm->x(), outputForm->y(), cal, outputForm->height());
    }
}

void MainWindow::on_PB_numspace_clicked()
{
    QPushButton *btn = (QPushButton *) sender();
    QLabel *outputForm = this->ui->LB_output;
    int len = outputForm->text().length();
    if(this->ui->LB_answer->text() != "")
        this->ui->LB_answer->setText("");
    if(len < MAX_LEN){
        if(len == 1 && outputForm->text() == '0')
            outputForm->setText(btn->text());
        else
            outputForm->setText(outputForm->text() + btn->text());
        if(!isEnabledFuncButtons())
            enableFuncButtons(true);
        if(getLastDigitShort(outputForm->text().toStdString()).find(".") != std::string::npos)
            this->ui->PB_dot->setEnabled(false);
    }
}

void MainWindow::on_PB_funcspace_clicked()
{
    QPushButton *btn = (QPushButton *) sender();
    QLabel *outputForm = this->ui->LB_output;
    int len = outputForm->text().length();
    if(this->ui->LB_answer->text() != ""){
        if(this->ui->LB_answer->text() != "= Ошибка!")
            outputForm->setText(this->ui->LB_answer->text().mid(2,this->ui->LB_answer->text().length()-2));
        else
            outputForm->setText(outputForm->text());
        this->ui->LB_answer->setText("");
    }
    if(len < MAX_LEN
            && (outputForm->text() != '0' || (outputForm->text() == '0' && btn->text() == "."))
            && ((QString) "0123456789").contains(outputForm->text().back())
            && ((btn->text() == "." && (getLastDigitShort(outputForm->text().toStdString()).find(".")) == std::string::npos) || btn->text() != ".")){
        outputForm->setText(outputForm->text() + btn->text());
        enableFuncButtons(false);
        if(this->ui->PB_dot->isEnabled())
            this->ui->PB_dot->setEnabled(true);
    }
}

void MainWindow::on_PB_ac_clicked()
{
    if(this->ui->LB_answer->text() != "")
        this->ui->LB_answer->setText("");
    this->ui->LB_output->setText("0");
    if(!isEnabledFuncButtons())
        enableFuncButtons(true);
}

void MainWindow::on_PB_del_clicked()
{
    QLabel *outputForm = this->ui->LB_output;
    int len = outputForm->text().length();
    if(this->ui->LB_answer->text() != "")
        this->ui->LB_answer->setText("");
    if(len > 1){
        outputForm->setText(outputForm->text().mid(0,len-1));
        if(((QString) "+-*/").contains(outputForm->text().back()))
            enableFuncButtons(false);
        else
            enableFuncButtons(true);
        if(getLastDigitShort(outputForm->text().toStdString()).find(".") != std::string::npos)
            this->ui->PB_dot->setEnabled(false);
        else
            this->ui->PB_dot->setEnabled(true);
    }
}

void MainWindow::on_PB_fin_clicked()
{
    QLabel *outputForm = this->ui->LB_output;
    QString str = outputForm->text();
    if(((QString) "+-/*").contains(str.back()))
        str = str.mid(0, str.size()-1);
    qDebug() << "Original String: " << str;
    QString answer = QString::fromUtf8(reversePolskaFinal(str.toStdString()));
    qDebug() << "result: " << answer;
    this->ui->LB_answer->setText("= " + answer);
}

void MainWindow::on_PB_mc_clicked()
{
    QLabel *ans = this->ui->LB_mAns;
    if(ans->text() != "None"){
        ans->setText("None");
    }
}

void MainWindow::on_PB_Mplus_clicked()
{
    QLabel *ans = this->ui->LB_mAns;
    QLabel *AnsForm = this->ui->LB_answer;
    if(AnsForm->text() != "" && AnsForm->text() != "= Ошибка!"){
        QString res;
        if(AnsForm->text().mid(2,AnsForm->text().length()-2).toStdString()[0] == '-'){
            res = QString::fromUtf8(reversePolskaFinal(((ans->text() != "None") ? ans->text().toStdString() + "-" : "") + AnsForm->text().mid(3,AnsForm->text().length()-3).toStdString()));
        } else {
            res = QString::fromUtf8(reversePolskaFinal(((ans->text() != "None") ? ans->text().toStdString() + "+" : "") + AnsForm->text().mid(2,AnsForm->text().length()-2).toStdString()));

        }
        ans->setText(res);
    }
}

void MainWindow::on_PB_Mminus_clicked()
{
    QLabel *ans = this->ui->LB_mAns;
    QLabel *AnsForm = this->ui->LB_answer;
    if(AnsForm->text() != "" && AnsForm->text() != "= Ошибка!"){
        QString res;
        if(AnsForm->text().mid(2,AnsForm->text().length()-2).toStdString()[0] == '-'){
            res = QString::fromUtf8(reversePolskaFinal(((ans->text() != "None") ? ans->text().toStdString() + "+" : "+") + AnsForm->text().mid(3,AnsForm->text().length()-3).toStdString()));
        } else {
            res = QString::fromUtf8(reversePolskaFinal(((ans->text() != "None") ? ans->text().toStdString() + "-" : "-") + AnsForm->text().mid(2,AnsForm->text().length()-2).toStdString()));

        }
        ans->setText(res);
    }
}

void MainWindow::enableFuncButtons(bool var){
    QPushButton *FuncButtons[5] = {ui->PB_dot, ui->PB_dev, ui->PB_mult, ui->PB_minus, ui->PB_plus};
    for(QPushButton *button : FuncButtons){
        button->setEnabled(var);
    }
}

bool MainWindow::isEnabledFuncButtons(){
    bool result = true;
    QPushButton *FuncButtons[5] = {ui->PB_dot, ui->PB_dev, ui->PB_mult, ui->PB_minus, ui->PB_plus};
    for(QPushButton *button : FuncButtons){
        result = result && button->isEnabled();
    }
    return result;
}


void MainWindow::on_PB_mr_clicked()
{
    QLabel *ans = this->ui->LB_mAns;
    QLabel *outputForm = this->ui->LB_output;
    if(ans->text() != "None"){
        if(!((QString) "+-/*").contains(outputForm->text().back())){
            if(!ans->text().contains("-"))
                outputForm->setText(outputForm->text() + "+" + ans->text());
            else
                outputForm->setText(outputForm->text() + "-" + ans->text().mid(1, ans->text().length()-1));
        } else {
            if(!isEnabledFuncButtons())
                enableFuncButtons(true);
            outputForm->setText(outputForm->text() + ans->text());
        }
    }
}

