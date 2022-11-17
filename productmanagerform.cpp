#include "productmanagerform.h"
#include "ui_productmanagerform.h"

#include <QMenu>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QStandardItemModel>

ProductManagerForm::ProductManagerForm(QWidget *parent) : // 생성자
    QWidget(parent),
    ui(new Ui::ProductManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes; //list sizes 설정
    sizes << 640 << 300;
    ui->splitter->setSizes(sizes);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));

    searchModel = new QStandardItemModel(0, 4); //data를 저장할 model을 만들어준다
    searchModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    searchModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    searchModel->setHeaderData(2, Qt::Horizontal, tr("Type"));
    searchModel->setHeaderData(3, Qt::Horizontal, tr("Price"));
    searchModel->setHeaderData(4, Qt::Horizontal, tr("Stock"));
    ui->serchtableView->setModel(searchModel);
     ui->tableView->resizeColumnsToContents();
}

void ProductManagerForm::loadData()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","productConnection"); //Qt에 내장되어 있는 SQLLIte에 연결한다.
    db.setDatabaseName("product.db"); //product database에 연결
    if (db.open( )) {
        QSqlQuery query(db); //quer 생성
        query.exec("CREATE TABLE IF NOT EXISTS product(id INTEGER Primary Key, name VARCHAR(30) NOT NULL, "
                   "type VARCHAR(20) NOT NULL, price number(20), stock number(20));"); //id를 기본키로 설정

        productModel = new QSqlTableModel(this, db); //db를 model에 담는다.
        productModel->setTable("product");
        productModel->select();
        productModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        productModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        productModel->setHeaderData(2, Qt::Horizontal, tr("Type"));
        productModel->setHeaderData(3, Qt::Horizontal, tr("Price"));
        productModel->setHeaderData(4, Qt::Horizontal, tr("Stock"));

        ui->tableView->setModel(productModel);
        ui->tableView->resizeColumnsToContents();
    }

    for(int i = 0; i < productModel->rowCount(); i++) {
        int id = productModel->data(productModel->index(i, 0)).toInt();
        QString name = productModel->data(productModel->index(i, 1)).toString();
        QString type = productModel ->data(productModel->index(i,2)).toString();
        int price = productModel ->data(productModel->index(i,3)).toInt();
        int stock = productModel ->data(productModel->index(i,4)).toInt();
        emit productAdded(id, name, type, price, stock);
    }
}

ProductManagerForm::~ProductManagerForm() //소멸자
{
    delete ui;
    QSqlDatabase db = QSqlDatabase::database("productConnection"); //db에 연결
    if(db.isOpen()) {
        productModel->submitAll();
        delete productModel;
        db.close();
    }
}

int ProductManagerForm::makeId( ) //id를 만든다.
{
    if(productModel->rowCount() == 0) {
        return 100;
    } else {
        auto id = productModel->data(productModel->index(productModel->rowCount()-1, 0)).toInt();
        return ++id;
    }
}

void ProductManagerForm::removeItem() //Item을 삭제하는 함수
{
    QModelIndex index = ui->tableView->currentIndex();
    if(index.isValid()) {
        //clientList.remove(clientModel->data(index.siblingAtColumn(0)).toInt());
        productModel->removeRow(index.row());
        productModel->select();
        ui->tableView->resizeColumnsToContents();
    }else {
        QMessageBox::warning(this, tr("Product Manager"), tr("No Item is selected"));
    }
     emit productRemove(index.row());
}

void ProductManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->tableView->mapToGlobal(pos);
    if(ui->tableView->indexAt(pos).isValid())
        menu->exec(globalPos);
}

void ProductManagerForm::on_searchPushButton_clicked() // 검색 버튼을 눌렀을 때 검색하는 함수
{
    searchModel->clear();
    int i = ui->searchComboBox->currentIndex(); //검색 combobox를 눌렀을 때 해당하는 index를 접근
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    QModelIndexList indexes = productModel->match(productModel->index(0, i), Qt::EditRole, ui->searchLineEdit->text(), -1, Qt::MatchFlags(flag));

    foreach(auto ix, indexes) {
        int id = productModel->data(ix.siblingAtColumn(0)).toInt(); //c->id();
        QString name = productModel->data(ix.siblingAtColumn(1)).toString();
        QString type = productModel->data(ix.siblingAtColumn(2)).toString();
        QString price = productModel->data(ix.siblingAtColumn(3)).toString();
        QString stock =  productModel->data(ix.siblingAtColumn(4)).toString();
        QStringList strings;
        strings << QString::number(id) << name << type << price<< stock;

        QList<QStandardItem *> items;
        for (int i = 0; i < 4; ++i) {
            items.append(new QStandardItem(strings.at(i)));
        }
        searchModel->appendRow(items);  //검색model에 item을 보낸다.
        productModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        productModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        productModel->setHeaderData(2, Qt::Horizontal, tr("type"));
        productModel->setHeaderData(3, Qt::Horizontal, tr("price"));
        productModel->setHeaderData(4, Qt::Horizontal, tr("stock"));
        ui->serchtableView->resizeColumnsToContents();
    }

}


