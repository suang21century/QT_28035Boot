/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QPushButton *pushButton_cmopen;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *textEdit;
    QPushButton *pushButton_readhex;
    QPushButton *pushButton_sendhex;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(150, 10, 231, 111));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        comboBox = new QComboBox(frame);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(80, 10, 91, 22));
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(80, 50, 91, 20));
        pushButton_cmopen = new QPushButton(frame);
        pushButton_cmopen->setObjectName(QStringLiteral("pushButton_cmopen"));
        pushButton_cmopen->setGeometry(QRect(60, 80, 75, 23));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 10, 54, 12));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 50, 54, 12));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(20, 20, 104, 71));
        pushButton_readhex = new QPushButton(centralWidget);
        pushButton_readhex->setObjectName(QStringLiteral("pushButton_readhex"));
        pushButton_readhex->setGeometry(QRect(30, 130, 81, 23));
        pushButton_sendhex = new QPushButton(centralWidget);
        pushButton_sendhex->setObjectName(QStringLiteral("pushButton_sendhex"));
        pushButton_sendhex->setGeometry(QRect(30, 170, 81, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("MainWindow", "115200", Q_NULLPTR));
        pushButton_cmopen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\267\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207\357\274\232", Q_NULLPTR));
        pushButton_readhex->setText(QApplication::translate("MainWindow", "\350\257\273\345\217\226hex\346\226\207\344\273\266", Q_NULLPTR));
        pushButton_sendhex->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201hex\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
