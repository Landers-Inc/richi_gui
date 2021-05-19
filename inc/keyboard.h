#pragma once

#include <QObject>
#include <QQuickWidget>
#include <iostream>

class Keyboard : public QQuickWidget {
    Q_OBJECT
   public:
    using QQuickWidget::QQuickWidget;
    void keyPressEvent(QKeyEvent *event) override {
        std::cout << "Funcionaaaa" << std::endl;
    };
};
