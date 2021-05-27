#pragma once

#include <QQmlApplicationEngine>
#include <QQuickWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "inputdialog.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
   public:
    QCPItemText *textLabel;
    QCPAxisRect *wideAxisOne;
    QCPAxisRect *wideAxisTwo;
    QCPAxisRect *wideAxisThree;
    QCPGraph *mainGraphOne;
    QCPGraph *mainGraphTwo;
    QCPGraph *mainGraphThree;

    QWidget *centralWidget;
    QFrame *statusLine;
    QLabel *statusLabel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *plotsLayout;
    QCustomPlot *rightPlot;
    QCustomPlot *leftPlot;
    QHBoxLayout *panelLayout;
    QVBoxLayout *dataLayout;
    QHBoxLayout *miscLayout;
    QVBoxLayout *peaksLayout;
    QLabel *peaksTitle;
    QGridLayout *peaksData;
    QHBoxLayout *peakOneFreq;
    QLabel *peakOneFreqValue;
    QLabel *peakOneFreqUnit;
    QHBoxLayout *peakTwoFreq;
    QLabel *peakTwoFreqValue;
    QLabel *peakTwoFreqUnit;
    QHBoxLayout *peakThreeFreq;
    QLabel *peakThreeFreqValue;
    QLabel *peakThreeFreqUnit;
    QHBoxLayout *peakOnePower;
    QLabel *peakOnePowerValue;
    QLabel *peakOnePowerUnit;
    QHBoxLayout *peakTwoPower;
    QLabel *peakTwoPowerValue;
    QLabel *peakTwoPowerUnit;
    QHBoxLayout *peakThreePower;
    QLabel *peakThreePowerValue;
    QLabel *peakThreePowerUnit;
    QVBoxLayout *beaconLayout;
    QPushButton *selectBeacon;
    InputDialog *inputBeaconWidget;
    QPushButton *beaconFound;
    QVBoxLayout *logLayout;
    QPushButton *preblastLog;
    QPushButton *postblastLog;
    QHBoxLayout *saveLayout;
    QPushButton *startLog;
    QPushButton *saveLog;
    QPushButton *closeShutdown;
    QVBoxLayout *selectLayout;
    QPushButton *selectDisplayFreq;
    QPushButton *selectOneFreq;
    QPushButton *selectTwoFreq;
    QPushButton *selectThreeFreq;

    void setupUi(QMainWindow *MainWindow) {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 800);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1280, 800));
        MainWindow->setStyleSheet(QString::fromUtf8(
            "QWidget#centralWidget {\n"
            "	background: #ddd;\n"
            "}\n"
            "QWidget#inputBeaconWidget {\n"
            "   background: #ddd;\n"
            "   border-radius: 10px;\n"
            "   border-style: solid;\n"
            "   border-width: 2px;\n"
            "   border-radius: 7px;\n"
            "   border-color: black;\n"
            "}\n"
            "\n"
            "QLabel {\n"
            "	color: #333;\n"
            "}\n"
            "\n"
            "QPushButton {\n"
            "    color: #111;\n"
            "    border-radius: 10px;\n"
            "    border-style: outset;\n"
            "    border-color: black;\n"
            "    background: #888;\n"
            "   font: 20px 'Ubuntu';\n"
            "   font-weight: bold;\n"
            "}\n"
            "\n"
            "QPushButton:hover {\n"
            "    background: qradialgradient(\n"
            "        cx: 0.3, cy: -0.4, fx: 0.3, fy: 0.4,\n"
            "        radius: 1.35, stop: 0 #fff, stop: 1 #bbb\n"
            "    );\n"
            "}\n"
            "\n"
            "QPushButton:pressed {\n"
            "    border-style: inset;\n"
            "    background: qradialgradient(\n"
            "        cx: 0.4, cy: -0.1, fx: 0.4, fy: 0.1,\n"
            "        radius: 1.35, stop: 0 #fff, stop: 1 #ddd\n"
            "    );\n"
            "}\n"
            "\n"
            "QLabel {\n"
            "	border: 1px solid #000;\n"
            "	font: 24px 'Ubuntu';\n"
            "	font-weight: bold;\n"
            "}\n"
            "\n"
            "QLabel#peaksTitle {\n"
            "	font-size: 30px;\n"
            "}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(1280, 800));
        centralWidget->setMaximumSize(QSize(1280, 800));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 1260, 780));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        plotsLayout = new QHBoxLayout();
        plotsLayout->setSpacing(10);
        plotsLayout->setObjectName(QString::fromUtf8("plotsLayout"));
        plotsLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        plotsLayout->setContentsMargins(10, 10, 10, 10);
        rightPlot = new QCustomPlot(layoutWidget);
        rightPlot->setObjectName(QString::fromUtf8("rightPlot"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(rightPlot->sizePolicy().hasHeightForWidth());
        rightPlot->setSizePolicy(sizePolicy1);
        rightPlot->setMinimumSize(QSize(0, 0));
        rightPlot->setMaximumSize(QSize(16777215, 16777215));
        rightPlot->setAutoFillBackground(false);

        plotsLayout->addWidget(rightPlot);

        leftPlot = new QCustomPlot(layoutWidget);
        leftPlot->setObjectName(QString::fromUtf8("leftPlot"));
        leftPlot->setEnabled(true);
        sizePolicy1.setHeightForWidth(leftPlot->sizePolicy().hasHeightForWidth());
        leftPlot->setSizePolicy(sizePolicy1);
        leftPlot->setMinimumSize(QSize(0, 0));
        leftPlot->setMaximumSize(QSize(16777215, 16777215));
        leftPlot->setAutoFillBackground(false);

        plotsLayout->addWidget(leftPlot);

        plotsLayout->setStretch(0, 3);
        plotsLayout->setStretch(1, 2);

        verticalLayout->addLayout(plotsLayout);

        panelLayout = new QHBoxLayout();
        panelLayout->setSpacing(10);
        panelLayout->setObjectName(QString::fromUtf8("panelLayout"));
        panelLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        panelLayout->setContentsMargins(10, 10, 10, 10);
        dataLayout = new QVBoxLayout();
        dataLayout->setObjectName(QString::fromUtf8("dataLayout"));
        miscLayout = new QHBoxLayout();
        miscLayout->setObjectName(QString::fromUtf8("miscLayout"));
        peaksLayout = new QVBoxLayout();
        peaksLayout->setSpacing(0);
        peaksLayout->setObjectName(QString::fromUtf8("peaksLayout"));
        peaksLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        peaksLayout->setContentsMargins(10, 10, 10, 10);
        peaksTitle = new QLabel(layoutWidget);
        peaksTitle->setObjectName(QString::fromUtf8("peaksTitle"));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu"));
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        peaksTitle->setFont(font);
        peaksTitle->setAlignment(Qt::AlignCenter);

        peaksLayout->addWidget(peaksTitle);

        peaksData = new QGridLayout();
        peaksData->setSpacing(0);
        peaksData->setObjectName(QString::fromUtf8("peaksData"));
        peaksData->setSizeConstraint(QLayout::SetDefaultConstraint);
        peaksData->setContentsMargins(0, 0, 0, 0);
        peakOneFreq = new QHBoxLayout();
        peakOneFreq->setSpacing(0);
        peakOneFreq->setObjectName(QString::fromUtf8("peakOneFreq"));
        peakOneFreq->setContentsMargins(0, 0, 0, 0);
        peakOneFreqValue = new QLabel(layoutWidget);
        peakOneFreqValue->setObjectName(QString::fromUtf8("peakOneFreqValue"));
        peakOneFreqValue->setFont(font);
        peakOneFreqValue->setAutoFillBackground(true);
        peakOneFreqValue->setScaledContents(false);
        peakOneFreqValue->setAlignment(Qt::AlignCenter);
        peakOneFreqValue->setStyleSheet(QString::fromUtf8("QLabel {background-color: white}"));

        peakOneFreq->addWidget(peakOneFreqValue);

        peakOneFreqUnit = new QLabel(layoutWidget);
        peakOneFreqUnit->setObjectName(QString::fromUtf8("peakOneFreqUnit"));
        peakOneFreqUnit->setFont(font);
        peakOneFreqUnit->setScaledContents(false);
        peakOneFreqUnit->setAlignment(Qt::AlignCenter);

        peakOneFreq->addWidget(peakOneFreqUnit);

        peakOneFreq->setStretch(0, 2);
        peakOneFreq->setStretch(1, 1);

        peaksData->addLayout(peakOneFreq, 0, 0, 1, 1);

        peakTwoFreq = new QHBoxLayout();
        peakTwoFreq->setSpacing(0);
        peakTwoFreq->setObjectName(QString::fromUtf8("peakTwoFreq"));
        peakTwoFreq->setContentsMargins(0, 0, 0, 0);
        peakTwoFreqValue = new QLabel(layoutWidget);
        peakTwoFreqValue->setObjectName(QString::fromUtf8("peakTwoFreqValue"));
        peakTwoFreqValue->setFont(font);
        peakTwoFreqValue->setAutoFillBackground(true);
        peakTwoFreqValue->setScaledContents(false);
        peakTwoFreqValue->setAlignment(Qt::AlignCenter);
        peakTwoFreqValue->setStyleSheet(QString::fromUtf8("QLabel {background-color: white}"));

        peakTwoFreq->addWidget(peakTwoFreqValue);

        peakTwoFreqUnit = new QLabel(layoutWidget);
        peakTwoFreqUnit->setObjectName(QString::fromUtf8("peakTwoFreqUnit"));
        peakTwoFreqUnit->setFont(font);
        peakTwoFreqUnit->setScaledContents(false);
        peakTwoFreqUnit->setAlignment(Qt::AlignCenter);

        peakTwoFreq->addWidget(peakTwoFreqUnit);

        peakTwoFreq->setStretch(0, 2);
        peakTwoFreq->setStretch(1, 1);

        peaksData->addLayout(peakTwoFreq, 1, 0, 1, 1);

        peakThreeFreq = new QHBoxLayout();
        peakThreeFreq->setSpacing(0);
        peakThreeFreq->setObjectName(QString::fromUtf8("peakThreeFreq"));
        peakThreeFreq->setContentsMargins(0, 0, 0, 0);
        peakThreeFreqValue = new QLabel(layoutWidget);
        peakThreeFreqValue->setObjectName(QString::fromUtf8("peakThreeFreqValue"));
        peakThreeFreqValue->setFont(font);
        peakThreeFreqValue->setAutoFillBackground(true);
        peakThreeFreqValue->setScaledContents(false);
        peakThreeFreqValue->setAlignment(Qt::AlignCenter);
        peakThreeFreqValue->setStyleSheet(QString::fromUtf8("QLabel {background-color: white}"));

        peakThreeFreq->addWidget(peakThreeFreqValue);

        peakThreeFreqUnit = new QLabel(layoutWidget);
        peakThreeFreqUnit->setObjectName(QString::fromUtf8("peakThreeFreqUnit"));
        peakThreeFreqUnit->setFont(font);
        peakThreeFreqUnit->setScaledContents(false);
        peakThreeFreqUnit->setAlignment(Qt::AlignCenter);

        peakThreeFreq->addWidget(peakThreeFreqUnit);

        peakThreeFreq->setStretch(0, 2);
        peakThreeFreq->setStretch(1, 1);

        peaksData->addLayout(peakThreeFreq, 2, 0, 1, 1);

        peakOnePower = new QHBoxLayout();
        peakOnePower->setSpacing(0);
        peakOnePower->setObjectName(QString::fromUtf8("peakOnePower"));
        peakOnePower->setContentsMargins(0, 0, 0, 0);
        peakOnePowerValue = new QLabel(layoutWidget);
        peakOnePowerValue->setObjectName(QString::fromUtf8("peakOnePowerValue"));
        peakOnePowerValue->setFont(font);
        peakOnePowerValue->setAutoFillBackground(true);
        peakOnePowerValue->setScaledContents(false);
        peakOnePowerValue->setAlignment(Qt::AlignCenter);
        peakOnePowerValue->setStyleSheet(QString::fromUtf8("QLabel {background-color: white}"));

        peakOnePower->addWidget(peakOnePowerValue);

        peakOnePowerUnit = new QLabel(layoutWidget);
        peakOnePowerUnit->setObjectName(QString::fromUtf8("peakOnePowerUnit"));
        peakOnePowerUnit->setFont(font);
        peakOnePowerUnit->setScaledContents(false);
        peakOnePowerUnit->setAlignment(Qt::AlignCenter);

        peakOnePower->addWidget(peakOnePowerUnit);

        peakOnePower->setStretch(0, 2);
        peakOnePower->setStretch(1, 1);

        peaksData->addLayout(peakOnePower, 0, 1, 1, 1);

        peakTwoPower = new QHBoxLayout();
        peakTwoPower->setSpacing(0);
        peakTwoPower->setObjectName(QString::fromUtf8("peakTwoPower"));
        peakTwoPower->setContentsMargins(0, 0, 0, 0);
        peakTwoPowerValue = new QLabel(layoutWidget);
        peakTwoPowerValue->setObjectName(QString::fromUtf8("peakTwoPowerValue"));
        peakTwoPowerValue->setFont(font);
        peakTwoPowerValue->setAutoFillBackground(true);
        peakTwoPowerValue->setScaledContents(false);
        peakTwoPowerValue->setAlignment(Qt::AlignCenter);
        peakTwoPowerValue->setStyleSheet(QString::fromUtf8("QLabel {background-color: white}"));

        peakTwoPower->addWidget(peakTwoPowerValue);

        peakTwoPowerUnit = new QLabel(layoutWidget);
        peakTwoPowerUnit->setObjectName(QString::fromUtf8("peakTwoPowerUnit"));
        peakTwoPowerUnit->setFont(font);
        peakTwoPowerUnit->setScaledContents(false);
        peakTwoPowerUnit->setAlignment(Qt::AlignCenter);

        peakTwoPower->addWidget(peakTwoPowerUnit);

        peakTwoPower->setStretch(0, 2);
        peakTwoPower->setStretch(1, 1);

        peaksData->addLayout(peakTwoPower, 1, 1, 1, 1);

        peakThreePower = new QHBoxLayout();
        peakThreePower->setSpacing(0);
        peakThreePower->setObjectName(QString::fromUtf8("peakThreePower"));
        peakThreePower->setContentsMargins(0, 0, 0, 0);
        peakThreePowerValue = new QLabel(layoutWidget);
        peakThreePowerValue->setObjectName(QString::fromUtf8("peakThreePowerValue"));
        peakThreePowerValue->setFont(font);
        peakThreePowerValue->setAutoFillBackground(true);
        peakThreePowerValue->setScaledContents(false);
        peakThreePowerValue->setAlignment(Qt::AlignCenter);
        peakThreePowerValue->setStyleSheet(QString::fromUtf8("QLabel {background-color: white}"));

        peakThreePower->addWidget(peakThreePowerValue);

        peakThreePowerUnit = new QLabel(layoutWidget);
        peakThreePowerUnit->setObjectName(QString::fromUtf8("peakThreePowerUnit"));
        peakThreePowerUnit->setFont(font);
        peakThreePowerUnit->setScaledContents(false);
        peakThreePowerUnit->setAlignment(Qt::AlignCenter);

        peakThreePower->addWidget(peakThreePowerUnit);

        peakThreePower->setStretch(0, 2);
        peakThreePower->setStretch(1, 1);

        peaksData->addLayout(peakThreePower, 2, 1, 1, 1);

        peaksData->setRowStretch(0, 1);
        peaksData->setRowStretch(1, 1);
        peaksData->setRowStretch(2, 1);
        peaksData->setColumnStretch(0, 1);
        peaksData->setColumnStretch(1, 1);

        peaksLayout->addLayout(peaksData);

        peaksLayout->setStretch(0, 1);
        peaksLayout->setStretch(1, 2);

        miscLayout->addLayout(peaksLayout);

        beaconLayout = new QVBoxLayout();
        beaconLayout->setObjectName(QString::fromUtf8("beaconLayout"));
        beaconLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        beaconLayout->setContentsMargins(10, 10, 10, 10);
        selectBeacon = new QPushButton(layoutWidget);
        selectBeacon->setObjectName(QString::fromUtf8("selectBeacon"));
        sizePolicy1.setHeightForWidth(selectBeacon->sizePolicy().hasHeightForWidth());
        selectBeacon->setSizePolicy(sizePolicy1);
        selectBeacon->setFont(font);

        beaconLayout->addWidget(selectBeacon);

        inputBeaconWidget = new InputDialog(MainWindow);

        beaconFound = new QPushButton(layoutWidget);
        beaconFound->setObjectName(QString::fromUtf8("beaconFound"));
        sizePolicy1.setHeightForWidth(beaconFound->sizePolicy().hasHeightForWidth());
        beaconFound->setSizePolicy(sizePolicy1);
        beaconFound->setFont(font);

        beaconLayout->addWidget(beaconFound);

        beaconLayout->setStretch(0, 1);
        beaconLayout->setStretch(1, 1);

        miscLayout->addLayout(beaconLayout);

        logLayout = new QVBoxLayout();
        logLayout->setObjectName(QString::fromUtf8("logLayout"));
        logLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        logLayout->setContentsMargins(10, 10, 10, 10);
        preblastLog = new QPushButton(layoutWidget);
        preblastLog->setObjectName(QString::fromUtf8("preblastLog"));
        sizePolicy1.setHeightForWidth(preblastLog->sizePolicy().hasHeightForWidth());
        preblastLog->setSizePolicy(sizePolicy1);
        preblastLog->setFont(font);

        logLayout->addWidget(preblastLog);

        postblastLog = new QPushButton(layoutWidget);
        postblastLog->setObjectName(QString::fromUtf8("postblastLog"));
        sizePolicy1.setHeightForWidth(postblastLog->sizePolicy().hasHeightForWidth());
        postblastLog->setSizePolicy(sizePolicy1);
        postblastLog->setFont(font);

        logLayout->addWidget(postblastLog);

        logLayout->setStretch(0, 1);
        logLayout->setStretch(1, 1);

        miscLayout->addLayout(logLayout);

        miscLayout->setStretch(0, 2);
        miscLayout->setStretch(1, 1);
        miscLayout->setStretch(2, 1);

        dataLayout->addLayout(miscLayout);

        saveLayout = new QHBoxLayout();
        saveLayout->setObjectName(QString::fromUtf8("saveLayout"));
        saveLayout->setContentsMargins(10, 10, 10, 10);
        startLog = new QPushButton(layoutWidget);
        startLog->setObjectName(QString::fromUtf8("startLog"));
        sizePolicy1.setHeightForWidth(startLog->sizePolicy().hasHeightForWidth());
        startLog->setSizePolicy(sizePolicy1);
        startLog->setFont(font);
        startLog->setCheckable(false);

        saveLayout->addWidget(startLog);

        saveLog = new QPushButton(layoutWidget);
        saveLog->setObjectName(QString::fromUtf8("saveLog"));
        sizePolicy1.setHeightForWidth(saveLog->sizePolicy().hasHeightForWidth());
        saveLog->setSizePolicy(sizePolicy1);
        saveLog->setFont(font);

        saveLayout->addWidget(saveLog);

        closeShutdown = new QPushButton(layoutWidget);
        closeShutdown->setObjectName(QString::fromUtf8("closeShutdown"));
        sizePolicy1.setHeightForWidth(closeShutdown->sizePolicy().hasHeightForWidth());
        closeShutdown->setSizePolicy(sizePolicy1);
        closeShutdown->setFont(font);

        saveLayout->addWidget(closeShutdown);

        dataLayout->addLayout(saveLayout);

        dataLayout->setStretch(0, 3);
        dataLayout->setStretch(1, 1);

        panelLayout->addLayout(dataLayout);

        selectLayout = new QVBoxLayout();
        selectLayout->setSpacing(10);
        selectLayout->setObjectName(QString::fromUtf8("selectLayout"));
        selectLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        selectLayout->setContentsMargins(10, 10, 10, 10);
        selectDisplayFreq = new QPushButton(layoutWidget);
        selectDisplayFreq->setObjectName(QString::fromUtf8("selectDisplayFreq"));
        sizePolicy1.setHeightForWidth(selectDisplayFreq->sizePolicy().hasHeightForWidth());
        selectDisplayFreq->setSizePolicy(sizePolicy1);
        selectDisplayFreq->setFont(font);
        selectDisplayFreq->setStyleSheet(QString::fromUtf8(""));
        selectDisplayFreq->setFlat(false);
        selectDisplayFreq->setEnabled(false);

        selectLayout->addWidget(selectDisplayFreq);

        selectOneFreq = new QPushButton(layoutWidget);
        selectOneFreq->setObjectName(QString::fromUtf8("selectOneFreq"));
        sizePolicy1.setHeightForWidth(selectOneFreq->sizePolicy().hasHeightForWidth());
        selectOneFreq->setSizePolicy(sizePolicy1);
        selectOneFreq->setFont(font);

        selectLayout->addWidget(selectOneFreq);

        selectTwoFreq = new QPushButton(layoutWidget);
        selectTwoFreq->setObjectName(QString::fromUtf8("selectTwoFreq"));
        sizePolicy1.setHeightForWidth(selectTwoFreq->sizePolicy().hasHeightForWidth());
        selectTwoFreq->setSizePolicy(sizePolicy1);
        selectTwoFreq->setFont(font);

        selectLayout->addWidget(selectTwoFreq);

        selectThreeFreq = new QPushButton(layoutWidget);
        selectThreeFreq->setObjectName(QString::fromUtf8("selectThreeFreq"));
        sizePolicy1.setHeightForWidth(selectThreeFreq->sizePolicy().hasHeightForWidth());
        selectThreeFreq->setSizePolicy(sizePolicy1);
        selectThreeFreq->setFont(font);

        selectLayout->addWidget(selectThreeFreq);

        panelLayout->addLayout(selectLayout);

        panelLayout->setStretch(0, 4);
        panelLayout->setStretch(1, 1);

        verticalLayout->addLayout(panelLayout);

        statusLine = new QFrame(layoutWidget);
        statusLine->setObjectName(QString::fromUtf8("statusLine"));
        statusLine->setFrameShape(QFrame::HLine);
        statusLine->setFrameShadow(QFrame::Sunken);
        statusLine->setLineWidth(1280);
        statusLabel = new QLabel(layoutWidget);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(10, 710, 1260, 80));

        verticalLayout->addWidget(statusLine);
        verticalLayout->addWidget(statusLabel);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    }  // setupUi

    void retranslateUi(QMainWindow *MainWindow) {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Status: Inicializando", nullptr));
        peaksTitle->setText(QCoreApplication::translate("MainWindow", "Peaks Detectados", nullptr));
        peakOneFreqValue->setText(QCoreApplication::translate("MainWindow", "", nullptr));
        peakOneFreqUnit->setText(QCoreApplication::translate("MainWindow", "kHz", nullptr));
        peakTwoFreqValue->setText(QCoreApplication::translate("MainWindow", "", nullptr));
        peakTwoFreqUnit->setText(QCoreApplication::translate("MainWindow", "kHz", nullptr));
        peakThreeFreqValue->setText(QCoreApplication::translate("MainWindow", "", nullptr));
        peakThreeFreqUnit->setText(QCoreApplication::translate("MainWindow", "kHz", nullptr));
        peakOnePowerValue->setText(QCoreApplication::translate("MainWindow", "", nullptr));
        peakOnePowerUnit->setText(QCoreApplication::translate("MainWindow", "dBFS", nullptr));
        peakTwoPowerValue->setText(QCoreApplication::translate("MainWindow", "", nullptr));
        peakTwoPowerUnit->setText(QCoreApplication::translate("MainWindow", "dBFS", nullptr));
        peakThreePowerValue->setText(QCoreApplication::translate("MainWindow", "", nullptr));
        peakThreePowerUnit->setText(QCoreApplication::translate("MainWindow", "dBFS", nullptr));
        selectBeacon->setText(QCoreApplication::translate("MainWindow", "Seleccionar\nBeacon", nullptr));
        beaconFound->setText(QCoreApplication::translate("MainWindow", "Beacon\nEncontrado", nullptr));
        preblastLog->setText(QCoreApplication::translate("MainWindow", "Registro\nPre-Estallido", nullptr));
        postblastLog->setText(QCoreApplication::translate("MainWindow", "Registro\nPost-Estallido", nullptr));
        startLog->setText(QCoreApplication::translate("MainWindow", "Empezar Nuevo\nRegistro", nullptr));
        saveLog->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        closeShutdown->setText(QCoreApplication::translate("MainWindow", "Cerrar y Apagar", nullptr));
        selectDisplayFreq->setText(QCoreApplication::translate("MainWindow", "Seleccionar\nFrecuencia", nullptr));
        selectOneFreq->setText(QCoreApplication::translate("MainWindow", "11 kHz", nullptr));
        selectTwoFreq->setText(QCoreApplication::translate("MainWindow", "12 kHz", nullptr));
        selectThreeFreq->setText(QCoreApplication::translate("MainWindow", "13 kHz", nullptr));

        inputBeaconWidget->inputBeaconTopLabel->setText(QCoreApplication::translate("MainWindow", "Ingreso Nuevo Beacon", nullptr));
        inputBeaconWidget->inputBeaconOneLabel->setText(QCoreApplication::translate("MainWindow", "Distancia Beacon [metros]", nullptr));
        inputBeaconWidget->inputBeaconAccept->setText(QCoreApplication::translate("MainWindow", "Aceptar", nullptr));
        inputBeaconWidget->inputBeaconCancel->setText(QCoreApplication::translate("MainWindow", "Cancelar", nullptr));
    }
};

namespace Ui {
class MainWindow : public Ui_MainWindow {
};
}  // namespace Ui

QT_END_NAMESPACE
