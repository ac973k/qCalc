#include "MatrixOperationsDialog.hpp"
#include "MatrixInputDialog.hpp"
#include "qdebug.h"
#include <QVBoxLayout>
#include <QHBoxLayout> // Добавлен для размещения элементов в одной строке

MatrixOperationsDialog::MatrixOperationsDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Матричные операции");
    setupUI();
}

void MatrixOperationsDialog::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *matrix1Label = new QLabel("Размеры матрицы 1:");
    rowsSpinBox1 = new QSpinBox;
    colsSpinBox1 = new QSpinBox;

    QLabel *matrix2Label = new QLabel("Размеры матрицы 2:");
    rowsSpinBox2 = new QSpinBox;
    colsSpinBox2 = new QSpinBox;

    QLabel *operationLabel = new QLabel("Операция:");
    operationComboBox = new QComboBox;
    operationComboBox->addItem("Транспонирование");
    operationComboBox->addItem("Сложение");
    operationComboBox->addItem("Вычитание");
    operationComboBox->addItem("Умножение");
    operationComboBox->addItem("Обратная матрица");
    operationComboBox->addItem("Умножение на число");
    operationComboBox->addItem("Нахождение определителя");

    QHBoxLayout *matrix1Layout = new QHBoxLayout;
    matrix1Layout->addWidget(matrix1Label);
    matrix1Layout->addWidget(rowsSpinBox1);
    matrix1Layout->addWidget(colsSpinBox1);

    QHBoxLayout *matrix2Layout = new QHBoxLayout;
    matrix2Layout->addWidget(matrix2Label);
    matrix2Layout->addWidget(rowsSpinBox2);
    matrix2Layout->addWidget(colsSpinBox2);

    layout->addLayout(matrix1Layout);
    layout->addLayout(matrix2Layout);

    layout->addWidget(operationLabel);
    layout->addWidget(operationComboBox);

    calculateButton = new QPushButton("Выполнить");
    layout->addWidget(calculateButton);

    connect(calculateButton, &QPushButton::clicked, this, &MatrixOperationsDialog::performOperation);

    setLayout(layout);
}

void MatrixOperationsDialog::performOperation() {
    int operationIndex = operationComboBox->currentIndex();

    if (operationIndex == 0 || operationIndex == 4 || operationIndex == 5 || operationIndex == 6) { // Транспонирование и обратная матрица
        int rows1 = rowsSpinBox1->value();
        int cols1 = colsSpinBox1->value();

        qDebug() << rows1 << cols1;

        MatrixInputDialog inputDialog(rows1, cols1, operationIndex);
        inputDialog.exec();
    } else if (operationIndex >= 1 && operationIndex <= 3) { // Операции с матрицами
        int rows1 = rowsSpinBox1->value();
        int cols1 = colsSpinBox1->value();
        int rows2 = rowsSpinBox2->value();
        int cols2 = colsSpinBox2->value();

        MatrixInputDialog inputDialog(rows1, cols1, rows2, cols2, operationIndex);
        inputDialog.exec();
    }
}
