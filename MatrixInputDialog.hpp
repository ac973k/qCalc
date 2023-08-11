#ifndef MATRIXINPUTDIALOG_HPP
#define MATRIXINPUTDIALOG_HPP

#include <QDialog>
#include <QVector>

class QLineEdit;

class MatrixInputDialog : public QDialog {
    Q_OBJECT

public:
     MatrixInputDialog(int rows, int cols, int operationIndex, QWidget *parent = nullptr);
    MatrixInputDialog(int rows1, int cols1,
                      int rows2, int cols2,
                      int operationIndex, QWidget *parent = nullptr);

    QVector<QVector<double>> calculateInverseMatrix(const QVector<QVector<double>>& matrix);

private slots:
    void calculateSolution();

private:
    int operationIndex;
    int rows1, cols1, rows2, cols2;
    QVector<QVector<QLineEdit*>> matrix1LineEdit; // Используйте для ввода первой матрицы
    QVector<QVector<QLineEdit*>> matrix2LineEdit; // Используйте для ввода второй матрицы
    QPushButton *calculateButton;

    double determinantGauss(const QVector<QVector<double>>& matrix) const;
    void swapRows(QVector<QVector<double>>& matrix, int row1, int row2) const;
    bool isSquareMatrix(const QVector<QVector<double>>& matrix) const;
    bool isNonSingularMatrix(const QVector<QVector<double>>& matrix) const;

    QVector<QVector<double>> getMinor(const QVector<QVector<double>>& matrix, int row, int col);
    QVector<QVector<double>> getAlgebraicComplements(const QVector<QVector<double>>& matrix);

    QVector<QVector<double>> transposeMatrix(const QVector<QVector<double>>& matrix);
    QVector<QVector<double>> findInverseMatrix(const QVector<QVector<double>>& matrix);
};

#endif // MATRIXINPUTDIALOG_HPP
