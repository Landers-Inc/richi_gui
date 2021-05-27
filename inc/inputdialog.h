#pragma once

#include <QDialog>
#include <QQuickWidget>
#include <QtWidgets>
#include <iostream>

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
    }
};

class InputDialog : public QDialog {
    Q_OBJECT
   public:
    QWidget *dialogWidget;
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
    QPushButton *inputBeaconAccept;
    QPushButton *inputBeaconCancel;

    explicit InputDialog(QWidget *parent = 0) {
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu"));
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);

        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(parent->sizePolicy().hasHeightForWidth());

        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);

        dialogWidget = new QWidget(parent);
        dialogWidget->setObjectName(QString::fromUtf8("dialogWidget"));
        sizePolicy.setHeightForWidth(dialogWidget->sizePolicy().hasHeightForWidth());
        dialogWidget->setSizePolicy(sizePolicy);
        dialogWidget->setMinimumSize(QSize(1280, 800));
        dialogWidget->setMaximumSize(QSize(1280, 800));
        dialogWidget->setVisible(false);

        inputBeaconWidget = new InputWidget(dialogWidget);
        inputBeaconWidget->setObjectName(QString::fromUtf8("inputBeaconWidget"));
        inputBeaconWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        inputBeaconWidget->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
        inputBeaconWidget->move(200, 20);
        inputBeaconWidget->setMinimumSize(880, 300);
        inputBeaconWidget->setWindowFlags(Qt::Dialog);

        inputBeaconLayout = new QVBoxLayout(inputBeaconWidget);
        inputBeaconLayout->setObjectName(QString::fromUtf8("inputBeaconLayout"));
        inputBeaconLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        inputBeaconLayout->setContentsMargins(10, 10, 10, 10);
        inputBeaconTopLabel = new QLabel(inputBeaconWidget);
        inputBeaconTopLabel->setObjectName(QString::fromUtf8("inputBeaconTopLabel"));
        inputBeaconTopLabel->setContentsMargins(10, 10, 10, 10);

        keyboardWidget = new QQuickWidget(QUrl("qrc:/main.qml"), dialogWidget);
        keyboardWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        keyboardWidget->move(200, 300);
        keyboardWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
        keyboardWidget->setAttribute(Qt::WA_TranslucentBackground);
        keyboardWidget->setAttribute(Qt::WA_InputMethodEnabled, true);
        keyboardWidget->setClearColor(Qt::transparent);
        keyboardWidget->setMinimumSize(880, 500);
        keyboardWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

        inputBeaconLayout->addWidget(inputBeaconTopLabel);

        inputBeaconOneLayout = new QHBoxLayout();
        inputBeaconOneLayout->setObjectName(QString::fromUtf8("inputBeaconOneLayout"));
        inputBeaconOneLayout->setContentsMargins(10, 10, 10, 10);
        inputBeaconOneLabel = new QLabel(inputBeaconWidget);
        inputBeaconOneLabel->setObjectName(QString::fromUtf8("inputBeaconOneLabel"));
        inputBeaconOneText = new QLineEdit(inputBeaconWidget);
        inputBeaconOneText->setObjectName(QString::fromUtf8("inputBeaconOneText"));
        inputBeaconOneText->setInputMethodHints(Qt::ImhDigitsOnly);

        inputBeaconOneLayout->addWidget(inputBeaconOneLabel);
        inputBeaconOneLayout->addWidget(inputBeaconOneText);

        inputBeaconLayout->addLayout(inputBeaconOneLayout);

        inputBeaconOneLayout->setStretch(0, 1);
        inputBeaconOneLayout->setStretch(1, 1);

        inputBeaconTwoLayout = new QHBoxLayout();
        inputBeaconTwoLayout->setObjectName(QString::fromUtf8("inputBeaconTwoLayout"));
        inputBeaconTwoLayout->setContentsMargins(10, 10, 10, 10);
        inputBeaconAccept = new QPushButton(inputBeaconWidget);
        inputBeaconAccept->setObjectName(QString::fromUtf8("inputBeaconAccept"));
        sizePolicy1.setHeightForWidth(inputBeaconAccept->sizePolicy().hasHeightForWidth());
        inputBeaconAccept->setSizePolicy(sizePolicy1);
        inputBeaconAccept->setFont(font);
        inputBeaconCancel = new QPushButton(inputBeaconWidget);
        inputBeaconCancel->setObjectName(QString::fromUtf8("inputBeaconCancel"));
        sizePolicy1.setHeightForWidth(inputBeaconCancel->sizePolicy().hasHeightForWidth());
        inputBeaconCancel->setSizePolicy(sizePolicy1);
        inputBeaconCancel->setFont(font);

        inputBeaconTwoLayout->addWidget(inputBeaconAccept);
        inputBeaconTwoLayout->addWidget(inputBeaconCancel);

        inputBeaconLayout->addLayout(inputBeaconTwoLayout);

        inputBeaconTwoLayout->setStretch(0, 1);
        inputBeaconTwoLayout->setStretch(1, 1);

        inputBeaconLayout->setStretch(0, 1);
        inputBeaconLayout->setStretch(1, 1);
        inputBeaconLayout->setStretch(2, 1);
    }
};
