#pragma once

#include <QObject>
#include <QQuickWidget>
#include <QtWidgets>

class InputDialog : public QObject{
    Q_OBJECT
private:
    QQuickWidget *keyboardWidget;
    QWidget *inputBeaconWidget;
    QVBoxLayout *inputBeaconLayout;
    QHBoxLayout *inputBeaconOneLayout;
    QHBoxLayout *inputBeaconTwoLayout;
    QLabel *inputBeaconTopLabel;
    QLabel *inputBeaconOneLabel;
    QLabel *inputBeaconTwoLabel;
    QLineEdit *inputBeaconOneText;
    QLineEdit *inputBeaconTwoText;
public:
    explicit InputDialog(QWidget *parent = 0){
        inputBeaconWidget = new QWidget(parent);
        inputBeaconWidget->setObjectName(QString::fromUtf8("inputBeaconWidget"));
        inputBeaconWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        inputBeaconWidget->move(440, 50);
        inputBeaconWidget->setMinimumSize(400, 300);
        inputBeaconWidget->setWindowFlags(Qt::Dialog);
        inputBeaconWidget->setVisible(false);

        inputBeaconLayout = new QVBoxLayout(inputBeaconWidget);
        inputBeaconLayout->setObjectName(QString::fromUtf8("inputBeaconLayout"));
        inputBeaconLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        inputBeaconLayout->setContentsMargins(10, 10, 10, 10);
        inputBeaconTopLabel = new QLabel(inputBeaconWidget);
        inputBeaconTopLabel->setObjectName(QString::fromUtf8("inputBeaconTopLabel"));
        inputBeaconTopLabel->setContentsMargins(10, 10, 10, 10);

        keyboardWidget = new QQuickWidget(QUrl("qrc:/main.qml"), parent);
        keyboardWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        keyboardWidget->move(200, 400);
        keyboardWidget->setMinimumSize(880, 400);
        keyboardWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
        keyboardWidget->setVisible(false);

        inputBeaconLayout->addWidget(inputBeaconTopLabel);

        inputBeaconOneLayout = new QHBoxLayout();
        inputBeaconOneLayout->setObjectName(QString::fromUtf8("inputBeaconOneLayout"));
        inputBeaconOneLayout->setContentsMargins(10, 10, 10, 10);
        inputBeaconOneLabel = new QLabel(inputBeaconWidget);
        inputBeaconOneLabel->setObjectName(QString::fromUtf8("inputBeaconOneLabel"));
        inputBeaconOneText = new QLineEdit(inputBeaconWidget);
        inputBeaconOneText->setObjectName(QString::fromUtf8("inputBeaconOneText"));

        inputBeaconOneLayout->addWidget(inputBeaconOneLabel);
        inputBeaconOneLayout->addWidget(inputBeaconOneText);

        inputBeaconLayout->addLayout(inputBeaconOneLayout);

        inputBeaconOneLayout->setStretch(0, 1);
        inputBeaconOneLayout->setStretch(1, 1);

        inputBeaconTwoLayout = new QHBoxLayout();
        inputBeaconTwoLayout->setObjectName(QString::fromUtf8("inputBeaconTwoLayout"));
        inputBeaconTwoLayout->setContentsMargins(10, 10, 10, 10);
        inputBeaconTwoLabel = new QLabel(inputBeaconWidget);
        inputBeaconTwoLabel->setObjectName(QString::fromUtf8("inputBeaconTwoLabel"));
        inputBeaconTwoText = new QLineEdit(inputBeaconWidget);
        inputBeaconTwoText->setObjectName(QString::fromUtf8("inputBeaconTwoText"));

        inputBeaconTwoLayout->addWidget(inputBeaconTwoLabel);
        inputBeaconTwoLayout->addWidget(inputBeaconTwoText);

        inputBeaconLayout->addLayout(inputBeaconTwoLayout);

        inputBeaconTwoLayout->setStretch(0, 1);
        inputBeaconTwoLayout->setStretch(1, 1);

        inputBeaconLayout->setStretch(0, 1);
        inputBeaconLayout->setStretch(1, 1);
        inputBeaconLayout->setStretch(2, 1);
    }
};
