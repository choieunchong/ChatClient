#ifndef PRODUCTMANAGERFORM_H
#define PRODUCTMANAGERFORM_H

#include <QWidget>
#include <QHash>

class ProductItem;
class QMenu;
class QTreeWidgetItem;
class QSqlTableModel;
class QStandardItemModel;
namespace Ui {
class ProductManagerForm;
}

class ProductManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductManagerForm(QWidget *parent = nullptr);
    ~ProductManagerForm();
    void loadData();

private slots:
    /* QTreeWidget을 위한 슬롯 */
    void showContextMenu(const QPoint &);
    void removeItem();              /* QAction을 위한 슬롯 */
    void on_addPushButton_clicked();
    void on_modifyPushButton_clicked();
    void on_searchPushButton_clicked();
    void acceptProductInfo(int);
    void on_tableView_clicked(const QModelIndex &index);

signals:
    void productAdded(int, QString, QString, int, int);
    void sendProductInfo(QString, QString, int, int);
    void talktoorder(QMap<int, ProductItem*>*);
    void productRemove(int);
private:
    Ui::ProductManagerForm *ui;
    int makeId();
   // QMap<int, ProductItem*> ProductList;
    QMenu* menu;
    QSqlTableModel* productModel;
    QStandardItemModel *searchModel;
};

#endif // PRODUCTMANAGERFORM_H
