#include "ordermanagerform.h"
#include "orderitem.h"
#include "ui_ordermanagerform.h"

#include <QMenu>
#include <QFile>
#include <QString>
#include <QSqlTableModel>
#include<QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QStandardItemModel>

OrderManagerForm::OrderManagerForm(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::OrderManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 540 << 400;
    ui->splitter->setSizes(sizes);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));
    //  connect(ui->addPushButton, SIGNAL(pressed()), this, SLOT(on_addPushButton_clicked()));
    connect(ui->countspin, SIGNAL(textChanged(QString)),this, SLOT(total(QString)));

    searchModel = new QStandardItemModel(0, 6);
    searchModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    searchModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    searchModel->setHeaderData(2, Qt::Horizontal, tr("ProductName"));
    searchModel->setHeaderData(3, Qt::Horizontal, tr("Price"));
    searchModel->setHeaderData(4, Qt::Horizontal, tr("Count"));
    searchModel->setHeaderData(5, Qt::Horizontal, tr("Total"));
    ui->serchTableView->setModel(searchModel);
    ui->tableView->resizeColumnsToContents();
}

void OrderManagerForm::addProduct(int id, QString name, QString type, int price, int count)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->ProductW);
    item->setText(0,QString::number(id));
    item->setText(1,name);
    item->setText(2, type);
    item->setText(3, QString::number(price));
    item->setText(4,QString::number(count));
    productIDList << id;
    ui->productcombo->addItem(name);

}

void OrderManagerForm::addClient(int id, QString name, QString number, QString address)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->ClientW);
    item->setText(0,QString::number(id));
    item->setText(1,name);
    item->setText(2,number);
    item->setText(3,address);
    clientIDList << id;
    ui->clientcombo->addItem(name);
}

void OrderManagerForm::total(QString total)
{
    int b= ui->PriceLineEdit->text().toInt() * ui->countspin->text().toInt();
    ui->TotalLineEdit->setText(QString::number(b));
}

void OrderManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->tableView->mapToGlobal(pos);
    menu->exec(globalPos);
}

void OrderManagerForm::getProductInfo( QString name, QString type, int price, int count)     // ??????
{
    ui->ProductW->clear();
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->ProductW);
    //   item->setText(0, QString::number(id));
    item->setText(1, name);
    item->setText(2,type);
    item->setText(3, QString::number(price));
    item->setText(4, QString::number(count));

    ui->PriceLineEdit->setText(QString::number(price));
    ui->countspin->setMaximum(count);
}

void OrderManagerForm::getClientInfo(QString name, QString phoneNumber, QString address)
{
    ui->ClientW->clear();
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->ClientW);
  //  item->setText(0,QString::number (0));
    item->setText(1, name);
    item->setText(2, phoneNumber);
    item->setText(3, address);
}

int OrderManagerForm::makeId() //??????????????? ????????? ????????? ?????? ??????
{
    if(orderModel->rowCount() == 0) {
        return 100;
    } else {
        auto id = orderModel->data(orderModel->index(orderModel->rowCount()-1, 0)).toInt();
        return ++id;
    }
}

void OrderManagerForm::loadData() //??????????????? txt????????? ???????????? ?????? ??????
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","orderConnection");
    db.setDatabaseName("orderlist.db");
    if (db.open()) {
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS orders(id INTEGER Primary Key, cname VARCHAR(30) NOT NULL, "
                   "pname VARCHAR(30) NOT NULL, price number(20), count number(20), toal number(20));");
        orderModel = new QSqlTableModel(this,db);
        orderModel->setTable("orders");
        orderModel->select();
        orderModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        orderModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        orderModel->setHeaderData(2, Qt::Horizontal, tr("ProductName"));
        orderModel->setHeaderData(3, Qt::Horizontal, tr("Price"));
        orderModel->setHeaderData(4, Qt::Horizontal, tr("Count"));
        orderModel->setHeaderData(5, Qt::Horizontal, tr("Total"));

        ui->tableView->setModel(orderModel);
        ui->tableView->resizeColumnsToContents();
    }

    for(int i = 0; i < orderModel->rowCount(); i++) {
        int id = orderModel->data(orderModel->index(i, 0)).toInt();
        QString name = orderModel->data(orderModel->index(i, 1)).toString();
        QString type = orderModel->data(orderModel->index(i, 2)).toString();
        int price = orderModel->data(orderModel->index(i, 3)).toInt();
        int count = orderModel->data(orderModel->index(i, 4)).toInt();
        int total = orderModel->data(orderModel->index(i, 5)).toInt();
        emit orderAdded(id, name, type, price, count, total);
    }
}

OrderManagerForm::~OrderManagerForm() //????????? ???????????? order.txt????????? orderlist??? ????????????.
{
    delete ui;
    QSqlDatabase db = QSqlDatabase::database("orderConnection");
    if(db.isOpen()) {
        orderModel->submitAll();
        db.close();  //db??????
        QSqlDatabase::removeDatabase("orderConnection");
    }
}

void OrderManagerForm::removeItem() // ??? ????????? ?????? ?????? ?????? ??????
{
    QModelIndex index = ui->tableView->currentIndex();
    if(index.isValid() ) {
        orderModel->removeRow(index.row());
        orderModel->select();
        ui->tableView->resizeColumnsToContents();

    }
}

