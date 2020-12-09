#include "RegistWindow.h"
#include "ui_RegistWindow.h"

RegistWindow::RegistWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistWindow)
{
    ui->setupUi(this);

    QRegExp rx_s("^[a-zA-Zа-яА-Я0-9_]*$");
    QValidator *val_name = new QRegExpValidator(rx_s, this);
    ui->login->setValidator(val_name);
    ui->password->setValidator(val_name);
}

RegistWindow::~RegistWindow()
{
    delete ui;
}

bool RegistWindow::registration(QString login, QString password)
{

    query->prepare("SELECT login FROM userInfo "
                   "WHERE login = :login;");
    query->bindValue(":login",login);

    bool check;
    if (!query->exec()) {
        qDebug() << "select from userInfo tabel error" << endl;
        check = false;
    } else {
        query->prepare("INSERT INTO userInfo "
                           "(login,password) "
                       "VALUES(:login, :password);");
        query->bindValue(":login",login);
        query->bindValue(":password",password);
        if (!query->exec()) {
            qDebug() << "insert into userInfo tabel error" << endl;
            check = false;
        } else {
            check = true;
        }
    }
    return check;
}

void RegistWindow::on_regist_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();

    if (registration(login,password) == true) {
        QMessageBox::information(this,"success","успешная регистрация!");
        hide();
        ab = new AddressBook();
        ab->user.login = login;
        ab->user.password = password;
        ab->show();
    } else {
         QMessageBox::warning(this,"some error","какая-то ошибка, попробуйте ещё раз");
    }
}
