#pragma once

#include <QDialog>
#include <QQuickWidget>
#include <QtWidgets>
#include <iostream>

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
        dialogWidget->setMinimumSize(QSize(1280, 800));
        dialogWidget->setMaximumSize(QSize(1280, 800));
        dialogWidget->setVisible(false);

        warningWidget = new QDialog(dialogWidget);
        warningWidget->setObjectName("warningWidget");
        warningWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        warningWidget->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
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
        warningOneLayout->setObjectName("inputBeaconTwoLayout");
        warningOneLayout->setContentsMargins(10, 10, 10, 10);
        warningAccept = new QPushButton(warningWidget);
        warningAccept->setObjectName("warningAccept");
        sizePolicy1.setHeightForWidth(warningAccept->sizePolicy().hasHeightForWidth());
        warningAccept->setSizePolicy(sizePolicy1);
        warningCancel = new QPushButton(warningWidget);
        warningCancel->setObjectName("warningCancel");
        sizePolicy1.setHeightForWidth(warningCancel->sizePolicy().hasHeightForWidth());
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
