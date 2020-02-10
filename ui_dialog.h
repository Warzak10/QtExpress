/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLineEdit *projectNameLineEdit;
    QLabel *directoryLabel;
    QLabel *projectNameLabel;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *directoryLineEdit;
    QPushButton *browseButton;
    QCheckBox *checkBox;
    QLabel *projectTypeLabel;
    QComboBox *projectTypeCombo;
    QLabel *projectKitLabel;
    QComboBox *projectKitCombo;
    QHBoxLayout *horizontalLayout_2;
    QLabel *warningLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(480, 184);
        verticalLayout_2 = new QVBoxLayout(Dialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        projectNameLineEdit = new QLineEdit(Dialog);
        projectNameLineEdit->setObjectName(QString::fromUtf8("projectNameLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, projectNameLineEdit);

        directoryLabel = new QLabel(Dialog);
        directoryLabel->setObjectName(QString::fromUtf8("directoryLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, directoryLabel);

        projectNameLabel = new QLabel(Dialog);
        projectNameLabel->setObjectName(QString::fromUtf8("projectNameLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, projectNameLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        directoryLineEdit = new QLineEdit(Dialog);
        directoryLineEdit->setObjectName(QString::fromUtf8("directoryLineEdit"));

        horizontalLayout->addWidget(directoryLineEdit);

        browseButton = new QPushButton(Dialog);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));

        horizontalLayout->addWidget(browseButton);


        verticalLayout->addLayout(horizontalLayout);

        checkBox = new QCheckBox(Dialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);


        formLayout->setLayout(3, QFormLayout::FieldRole, verticalLayout);

        projectTypeLabel = new QLabel(Dialog);
        projectTypeLabel->setObjectName(QString::fromUtf8("projectTypeLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, projectTypeLabel);

        projectTypeCombo = new QComboBox(Dialog);
        projectTypeCombo->setObjectName(QString::fromUtf8("projectTypeCombo"));

        formLayout->setWidget(0, QFormLayout::FieldRole, projectTypeCombo);

        projectKitLabel = new QLabel(Dialog);
        projectKitLabel->setObjectName(QString::fromUtf8("projectKitLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, projectKitLabel);

        projectKitCombo = new QComboBox(Dialog);
        projectKitCombo->setObjectName(QString::fromUtf8("projectKitCombo"));

        formLayout->setWidget(1, QFormLayout::FieldRole, projectKitCombo);


        verticalLayout_2->addLayout(formLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        warningLabel = new QLabel(Dialog);
        warningLabel->setObjectName(QString::fromUtf8("warningLabel"));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(208, 208, 208, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        QBrush brush2(QColor(255, 0, 0, 128));
        brush2.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        QBrush brush3(QColor(164, 166, 168, 96));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        QBrush brush4(QColor(208, 208, 208, 128));
        brush4.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush4);
#endif
        warningLabel->setPalette(palette);

        horizontalLayout_2->addWidget(warningLabel);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        directoryLabel->setText(QCoreApplication::translate("Dialog", "Emplacement :", nullptr));
        projectNameLabel->setText(QCoreApplication::translate("Dialog", "Nom du projet :", nullptr));
        browseButton->setText(QCoreApplication::translate("Dialog", "Parcourir", nullptr));
        checkBox->setText(QCoreApplication::translate("Dialog", "Utiliser comme emplacement par defaut pour les projets", nullptr));
        projectTypeLabel->setText(QCoreApplication::translate("Dialog", "Type de projet :", nullptr));
        projectKitLabel->setText(QCoreApplication::translate("Dialog", "Kit \303\240 utiliser :", nullptr));
        warningLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
