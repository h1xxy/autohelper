#include "Autohelper.h"
#include "ui_AddressBook.h"

Autohelper::Autohelper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Autohelper)
{
    ui->setupUi(this);
    createTabel();
    ui->deleteContact->setEnabled(false);
    ui->editContact->setEnabled(false);
    editDone = true;
}

Autohelper::Autohelper
{
    delete ui;
}

void Autohelper::createTabel()
{
    QString userData = "CREATE TABLE IF NOT EXISTS userData"
                       "("
                       "user_login TEXT, "
                       "contact_name TEXT, "
                       "contact_surname TEXT,"
                       "contact_phone INTEGER,"
                       "contact_mail TEXT,"
                       "contact_adress TEXT,"
                       "contact_note TEXT,"
                       "contact_photo BLOB,"
                       "id INTEGER PRIMARY KEY AUTOINCREMENT"
                       ");";

    query = new QSqlQuery;
    if (!query->exec(userData)) {
        qDebug() << "create userData tabel error" << endl;
    }
}

void Autohelper::getContacts()
{
    vector<Contact> list;
    Contact contact;

    query->prepare("SELECT "
                    "user_login,"
                    "contact_name,"
                    "contact_surname "
                    "FROM userData "
                    "WHERE user_login = :login;");
    query->bindValue(":login",user.login);
    if (!query->exec()) {
        qDebug() << "get Contacts error" << endl;
    }

    QSqlRecord rec = query->record();
    while (query->next()) {
        contact.name = query->value(rec.indexOf("contact_name")).toString();
        contact.surname = query->value(rec.indexOf("contact_surname")).toString();
        list.push_back(contact);
    }

    // for update contacts list, else duplicate contacts
    ui->contactsList->clear();

    vector<QString> sort_list;

    // add contacts list to list view in Adress Book
    for (uint64_t i = 0; i < list.size(); ++i) {
        auto contactInfo = list[i].name + " " + list[i].surname;
        sort_list.push_back(contactInfo);
    }

    stable_sort(sort_list.begin(),sort_list.end());
    for (uint64_t i = 0; i < sort_list.size(); ++i) {
        ui->contactsList->addItem(sort_list[i]);
    }
}

void Autohelper::showContact(QListWidgetItem *item)
{
    ui->deleteContact->setEnabled(true);
    ui->editContact->setEnabled(true);

    QStringList list;
    QString fio = item->text();


    list = fio.split(" ");
    QString name = list.at(0);
    QString surname = list.at(1);

    Contact contact;

    query->prepare("SELECT "
                   "user_login,"
                   "contact_name,"
                   "contact_surname,"
                   "contact_phone,"
                   "contact_mail,"
                   "contact_adress,"
                   "contact_note,"
                   "contact_photo "
                   "FROM userData WHERE "
                   "user_login = :login AND "
                   "contact_name = :name AND "
                   "contact_surname = :surname;");
    query->bindValue(":login", user.login);
    query->bindValue(":name", name);
    query->bindValue(":surname", surname);

    qDebug() << "name: " << name << endl;

    if(!query->exec()) {
        qDebug() << "select from userData tabel error" << endl;
    }

    QByteArray photo;
    QSqlRecord rec = query->record();
    while (query->next()) {
        contact.name = query->value(rec.indexOf("contact_name")).toString();
        contact.surname = query->value(rec.indexOf("contact_surname")).toString();
        contact.phone = query->value(rec.indexOf("contact_phone")).toString();
        contact.mail = query->value(rec.indexOf("contact_mail")).toString();
        contact.adress = query->value(rec.indexOf("contact_adress")).toString();
        contact.note = query->value(rec.indexOf("contact_note")).toString();
        photo = query->value(rec.indexOf("contact_photo")).toByteArray();
    }

    contact.photo.loadFromData(photo);


    qDebug() << "contact name: " << contact.name << endl;

    ui->name_field->setText(contact.name);
    ui->sname_field->setText(contact.surname);
    ui->phone_field->setText(contact.phone);
    ui->email_field->setText(contact.mail);
    ui->adress_field->setText(contact.adress);
    ui->note_field->setText(contact.note);
    ui->photo->setPixmap(contact.photo);
}

void Autohelper::on_addContact_clicked()
{
    add = new addContact(this);
    add->show();
    clearContactFields();
}

void Autohelper::on_deleteauto_clicked()
{

    query->prepare("DELETE FROM userInfo "
                   "WHERE login = :login "
                   "AND password = :password;");
    query->bindValue(":login", user.login);
    query->bindValue(":password", user.password);
    if (!query->exec()) {
        qDebug() << "delete data from userInfo error" << endl;
    }
    query->prepare("DELETE FROM userData "
                   "WHERE user_login = :login;");
    query->bindValue(":login",user.login);

    if (!query->exec()) {
        qDebug() << "delete data from userData error" << endl;
    } else {
        QMessageBox::information(this,"sucsess","адресная книжка удалена");
    }
    close();
}

void Autohelper::on_contactsList_itemClicked(QListWidgetItem *item)
{
    if (item) {
        showContact(item);
    }
}

void Autohelper::on_deleteContact_clicked()
{
    QMessageBox::StandardButton replay =
            QMessageBox::question(this,"qusetion","Все контакты с этой фамилией и именем будут удалены.\nХотите продолжить?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (replay == QMessageBox::Yes) {

        if (ui->contactsList->currentItem()->isSelected() == true) {
            QStringList list;
            QString fio = ui->contactsList->currentItem()->text();

            list = fio.split(" ");
            QString name = list.at(0);
            QString surname = list.at(1);

            query->prepare("DELETE FROM userData "
                       "WHERE user_login = :login "
                       "AND contact_name = :name "
                       "AND contact_surname = :surname;");
            query->bindValue(":login", user.login);
            query->bindValue(":name", name);
            query->bindValue(":surname", surname);

            if (!query->exec()) {
                qDebug() << "delete contact from userData error" << endl;
            } else {
                QMessageBox::information(this,"sucsess","контакт удалён");
            }
        }
        this->getContacts();
        clearContactFields();
    }

}

void Autohelper::on_editauto_clicked()
{
    if(editDone){
        QString name = ui->name_field->text();
        QString surname = ui->sname_field->text();
        QString phone = ui->phone_field->text();
        QString email = ui->email_field->text();
        QString adress = ui->adress_field->toPlainText();
        QString note = ui->note_field->toPlainText();

        edit = new editContact(this);
        edit->editContactWindow(name,surname,phone,email,adress,note);
        edit->show();
        connect(edit, SIGNAL(editDone(bool)), this, SLOT(setEditDone(bool)) );
        editDone = false;
        clearContactFields();
    }
    else QMessageBox::information(this,"Warning","Окно редактирования уже открыто.\n"
                                                 "Сохраните изменения перед \nредактированием нового контакта.");
}


void Autohelper::clearContactFields(){
    ui->deleteContact->setEnabled(false);
    ui->editContact->setEnabled(false);
    ui->name_field->setText("");
    ui->sname_field->setText("");
    ui->phone_field->setText("");
    ui->email_field->setText("");
    ui->adress_field->setText("");
    ui->note_field->setText("");
    ui->photo->clear();
}
void Autohelper::setEditDone(bool ed){
    editDone = ed;
}

