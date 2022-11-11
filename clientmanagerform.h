#ifndef CLIENTMANAGERFORM_H
#define CLIENTMANAGERFORM_H

#include <QWidget>
#include <QHash>

class ClientItem;
class QMenu;
class QTreeWidgetItem;
class QSqlTableModel;
class QSqlDatabase;
class QStandardItemModel;

namespace Ui {
class ClientManagerForm;
}

class ClientManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientManagerForm(QWidget *parent = nullptr);
    ~ClientManagerForm();
    void loadData();

private slots:
    /* QTreeWidget을 위한 슬롯 */

    void showContextMenu(const QPoint &);
    void removeItem();              /* QAction을 위한 슬롯 */
    void on_addPushButton_clicked(); // 추가버튼 함수
    void on_modifyPushButton_clicked();
    void on_searchPushButton_clicked();
//    void addClient(ClientItem*);
    void acceptClientInfo(int);
    void on_tableView_clicked(const QModelIndex &index);

signals:
    void clientAdded(int,QString, QString, QString);
    void talktoorder(QMap<int, ClientItem*>*);
    void tcpClient(int, QString, QString, QString);
    void sendClientInfo(QString, QString, QString);
private:
    int makeId();

  //  QMap<int, ClientItem*> clientList;
    Ui::ClientManagerForm *ui;
    QMenu* menu;
    QSqlTableModel* clientModel;
    QStandardItemModel* searchModel;
};

#endif // CLIENTMANAGERFORM_H