void OrderManagerForm::ClientRemove(int index) // client ????????? ??????
{

    ui->ClientW->takeTopLevelItem(index);
    ui->tableView->resizeColumnsToContents();
}
void OrderManagerForm::ProductRemove(int index) // product ????????? ??????
{

    ui->ProductW->takeTopLevelItem(index);
    ui->tableView->resizeColumnsToContents();
}
void OrderManagerForm::on_searchPushButton_clicked() // ?????? ?????? model??? ???????????? ?????? ????????? ???????????? ??????
{
    searchModel->clear();
    int i = ui->searchComboBox->currentIndex();
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    QModelIndexList indexes = orderModel->match(orderModel->index(0, i), Qt::EditRole, ui->searchLineEdit->text(), -1, Qt::MatchFlags(flag));

    foreach(auto ix, indexes) {
        int id = orderModel->data(ix.siblingAtColumn(0)).toInt(); //c->id();
        QString cname = orderModel->data(ix.siblingAtColumn(1)).toString();
        QString pname = orderModel->data(ix.siblingAtColumn(2)).toString();
        QString price = orderModel->data(ix.siblingAtColumn(3)).toString();
        QString count = orderModel->data(ix.siblingAtColumn(4)).toString();
        QString total = orderModel->data(ix.siblingAtColumn(5)).toString();
        QStringList strings;
        strings << QString::number(id) << cname << pname << price << count << total;

        QList<QStandardItem *> items;
        for (int i = 0; i < 6; ++i) {
            items.append(new QStandardItem(strings.at(i)));
        }
        searchModel->appendRow(items);
        searchModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        searchModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        searchModel->setHeaderData(2, Qt::Horizontal, tr("ProductName"));
        searchModel->setHeaderData(3, Qt::Horizontal, tr("Price"));
        searchModel->setHeaderData(4, Qt::Horizontal, tr("Count"));
        searchModel->setHeaderData(5, Qt::Horizontal, tr("Total"));
        ui->serchTableView->resizeColumnsToContents();
    }
}

void OrderManagerForm::on_ClientW_itemClicked(QTreeWidgetItem *item, int column) // client??? ????????? order??? ???????????? ?????? ??????
{
    Q_UNUSED(column);
    ui->idLineEdit->setText(item->text(0));
    ui->clientcombo->setCurrentText(item->text(1));

}

void OrderManagerForm::on_ProductW_itemClicked(QTreeWidgetItem *item, int column) // product??? ?????? ????????? order??? ???????????? ?????? ??????
{
    Q_UNUSED(column);
    ui->productcombo->setCurrentText(item->text(1));
    ui->PriceLineEdit->setText(item->text(3));

}

void OrderManagerForm::on_modifyPushButton_clicked() // order??? ?????? tableview??? ???????????? ?????? ??????
{
    QModelIndex index = ui->tableView->currentIndex();
    if(index.isValid()) {
        QString Clientname, Productname;
        int  price,count;
        Clientname = ui->clientcombo->currentText();
        Productname = ui->productcombo->currentText();
        price = ui->PriceLineEdit->text().toInt();
        count = ui->countspin->text().toInt();
        orderModel->setData(index.siblingAtColumn(1), Clientname); // ordermodel??? ???????????? row??? ????????????.
        orderModel->setData(index.siblingAtColumn(2), Productname);
        orderModel->setData(index.siblingAtColumn(3), price);
        orderModel->setData(index.siblingAtColumn(4), count);
        orderModel->submit();
        ui->tableView->resizeColumnsToContents();
    }
}


void OrderManagerForm::on_countspin_valueChanged(int arg1) //??? ????????? ????????? ?????? ??????
{ // total spinbox??? ???????????? ???????????? ????????? ?????????.
    ui->TotalLineEdit->setText(QString::number(arg1 * ui->PriceLineEdit->text().toInt()));
}
#include <QSqlError>
void OrderManagerForm::on_addPushButton_clicked() //?????? ??????
{
    int id = makeId();
    QString cname, pname;
    int  price, count, total;;
    cname = ui->clientcombo->currentText();
    qDebug()<<cname;
    pname = ui->productcombo->currentText();
    price = ui->PriceLineEdit->text().toInt();
    count = ui->countspin->text().toInt();
    total = ui->TotalLineEdit->text().toInt();

    QSqlDatabase db = QSqlDatabase::database("orderConnection");

    if(db.isOpen()&&cname.length()) { //database??? ???????????? ??????
        QSqlQuery query(orderModel->database());
        query.prepare("INSERT INTO orders VALUES (:id, :cname, :pname, :price, :count, :total)");
        query.bindValue(":id", id);
        query.bindValue(":cname", cname);
        query.bindValue(":pname", pname);
        query.bindValue(":price", price);
        query.bindValue(":count", count);
        query.bindValue(":total", total);
        query.exec();
        orderModel->select();
        ui->tableView->resizeColumnsToContents();
    }
}

void OrderManagerForm::on_tableView_clicked(const QModelIndex &index) //tableview??? ???????????? data??? ????????????
{
    QString id = orderModel->data(index.siblingAtColumn(0)).toString();
    QString cname = orderModel->data(index.siblingAtColumn(1)).toString();
    QString pname = orderModel->data(index.siblingAtColumn(2)).toString();
    int price = orderModel->data(index.siblingAtColumn(3)).toInt();
    int count = orderModel->data(index.siblingAtColumn(4)).toInt();
    int total = orderModel->data(index.siblingAtColumn(5)).toInt();
    ui->idLineEdit->setText(id);
    ui->clientcombo->setCurrentText(cname);
    ui->productcombo->setCurrentText(pname);
    ui->PriceLineEdit->setText(QString::number(price));
    ui->countspin->setValue(count);
    ui->TotalLineEdit->setText(QString::number(total));
    ui->toolBox->setCurrentIndex(0);
}

