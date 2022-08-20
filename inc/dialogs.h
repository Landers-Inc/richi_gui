#pragma once

#include <QDialog>
#include <QQuickWidget>
#include <QtWidgets>
#include <iostream>

#include "datawindow.h"
#include "stylesheetdefines.h"

class InputWidget : public QDialog {
    Q_OBJECT
   public:
    using QDialog::QDialog;

   protected:
    void keyPressEvent(QKeyEvent *event) override {
        std::cout << "Funcionaaaa Key" << std::endl;
        QWidget::keyPressEvent(event);
    }
    void keyReleaseEvent(QKeyEvent *event) override {
        std::cout << "Funcionaaaa Key Rel" << std::endl;
        QWidget::keyReleaseEvent(event);
    }
    void inputMethodEvent(QInputMethodEvent *event) override {
        std::cout << "Funcionaaaa Method" << std::endl;
        QWidget::inputMethodEvent(event);
    }
    bool eventFilter(QObject *object, QEvent *event) {
        std::cout << "Funcionaaaa Event" << std::endl;
        return true;
    }
};

class BeaconInputDialog : public QDialog {
    Q_OBJECT
   public:
    QWidget *dialogInputWidget;
    QWidget *beaconInputWidget;
    QVBoxLayout *beaconInputLayout;
    QHBoxLayout *beaconOneInputLayout;
    QHBoxLayout *beaconTwoInputLayout;
    QHBoxLayout *beaconThreeInputLayout;
    QLabel *beaconTopInputLabel;
    QLabel *beaconOneInputLabel;
    QLineEdit *beaconOneInputText;
    QPushButton *beaconInputAccept;
    QPushButton *beaconInputCancel;
    QPushButton *beaconTypeA;
    QPushButton *beaconTypeB;
    QPushButton *beaconTypeC;

    int beaconTypeSelect = 0;

    explicit BeaconInputDialog(QWidget *parent = 0) {
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(parent->sizePolicy().hasHeightForWidth());

        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);

        dialogInputWidget = new QWidget(parent);
        dialogInputWidget->setObjectName("dialogInputWidget");
        sizePolicy.setHeightForWidth(dialogInputWidget->sizePolicy().hasHeightForWidth());
        dialogInputWidget->setSizePolicy(sizePolicy);
        dialogInputWidget->setMinimumSize(QSize(1024, 768));
        dialogInputWidget->setMaximumSize(QSize(1024, 768));
        dialogInputWidget->setVisible(false);

        beaconInputWidget = new InputWidget(dialogInputWidget);
        beaconInputWidget->setObjectName("beaconInputWidget");
        beaconInputWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        beaconInputWidget->move(300, 100);
        beaconInputWidget->setMinimumSize(680, 320);
        beaconInputWidget->setWindowFlags(Qt::Dialog);
        beaconInputWidget->setStyleSheet(
            "#beaconInputWidget{"
            "background: #ddd;"
            "border-radius: 10px;"
            "border-style: solid;"
            "border-width: 2px;"
            "border-radius: 7px;"
            "border-color: black;}");

        beaconInputLayout = new QVBoxLayout(beaconInputWidget);
        beaconInputLayout->setObjectName("beaconInputLayout");
        beaconInputLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        beaconInputLayout->setContentsMargins(10, 10, 10, 10);
        beaconTopInputLabel = new QLabel(beaconInputWidget);
        beaconTopInputLabel->setObjectName("beaconTopInputLabel");
        beaconTopInputLabel->setContentsMargins(10, 10, 10, 10);
        beaconTopInputLabel->setAlignment(Qt::AlignCenter);
        beaconTopInputLabel->setStyleSheet(
            "border: 1px solid #000;"
            "font: 30px 'Ubuntu';"
            "font-weight: bold;");

        beaconInputLayout->addWidget(beaconTopInputLabel);

        beaconOneInputLayout = new QHBoxLayout();
        beaconOneInputLayout->setObjectName("beaconOneInputLayout");
        beaconOneInputLayout->setContentsMargins(10, 10, 10, 10);
        beaconOneInputLabel = new QLabel(beaconInputWidget);
        beaconOneInputLabel->setObjectName("beaconOneInputLabel");
        beaconOneInputLabel->setAlignment(Qt::AlignCenter);
        beaconOneInputLabel->setStyleSheet(
            "font: 18px 'Ubuntu';"
            "font-weight: bold;");
        beaconOneInputText = new QLineEdit(beaconInputWidget);
        beaconOneInputText->setObjectName("beaconOneInputText");
        beaconOneInputText->setInputMethodHints(Qt::ImhDigitsOnly);

        beaconOneInputLayout->addWidget(beaconOneInputLabel);
        beaconOneInputLayout->addWidget(beaconOneInputText);
        beaconOneInputLayout->setStretch(0, 1);
        beaconOneInputLayout->setStretch(1, 1);

        beaconInputLayout->addLayout(beaconOneInputLayout);

        beaconTwoInputLayout = new QHBoxLayout();
        beaconTwoInputLayout->setObjectName("beaconTwoInputLayout");
        beaconTwoInputLayout->setContentsMargins(10, 10, 10, 10);
        beaconTypeA = new QPushButton(beaconInputWidget);
        beaconTypeA->setObjectName("beaconTypeA");
        sizePolicy1.setHeightForWidth(beaconTypeA->sizePolicy().hasHeightForWidth());
        beaconTypeA->setFocusPolicy(Qt::NoFocus);
        beaconTypeA->setSizePolicy(sizePolicy1);
        beaconTypeA->setStyleSheet(GREEN_BUTTON);
        beaconTypeB = new QPushButton(beaconInputWidget);
        beaconTypeB->setObjectName("beaconTypeB");
        sizePolicy1.setHeightForWidth(beaconTypeB->sizePolicy().hasHeightForWidth());
        beaconTypeB->setFocusPolicy(Qt::NoFocus);
        beaconTypeB->setSizePolicy(sizePolicy1);
        beaconTypeB->setStyleSheet(RED_BUTTON);
        beaconTypeC = new QPushButton(beaconInputWidget);
        beaconTypeC->setObjectName("beaconTypeC");
        sizePolicy1.setHeightForWidth(beaconTypeC->sizePolicy().hasHeightForWidth());
        beaconTypeC->setFocusPolicy(Qt::NoFocus);
        beaconTypeC->setSizePolicy(sizePolicy1);
        beaconTypeC->setStyleSheet(RED_BUTTON);

