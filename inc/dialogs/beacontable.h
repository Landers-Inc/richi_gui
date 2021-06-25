#pragma once

#include <QDialog>
#include <QQuickWidget>
#include <QtWidgets>
#include <iostream>

class BeaconTable : public QDialog {
    Q_OBJECT
   public:
    QWidget *tableWidget;
    QVBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QVBoxLayout *beaconListLayout;
    QHBoxLayout *beaconLabelsLayout;
    QLabel *beaconPreLabel;
    QLabel *beaconPostLabel;
    QLabel *beaconDiffLabel;
    QHBoxLayout *buttonsLayout;
    QPushButton *updateButton;
    QPushButton *cancelButton;

    explicit BeaconTable(QWidget *parent = 0) {
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(parent->sizePolicy().hasHeightForWidth());

        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);

        tableWidget = new QWidget(parent);
        tableWidget->setObjectName("tableWidget");
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setMinimumSize(QSize(1280, 800));
        tableWidget->setMaximumSize(QSize(1280, 800));
        tableWidget->setVisible(true);

        mainLayout = new QVBoxLayout(tableWidget);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        mainLayout->setContentsMargins(10, 10, 10, 10);

        beaconListLayout = new QVBoxLayout();
        beaconListLayout->setObjectName("beaconListLayout");
        beaconListLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        beaconListLayout->setContentsMargins(10, 10, 10, 10);
        beaconListLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

        beaconLabelsLayout = new QHBoxLayout();
        beaconLabelsLayout->setObjectName("beaconLabelsLayout");
        beaconLabelsLayout->setContentsMargins(10, 10, 10, 10);

        beaconPreLabel = new QLabel(tableWidget);
        beaconPreLabel->setObjectName("beaconPreLabel");
        beaconPreLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        beaconPreLabel->setFixedHeight(50);
        beaconPreLabel->setContentsMargins(10, 10, 10, 10);
        beaconPreLabel->setAlignment(Qt::AlignCenter);
        beaconPreLabel->setStyleSheet(
            "border: 1px solid #000;"
            "font: 30px 'Ubuntu';"
            "font-weight: bold;");

        beaconPostLabel = new QLabel(tableWidget);
        beaconPostLabel->setObjectName("beaconPostLabel");
        beaconPostLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        beaconPostLabel->setFixedHeight(50);
        beaconPostLabel->setContentsMargins(10, 10, 10, 10);
        beaconPostLabel->setAlignment(Qt::AlignCenter);
        beaconPostLabel->setStyleSheet(
            "border: 1px solid #000;"
            "font: 30px 'Ubuntu';"
            "font-weight: bold;");

        beaconDiffLabel = new QLabel(tableWidget);
        beaconDiffLabel->setObjectName("beaconDiffLabel");
        beaconDiffLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        beaconDiffLabel->setFixedHeight(50);
        beaconDiffLabel->setContentsMargins(10, 10, 10, 10);
        beaconDiffLabel->setAlignment(Qt::AlignCenter);
        beaconDiffLabel->setStyleSheet(
            "border: 1px solid #000;"
            "font: 30px 'Ubuntu';"
            "font-weight: bold;");

        beaconLabelsLayout->addWidget(beaconPreLabel);
        beaconLabelsLayout->addWidget(beaconPostLabel);
        beaconLabelsLayout->addWidget(beaconDiffLabel);

        beaconLabelsLayout->setStretch(0, 1);
        beaconLabelsLayout->setStretch(1, 1);
        beaconLabelsLayout->setStretch(2, 1);

        beaconListLayout->addLayout(beaconLabelsLayout);

        scrollArea = new QScrollArea(tableWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setBackgroundRole(QPalette::Dark);
        scrollArea->setLayout(beaconListLayout);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        buttonsLayout = new QHBoxLayout();
        buttonsLayout->setObjectName("buttonsLayout");
        buttonsLayout->setContentsMargins(10, 10, 10, 10);

        updateButton = new QPushButton(tableWidget);
        updateButton->setObjectName("updateButton");
        sizePolicy1.setHeightForWidth(updateButton->sizePolicy().hasHeightForWidth());
        updateButton->setFocusPolicy(Qt::NoFocus);
        updateButton->setSizePolicy(sizePolicy1);

        cancelButton = new QPushButton(tableWidget);
        cancelButton->setObjectName("cancelButton");
        sizePolicy1.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
        cancelButton->setFocusPolicy(Qt::NoFocus);
        cancelButton->setSizePolicy(sizePolicy1);

        buttonsLayout->addWidget(updateButton);
        buttonsLayout->addWidget(cancelButton);

        buttonsLayout->setStretch(0, 1);
        buttonsLayout->setStretch(1, 1);

        mainLayout->addWidget(scrollArea);
        mainLayout->addLayout(buttonsLayout);

        mainLayout->setStretch(0, 5);
        mainLayout->setStretch(0, 1);
    }
};