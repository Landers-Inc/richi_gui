#pragma once

#include <QDialog>
#include <QQuickWidget>
#include <QtWidgets>
#include <iostream>

#include "../stylesheetdefines.h"

class BeaconTableItem : public QHBoxLayout {
    Q_OBJECT
   public:
    QLabel *id;
    QLabel *beaconType;
    QLabel *preDistance;
    QLabel *prePower;
    QLabel *postPower;

    explicit BeaconTableItem(QWidget *parent = 0) {
        this->setContentsMargins(0, 0, 0, 0);
        this->setSpacing(0);
        id = new QLabel();
        id->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        id->setFixedHeight(40);
        id->setAlignment(Qt::AlignCenter);
        id->setStyleSheet(BEACON_TABLE_ITEM);
        beaconType = new QLabel();
        beaconType->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        beaconType->setFixedHeight(40);
        beaconType->setAlignment(Qt::AlignCenter);
        beaconType->setStyleSheet(BEACON_TABLE_ITEM);
        preDistance = new QLabel();
        preDistance->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        preDistance->setFixedHeight(40);
        preDistance->setAlignment(Qt::AlignCenter);
        preDistance->setStyleSheet(BEACON_TABLE_ITEM);
        prePower = new QLabel();
        prePower->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        prePower->setFixedHeight(40);
        prePower->setAlignment(Qt::AlignCenter);
        prePower->setStyleSheet(BEACON_TABLE_ITEM);
        postPower = new QLabel();
        postPower->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        postPower->setFixedHeight(40);
        postPower->setAlignment(Qt::AlignCenter);
        postPower->setStyleSheet(BEACON_TABLE_ITEM);
        this->addWidget(id);
        this->addWidget(beaconType);
        this->addWidget(preDistance);
        this->addWidget(prePower);
        this->addWidget(postPower);
        this->setStretch(0, 1);
        this->setStretch(1, 1);
        this->setStretch(2, 1);
        this->setStretch(3, 1);
        this->setStretch(4, 1);
    }
};

class BeaconTable : public QDialog {
    Q_OBJECT
   public:
    QWidget *tableWidget;
    QVBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QVBoxLayout *beaconListLayout;
    BeaconTableItem *beaconLabelsLayout;
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
        tableWidget->setStyleSheet("#tableWidget{background: #ddd;}");
        tableWidget->setVisible(false);

        mainLayout = new QVBoxLayout(tableWidget);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        mainLayout->setContentsMargins(10, 10, 10, 10);

        beaconListLayout = new QVBoxLayout();
        beaconListLayout->setObjectName("beaconListLayout");
        beaconListLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        beaconListLayout->setContentsMargins(10, 10, 25, 10);
        beaconListLayout->setSpacing(0);
        beaconListLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

        beaconLabelsLayout = new BeaconTableItem();

        beaconListLayout->addLayout(beaconLabelsLayout);

        scrollArea = new QScrollArea(tableWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setBackgroundRole(QPalette::Dark);
        scrollArea->setLayout(beaconListLayout);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setStyleSheet("#scrollArea{background: #ddd;}");

        buttonsLayout = new QHBoxLayout();
        buttonsLayout->setObjectName("buttonsLayout");
        buttonsLayout->setContentsMargins(10, 10, 10, 10);

        updateButton = new QPushButton(tableWidget);
        updateButton->setObjectName("updateButton");
        updateButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        updateButton->setFixedHeight(60);
        updateButton->setFocusPolicy(Qt::NoFocus);

        cancelButton = new QPushButton(tableWidget);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        cancelButton->setFixedHeight(60);
        cancelButton->setFocusPolicy(Qt::NoFocus);

        buttonsLayout->addWidget(updateButton);
        buttonsLayout->addWidget(cancelButton);

        buttonsLayout->setStretch(0, 1);
        buttonsLayout->setStretch(1, 1);

        mainLayout->addWidget(scrollArea);
        mainLayout->addLayout(buttonsLayout);

        mainLayout->setStretch(0, 3);
        mainLayout->setStretch(0, 1);
    }
};