        beaconTwoInputLayout->addWidget(beaconTypeA);
        beaconTwoInputLayout->addWidget(beaconTypeB);
        beaconTwoInputLayout->addWidget(beaconTypeC);
        beaconTwoInputLayout->setStretch(0, 1);
        beaconTwoInputLayout->setStretch(1, 1);
        beaconTwoInputLayout->setStretch(2, 1);

        beaconInputLayout->addLayout(beaconTwoInputLayout);

        beaconThreeInputLayout = new QHBoxLayout();
        beaconThreeInputLayout->setObjectName("beaconThreeInputLayout");
        beaconThreeInputLayout->setContentsMargins(10, 10, 10, 10);
        beaconInputAccept = new QPushButton(beaconInputWidget);
        beaconInputAccept->setObjectName("beaconInputAccept");
        sizePolicy1.setHeightForWidth(beaconInputAccept->sizePolicy().hasHeightForWidth());
        beaconInputAccept->setFocusPolicy(Qt::NoFocus);
        beaconInputAccept->setSizePolicy(sizePolicy1);
        beaconInputCancel = new QPushButton(beaconInputWidget);
        beaconInputCancel->setObjectName("beaconInputCancel");
        sizePolicy1.setHeightForWidth(beaconInputCancel->sizePolicy().hasHeightForWidth());
        beaconInputCancel->setFocusPolicy(Qt::NoFocus);
        beaconInputCancel->setSizePolicy(sizePolicy1);

        beaconThreeInputLayout->addWidget(beaconInputAccept);
        beaconThreeInputLayout->addWidget(beaconInputCancel);
        beaconThreeInputLayout->setStretch(0, 1);
        beaconThreeInputLayout->setStretch(1, 1);

        beaconInputLayout->addLayout(beaconThreeInputLayout);

        beaconInputLayout->setStretch(0, 1);
        beaconInputLayout->setStretch(1, 1);
        beaconInputLayout->setStretch(2, 1);
        beaconInputLayout->setStretch(3, 1);
    }
};

class BeaconFoundDialog : public QDialog {
    Q_OBJECT
   public:
    QWidget *dialogFoundWidget;
    QWidget *beaconFoundWidget;
    QVBoxLayout *beaconFoundLayout;
    QHBoxLayout *beaconOneFoundLayout;
    QHBoxLayout *beaconTwoFoundLayout;
    QLabel *beaconFoundLabel;
    QLabel *beaconOneFoundLabel;
    QLineEdit *beaconOneFoundText;
    QPushButton *beaconFoundAccept;
    QPushButton *beaconFoundNotFound;
    QPushButton *beaconFoundCancel;

    explicit BeaconFoundDialog(QWidget *parent = 0) {
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(parent->sizePolicy().hasHeightForWidth());

        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);

        dialogFoundWidget = new QWidget(parent);
        dialogFoundWidget->setObjectName("dialogFoundWidget");
        sizePolicy.setHeightForWidth(dialogFoundWidget->sizePolicy().hasHeightForWidth());
        dialogFoundWidget->setSizePolicy(sizePolicy);
        dialogFoundWidget->setMinimumSize(QSize(1024, 768));
        dialogFoundWidget->setMaximumSize(QSize(1024, 768));
        dialogFoundWidget->setVisible(false);

        beaconFoundWidget = new InputWidget(dialogFoundWidget);
        beaconFoundWidget->setObjectName("beaconFoundWidget");
        beaconFoundWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        beaconFoundWidget->move(300, 100);
        beaconFoundWidget->setMinimumSize(680, 220);
        beaconFoundWidget->setWindowFlags(Qt::Dialog);
        beaconFoundWidget->setStyleSheet(
            "#beaconFoundWidget{"
            "background: #ddd;"
            "border-radius: 10px;"
            "border-style: solid;"
            "border-width: 2px;"
            "border-radius: 7px;"
            "border-color: black;}");

        beaconFoundLayout = new QVBoxLayout(beaconFoundWidget);
        beaconFoundLayout->setObjectName("beaconFoundLayout");
        beaconFoundLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        beaconFoundLayout->setContentsMargins(10, 10, 10, 10);
        beaconFoundLabel = new QLabel(beaconFoundWidget);
        beaconFoundLabel->setObjectName("beaconFoundLabel");
        beaconFoundLabel->setContentsMargins(10, 10, 10, 10);
        beaconFoundLabel->setAlignment(Qt::AlignCenter);
        beaconFoundLabel->setStyleSheet(
            "border: 1px solid #000;"
            "font: 20px 'Ubuntu';"
            "font-weight: bold;");

        beaconFoundLayout->addWidget(beaconFoundLabel);

        beaconOneFoundLayout = new QHBoxLayout();
        beaconOneFoundLayout->setObjectName("beaconOneFoundLayout");
        beaconOneFoundLayout->setContentsMargins(10, 10, 10, 10);
        beaconOneFoundLabel = new QLabel(beaconFoundWidget);
        beaconOneFoundLabel->setObjectName("beaconOneFoundLabel");
        beaconOneFoundLabel->setAlignment(Qt::AlignCenter);
        beaconOneFoundLabel->setStyleSheet(
            "font: 18px 'Ubuntu';"
            "font-weight: bold;");
        beaconOneFoundText = new QLineEdit(beaconFoundWidget);
        beaconOneFoundText->setObjectName("beaconOneFoundText");
        beaconOneFoundText->setInputMethodHints(Qt::ImhDigitsOnly);

        beaconOneFoundLayout->addWidget(beaconOneFoundLabel);
        beaconOneFoundLayout->addWidget(beaconOneFoundText);

        beaconFoundLayout->addLayout(beaconOneFoundLayout);

        beaconOneFoundLayout->setStretch(0, 1);
        beaconOneFoundLayout->setStretch(1, 1);

