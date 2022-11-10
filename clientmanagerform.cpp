#include "clientmanagerform.h"
#include "ui_clientmanagerform.h"
//#include "clientitem.h"

#include <QFile>
#include <QMenu>
#include <QSqlTableModel>
#include<QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>

ClientManagerForm::ClientManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 540 << 400; //client의 sizes 값
    ui->splitter->setSizes(sizes);

    QAction* removeAction = new QAction(tr("&Remove")); //client의 삭제액션
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem())); //client의 삭제액션을 누를때 clientItem삭제

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));

}

void ClientManagerForm::loadData() //clientItem의 txt파일을 불러오기 위한 함수
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","clientConnection");
    db.setDatabaseName("client.db");
    qDebug("hihi!!!!!!!!!!");
    if(db.open()){
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS client(id INTEGER Primary Key, name VARCHAR(30) NOT NULL, "
                   "phoneNumber VARCHAR(20) NOT NULL, address VARCHAR(50));");

        clientModel = new QSqlTableModel(this, db);
        clientModel->setTable("client");
        clientModel->select();
        clientModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        clientModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
        clientModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Phone Number"));
        clientModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Address"));

        ui->tableView->setModel(clientModel);
        ui->tableView->resizeColumnsToContents();
    }

    for(int i = 0; i < clientModel->rowCount(); i++) {
        int id = clientModel->data(clientModel->index(i, 0)).toInt();
        QString name = clientModel->data(clientModel->index(i, 1)).toString();
        emit clientAdded(id,name);
    }

}

ClientManagerForm::~ClientManagerForm()
{
    delete ui;
    QSqlDatabase db = QSqlDatabase::database("clientConnection");
    if(db.isOpen()) {
        clientModel->submitAll();
        db.close();
        QSqlDatabase::removeDatabase("clientConnection");
    }
}


int ClientManagerForm::makeId( ) //아이디 만듬
{
    if(clientModel->rowCount() == 0) {
        return 100;
    } else {
        auto id = clientModel->data(clientModel->index(clientModel->rowCount()-1, 0)).toInt();
        return ++id;
    }
}

void ClientManagerForm::removeItem() //삭제
{
    QModelIndex index = ui->tableView->currentIndex();
    if(index.isValid()) {
        clientModel->removeRow(index.row());
        clientModel->select();
        ui->tableView->resizeColumnsToContents();
    }
}

void ClientManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->tableView->mapToGlobal(pos);
    if(ui->tableView->indexAt(pos).isValid())
        menu->exec(globalPos);
}

void ClientManagerForm::on_searchPushButton_clicked()
{
    ui->searchTreeWidget->clear();
    int i = ui->searchComboBox->currentIndex();
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    QModelIndexList indexes = clientModel->match(clientModel->index(0, i), Qt::EditRole, ui->searchLineEdit->text(), -1, Qt::MatchFlags(flag));

    foreach(auto ix, indexes) {
        int id = clientModel->data(ix.siblingAtColumn(0)).toInt(); //c->id();
        QString name = clientModel->data(ix.siblingAtColumn(1)).toString();
        QString number = clientModel->data(ix.siblingAtColumn(2)).toString();
        QString address = clientModel->data(ix.siblingAtColumn(3)).toString();
        QStringList strings;
        strings << QString::number(id) << name << number << address;
        new QTreeWidgetItem(ui->searchTreeWidget, strings);
        for(int i = 0; i < ui->searchTreeWidget->columnCount(); i++)
            ui->searchTreeWidget->resizeColumnToContents(i);
    }
}

void ClientManagerForm::on_modifyPushButton_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if(index.isValid()) {
        //      int id = clientModel->data(index.siblingAtColumn(0)).toInt();
        QString name, number, address;
        name = ui->nameLineEdit->text();
        number = ui->phoneNumberLineEdit->text();
        address = ui->addressLineEdit->text();

        clientModel->setData(index.siblingAtColumn(1), name);
        clientModel->setData(index.siblingAtColumn(2), number);
        clientModel->setData(index.siblingAtColumn(3), address);
        clientModel->submit();

//        clientModel->select();
        ui->tableView->resizeColumnsToContents();
    }
}

void ClientManagerForm::on_addPushButton_clicked() //addPushbutton을 눌렀을때 name, number, address를 추가한다.
{
    QString name, number, address;
    int id = makeId( );
    ui->idLineEdit->setText(QString::number(id));
    name = ui->nameLineEdit->text();
    number = ui->phoneNumberLineEdit->text();
    address = ui->addressLineEdit->text();

    QSqlDatabase db = QSqlDatabase::database("clientConnection");

    if(db.isOpen()&&name.length()) {
        QSqlQuery query(clientModel->database());
        query.prepare("INSERT INTO client VALUES (?, ?, ?, ?)");
        query.bindValue(0, id);
        query.bindValue(1, name);
        query.bindValue(2, number);
        query.bindValue(3, address);
        query.exec();
        clientModel->select();
        ui->tableView->resizeColumnsToContents();
        emit clientAdded(id, name);
    }
}

void ClientManagerForm::acceptClientInfo(int key)
{
    QModelIndexList indexes = clientModel->match(clientModel->index(0, 0), Qt::EditRole, key, -1, Qt::MatchFlags(Qt::MatchCaseSensitive));

    foreach(auto index, indexes) {
        //    QModelIndex index = clientList[key];
        QString name = clientModel->data(index.siblingAtColumn(1)).toString();
        QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
        QString address = clientModel->data(index.siblingAtColumn(3)).toString();
        emit sendClientInfo(name, phoneNumber, address);
    }
}

void ClientManagerForm::on_tableView_clicked(const QModelIndex &index)
{
    QString id = clientModel->data(index.siblingAtColumn(0)).toString();
    QString name = clientModel->data(index.siblingAtColumn(1)).toString();
    QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
    QString address = clientModel->data(index.siblingAtColumn(3)).toString();

    ui->idLineEdit->setText(id);
    ui->nameLineEdit->setText(name);
    ui->phoneNumberLineEdit->setText(phoneNumber);
    ui->addressLineEdit->setText(address);
    ui->toolBox->setCurrentIndex(0);
}

