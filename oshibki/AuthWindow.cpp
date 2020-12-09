#include "AuthWindow.h"
#include "ui_AuthWindow.h"

AuthWindow::AuthWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
    createConnection();
    createTabel();
}

AuthWindow::~AuthWindow()
{
    delete ui;
}

bool AuthWindow::createConnection()
{
    bool connect;
    static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("AdressBook.db");
        if (!db.open()){
            qDebug() << "db not working" << db.lastError();
            connect = false;
        } else {
            connect = true;
        }
        return connect;
}

void AuthWindow::createTabel()
{
    QString userInfo = "CREATE TABLE IF NOT EXISTS userInfo"
                    "("
                    "user_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "login TEXT UNIQUE,"
                    "password TEXT"
                    ");";
    query = new QSqlQuery;
    if(!query->exec(userInfo)) {
        qDebug() << "create userInfo tabel error" << endl;
    }
}

bool AuthWindow::authUser(QString login, QString password)
{
    query->prepare("SELECT login, password FROM userInfo "
                      "WHERE login = :login AND password = :password;");
    query->bindValue(":login",login);
    query->bindValue(":password",password);

    if(!query->exec()){
        qDebug() << "select from userInfo tabel error" << endl;
    }

    // check authorization
    bool sucsessAuth;
    int elem = 0;
    while (query->next()) {
        elem++;
    }
    if (elem == 1) {
        sucsessAuth = true;
    } else  {
        sucsessAuth = false;
        qDebug() << "wrong authorization" << endl;
    }
    return sucsessAuth;
}

void AuthWindow::on_enter_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();

    if (authUser(login,password) == true)
    {
        QMessageBox::information(this,"sucsess","успешная авторизация!");
        hide();
        ab = new AddressBook();
        ab->user.login = login;
        ab->user.password = password;
        ab->getContacts();
        ab->show();
    } else {
        QMessageBox::warning(this,"wrong log or pass", "введены некорректные данные");
    }
}

void AuthWindow::on_registration_clicked()
{
    hide();
    regist = new RegistWindow();
    regist->show();
}