        beaconTwoFoundLayout = new QHBoxLayout();
        beaconTwoFoundLayout->setObjectName("beaconTwoFoundLayout");
        beaconTwoFoundLayout->setContentsMargins(10, 10, 10, 10);
        beaconFoundAccept = new QPushButton(beaconFoundWidget);
        beaconFoundAccept->setObjectName("beaconFoundAccept");
        sizePolicy1.setHeightForWidth(beaconFoundAccept->sizePolicy().hasHeightForWidth());
        beaconFoundAccept->setFocusPolicy(Qt::NoFocus);
        beaconFoundAccept->setSizePolicy(sizePolicy1);
        beaconFoundNotFound = new QPushButton(beaconFoundWidget);
        beaconFoundNotFound->setObjectName("beaconFoundNotFound");
        sizePolicy1.setHeightForWidth(beaconFoundNotFound->sizePolicy().hasHeightForWidth());
        beaconFoundNotFound->setFocusPolicy(Qt::NoFocus);
        beaconFoundNotFound->setSizePolicy(sizePolicy1);
        beaconFoundCancel = new QPushButton(beaconFoundWidget);
        beaconFoundCancel->setObjectName("beaconFoundCancel");
        sizePolicy1.setHeightForWidth(beaconFoundCancel->sizePolicy().hasHeightForWidth());
        beaconFoundCancel->setFocusPolicy(Qt::NoFocus);
        beaconFoundCancel->setSizePolicy(sizePolicy1);

        beaconTwoFoundLayout->addWidget(beaconFoundAccept);
        beaconTwoFoundLayout->addWidget(beaconFoundNotFound);
        beaconTwoFoundLayout->addWidget(beaconFoundCancel);

        beaconFoundLayout->addLayout(beaconTwoFoundLayout);

        beaconTwoFoundLayout->setStretch(0, 1);
        beaconTwoFoundLayout->setStretch(1, 1);
        beaconTwoFoundLayout->setStretch(2, 1);

        beaconFoundLayout->setStretch(0, 1);
        beaconFoundLayout->setStretch(1, 1);
        beaconFoundLayout->setStretch(2, 1);
    }
};

class WarningDialog : public QDialog {
    Q_OBJECT
   public:
    QWidget *dialogWidget;
    QWidget *warningWidget;
    QVBoxLayout *warningLayout;
    QHBoxLayout *warningOneLayout;
    QLabel *warningLabel;
    QPushButton *warningAccept;
    QPushButton *warningCancel;

    explicit WarningDialog(QWidget *parent = 0) {
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(parent->sizePolicy().hasHeightForWidth());

        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);

        dialogWidget = new QWidget(parent);
        dialogWidget->setObjectName("dialogWidget");
        sizePolicy.setHeightForWidth(dialogWidget->sizePolicy().hasHeightForWidth());
        dialogWidget->setSizePolicy(sizePolicy);
        dialogWidget->setMinimumSize(QSize(1024, 768));
        dialogWidget->setMaximumSize(QSize(1024, 768));
        dialogWidget->setVisible(false);

        warningWidget = new QDialog(dialogWidget);
        warningWidget->setObjectName("warningWidget");
        warningWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        warningWidget->move(300, 100);
        warningWidget->setMinimumSize(680, 200);
        warningWidget->setWindowFlags(Qt::Dialog);
        warningWidget->setStyleSheet(
            "#warningWidget{"
            "background: #ddd;"
            "border-radius: 10px;"
            "border-style: solid;"
            "border-width: 2px;"
            "border-radius: 7px;"
            "border-color: black;}");

        warningLayout = new QVBoxLayout(warningWidget);
        warningLayout->setObjectName("warningLayout");
        warningLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        warningLayout->setContentsMargins(10, 10, 10, 10);
        warningLabel = new QLabel(warningWidget);
        warningLabel->setObjectName("warningLabel");
        warningLabel->setContentsMargins(10, 10, 10, 10);
        warningLabel->setAlignment(Qt::AlignCenter);
        warningLabel->setStyleSheet(
            "border: 1px solid #000;"
            "font: 20px 'Ubuntu';"
            "font-weight: bold;");

        warningLayout->addWidget(warningLabel);

        warningOneLayout = new QHBoxLayout();
        warningOneLayout->setObjectName("warningOneLayout");
        warningOneLayout->setContentsMargins(10, 10, 10, 10);
        warningAccept = new QPushButton(warningWidget);
        warningAccept->setObjectName("warningAccept");
        sizePolicy1.setHeightForWidth(warningAccept->sizePolicy().hasHeightForWidth());
        warningAccept->setFocusPolicy(Qt::NoFocus);
        warningAccept->setSizePolicy(sizePolicy1);
        warningCancel = new QPushButton(warningWidget);
        warningCancel->setObjectName("warningCancel");
        sizePolicy1.setHeightForWidth(warningCancel->sizePolicy().hasHeightForWidth());
        warningCancel->setFocusPolicy(Qt::NoFocus);
        warningCancel->setSizePolicy(sizePolicy1);

        warningOneLayout->addWidget(warningAccept);
        warningOneLayout->addWidget(warningCancel);

        warningLayout->addLayout(warningOneLayout);

        warningOneLayout->setStretch(0, 1);
        warningOneLayout->setStretch(1, 1);

        warningLayout->setStretch(0, 1);
        warningLayout->setStretch(1, 1);
        warningLayout->setStretch(2, 1);
    }
};

class GPSStatus : public QDialog {
    Q_OBJECT
   public:
    QWidget *dialogWidget;
    QWidget *statusWidget;
    QVBoxLayout *statusLayout;
    QLabel *statusTitle;
    QHBoxLayout *statusOneLayout;
    QLabel *gpsNameLabel;
    QLabel *gpsName;
    QHBoxLayout *statusTwoLayout;
    QLabel *gpsStatusLabel;
    QLabel *gpsStatus;
    QHBoxLayout *statusThreeLayout;
    QLabel *gpsModeLabel;
    QLabel *gpsMode;
    QHBoxLayout *statusFourLayout;
    QLabel *gpsCoordXLabel;
    QLabel *gpsCoordX;
    QHBoxLayout *statusFiveLayout;
    QLabel *gpsCoordYLabel;
    QLabel *gpsCoordY;
    QHBoxLayout *statusSixLayout;
    QLabel *gpsCoordZLabel;
    QLabel *gpsCoordZ;
    QHBoxLayout *statusSevenLayout;
    QLabel *gpsAccHorLabel;
    QLabel *gpsAccHor;
    QHBoxLayout *statusEightLayout;
    QLabel *gpsAccVerLabel;
    QLabel *gpsAccVer;
    QPushButton *statusClose;