void ProductManagerForm::on_addPushButton_clicked() // 검색버튼을 눌렀을 때 발생하는 함수
{
    QString name, type;
    int    price, stock;
    int id = makeId( );
    name = ui->ProductNameLineEdit->text(); //제품 이름을 보여준다
    type = ui->typeLineEdit->text(); // 제품 정보를 보여준다.
    price = ui->PriceLineEdit->text().toInt(); // 가격을 보여준다.
    stock = ui-> stockspinBox->text().toInt(); // 재로를 보여준다.

    QSqlDatabase db = QSqlDatabase::database("productConnection"); // product에 해당하는 db 에 연결

    if(name.length()) {
        QSqlQuery query(productModel->database());
        query.prepare("INSERT INTO product VALUES (:id, :name, :type, :price, :stock)");
        query.bindValue(":id", id);
        query.bindValue(":name", name);
        query.bindValue(":type", type);
        query.bindValue(":price", price);
        query.bindValue(":stock", stock);
        query.exec();
        productModel->select();
        ui->tableView->resizeColumnsToContents();
        emit productAdded(id, name, type, price, stock);
    }
}


void ProductManagerForm::on_modifyPushButton_clicked() // 수정버튼을 눌렀을 때 발생하는 함수
{
    QModelIndex index  = ui->tableView->currentIndex(); //tableview에 index담기
    if(index.isValid()) {
        //        int id = clientModel->data(index.siblingAtColumn(0)).toInt();
        QString name, type;
        int id ;
        int price, stock;
        id = ui->idLineEdit->text().toInt();
        name = ui->ProductNameLineEdit->text();
        type = ui->typeLineEdit->text();
        price = ui->PriceLineEdit->text().toInt();
        stock = ui->stockspinBox->text().toInt();

        productModel->setData(index.siblingAtColumn(0), id);
        productModel->setData(index.siblingAtColumn(1), name);
        productModel->setData(index.siblingAtColumn(2), type);
        productModel->setData(index.siblingAtColumn(3), price);
        productModel->setData(index.siblingAtColumn(4), stock);
        productModel->submit();

        ui->tableView->resizeColumnsToContents();
        emit productRemove(index.row());
         emit productAdded(id, name, type, price, stock);
    }
}

void ProductManagerForm::acceptProductInfo(int key) // product의 정보를 emit함수에 담아 보낼 함수
{
    QModelIndexList indexes = productModel->match(productModel->index(0, 0), Qt::EditRole, key, -1, Qt::MatchFlags(Qt::MatchCaseSensitive));

    foreach(auto index, indexes) {
        //    QModelIndex index = clientList[key];
        QString name = productModel->data(index.siblingAtColumn(1)).toString();
        QString type = productModel->data(index.siblingAtColumn(2)).toString();
        int price = productModel->data(index.siblingAtColumn(3)).toInt();
        int stock = productModel->data(index.siblingAtColumn(4)).toInt();
        emit sendProductInfo(name, type, price, stock);
    }
}


void ProductManagerForm::on_tableView_clicked(const QModelIndex &index) // tableview를 click할때 방생하는 함수
{
    int id = productModel->data(index.siblingAtColumn(0)).toInt(); // id를 보여준다
    QString name = productModel->data(index.siblingAtColumn(1)).toString(); // 이름을 보여준다.
    QString type = productModel->data(index.siblingAtColumn(2)).toString(); // 정보를 보여준다.
    int price = productModel->data(index.siblingAtColumn(3)).toInt(); // 가격을 보여준다.
    int stock = productModel->data(index.siblingAtColumn(4)).toInt(); // 재고를 보여준다

    ui->idLineEdit->setText(QString::number(id));
    ui->ProductNameLineEdit->setText(name);
    ui->typeLineEdit->setText(type);
    ui->PriceLineEdit->setText(QString::number(price));
    ui->stockspinBox->setValue(stock);
    ui->toolBox->setCurrentIndex(0);
}

