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
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 800);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1280, 800));
        MainWindow->setStyleSheet(
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
            "}");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(1280, 800));
        centralWidget->setMaximumSize(QSize(1280, 800));
        centralWidget->setStyleSheet(
            "#centralWidget{"
            "background: #ddd;}");
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 1260, 780));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        plotsLayout = new QHBoxLayout();
        plotsLayout->setSpacing(10);
        plotsLayout->setObjectName("plotsLayout");
        plotsLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        plotsLayout->setContentsMargins(10, 10, 10, 10);
        rightPlot = new QCustomPlot(layoutWidget);
        rightPlot->setObjectName("rightPlot");
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
        leftPlot->setObjectName("leftPlot");
        leftPlot->setEnabled(true);
        sizePolicy1.setHeightForWidth(leftPlot->sizePolicy().hasHeightForWidth());
        leftPlot->setSizePolicy(sizePolicy1);
        leftPlot->setMinimumSize(QSize(0, 0));
        leftPlot->setMaximumSize(QSize(16777215, 16777215));
        leftPlot->setAutoFillBackground(false);

        plotsLayout->addWidget(leftPlot);

        plotsLayout->setStretch(0, 2);
        plotsLayout->setStretch(1, 3);

        verticalLayout->addLayout(plotsLayout);

        panelLayout = new QHBoxLayout();
        panelLayout->setSpacing(10);
        panelLayout->setObjectName("panelLayout");
        panelLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        panelLayout->setContentsMargins(10, 10, 10, 10);
        dataLayout = new QVBoxLayout();
        dataLayout->setObjectName("dataLayout");
        miscLayout = new QHBoxLayout();
        miscLayout->setObjectName("miscLayout");
        peaksLayout = new QVBoxLayout();
        peaksLayout->setSpacing(0);
        peaksLayout->setObjectName("peaksLayout");
        peaksLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        peaksLayout->setContentsMargins(10, 10, 10, 10);
        peaksTitle = new QLabel(layoutWidget);
        peaksTitle->setObjectName("peaksTitle");
        peaksTitle->setAlignment(Qt::AlignCenter);
        peaksTitle->setStyleSheet(
            "border: 1px solid #000;"
            "font: 30px 'Ubuntu';"
            "font-weight: bold;");

        peaksLayout->addWidget(peaksTitle);

        peaksData = new QGridLayout();
        peaksData->setSpacing(0);
        peaksData->setObjectName("peaksData");
        peaksData->setSizeConstraint(QLayout::SetDefaultConstraint);
        peaksData->setContentsMargins(0, 0, 0, 0);
        peakOneFreq = new QHBoxLayout();
        peakOneFreq->setSpacing(0);
        peakOneFreq->setObjectName("peakOneFreq");
        peakOneFreq->setContentsMargins(0, 0, 0, 0);
        peakOneFreqValue = new QLabel(layoutWidget);
        peakOneFreqValue->setObjectName("peakOneFreqValue");
        peakOneFreqValue->setAutoFillBackground(true);
        peakOneFreqValue->setScaledContents(false);
        peakOneFreqValue->setAlignment(Qt::AlignCenter);
        peakOneFreqValue->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        peakOneFreq->addWidget(peakOneFreqValue);

        peakOneFreqUnit = new QLabel(layoutWidget);
        peakOneFreqUnit->setObjectName("peakOneFreqUnit");
        peakOneFreqUnit->setScaledContents(false);
        peakOneFreqUnit->setAlignment(Qt::AlignCenter);
        peakOneFreqUnit->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");

        peakOneFreq->addWidget(peakOneFreqUnit);

        peakOneFreq->setStretch(0, 2);
        peakOneFreq->setStretch(1, 1);

        peaksData->addLayout(peakOneFreq, 0, 0, 1, 1);

        peakTwoFreq = new QHBoxLayout();
        peakTwoFreq->setSpacing(0);
        peakTwoFreq->setObjectName("peakTwoFreq");
        peakTwoFreq->setContentsMargins(0, 0, 0, 0);
        peakTwoFreqValue = new QLabel(layoutWidget);
        peakTwoFreqValue->setObjectName("peakTwoFreqValue");
        peakTwoFreqValue->setAutoFillBackground(true);
        peakTwoFreqValue->setScaledContents(false);
        peakTwoFreqValue->setAlignment(Qt::AlignCenter);
        peakTwoFreqValue->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        peakTwoFreq->addWidget(peakTwoFreqValue);

        peakTwoFreqUnit = new QLabel(layoutWidget);
        peakTwoFreqUnit->setObjectName("peakTwoFreqUnit");
        peakTwoFreqUnit->setScaledContents(false);
        peakTwoFreqUnit->setAlignment(Qt::AlignCenter);
        peakTwoFreqUnit->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");

        peakTwoFreq->addWidget(peakTwoFreqUnit);

        peakTwoFreq->setStretch(0, 2);
        peakTwoFreq->setStretch(1, 1);

        peaksData->addLayout(peakTwoFreq, 1, 0, 1, 1);

        peakThreeFreq = new QHBoxLayout();
        peakThreeFreq->setSpacing(0);
        peakThreeFreq->setObjectName("peakThreeFreq");
        peakThreeFreq->setContentsMargins(0, 0, 0, 0);
        peakThreeFreqValue = new QLabel(layoutWidget);
        peakThreeFreqValue->setObjectName("peakThreeFreqValue");
        peakThreeFreqValue->setAutoFillBackground(true);
        peakThreeFreqValue->setScaledContents(false);
        peakThreeFreqValue->setAlignment(Qt::AlignCenter);
        peakThreeFreqValue->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        peakThreeFreq->addWidget(peakThreeFreqValue);

        peakThreeFreqUnit = new QLabel(layoutWidget);
        peakThreeFreqUnit->setObjectName("peakThreeFreqUnit");
        peakThreeFreqUnit->setScaledContents(false);
        peakThreeFreqUnit->setAlignment(Qt::AlignCenter);
        peakThreeFreqUnit->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");

        peakThreeFreq->addWidget(peakThreeFreqUnit);

        peakThreeFreq->setStretch(0, 2);
        peakThreeFreq->setStretch(1, 1);

        peaksData->addLayout(peakThreeFreq, 2, 0, 1, 1);

        peakOnePower = new QHBoxLayout();
        peakOnePower->setSpacing(0);
        peakOnePower->setObjectName("peakOnePower");
        peakOnePower->setContentsMargins(0, 0, 0, 0);
        peakOnePowerValue = new QLabel(layoutWidget);
        peakOnePowerValue->setObjectName("peakOnePowerValue");
        peakOnePowerValue->setAutoFillBackground(true);
        peakOnePowerValue->setScaledContents(false);
        peakOnePowerValue->setAlignment(Qt::AlignCenter);
        peakOnePowerValue->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white");

        peakOnePower->addWidget(peakOnePowerValue);

        peakOnePowerUnit = new QLabel(layoutWidget);
        peakOnePowerUnit->setObjectName("peakOnePowerUnit");
        peakOnePowerUnit->setScaledContents(false);
        peakOnePowerUnit->setAlignment(Qt::AlignCenter);
        peakOnePowerUnit->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");

        peakOnePower->addWidget(peakOnePowerUnit);

        peakOnePower->setStretch(0, 2);
        peakOnePower->setStretch(1, 1);

        peaksData->addLayout(peakOnePower, 0, 1, 1, 1);

        peakTwoPower = new QHBoxLayout();
        peakTwoPower->setSpacing(0);
        peakTwoPower->setObjectName("peakTwoPower");
        peakTwoPower->setContentsMargins(0, 0, 0, 0);
        peakTwoPowerValue = new QLabel(layoutWidget);
        peakTwoPowerValue->setObjectName("peakTwoPowerValue");
        peakTwoPowerValue->setAutoFillBackground(true);
        peakTwoPowerValue->setScaledContents(false);
        peakTwoPowerValue->setAlignment(Qt::AlignCenter);
        peakTwoPowerValue->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        peakTwoPower->addWidget(peakTwoPowerValue);

        peakTwoPowerUnit = new QLabel(layoutWidget);
        peakTwoPowerUnit->setObjectName("peakTwoPowerUnit");
        peakTwoPowerUnit->setScaledContents(false);
        peakTwoPowerUnit->setAlignment(Qt::AlignCenter);
        peakTwoPowerUnit->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");

        peakTwoPower->addWidget(peakTwoPowerUnit);

        peakTwoPower->setStretch(0, 2);
        peakTwoPower->setStretch(1, 1);

        peaksData->addLayout(peakTwoPower, 1, 1, 1, 1);

        peakThreePower = new QHBoxLayout();
        peakThreePower->setSpacing(0);
        peakThreePower->setObjectName("peakThreePower");
        peakThreePower->setContentsMargins(0, 0, 0, 0);
        peakThreePowerValue = new QLabel(layoutWidget);
        peakThreePowerValue->setObjectName("peakThreePowerValue");
        peakThreePowerValue->setAutoFillBackground(true);
        peakThreePowerValue->setScaledContents(false);
        peakThreePowerValue->setAlignment(Qt::AlignCenter);
        peakThreePowerValue->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        peakThreePower->addWidget(peakThreePowerValue);

        peakThreePowerUnit = new QLabel(layoutWidget);
        peakThreePowerUnit->setObjectName("peakThreePowerUnit");
        peakThreePowerUnit->setScaledContents(false);
        peakThreePowerUnit->setAlignment(Qt::AlignCenter);
        peakThreePowerUnit->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");

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
        beaconLayout->setObjectName("beaconLayout");
        beaconLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        beaconLayout->setContentsMargins(10, 10, 10, 10);
        selectBeacon = new QPushButton(layoutWidget);
        selectBeacon->setObjectName("selectBeacon");
        sizePolicy1.setHeightForWidth(selectBeacon->sizePolicy().hasHeightForWidth());
        selectBeacon->setSizePolicy(sizePolicy1);

        beaconLayout->addWidget(selectBeacon);

        inputBeaconWidget = new InputDialog(MainWindow);

        beaconFound = new QPushButton(layoutWidget);
        beaconFound->setObjectName("beaconFound");
        sizePolicy1.setHeightForWidth(beaconFound->sizePolicy().hasHeightForWidth());
        beaconFound->setSizePolicy(sizePolicy1);

        beaconLayout->addWidget(beaconFound);

        beaconLayout->setStretch(0, 1);
        beaconLayout->setStretch(1, 1);

        miscLayout->addLayout(beaconLayout);

        logLayout = new QVBoxLayout();
        logLayout->setObjectName("logLayout");
        logLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        logLayout->setContentsMargins(10, 10, 10, 10);
        preblastLog = new QPushButton(layoutWidget);
        preblastLog->setObjectName("preblastLog");
        sizePolicy1.setHeightForWidth(preblastLog->sizePolicy().hasHeightForWidth());
        preblastLog->setSizePolicy(sizePolicy1);

        logLayout->addWidget(preblastLog);

        postblastLog = new QPushButton(layoutWidget);
        postblastLog->setObjectName("postblastLog");
        sizePolicy1.setHeightForWidth(postblastLog->sizePolicy().hasHeightForWidth());
        postblastLog->setSizePolicy(sizePolicy1);

        logLayout->addWidget(postblastLog);

        logLayout->setStretch(0, 1);
        logLayout->setStretch(1, 1);

        miscLayout->addLayout(logLayout);

        miscLayout->setStretch(0, 2);
        miscLayout->setStretch(1, 1);
        miscLayout->setStretch(2, 1);

        dataLayout->addLayout(miscLayout);

        saveLayout = new QHBoxLayout();
        saveLayout->setObjectName("saveLayout");
        saveLayout->setContentsMargins(10, 10, 10, 10);
        saveLog = new QPushButton(layoutWidget);
        saveLog->setObjectName("simpleView");
        sizePolicy1.setHeightForWidth(saveLog->sizePolicy().hasHeightForWidth());
        saveLog->setSizePolicy(sizePolicy1);

        saveLayout->addWidget(saveLog);

        startLog = new QPushButton(layoutWidget);
        startLog->setObjectName("startLog");
        sizePolicy1.setHeightForWidth(startLog->sizePolicy().hasHeightForWidth());
        startLog->setSizePolicy(sizePolicy1);

        startLog->setCheckable(false);

        saveLayout->addWidget(startLog);

        closeShutdown = new QPushButton(layoutWidget);
        closeShutdown->setObjectName("closeShutdown");
        sizePolicy1.setHeightForWidth(closeShutdown->sizePolicy().hasHeightForWidth());
        closeShutdown->setSizePolicy(sizePolicy1);

        saveLayout->addWidget(closeShutdown);

        saveLayout->setStretch(0, 2);
        saveLayout->setStretch(1, 3);
        saveLayout->setStretch(2, 3);

        dataLayout->addLayout(saveLayout);

        dataLayout->setStretch(0, 3);
        dataLayout->setStretch(1, 1);

        panelLayout->addLayout(dataLayout);

        selectLayout = new QVBoxLayout();
        selectLayout->setSpacing(10);
        selectLayout->setObjectName("selectLayout");
        selectLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        selectLayout->setContentsMargins(10, 10, 10, 10);
        selectDisplayFreq = new QPushButton(layoutWidget);
        selectDisplayFreq->setObjectName("selectDisplayFreq");
        sizePolicy1.setHeightForWidth(selectDisplayFreq->sizePolicy().hasHeightForWidth());
        selectDisplayFreq->setSizePolicy(sizePolicy1);
        selectDisplayFreq->setStyleSheet("");
        selectDisplayFreq->setFlat(false);
        selectDisplayFreq->setEnabled(false);

        selectLayout->addWidget(selectDisplayFreq);

        selectOneFreq = new QPushButton(layoutWidget);
        selectOneFreq->setObjectName("selectOneFreq");
        sizePolicy1.setHeightForWidth(selectOneFreq->sizePolicy().hasHeightForWidth());
        selectOneFreq->setSizePolicy(sizePolicy1);

        selectLayout->addWidget(selectOneFreq);

        selectTwoFreq = new QPushButton(layoutWidget);
        selectTwoFreq->setObjectName("selectTwoFreq");
        sizePolicy1.setHeightForWidth(selectTwoFreq->sizePolicy().hasHeightForWidth());
        selectTwoFreq->setSizePolicy(sizePolicy1);

        selectLayout->addWidget(selectTwoFreq);

        selectThreeFreq = new QPushButton(layoutWidget);
        selectThreeFreq->setObjectName("selectThreeFreq");
        sizePolicy1.setHeightForWidth(selectThreeFreq->sizePolicy().hasHeightForWidth());
        selectThreeFreq->setSizePolicy(sizePolicy1);

        selectLayout->addWidget(selectThreeFreq);

        panelLayout->addLayout(selectLayout);

        panelLayout->setStretch(0, 4);
        panelLayout->setStretch(1, 1);

        verticalLayout->addLayout(panelLayout);

        statusLine = new QFrame(layoutWidget);
        statusLine->setObjectName("statusLine");
        statusLine->setFrameShape(QFrame::HLine);
        statusLine->setFrameShadow(QFrame::Sunken);
        statusLine->setLineWidth(1280);
        statusLabel = new QLabel(layoutWidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(10, 710, 1260, 80));

        verticalLayout->addWidget(statusLine);
        verticalLayout->addWidget(statusLabel);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    }

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
        selectBeacon->setText(QCoreApplication::translate("MainWindow", "Seleccionar\nBaliza", nullptr));
        beaconFound->setText(QCoreApplication::translate("MainWindow", "Baliza\nEncontrada", nullptr));
        preblastLog->setText(QCoreApplication::translate("MainWindow", "Registro\nPre-Tronadura", nullptr));
        postblastLog->setText(QCoreApplication::translate("MainWindow", "Registro\nPost-Tronadura", nullptr));
        saveLog->setText(QCoreApplication::translate("MainWindow", "Vista avanzada", nullptr));
        startLog->setText(QCoreApplication::translate("MainWindow", "Empezar Nuevo\nRegistro", nullptr));
        closeShutdown->setText(QCoreApplication::translate("MainWindow", "Cerrar y Apagar", nullptr));
        selectDisplayFreq->setText(QCoreApplication::translate("MainWindow", "Seleccionar\nFrecuencia", nullptr));
        selectOneFreq->setText(QCoreApplication::translate("MainWindow", "13.75 kHz", nullptr));
        selectTwoFreq->setText(QCoreApplication::translate("MainWindow", "14.00 kHz", nullptr));
        selectThreeFreq->setText(QCoreApplication::translate("MainWindow", "14.25 kHz", nullptr));

        inputBeaconWidget->inputBeaconTopLabel->setText(QCoreApplication::translate("MainWindow", "Ingreso Nueva Baliza", nullptr));
        inputBeaconWidget->inputBeaconOneLabel->setText(QCoreApplication::translate("MainWindow", "Distancia Baliza [metros]", nullptr));
        inputBeaconWidget->inputBeaconAccept->setText(QCoreApplication::translate("MainWindow", "Aceptar", nullptr));
        inputBeaconWidget->inputBeaconCancel->setText(QCoreApplication::translate("MainWindow", "Cancelar", nullptr));
    }
};

namespace Ui {
class MainWindow : public Ui_MainWindow {
};
}  // namespace Ui

QT_END_NAMESPACE
