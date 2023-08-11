#ifndef MATRIXOPERATIONSDIALOG_HPP
#define MATRIXOPERATIONSDIALOG_HPP

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>

class MatrixOperationsDialog : public QDialog {
    Q_OBJECT

public:
    MatrixOperationsDialog(QWidget *parent = nullptr);

private:
    QSpinBox *rowsSpinBox1;
    QSpinBox *colsSpinBox1;
    QSpinBox *rowsSpinBox2;
    QSpinBox *colsSpinBox2;
    QComboBox *operationComboBox;
    QPushButton *calculateButton;

    void setupUI();
    void performOperation();
};

#endif // MATRIXOPERATIONSDIALOG_HPP
