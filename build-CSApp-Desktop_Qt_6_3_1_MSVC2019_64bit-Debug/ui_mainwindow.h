/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionClient;
    QAction *actionProduct;
    QAction *actionOrder;
    QAction *actionete;
    QAction *actionchat;
    QAction *actionServer;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QMdiArea *mdiArea;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(652, 412);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/quit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon);
        actionClient = new QAction(MainWindow);
        actionClient->setObjectName(QString::fromUtf8("actionClient"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/client.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClient->setIcon(icon1);
        actionProduct = new QAction(MainWindow);
        actionProduct->setObjectName(QString::fromUtf8("actionProduct"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/product.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionProduct->setIcon(icon2);
        actionOrder = new QAction(MainWindow);
        actionOrder->setObjectName(QString::fromUtf8("actionOrder"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/order.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOrder->setIcon(icon3);
        actionete = new QAction(MainWindow);
        actionete->setObjectName(QString::fromUtf8("actionete"));
        actionchat = new QAction(MainWindow);
        actionchat->setObjectName(QString::fromUtf8("actionchat"));
        actionServer = new QAction(MainWindow);
        actionServer->setObjectName(QString::fromUtf8("actionServer"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/chat.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionServer->setIcon(icon4);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        mdiArea = new QMdiArea(centralwidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
        mdiArea->setViewMode(QMdiArea::TabbedView);
        mdiArea->setDocumentMode(true);
        mdiArea->setTabsClosable(false);

        horizontalLayout->addWidget(mdiArea);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 652, 17));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::RightToolBarArea, toolBar);

        menubar->addAction(menu_File->menuAction());
        menu_File->addSeparator();
        menu_File->addAction(actionQuit);
        toolBar->addAction(actionClient);
        toolBar->addSeparator();
        toolBar->addAction(actionProduct);
        toolBar->addAction(actionOrder);
        toolBar->addAction(actionServer);
        toolBar->addAction(actionQuit);
        toolBar->addSeparator();

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, &QAction::triggered, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        actionClient->setText(QCoreApplication::translate("MainWindow", "Client Info", nullptr));
#if QT_CONFIG(shortcut)
        actionClient->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionProduct->setText(QCoreApplication::translate("MainWindow", "Product Info", nullptr));
#if QT_CONFIG(shortcut)
        actionProduct->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+2", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOrder->setText(QCoreApplication::translate("MainWindow", "Order Info", nullptr));
#if QT_CONFIG(shortcut)
        actionOrder->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+3", nullptr));
#endif // QT_CONFIG(shortcut)
        actionete->setText(QCoreApplication::translate("MainWindow", "ete", nullptr));
        actionchat->setText(QCoreApplication::translate("MainWindow", "chat", nullptr));
        actionServer->setText(QCoreApplication::translate("MainWindow", "Server", nullptr));
        menu_File->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
