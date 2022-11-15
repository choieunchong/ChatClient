/********************************************************************************
** Form generated from reading UI file 'productmanagerform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTMANAGERFORM_H
#define UI_PRODUCTMANAGERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProductManagerForm
{
public:
    QGridLayout *gridLayout_2;
    QSplitter *splitter_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSplitter *splitter;
    QTableView *tableView;
    QToolBox *toolBox;
    QWidget *inputPage;
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *idLabel;
    QLineEdit *idLineEdit;
    QLabel *nameLabel;
    QLineEdit *ProductNameLineEdit;
    QLabel *typeLabel;
    QLineEdit *typeLineEdit;
    QLabel *ProductPriceLabel;
    QLineEdit *PriceLineEdit;
    QLabel *Stocklabel;
    QSpinBox *stockspinBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addPushButton;
    QPushButton *modifyPushButton;
    QWidget *searchPage;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTableView *serchtableView;
    QHBoxLayout *horizontalLayout;
    QComboBox *searchComboBox;
    QLineEdit *searchLineEdit;
    QPushButton *searchPushButton;

    void setupUi(QWidget *ProductManagerForm)
    {
        if (ProductManagerForm->objectName().isEmpty())
            ProductManagerForm->setObjectName(QString::fromUtf8("ProductManagerForm"));
        ProductManagerForm->resize(551, 426);
        gridLayout_2 = new QGridLayout(ProductManagerForm);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        splitter_2 = new QSplitter(ProductManagerForm);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamilies({QString::fromUtf8("\355\234\264\353\250\274\353\221\245\352\267\274\355\227\244\353\223\234\353\235\274\354\235\270")});
        font.setPointSize(18);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        splitter_2->addWidget(layoutWidget);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tableView = new QTableView(splitter);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        splitter->addWidget(tableView);
        tableView->horizontalHeader()->setStretchLastSection(true);
        toolBox = new QToolBox(splitter);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        inputPage = new QWidget();
        inputPage->setObjectName(QString::fromUtf8("inputPage"));
        inputPage->setGeometry(QRect(0, 0, 276, 335));
        gridLayout = new QGridLayout(inputPage);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        idLabel = new QLabel(inputPage);
        idLabel->setObjectName(QString::fromUtf8("idLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, idLabel);

        idLineEdit = new QLineEdit(inputPage);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));
        idLineEdit->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, idLineEdit);

        nameLabel = new QLabel(inputPage);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, nameLabel);

        ProductNameLineEdit = new QLineEdit(inputPage);
        ProductNameLineEdit->setObjectName(QString::fromUtf8("ProductNameLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, ProductNameLineEdit);

        typeLabel = new QLabel(inputPage);
        typeLabel->setObjectName(QString::fromUtf8("typeLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, typeLabel);

        typeLineEdit = new QLineEdit(inputPage);
        typeLineEdit->setObjectName(QString::fromUtf8("typeLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, typeLineEdit);

        ProductPriceLabel = new QLabel(inputPage);
        ProductPriceLabel->setObjectName(QString::fromUtf8("ProductPriceLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, ProductPriceLabel);

        PriceLineEdit = new QLineEdit(inputPage);
        PriceLineEdit->setObjectName(QString::fromUtf8("PriceLineEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, PriceLineEdit);

        Stocklabel = new QLabel(inputPage);
        Stocklabel->setObjectName(QString::fromUtf8("Stocklabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, Stocklabel);

        stockspinBox = new QSpinBox(inputPage);
        stockspinBox->setObjectName(QString::fromUtf8("stockspinBox"));

        formLayout->setWidget(4, QFormLayout::FieldRole, stockspinBox);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 89, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        addPushButton = new QPushButton(inputPage);
        addPushButton->setObjectName(QString::fromUtf8("addPushButton"));

        horizontalLayout_3->addWidget(addPushButton);

        modifyPushButton = new QPushButton(inputPage);
        modifyPushButton->setObjectName(QString::fromUtf8("modifyPushButton"));

        horizontalLayout_3->addWidget(modifyPushButton);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        toolBox->addItem(inputPage, QString::fromUtf8("&Input"));
        searchPage = new QWidget();
        searchPage->setObjectName(QString::fromUtf8("searchPage"));
        searchPage->setGeometry(QRect(0, 0, 276, 335));
        gridLayout_3 = new QGridLayout(searchPage);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        serchtableView = new QTableView(searchPage);
        serchtableView->setObjectName(QString::fromUtf8("serchtableView"));
        serchtableView->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(serchtableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        searchComboBox = new QComboBox(searchPage);
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->setObjectName(QString::fromUtf8("searchComboBox"));

        horizontalLayout->addWidget(searchComboBox);

        searchLineEdit = new QLineEdit(searchPage);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));

        horizontalLayout->addWidget(searchLineEdit);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        searchPushButton = new QPushButton(searchPage);
        searchPushButton->setObjectName(QString::fromUtf8("searchPushButton"));

        verticalLayout_2->addWidget(searchPushButton);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);

        toolBox->addItem(searchPage, QString::fromUtf8("&Search"));
        splitter->addWidget(toolBox);
        splitter_2->addWidget(splitter);

        gridLayout_2->addWidget(splitter_2, 0, 0, 1, 1);

#if QT_CONFIG(shortcut)
        idLabel->setBuddy(idLineEdit);
        nameLabel->setBuddy(ProductNameLineEdit);
        typeLabel->setBuddy(typeLineEdit);
        ProductPriceLabel->setBuddy(PriceLineEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(ProductManagerForm);

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ProductManagerForm);
    } // setupUi

    void retranslateUi(QWidget *ProductManagerForm)
    {
        ProductManagerForm->setWindowTitle(QCoreApplication::translate("ProductManagerForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("ProductManagerForm", "Product", nullptr));
        idLabel->setText(QCoreApplication::translate("ProductManagerForm", "I&D", nullptr));
        nameLabel->setText(QCoreApplication::translate("ProductManagerForm", "&ProductName", nullptr));
        typeLabel->setText(QCoreApplication::translate("ProductManagerForm", "&Type", nullptr));
        ProductPriceLabel->setText(QCoreApplication::translate("ProductManagerForm", "&ProductPrice", nullptr));
        Stocklabel->setText(QCoreApplication::translate("ProductManagerForm", "&Stock", nullptr));
        addPushButton->setText(QCoreApplication::translate("ProductManagerForm", "&Add", nullptr));
        modifyPushButton->setText(QCoreApplication::translate("ProductManagerForm", "&Modify", nullptr));
        toolBox->setItemText(toolBox->indexOf(inputPage), QCoreApplication::translate("ProductManagerForm", "&Input", nullptr));
        searchComboBox->setItemText(0, QCoreApplication::translate("ProductManagerForm", "ID", nullptr));
        searchComboBox->setItemText(1, QCoreApplication::translate("ProductManagerForm", "Name", nullptr));
        searchComboBox->setItemText(2, QCoreApplication::translate("ProductManagerForm", "Type", nullptr));
        searchComboBox->setItemText(3, QCoreApplication::translate("ProductManagerForm", "Price", nullptr));
        searchComboBox->setItemText(4, QCoreApplication::translate("ProductManagerForm", "Stock", nullptr));

        searchPushButton->setText(QCoreApplication::translate("ProductManagerForm", "S&earch", nullptr));
        toolBox->setItemText(toolBox->indexOf(searchPage), QCoreApplication::translate("ProductManagerForm", "&Search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProductManagerForm: public Ui_ProductManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTMANAGERFORM_H
