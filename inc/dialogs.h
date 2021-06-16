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

class BeaconInputDialog : public QDialog {
    Q_OBJECT
   public:
    QWidget *dialogInputWidget;
    QWidget *beaconInputWidget;
    QVBoxLayout *beaconInputLayout;
    QHBoxLayout *beaconOneInputLayout;
    QHBoxLayout *beaconTwoInputLayout;
    QLabel *beaconTopInputLabel;
    QLabel *beaconOneInputLabel;
    QLineEdit *beaconOneInputText;
    QPushButton *beaconInputAccept;
    QPushButton *beaconInputCancel;

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
        dialogInputWidget->setMinimumSize(QSize(1280, 800));
        dialogInputWidget->setMaximumSize(QSize(1280, 800));
        dialogInputWidget->setVisible(false);

        beaconInputWidget = new InputWidget(dialogInputWidget);
        beaconInputWidget->setObjectName("beaconInputWidget");
        beaconInputWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        beaconInputWidget->move(400, 100);
        beaconInputWidget->setMinimumSize(480, 220);
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

        beaconInputLayout->addLayout(beaconOneInputLayout);

        beaconOneInputLayout->setStretch(0, 1);
        beaconOneInputLayout->setStretch(1, 1);

        beaconTwoInputLayout = new QHBoxLayout();
        beaconTwoInputLayout->setObjectName("beaconTwoInputLayout");
        beaconTwoInputLayout->setContentsMargins(10, 10, 10, 10);
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

        beaconTwoInputLayout->addWidget(beaconInputAccept);
        beaconTwoInputLayout->addWidget(beaconInputCancel);

        beaconInputLayout->addLayout(beaconTwoInputLayout);

        beaconTwoInputLayout->setStretch(0, 1);
        beaconTwoInputLayout->setStretch(1, 1);

        beaconInputLayout->setStretch(0, 1);
        beaconInputLayout->setStretch(1, 1);
        beaconInputLayout->setStretch(2, 1);
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
        dialogFoundWidget->setMinimumSize(QSize(1280, 800));
        dialogFoundWidget->setMaximumSize(QSize(1280, 800));
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
        dialogWidget->setMinimumSize(QSize(1280, 800));
        dialogWidget->setMaximumSize(QSize(1280, 800));
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