    explicit GPSStatus(QWidget *parent = 0) {
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(parent->sizePolicy().hasHeightForWidth());

        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);

        dialogWidget = new QWidget(parent);
        dialogWidget->setObjectName("dialogWidget");
        sizePolicy.setHeightForWidth(dialogWidget->sizePolicy().hasHeightForWidth());
        dialogWidget->setSizePolicy(sizePolicy);
        dialogWidget->setMinimumSize(QSize(1024, 768));
        dialogWidget->setMaximumSize(QSize(1024, 768));
        dialogWidget->setVisible(false);

        statusWidget = new QDialog(dialogWidget);
        statusWidget->setObjectName("statusWidget");
        statusWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        statusWidget->move(200, 100);
        statusWidget->setMinimumSize(880, 600);
        statusWidget->setWindowFlags(Qt::Dialog);
        statusWidget->setStyleSheet(
            "#statusWidget{"
            "background: #ddd;"
            "border-radius: 10px;"
            "border-style: solid;"
            "border-width: 2px;"
            "border-radius: 7px;"
            "border-color: black;}");

        statusLayout = new QVBoxLayout(statusWidget);
        statusLayout->setObjectName("statusLayout");
        statusLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        statusLayout->setContentsMargins(10, 10, 10, 10);
        statusTitle = new QLabel(statusWidget);
        statusTitle->setObjectName("statusTitle");
        statusTitle->setContentsMargins(10, 10, 10, 10);
        statusTitle->setAlignment(Qt::AlignCenter);
        statusTitle->setStyleSheet(
            "border: 1px solid #000;"
            "font: 30px 'Ubuntu';"
            "font-weight: bold;");

        statusLayout->addWidget(statusTitle);

