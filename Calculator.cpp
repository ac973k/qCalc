#include "Calculator.hpp"
#include "MatrixOperationsDialog.hpp"

Calculator::Calculator(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Calculator");

    layout = new QGridLayout(this);

    resultLabel = new QLabel("Result:", this);
    layout->addWidget(resultLabel, 0, 0, 1, 2);

    resultLineEdit = new QLineEdit(this);
    resultLineEdit->setReadOnly(true);
    layout->addWidget(resultLineEdit, 0, 2, 1, 2);

    createButtons();

    setLayout(layout);
}

void Calculator::createButtons() {
    // Остается без изменений
    QPushButton *buttons[5][4];
    const QString buttonText[5][4] = {
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"0", ".", "=", "+"},
        {"sqrt", "pow", "C", "%"}
    };

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            buttons[i][j] = new QPushButton(buttonText[i][j], this);
            layout->addWidget(buttons[i][j], i + 1, j);
            connect(buttons[i][j], &QPushButton::clicked, this, [=]() {
                onButtonClicked(buttonText[i][j]);
            });
        }
    }

    QPushButton *extraButton = new QPushButton("Дополнительно", this);
    layout->addWidget(extraButton, 6, 0, 1, 4); // Расположение в последней строке
    connect(extraButton, &QPushButton::clicked, this, &Calculator::openExtraWindow);
}

void Calculator::onButtonClicked(const QString &buttonText) {
    QString currentText = resultLineEdit->text();

    if (buttonText == "=") {
        try {
            double result = evaluateExpression(currentText);
            resultLineEdit->setText(QString::number(result));
        } catch (const std::invalid_argument &ex) {
            resultLineEdit->setText("Error");
        }
    } else if (buttonText == "C") {
        resultLineEdit->clear();
    } else if (buttonText == "sqrt") {
        try {
            double number = currentText.toDouble();
            if (number >= 0) {
                resultLineEdit->setText(QString::number(std::sqrt(number)));
            } else {
                resultLineEdit->setText("Error");
            }
        } catch (...) {
            resultLineEdit->setText("Error");
        }
    } else if (buttonText == "pow") {
        resultLineEdit->setText(currentText + " ^ ");
    } else if (buttonText == "+") {
        resultLineEdit->setText(currentText + " + ");
    } else if (buttonText == "-") {
        resultLineEdit->setText(currentText + " - ");
    } else if (buttonText == "*") {
        resultLineEdit->setText(currentText + " * ");
    } else if (buttonText == "/") {
        resultLineEdit->setText(currentText + " / ");
    } else if (buttonText == "%") {
        resultLineEdit->setText(currentText + " % ");
    } else {
        resultLineEdit->setText(currentText + buttonText);
    }
}

double Calculator::evaluateExpression(const QString &expression) {
    QStringList tokens = expression.split(' ');

    if (tokens.size() != 3) {
        throw std::invalid_argument("Invalid expression format");
    }

    double operand1 = tokens[0].toDouble();
    QString op = tokens[1];
    double operand2 = tokens[2].toDouble();

    if (op == "+") {
        return operand1 + operand2;
    } else if (op == "-") {
        return operand1 - operand2;
    } else if (op == "*") {
        return operand1 * operand2;
    } else if (op == "/") {
        if (operand2 != 0) {
            return operand1 / operand2;
        } else {
            throw std::invalid_argument("Division by zero");
        }
    } else if (op == "^") {
        return std::pow(operand1, operand2);
    } else if (op == "%") {
        return operand1 * (operand2 / 100.0);
    } else {
        throw std::invalid_argument("Invalid operator");
    }
}

void Calculator::openExtraWindow() {
    MatrixOperationsDialog dialog(this);
    dialog.exec(); // Отображение диалогового окна
}
