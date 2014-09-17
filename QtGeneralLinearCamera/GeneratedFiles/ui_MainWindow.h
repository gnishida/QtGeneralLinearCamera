/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Wed Sep 17 15:13:07 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionExit;
    QAction *actionOpen;
    QAction *actionCameraPerspective;
    QAction *actionCameraOrthogonal;
    QAction *actionCameraPushbroom;
    QAction *actionCameraBilinear;
    QAction *actionCameraXSlit;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuCamera;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(512, 512);
        MainWindowClass->setMaximumSize(QSize(512, 512));
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionOpen = new QAction(MainWindowClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionCameraPerspective = new QAction(MainWindowClass);
        actionCameraPerspective->setObjectName(QString::fromUtf8("actionCameraPerspective"));
        actionCameraOrthogonal = new QAction(MainWindowClass);
        actionCameraOrthogonal->setObjectName(QString::fromUtf8("actionCameraOrthogonal"));
        actionCameraPushbroom = new QAction(MainWindowClass);
        actionCameraPushbroom->setObjectName(QString::fromUtf8("actionCameraPushbroom"));
        actionCameraBilinear = new QAction(MainWindowClass);
        actionCameraBilinear->setObjectName(QString::fromUtf8("actionCameraBilinear"));
        actionCameraXSlit = new QAction(MainWindowClass);
        actionCameraXSlit->setObjectName(QString::fromUtf8("actionCameraXSlit"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 512, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuCamera = new QMenu(menuBar);
        menuCamera->setObjectName(QString::fromUtf8("menuCamera"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuCamera->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuCamera->addAction(actionCameraPerspective);
        menuCamera->addAction(actionCameraOrthogonal);
        menuCamera->addAction(actionCameraPushbroom);
        menuCamera->addAction(actionCameraBilinear);
        menuCamera->addAction(actionCameraXSlit);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindowClass", "Open", 0, QApplication::UnicodeUTF8));
        actionCameraPerspective->setText(QApplication::translate("MainWindowClass", "Perspective", 0, QApplication::UnicodeUTF8));
        actionCameraOrthogonal->setText(QApplication::translate("MainWindowClass", "Orthogonal", 0, QApplication::UnicodeUTF8));
        actionCameraPushbroom->setText(QApplication::translate("MainWindowClass", "Pushbroom", 0, QApplication::UnicodeUTF8));
        actionCameraBilinear->setText(QApplication::translate("MainWindowClass", "Bilinear", 0, QApplication::UnicodeUTF8));
        actionCameraXSlit->setText(QApplication::translate("MainWindowClass", "XSlit", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindowClass", "File", 0, QApplication::UnicodeUTF8));
        menuCamera->setTitle(QApplication::translate("MainWindowClass", "Camera", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