        statusOneLayout = new QHBoxLayout();
        statusOneLayout->setObjectName("statusOneLayout");
        gpsNameLabel = new QLabel(statusWidget);
        gpsNameLabel->setObjectName("gpsNameLabel");
        gpsNameLabel->setAutoFillBackground(true);
        gpsNameLabel->setScaledContents(false);
        gpsNameLabel->setAlignment(Qt::AlignCenter);
        gpsNameLabel->setStyleSheet(
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");
        gpsName = new QLabel(statusWidget);
        gpsName->setObjectName("gpsName");
        gpsName->setAutoFillBackground(true);
        gpsName->setScaledContents(false);
        gpsName->setAlignment(Qt::AlignCenter);
        gpsName->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        statusOneLayout->addWidget(gpsNameLabel);
        statusOneLayout->addWidget(gpsName);

        statusOneLayout->setStretch(0, 1);
        statusOneLayout->setStretch(1, 1);

        statusLayout->addLayout(statusOneLayout);

        statusThreeLayout = new QHBoxLayout();
        statusThreeLayout->setObjectName("statusThreeLayout");
        gpsModeLabel = new QLabel(statusWidget);
        gpsModeLabel->setObjectName("gpsModeLabel");
        gpsModeLabel->setAutoFillBackground(true);
        gpsModeLabel->setScaledContents(false);
        gpsModeLabel->setAlignment(Qt::AlignCenter);
        gpsModeLabel->setStyleSheet(
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");
        gpsMode = new QLabel(statusWidget);
        gpsMode->setObjectName("gpsMode");
        gpsMode->setAutoFillBackground(true);
        gpsMode->setScaledContents(false);
        gpsMode->setAlignment(Qt::AlignCenter);
        gpsMode->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        statusThreeLayout->addWidget(gpsModeLabel);
        statusThreeLayout->addWidget(gpsMode);

        statusThreeLayout->setStretch(0, 1);
        statusThreeLayout->setStretch(1, 1);

        statusLayout->addLayout(statusThreeLayout);

        statusTwoLayout = new QHBoxLayout();
        statusTwoLayout->setObjectName("statusTwoLayout");
        gpsStatusLabel = new QLabel(statusWidget);
        gpsStatusLabel->setObjectName("gpsStatusLabel");
        gpsStatusLabel->setAutoFillBackground(true);
        gpsStatusLabel->setScaledContents(false);
        gpsStatusLabel->setAlignment(Qt::AlignCenter);
        gpsStatusLabel->setStyleSheet(
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");
        gpsStatus = new QLabel(statusWidget);
        gpsStatus->setObjectName("gpsStatus");
        gpsStatus->setAutoFillBackground(true);
        gpsStatus->setScaledContents(false);
        gpsStatus->setAlignment(Qt::AlignCenter);
        gpsStatus->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        statusTwoLayout->addWidget(gpsStatusLabel);
        statusTwoLayout->addWidget(gpsStatus);

        statusTwoLayout->setStretch(0, 1);
        statusTwoLayout->setStretch(1, 1);

        statusLayout->addLayout(statusTwoLayout);

        statusFourLayout = new QHBoxLayout();
        statusFourLayout->setObjectName("statusFourLayout");
        gpsCoordXLabel = new QLabel(statusWidget);
        gpsCoordXLabel->setObjectName("gpsCoordXLabel");
        gpsCoordXLabel->setAutoFillBackground(true);
        gpsCoordXLabel->setScaledContents(false);
        gpsCoordXLabel->setAlignment(Qt::AlignCenter);
        gpsCoordXLabel->setStyleSheet(
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");
        gpsCoordX = new QLabel(statusWidget);
        gpsCoordX->setObjectName("gpsCoordX");
        gpsCoordX->setAutoFillBackground(true);
        gpsCoordX->setScaledContents(false);
        gpsCoordX->setAlignment(Qt::AlignCenter);
        gpsCoordX->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        statusFourLayout->addWidget(gpsCoordXLabel);
        statusFourLayout->addWidget(gpsCoordX);

        statusFourLayout->setStretch(0, 1);
        statusFourLayout->setStretch(1, 1);

        statusLayout->addLayout(statusFourLayout);

        statusFiveLayout = new QHBoxLayout();
        statusFiveLayout->setObjectName("statusFiveLayout");
        gpsCoordYLabel = new QLabel(statusWidget);
        gpsCoordYLabel->setObjectName("gpsCoordYLabel");
        gpsCoordYLabel->setAutoFillBackground(true);
        gpsCoordYLabel->setScaledContents(false);
        gpsCoordYLabel->setAlignment(Qt::AlignCenter);
        gpsCoordYLabel->setStyleSheet(
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");
        gpsCoordY = new QLabel(statusWidget);
        gpsCoordY->setObjectName("gpsCoordY");
        gpsCoordY->setAutoFillBackground(true);
        gpsCoordY->setScaledContents(false);
        gpsCoordY->setAlignment(Qt::AlignCenter);
        gpsCoordY->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        statusFiveLayout->addWidget(gpsCoordYLabel);
        statusFiveLayout->addWidget(gpsCoordY);

        statusFiveLayout->setStretch(0, 1);
        statusFiveLayout->setStretch(1, 1);

        statusLayout->addLayout(statusFiveLayout);

        statusSixLayout = new QHBoxLayout();
        statusSixLayout->setObjectName("statusSixLayout");
        gpsCoordZLabel = new QLabel(statusWidget);
        gpsCoordZLabel->setObjectName("gpsCoordZLabel");
        gpsCoordZLabel->setAutoFillBackground(true);
        gpsCoordZLabel->setScaledContents(false);
        gpsCoordZLabel->setAlignment(Qt::AlignCenter);
        gpsCoordZLabel->setStyleSheet(
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");
        gpsCoordZ = new QLabel(statusWidget);
        gpsCoordZ->setObjectName("gpsCoordZ");
        gpsCoordZ->setAutoFillBackground(true);
        gpsCoordZ->setScaledContents(false);
        gpsCoordZ->setAlignment(Qt::AlignCenter);
        gpsCoordZ->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        statusSixLayout->addWidget(gpsCoordZLabel);
        statusSixLayout->addWidget(gpsCoordZ);

        statusSixLayout->setStretch(0, 1);
        statusSixLayout->setStretch(1, 1);

        statusLayout->addLayout(statusSixLayout);

        statusSevenLayout = new QHBoxLayout();
        statusSevenLayout->setObjectName("statusSevenLayout");
        gpsAccHorLabel = new QLabel(statusWidget);
        gpsAccHorLabel->setObjectName("gpsAccHorLabel");
        gpsAccHorLabel->setAutoFillBackground(true);
        gpsAccHorLabel->setScaledContents(false);
        gpsAccHorLabel->setAlignment(Qt::AlignCenter);
        gpsAccHorLabel->setStyleSheet(
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");
        gpsAccHor = new QLabel(statusWidget);
        gpsAccHor->setObjectName("gpsAccHor");
        gpsAccHor->setAutoFillBackground(true);
        gpsAccHor->setScaledContents(false);
        gpsAccHor->setAlignment(Qt::AlignCenter);
        gpsAccHor->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        statusSevenLayout->addWidget(gpsAccHorLabel);
        statusSevenLayout->addWidget(gpsAccHor);

        statusSevenLayout->setStretch(0, 1);
        statusSevenLayout->setStretch(1, 1);

        statusLayout->addLayout(statusSevenLayout);

        statusEightLayout = new QHBoxLayout();
        statusEightLayout->setObjectName("statusEightLayout");
        gpsAccVerLabel = new QLabel(statusWidget);
        gpsAccVerLabel->setObjectName("gpsAccVerLabel");
        gpsAccVerLabel->setAutoFillBackground(true);
        gpsAccVerLabel->setScaledContents(false);
        gpsAccVerLabel->setAlignment(Qt::AlignCenter);
        gpsAccVerLabel->setStyleSheet(
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");
        gpsAccVer = new QLabel(statusWidget);
        gpsAccVer->setObjectName("gpsAccVer");
        gpsAccVer->setAutoFillBackground(true);
        gpsAccVer->setScaledContents(false);
        gpsAccVer->setAlignment(Qt::AlignCenter);
        gpsAccVer->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        statusEightLayout->addWidget(gpsAccVerLabel);
        statusEightLayout->addWidget(gpsAccVer);

        statusEightLayout->setStretch(0, 1);
        statusEightLayout->setStretch(1, 1);

        statusLayout->addLayout(statusEightLayout);

        statusClose = new QPushButton(statusWidget);
        statusClose->setObjectName("statusClose");
        sizePolicy1.setHeightForWidth(statusClose->sizePolicy().hasHeightForWidth());
        statusClose->setFocusPolicy(Qt::NoFocus);
        statusClose->setSizePolicy(sizePolicy1);

        statusLayout->addWidget(statusClose);

        statusLayout->setStretch(0, 1);
        statusLayout->setStretch(1, 1);
        statusLayout->setStretch(2, 1);
        statusLayout->setStretch(3, 1);
        statusLayout->setStretch(4, 1);
        statusLayout->setStretch(5, 1);
        statusLayout->setStretch(6, 1);
        statusLayout->setStretch(7, 1);
        statusLayout->setStretch(8, 1);
        statusLayout->setStretch(9, 1);
    }
};

class NameInputDialog : public QDialog {
    Q_OBJECT
   public:
    QWidget *dialogInputWidget;
    QWidget *nameInputWidget;
    QVBoxLayout *nameInputLayout;
    QHBoxLayout *nameOneInputLayout;
    QLabel *nameTopInputLabel;
    QLabel *nameOneInputLabel;
    QLineEdit *nameOneInputText;
    QPushButton *nameInputAccept;

    explicit NameInputDialog(QWidget *parent = 0) {
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(parent->sizePolicy().hasHeightForWidth());

        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);

        dialogInputWidget = new QWidget(parent);
        dialogInputWidget->setObjectName("dialogInputWidget");
        sizePolicy.setHeightForWidth(dialogInputWidget->sizePolicy().hasHeightForWidth());
        dialogInputWidget->setSizePolicy(sizePolicy);
        dialogInputWidget->setMinimumSize(QSize(1024, 768));
        dialogInputWidget->setMaximumSize(QSize(1024, 768));
        dialogInputWidget->setVisible(false);

        nameInputWidget = new InputWidget(dialogInputWidget);
        nameInputWidget->setObjectName("nameInputWidget");
        nameInputWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        nameInputWidget->move(200, 100);
        nameInputWidget->setMinimumSize(880, 180);
        nameInputWidget->setWindowFlags(Qt::Dialog);
        nameInputWidget->setStyleSheet(
            "#nameInputWidget{"
            "background: #ddd;"
            "border-radius: 10px;"
            "border-style: solid;"
            "border-width: 2px;"
            "border-radius: 7px;"
            "border-color: black;}");

        nameInputLayout = new QVBoxLayout(nameInputWidget);
        nameInputLayout->setObjectName("nameInputLayout");
        nameInputLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        nameInputLayout->setContentsMargins(10, 10, 10, 10);
        nameTopInputLabel = new QLabel(nameInputWidget);
        nameTopInputLabel->setObjectName("nameTopInputLabel");
        nameTopInputLabel->setContentsMargins(10, 10, 10, 10);
        nameTopInputLabel->setAlignment(Qt::AlignCenter);
        nameTopInputLabel->setStyleSheet(
            "border: 1px solid #000;"
            "font: 30px 'Ubuntu';"
            "font-weight: bold;");

        nameInputLayout->addWidget(nameTopInputLabel);

        nameOneInputLayout = new QHBoxLayout();
        nameOneInputLayout->setObjectName("nameOneInputLayout");
        nameOneInputLayout->setContentsMargins(10, 10, 10, 10);
        nameOneInputLabel = new QLabel(nameInputWidget);
        nameOneInputLabel->setObjectName("nameOneInputLabel");
        nameOneInputLabel->setAlignment(Qt::AlignCenter);
        nameOneInputLabel->setStyleSheet(
            "font: 18px 'Ubuntu';"
            "font-weight: bold;");
        nameOneInputText = new QLineEdit(nameInputWidget);
        nameOneInputText->setObjectName("nameOneInputText");
        nameOneInputText->setInputMethodHints(Qt::ImhUrlCharactersOnly);

        nameOneInputLayout->addWidget(nameOneInputLabel);
        nameOneInputLayout->addWidget(nameOneInputText);

        nameOneInputLayout->setStretch(0, 1);
        nameOneInputLayout->setStretch(1, 2);

        nameInputLayout->addLayout(nameOneInputLayout);

        nameInputAccept = new QPushButton(nameInputWidget);
        nameInputAccept->setObjectName("nameInputAccept");
        sizePolicy1.setHeightForWidth(nameInputAccept->sizePolicy().hasHeightForWidth());
        nameInputAccept->setFocusPolicy(Qt::NoFocus);
        nameInputAccept->setSizePolicy(sizePolicy1);

        nameInputLayout->addWidget(nameInputAccept);

        nameInputLayout->setStretch(0, 1);
        nameInputLayout->setStretch(1, 1);
        nameInputLayout->setStretch(2, 1);
    }
};

class AdjustSpectrum : public QDialog {
    Q_OBJECT
   public:
    QWidget *dialogInputWidget;
    QWidget *adjustInputWidget;
    QVBoxLayout *adjustInputLayout;
    QHBoxLayout *adjustOneInputLayout;
    QHBoxLayout *adjustWindowOptionInputLayout;
    QHBoxLayout *adjustSampleSizeInputLayout;
    QHBoxLayout *adjustBeaconsInputLayout;
    QVBoxLayout *adjustBeaconALayout;
    QVBoxLayout *adjustBeaconBLayout;
    QVBoxLayout *adjustBeaconCLayout;
    QHBoxLayout *adjustTwoInputLayout;
    QHBoxLayout *adjustThreeInputLayout;
    QLabel *adjustTopInputLabel;
    QLabel *adjustOneInputLabel;
    QLabel *adjustWindowOptionInputLabel;
    QLabel *adjustFrequencyInputLabel;
    QLabel *adjustSampleSizeInputLabel;
    QLabel *adjustAverageInputLabel;
    QLabel *adjustTwoInputLabel;
    QLabel *adjustBeaconAInputLabel;
    QLabel *adjustBeaconBInputLabel;
    QLabel *adjustBeaconCInputLabel;
    QLineEdit *adjustOneInputText;
    QLineEdit *adjustBeaconAInputText;
    QLineEdit *adjustBeaconBInputText;
    QLineEdit *adjustBeaconCInputText;
    QComboBox *adjustWindowOptionInputText;
    QComboBox *adjustFrequencyInputText;
    QComboBox *adjustSampleSizeInputText;
    QComboBox *adjustAverageInputText;
    QLineEdit *adjustTwoInputText;
    QPushButton *adjustInputAccept;
    QPushButton *adjustInputCancel;

    int beaconTypeSelect = 0;

    explicit AdjustSpectrum(QWidget *parent = 0) {
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(parent->sizePolicy().hasHeightForWidth());

        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);

        dialogInputWidget = new QWidget(parent);
        dialogInputWidget->setObjectName("dialogInputWidget");
        sizePolicy.setHeightForWidth(dialogInputWidget->sizePolicy().hasHeightForWidth());
        dialogInputWidget->setSizePolicy(sizePolicy);
        dialogInputWidget->setMinimumSize(QSize(1024, 768));
        dialogInputWidget->setMaximumSize(QSize(1024, 768));
        dialogInputWidget->setVisible(false);

        adjustInputWidget = new InputWidget(dialogInputWidget);
        adjustInputWidget->setObjectName("adjustInputWidget");
        adjustInputWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        adjustInputWidget->move(200, 0);
        adjustInputWidget->setMinimumSize(880, 420);
        adjustInputWidget->setWindowFlags(Qt::Dialog);
        adjustInputWidget->setStyleSheet(
            "#adjustInputWidget{"
            "background: #ddd;"
            "border-radius: 10px;"
            "border-style: solid;"
            "border-width: 2px;"
            "border-radius: 7px;"
            "border-color: black;}");

        adjustInputLayout = new QVBoxLayout(adjustInputWidget);
        adjustInputLayout->setObjectName("adjustInputLayout");
        adjustInputLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        adjustInputLayout->setContentsMargins(10, 10, 10, 10);

        adjustWindowOptionInputLayout = new QHBoxLayout();
        adjustWindowOptionInputLayout->setObjectName("adjustWindowOptionInputLayout");
        adjustWindowOptionInputLayout->setContentsMargins(10, 10, 10, 10);
        adjustWindowOptionInputLabel = new QLabel(adjustInputWidget);
        adjustWindowOptionInputLabel->setObjectName("adjustWindowOptionInputLabel");
        adjustWindowOptionInputLabel->setAlignment(Qt::AlignCenter);
        adjustWindowOptionInputLabel->setStyleSheet(
            "font: 18px 'Ubuntu';"
            "font-weight: bold;");
        adjustWindowOptionInputText = new QComboBox(adjustInputWidget);
        adjustWindowOptionInputText->setObjectName("adjustWindowOptionInputText");
        for (int i = 0; i < 7; i++) {
            adjustWindowOptionInputText->addItem(DataWindow::windowName(i), i);
        }

        adjustFrequencyInputLabel = new QLabel(adjustInputWidget);
        adjustFrequencyInputLabel->setObjectName("adjustFrequencyInputLabel");
        adjustFrequencyInputLabel->setAlignment(Qt::AlignCenter);
        adjustFrequencyInputLabel->setStyleSheet(
            "font: 18px 'Ubuntu';"
            "font-weight: bold;");
        adjustFrequencyInputText = new QComboBox(adjustInputWidget);
        adjustFrequencyInputText->setObjectName("adjustFrequencyInputText");
        adjustFrequencyInputText->addItem("44100.0", 44100.0);
        adjustFrequencyInputText->addItem("48000.0", 48000.0);

        adjustWindowOptionInputLayout->addWidget(adjustWindowOptionInputLabel);
        adjustWindowOptionInputLayout->addWidget(adjustWindowOptionInputText);
        adjustWindowOptionInputLayout->addWidget(adjustFrequencyInputLabel);
        adjustWindowOptionInputLayout->addWidget(adjustFrequencyInputText);
        adjustWindowOptionInputLayout->setStretch(0, 1);
        adjustWindowOptionInputLayout->setStretch(1, 1);
        adjustWindowOptionInputLayout->setStretch(2, 1);
        adjustWindowOptionInputLayout->setStretch(3, 1);

        adjustInputLayout->addLayout(adjustWindowOptionInputLayout);

        adjustSampleSizeInputLayout = new QHBoxLayout();
        adjustSampleSizeInputLayout->setObjectName("adjustSampleSizeInputLayout");
        adjustSampleSizeInputLayout->setContentsMargins(10, 10, 10, 10);
        adjustSampleSizeInputLabel = new QLabel(adjustInputWidget);
        adjustSampleSizeInputLabel->setObjectName("adjustSampleSizeInputLabel");
        adjustSampleSizeInputLabel->setAlignment(Qt::AlignCenter);
        adjustSampleSizeInputLabel->setStyleSheet(
            "font: 18px 'Ubuntu';"
            "font-weight: bold;");
        adjustSampleSizeInputText = new QComboBox(adjustInputWidget);
        adjustSampleSizeInputText->setObjectName("adjustSampleSizeInputText");
        // adjustSampleSizeInputText->addItem("1024", 1024);
        adjustSampleSizeInputText->addItem("2048", 2048);
        adjustSampleSizeInputText->addItem("4096", 4096);
        adjustSampleSizeInputText->addItem("8192", 8192);

        adjustAverageInputLabel = new QLabel(adjustInputWidget);
        adjustAverageInputLabel->setObjectName("adjustAverageInputLabel");
        adjustAverageInputLabel->setAlignment(Qt::AlignCenter);
        adjustAverageInputLabel->setStyleSheet(
            "font: 18px 'Ubuntu';"
            "font-weight: bold;");
        adjustAverageInputText = new QComboBox(adjustInputWidget);
        adjustAverageInputText->setObjectName("adjustAverageInputText");
        adjustAverageInputText->addItem("2", 2);
        adjustAverageInputText->addItem("4", 4);
        adjustAverageInputText->addItem("8", 8);
        adjustAverageInputText->addItem("12", 12);
        adjustAverageInputText->addItem("16", 16);

        adjustSampleSizeInputLayout->addWidget(adjustSampleSizeInputLabel);
        adjustSampleSizeInputLayout->addWidget(adjustSampleSizeInputText);
        adjustSampleSizeInputLayout->addWidget(adjustAverageInputLabel);
        adjustSampleSizeInputLayout->addWidget(adjustAverageInputText);
        adjustSampleSizeInputLayout->setStretch(0, 1);
        adjustSampleSizeInputLayout->setStretch(1, 1);
        adjustSampleSizeInputLayout->setStretch(2, 1);
        adjustSampleSizeInputLayout->setStretch(3, 1);

        adjustInputLayout->addLayout(adjustSampleSizeInputLayout);

        adjustOneInputLayout = new QHBoxLayout();
        adjustOneInputLayout->setObjectName("adjustOneInputLayout");
        adjustOneInputLayout->setContentsMargins(10, 10, 10, 10);
        adjustOneInputLabel = new QLabel(adjustInputWidget);
        adjustOneInputLabel->setObjectName("adjustOneInputLabel");
        adjustOneInputLabel->setAlignment(Qt::AlignCenter);
        adjustOneInputLabel->setStyleSheet(
            "font: 18px 'Ubuntu';"
            "font-weight: bold;");
        adjustOneInputText = new QLineEdit(adjustInputWidget);
        adjustOneInputText->setObjectName("adjustOneInputText");
        adjustOneInputText->setInputMethodHints(Qt::ImhFormattedNumbersOnly);

        adjustTwoInputLabel = new QLabel(adjustInputWidget);
        adjustTwoInputLabel->setObjectName("adjustTwoInputLabel");
        adjustTwoInputLabel->setAlignment(Qt::AlignCenter);
        adjustTwoInputLabel->setStyleSheet(
            "font: 18px 'Ubuntu';"
            "font-weight: bold;");
        adjustTwoInputText = new QLineEdit(adjustInputWidget);
        adjustTwoInputText->setObjectName("adjustTwoInputText");
        adjustTwoInputText->setInputMethodHints(Qt::ImhFormattedNumbersOnly);

        adjustOneInputLayout->addWidget(adjustOneInputLabel);
        adjustOneInputLayout->addWidget(adjustOneInputText);
        adjustOneInputLayout->addWidget(adjustTwoInputLabel);
        adjustOneInputLayout->addWidget(adjustTwoInputText);
        adjustOneInputLayout->setStretch(0, 1);
        adjustOneInputLayout->setStretch(1, 1);
        adjustOneInputLayout->setStretch(2, 1);
        adjustOneInputLayout->setStretch(3, 1);

        adjustInputLayout->addLayout(adjustOneInputLayout);

        adjustBeaconsInputLayout = new QHBoxLayout();
        adjustBeaconsInputLayout->setObjectName("adjustBeaconsInputLayout");
        adjustBeaconsInputLayout->setContentsMargins(10, 10, 10, 10);
        adjustBeaconALayout = new QVBoxLayout();
        adjustBeaconALayout->setObjectName("adjustBeaconALayout");
        adjustBeaconALayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        adjustBeaconALayout->setContentsMargins(10, 10, 10, 10);
        adjustBeaconAInputLabel = new QLabel(adjustInputWidget);
        adjustBeaconAInputLabel->setObjectName("adjustBeaconAInputLabel");
        adjustBeaconAInputLabel->setAlignment(Qt::AlignCenter);
        adjustBeaconAInputLabel->setStyleSheet(
            "font: 18px 'Ubuntu';"
            "font-weight: bold;");
        adjustBeaconAInputText = new QLineEdit(adjustInputWidget);
        adjustBeaconAInputText->setObjectName("adjustBeaconAInputText");
        adjustBeaconAInputText->setInputMethodHints(Qt::ImhFormattedNumbersOnly);

        adjustBeaconALayout->addWidget(adjustBeaconAInputLabel);
        adjustBeaconALayout->addWidget(adjustBeaconAInputText);
        adjustBeaconALayout->setStretch(0, 1);
        adjustBeaconALayout->setStretch(1, 1);

        adjustBeaconsInputLayout->addLayout(adjustBeaconALayout);

        adjustBeaconBLayout = new QVBoxLayout();
        adjustBeaconBLayout->setObjectName("adjustBeaconBLayout");
        adjustBeaconBLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        adjustBeaconBLayout->setContentsMargins(10, 10, 10, 10);
        adjustBeaconBInputLabel = new QLabel(adjustInputWidget);
        adjustBeaconBInputLabel->setObjectName("adjustBeaconBInputLabel");
        adjustBeaconBInputLabel->setAlignment(Qt::AlignCenter);
        adjustBeaconBInputLabel->setStyleSheet(
            "font: 18px 'Ubuntu';"
            "font-weight: bold;");
        adjustBeaconBInputText = new QLineEdit(adjustInputWidget);
        adjustBeaconBInputText->setObjectName("adjustBeaconBInputText");
        adjustBeaconBInputText->setInputMethodHints(Qt::ImhFormattedNumbersOnly);

        adjustBeaconBLayout->addWidget(adjustBeaconBInputLabel);
        adjustBeaconBLayout->addWidget(adjustBeaconBInputText);
        adjustBeaconBLayout->setStretch(0, 1);
        adjustBeaconBLayout->setStretch(1, 1);

        adjustBeaconsInputLayout->addLayout(adjustBeaconBLayout);

        adjustBeaconCLayout = new QVBoxLayout();
        adjustBeaconCLayout->setObjectName("adjustBeaconCLayout");
        adjustBeaconCLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        adjustBeaconCLayout->setContentsMargins(10, 10, 10, 10);
        adjustBeaconCInputLabel = new QLabel(adjustInputWidget);
        adjustBeaconCInputLabel->setObjectName("adjustBeaconCInputLabel");
        adjustBeaconCInputLabel->setAlignment(Qt::AlignCenter);
        adjustBeaconCInputLabel->setStyleSheet(
            "font: 18px 'Ubuntu';"
            "font-weight: bold;");
        adjustBeaconCInputText = new QLineEdit(adjustInputWidget);
        adjustBeaconCInputText->setObjectName("adjustBeaconCInputText");
        adjustBeaconCInputText->setInputMethodHints(Qt::ImhFormattedNumbersOnly);

        adjustBeaconCLayout->addWidget(adjustBeaconCInputLabel);
        adjustBeaconCLayout->addWidget(adjustBeaconCInputText);
        adjustBeaconCLayout->setStretch(0, 1);
        adjustBeaconCLayout->setStretch(1, 1);

        adjustBeaconsInputLayout->addLayout(adjustBeaconCLayout);
        adjustBeaconsInputLayout->setStretch(0, 1);
        adjustBeaconsInputLayout->setStretch(1, 1);
        adjustBeaconsInputLayout->setStretch(2, 1);

        adjustInputLayout->addLayout(adjustBeaconsInputLayout);

        adjustThreeInputLayout = new QHBoxLayout();
        adjustThreeInputLayout->setObjectName("adjustThreeInputLayout");
        adjustThreeInputLayout->setContentsMargins(10, 10, 10, 10);
        adjustInputAccept = new QPushButton(adjustInputWidget);
        adjustInputAccept->setObjectName("adjustInputAccept");
        sizePolicy1.setHeightForWidth(adjustInputAccept->sizePolicy().hasHeightForWidth());
        adjustInputAccept->setFocusPolicy(Qt::NoFocus);
        adjustInputAccept->setSizePolicy(sizePolicy1);
        adjustInputCancel = new QPushButton(adjustInputWidget);
        adjustInputCancel->setObjectName("adjustInputCancel");
        sizePolicy1.setHeightForWidth(adjustInputCancel->sizePolicy().hasHeightForWidth());
        adjustInputCancel->setFocusPolicy(Qt::NoFocus);
        adjustInputCancel->setSizePolicy(sizePolicy1);

        adjustThreeInputLayout->addWidget(adjustInputAccept);
        adjustThreeInputLayout->addWidget(adjustInputCancel);
        adjustThreeInputLayout->setStretch(0, 1);
        adjustThreeInputLayout->setStretch(1, 1);

        adjustInputLayout->addLayout(adjustThreeInputLayout);

        adjustInputLayout->setStretch(0, 2);
        adjustInputLayout->setStretch(1, 2);
        adjustInputLayout->setStretch(2, 2);
        adjustInputLayout->setStretch(3, 2);
        adjustInputLayout->setStretch(4, 1);
    }
};