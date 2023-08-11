#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <cmath>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

private slots:
    void onButtonClicked(const QString &buttonText);
    double evaluateExpression(const QString &expression);
    void openExtraWindow();

private:
    QGridLayout *layout;
    QLabel *resultLabel;
    QLineEdit *resultLineEdit;

    void createButtons();
};

#endif // CALCULATOR_HPP
