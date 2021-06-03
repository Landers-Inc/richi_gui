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
    QWidget *dialogWidget;
    QQuickWidget *keyboardWidget;
    QWidget *beaconWidget;
    QVBoxLayout *beaconLayout;
    QHBoxLayout *beaconOneLayout;
    QHBoxLayout *beaconTwoLayout;
    QLabel *beaconTopLabel;
    QLabel *beaconOneLabel;
    QLabel *beaconTwoLabel;
    QLineEdit *beaconOneText;
    QLineEdit *beaconTwoText;
    QPushButton *beaconAccept;
    QPushButton *beaconCancel;

    explicit BeaconInputDialog(QWidget *parent = 0) {
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

        beaconWidget = new InputWidget(dialogWidget);
        beaconWidget->setObjectName("beaconWidget");
        beaconWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        beaconWidget->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
        beaconWidget->move(400, 100);
        beaconWidget->setMinimumSize(480, 200);
        beaconWidget->setWindowFlags(Qt::Dialog);
        beaconWidget->setStyleSheet(
            "#beaconWidget{"
            "background: #ddd;"
            "border-radius: 10px;"
            "border-style: solid;"
            "border-width: 2px;"
            "border-radius: 7px;"
            "border-color: black;}");

        beaconLayout = new QVBoxLayout(beaconWidget);
        beaconLayout->setObjectName("beaconLayout");
        beaconLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        beaconLayout->setContentsMargins(10, 10, 10, 10);
        beaconTopLabel = new QLabel(beaconWidget);
        beaconTopLabel->setObjectName("beaconTopLabel");
        beaconTopLabel->setContentsMargins(10, 10, 10, 10);
        beaconTopLabel->setAlignment(Qt::AlignCenter);
        beaconTopLabel->setStyleSheet(
            "border: 1px solid #000;"
            "font: 30px 'Ubuntu';"
            "font-weight: bold;");

        keyboardWidget = new QQuickWidget(QUrl("qrc:/main.qml"), dialogWidget);
        keyboardWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        keyboardWidget->move(200, 300);
        keyboardWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
        keyboardWidget->setAttribute(Qt::WA_TranslucentBackground);
        keyboardWidget->setAttribute(Qt::WA_InputMethodEnabled, true);
        keyboardWidget->setClearColor(Qt::transparent);
        keyboardWidget->setMinimumSize(880, 500);
        keyboardWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

        beaconLayout->addWidget(beaconTopLabel);

        beaconOneLayout = new QHBoxLayout();
        beaconOneLayout->setObjectName("beaconOneLayout");
        beaconOneLayout->setContentsMargins(10, 10, 10, 10);
        beaconOneLabel = new QLabel(beaconWidget);
        beaconOneLabel->setObjectName("beaconOneLabel");
        beaconOneLabel->setAlignment(Qt::AlignCenter);
        beaconOneLabel->setStyleSheet(
            "font: 18px 'Ubuntu';"
            "font-weight: bold;");
        beaconOneText = new QLineEdit(beaconWidget);
        beaconOneText->setObjectName("beaconOneText");
        beaconOneText->setInputMethodHints(Qt::ImhDigitsOnly);

        beaconOneLayout->addWidget(beaconOneLabel);
        beaconOneLayout->addWidget(beaconOneText);

        beaconLayout->addLayout(beaconOneLayout);

        beaconOneLayout->setStretch(0, 1);
        beaconOneLayout->setStretch(1, 1);

        beaconTwoLayout = new QHBoxLayout();
        beaconTwoLayout->setObjectName("beaconTwoLayout");
        beaconTwoLayout->setContentsMargins(10, 10, 10, 10);
        beaconAccept = new QPushButton(beaconWidget);
        beaconAccept->setObjectName("beaconAccept");
        sizePolicy1.setHeightForWidth(beaconAccept->sizePolicy().hasHeightForWidth());
        beaconAccept->setSizePolicy(sizePolicy1);
        beaconCancel = new QPushButton(beaconWidget);
        beaconCancel->setObjectName("beaconCancel");
        sizePolicy1.setHeightForWidth(beaconCancel->sizePolicy().hasHeightForWidth());
        beaconCancel->setSizePolicy(sizePolicy1);

        beaconTwoLayout->addWidget(beaconAccept);
        beaconTwoLayout->addWidget(beaconCancel);

        beaconLayout->addLayout(beaconTwoLayout);

        beaconTwoLayout->setStretch(0, 1);
        beaconTwoLayout->setStretch(1, 1);

        beaconLayout->setStretch(0, 1);
        beaconLayout->setStretch(1, 1);
        beaconLayout->setStretch(2, 1);
    }
};

class BeaconFoundDialog : public QDialog {
    Q_OBJECT
   public:
    QWidget *dialogWidget;
    QWidget *beaconWidget;
    QVBoxLayout *beaconLayout;
    QHBoxLayout *beaconOneLayout;
    QLabel *beaconLabel;
    QPushButton *beaconAccept;
    QPushButton *beaconCancel;

    explicit BeaconFoundDialog(QWidget *parent = 0) {
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

        beaconWidget = new QDialog(dialogWidget);
        beaconWidget->setObjectName("beaconWidget");
        beaconWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        beaconWidget->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
        beaconWidget->move(300, 100);
        beaconWidget->setMinimumSize(680, 200);
        beaconWidget->setWindowFlags(Qt::Dialog);
        beaconWidget->setStyleSheet(
            "#warningWidget{"
            "background: #ddd;"
            "border-radius: 10px;"
            "border-style: solid;"
            "border-width: 2px;"
            "border-radius: 7px;"
            "border-color: black;}");

        beaconLayout = new QVBoxLayout(beaconWidget);
        beaconLayout->setObjectName("beaconLayout");
        beaconLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        beaconLayout->setContentsMargins(10, 10, 10, 10);
        beaconLabel = new QLabel(beaconWidget);
        beaconLabel->setObjectName("beaconLabel");
        beaconLabel->setContentsMargins(10, 10, 10, 10);
        beaconLabel->setAlignment(Qt::AlignCenter);
        beaconLabel->setStyleSheet(
            "border: 1px solid #000;"
            "font: 20px 'Ubuntu';"
            "font-weight: bold;");

        beaconLayout->addWidget(beaconLabel);

        beaconOneLayout = new QHBoxLayout();
        beaconOneLayout->setObjectName("beaconOneLayout");
        beaconOneLayout->setContentsMargins(10, 10, 10, 10);
        beaconAccept = new QPushButton(beaconWidget);
        beaconAccept->setObjectName("beaconAccept");
        sizePolicy1.setHeightForWidth(beaconAccept->sizePolicy().hasHeightForWidth());
        beaconAccept->setSizePolicy(sizePolicy1);
        beaconCancel = new QPushButton(beaconWidget);
        beaconCancel->setObjectName("beaconCancel");
        sizePolicy1.setHeightForWidth(beaconCancel->sizePolicy().hasHeightForWidth());
        beaconCancel->setSizePolicy(sizePolicy1);

        beaconOneLayout->addWidget(beaconAccept);
        beaconOneLayout->addWidget(beaconCancel);

        beaconLayout->addLayout(beaconOneLayout);

        beaconOneLayout->setStretch(0, 1);
        beaconOneLayout->setStretch(1, 1);

        beaconLayout->setStretch(0, 1);
        beaconLayout->setStretch(1, 1);
        beaconLayout->setStretch(2, 1);
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
        warningOneLayout->setObjectName("warningOneLayout");
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
