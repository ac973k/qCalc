#include "MatrixInputDialog.hpp"
#include "Answer.hpp"
#include <QDebug>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVector>
#include <cmath>

MatrixInputDialog::MatrixInputDialog(int rows, int cols, int operationIndex,
                                     QWidget *parent)
    : QDialog(parent) {
  setWindowTitle("Ввод матрицы и решение");

  this->operationIndex = operationIndex;

  QVBoxLayout *layout = new QVBoxLayout(this);

  QLabel *matrixLabel = new QLabel("Введите значения матрицы:");
  layout->addWidget(matrixLabel);

  qDebug() << "MatrixInputDialog " << rows << cols;

  // Создаем таблицу для ввода матрицы
  matrix1LineEdit.resize(rows);
  for (int i = 0; i < rows; ++i) {
    QHBoxLayout *rowLayout = new QHBoxLayout;
    matrix1LineEdit[i].resize(cols);
    for (int j = 0; j < cols; ++j) {
      matrix1LineEdit[i][j] = new QLineEdit;
      rowLayout->addWidget(matrix1LineEdit[i][j]);
    }
    layout->addLayout(rowLayout);
  }

  calculateButton = new QPushButton("Ответ");
  layout->addWidget(calculateButton);

  connect(calculateButton, &QPushButton::clicked, this,
          &MatrixInputDialog::calculateSolution);

  setLayout(layout);
}

MatrixInputDialog::MatrixInputDialog(int rows1, int cols1, int rows2, int cols2,
                                     int operationIndex, QWidget *parent)
    : QDialog(parent), operationIndex(operationIndex), rows1(rows1),
      cols1(cols1) {
  setWindowTitle("Ввод матриц и решение");

  this->operationIndex = operationIndex;

  QVBoxLayout *layout = new QVBoxLayout(this);

  QLabel *matrix1Label = new QLabel("Введите значения 1 матрицы:");
  layout->addWidget(matrix1Label);
  // Создаем таблицу для ввода первой матрицы
  matrix1LineEdit.resize(rows1);
  for (int i = 0; i < rows1; ++i) {
    QHBoxLayout *rowLayout = new QHBoxLayout;
    matrix1LineEdit[i].resize(cols1);
    for (int j = 0; j < cols1; ++j) {
      matrix1LineEdit[i][j] = new QLineEdit();
      rowLayout->addWidget(matrix1LineEdit[i][j]);
    }
    layout->addLayout(rowLayout);
  }

  QLabel *matrix2Label = new QLabel("Введите значения 2 матрицы:");
  layout->addWidget(matrix2Label);
  // Создаем таблицу для ввода второй матрицы
  matrix2LineEdit.resize(rows2);
  for (int i = 0; i < rows2; ++i) {
    QHBoxLayout *rowLayout = new QHBoxLayout;
    matrix2LineEdit[i].resize(cols2);
    for (int j = 0; j < cols2; ++j) {
      matrix2LineEdit[i][j] = new QLineEdit();
      rowLayout->addWidget(matrix2LineEdit[i][j]);
    }
    layout->addLayout(rowLayout);
  }

  calculateButton = new QPushButton("Ответ");
  layout->addWidget(calculateButton);

  connect(calculateButton, &QPushButton::clicked, this,
          &MatrixInputDialog::calculateSolution);

  setLayout(layout);
}

void MatrixInputDialog::calculateSolution() {
  int rows1 = matrix1LineEdit.size();
  int cols1 = matrix1LineEdit[0].size();

  if (operationIndex == 0) { // Операция - транспонирование
    int rows = matrix1LineEdit.size();
    int cols = matrix1LineEdit[0].size();

    // Получаем значения из matrixLineEdit и записываем их в матрицу
    QVector<QVector<double>> matrix(rows, QVector<double>(cols));
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        matrix[i][j] = matrix1LineEdit[i][j]->text().toDouble();
      }
    }

    // Выполняем транспонирование матрицы
    QVector<QVector<double>> transposedMatrix(cols, QVector<double>(rows));
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        transposedMatrix[j][i] = matrix[i][j];
      }
    }

    // Создаем строку с результатом транспонирования
    QString resultString = "### Результат транспонирования\n\n";
    resultString += "**Исходная матрица:**\n\n";
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        resultString += QString::number(matrix[i][j]) + "  \t";
      }
      resultString += "\n";
    }

    resultString += "\n**Транспонированная матрица:**\n\n";
    for (int i = 0; i < cols; ++i) {
      for (int j = 0; j < rows; ++j) {
        resultString += QString::number(transposedMatrix[i][j]) + "  \t";
      }
      resultString += "\n";
    }

    QString stepByStepMarkdown = "\n\n### Пошаговое решение:\n";
    stepByStepMarkdown.append(
        "1. Взяли элемент A[1][1] и транспонировали его.\n");
    stepByStepMarkdown.append(
        "2. Перешли к элементу A[1][2] и транспонировали его.\n");
    stepByStepMarkdown.append("3. Продолжили для остальных элементов.\n\n");
    stepByStepMarkdown.append(
        "**Транспонирование матрицы** - это операция,\n"
        "при которой строки матрицы становятся столбцами,\n"
        "а столбцы - строками. Другими словами,\n"
        "элементы матрицы меняют свои позиции относительно главной диагонали.");

    Answer answerDialog(resultString, stepByStepMarkdown,
                        this); // Создаем диалоговое окно Answer
    answerDialog.exec(); // Отображаем диалоговое окно
  } else if (operationIndex >= 1 &&
             operationIndex <= 6) { // Операции с матрицами
    if (operationIndex == 1) {      // Операции - сложение
      QVector<QVector<double>> matrix1(rows1, QVector<double>(cols1));
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
          matrix1[i][j] = matrix1LineEdit[i][j]->text().toDouble();
        }
      }

      QVector<QVector<double>> matrix2(rows1, QVector<double>(cols1));
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
          matrix2[i][j] = matrix2LineEdit[i][j]->text().toDouble();
        }
      }

      // Выполняем операцию в зависимости от выбранной операции (например,
      // сложение)
      QVector<QVector<double>> resultMatrix;
      if (operationIndex == 1) { // Сложение
        resultMatrix.resize(rows1);
        for (int i = 0; i < rows1; ++i) {
          resultMatrix[i].resize(cols1);
          for (int j = 0; j < cols1; ++j) {
            resultMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
          }
        }
      }

      // Формирование строки с пошаговым решением
      QString stepByStepMarkdown = "Пошаговое решение сложения матриц:\n";
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
          stepByStepMarkdown +=
              QString("1. Взяли элемент A[%1][%2] и B[%1][%2] и сложили их.\n")
                  .arg(i)
                  .arg(j);
        }
      }

      // Создаем строку с результатом операции
      QString resultString = "### Результат сложения матриц\n\n";
      resultString += "**Первая матрица:**\n\n";
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
          resultString += QString::number(matrix1[i][j]) + "  \t";
        }
        resultString += "\n";
      }

      resultString += "\n**Вторая матрица:**\n\n";
      for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < cols2; ++j) {
          resultString += QString::number(matrix2[i][j]) + "  \t";
        }
        resultString += "\n";
      }

      resultString += "\n**Результат сложения:**\n\n";
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
          resultString += QString::number(resultMatrix[i][j]) + "  \t";
        }
        resultString += "\n";
      }

      // Отображение результата в окне Answer
      Answer answer(resultString, stepByStepMarkdown);
      answer.exec();
    } else if (operationIndex == 2) { // Операции - вычитание
      QVector<QVector<double>> matrix1(rows1, QVector<double>(cols1));
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
          matrix1[i][j] = matrix1LineEdit[i][j]->text().toDouble();
        }
      }

      QVector<QVector<double>> matrix2(rows1, QVector<double>(cols1));
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
          matrix2[i][j] = matrix2LineEdit[i][j]->text().toDouble();
        }
      }

      // Выполняем операцию в зависимости от выбранной операции (например,
      // сложение)
      QVector<QVector<double>> resultMatrix;
      if (operationIndex == 1) { // вычитание
        resultMatrix.resize(rows1);
        for (int i = 0; i < rows1; ++i) {
          resultMatrix[i].resize(cols1);
          for (int j = 0; j < cols1; ++j) {
            resultMatrix[i][j] = matrix1[i][j] - matrix2[i][j];
          }
        }
      }

      QString stepByStepMarkdown = "Пошаговое решение вычитания матриц:\n";
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
          stepByStepMarkdown +=
              QString("1. Взяли элемент A[%1][%2] и B[%1][%2] и вычли их.\n")
                  .arg(i)
                  .arg(j);
        }
      }

      // Создаем строку с результатом операции
      QString resultString = "### Результат вычитания матриц\n\n";
      resultString += "**Первая матрица:**\n\n";
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
          resultString += QString::number(matrix1[i][j]) + "  \t";
        }
        resultString += "\n";
      }

      resultString += "\n**Вторая матрица:**\n\n";
      for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < cols2; ++j) {
          resultString += QString::number(matrix2[i][j]) + "  \t";
        }
        resultString += "\n";
      }

      resultString += "\n**Результат вычитания:**\n\n";
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
          resultString += QString::number(resultMatrix[i][j]) + "  \t";
        }
        resultString += "\n";
      }

      // Отображение результата в окне Answer
      Answer answer(resultString, stepByStepMarkdown);
      answer.exec();
    } else if (operationIndex == 3) { // Операция - умножение
      // Код для умножения матриц
      int resultRows = rows1; // Количество строк в результирующей матрице
      int resultCols = cols2; // Количество столбцов в результирующей матрице

      // Получаем значения из matrix1LineEdit и matrix2LineEdit
      QVector<QVector<double>> matrix1(rows1, QVector<double>(cols1));
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
          matrix1[i][j] = matrix1LineEdit[i][j]->text().toDouble();
        }
      }

      QVector<QVector<double>> matrix2(rows2, QVector<double>(cols2));
      for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < cols2; ++j) {
          matrix2[i][j] = matrix2LineEdit[i][j]->text().toDouble();
        }
      }

      // Выполняем операцию умножения
      QVector<QVector<double>> resultMatrix(resultRows,
                                            QVector<double>(resultCols, 0));
      for (int i = 0; i < resultRows; ++i) {
        for (int j = 0; j < resultCols; ++j) {
          for (int k = 0; k < cols1; ++k) {
            resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
          }
        }
      }

      // Формирование строки с пошаговым решением
      QString stepByStepMarkdown = "Пошаговое решение умножения матриц:\n";
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
          stepByStepMarkdown += QString("1. Взяли строку %1 из матрицы A и "
                                        "столбец %2 из матрицы B.\n")
                                    .arg(i)
                                    .arg(j);
          stepByStepMarkdown +=
              "2. Перемножили соответствующие элементы и сложили результаты.\n";
        }
      }

      // Создаем строку с результатом операции
      QString resultString = "### Результат умножения матриц\n\n";
      resultString += "**Первая матрица:**\n\n";
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
          resultString += QString::number(matrix1[i][j]) + "  \t";
        }
        resultString += "\n";
      }

      resultString += "\n**Вторая матрица:**\n\n";
      for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < cols2; ++j) {
          resultString += QString::number(matrix2[i][j]) + "  \t";
        }
        resultString += "\n";
      }

      resultString += "\n**Результат умножения:**\n\n";
      for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
          resultString += QString::number(resultMatrix[i][j]) + "  \t";
        }
        resultString += "\n";
      }

      // Отображение результата в окне Answer
      Answer answer(resultString, stepByStepMarkdown);
      answer.exec();
    } else if (operationIndex == 4) { // Операция - обратная матрица
      // Получаем значения из matrixLineEdit и записываем их в матрицу
      int rows = matrix1LineEdit.size();
      int cols = matrix1LineEdit[0].size();

      qDebug() << "Rows: " << rows << "Cols: " << cols;

      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          qDebug() << "Value at [" << i << "][" << j
                   << "]: " << matrix1LineEdit[i][j]->text();
        }
      }

      // Получаем значения из matrixLineEdit и записываем их в матрицу
      QVector<QVector<double>> matrix(rows, QVector<double>(cols));
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          matrix[i][j] = matrix1LineEdit[i][j]->text().toDouble();
        }
      }

      qDebug() << "Rows: " << rows << "Cols: " << cols;

      if (!isSquareMatrix(matrix)) {
        QMessageBox::warning(this, tr("Ошибка"),
                             tr("Матрица должна быть квадратной."));
        return;
      }

      // Проверка на невырожденность матрицы
      if (!isNonSingularMatrix(matrix)) {
        QMessageBox::warning(this, tr("Ошибка"),
                             tr("Матрица вырождена, обратной матрицы нет."));
        return;
      }

      // Вычисление обратной матрицы
      QVector<QVector<double>> inverseMatrix = calculateInverseMatrix(matrix);

      // Проверка на ошибку в вычислении обратной матрицы
      if (inverseMatrix.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"),
                             tr("Не удалось вычислить обратную матрицу."));
        return;
      }

      // Вывод сообщения об успешной операции и inverseMatrix
      QString resultString = "### Результат нахождения обратной матрицы\n\n";
      resultString += "\n**Обратная матрица:**\n\n";
      for (int i = 0; i < inverseMatrix.size(); ++i) {
        for (int j = 0; j < inverseMatrix[i].size(); ++j) {
          resultString += QString::number(inverseMatrix[i][j]) + "\t";
        }
        resultString += "\n";
      }

      QString stepByStepMarkdown =
          "Пошаговое решение нахождения обратной матрицы:\n";

      // Добавьте пояснения для каждого шага вычислений
      stepByStepMarkdown += "1. Создали единичную матрицу того же размера, что "
                            "и исходная матрица.\n";
      stepByStepMarkdown += "2. Создали расширенную матрицу путем объединения "
                            "исходной матрицы и единичной матрицы.\n";
      // ... продолжайте добавлять остальные шаги

      // Отображение пошагового решения в окне Answer
      Answer answer(resultString, stepByStepMarkdown);
      answer.exec();

    } else if (operationIndex == 5) { // Операция - умножение на число
      // Получаем значения из matrixLineEdit и записываем их в матрицу
      int rows = matrix1LineEdit.size();
      int cols = matrix1LineEdit[0].size();

      qDebug() << "Rows: " << rows << "Cols: " << cols;

      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          qDebug() << "Value at [" << i << "][" << j
                   << "]: " << matrix1LineEdit[i][j]->text();
        }
      }

      // Получаем значения из matrixLineEdit и записываем их в матрицу
      QVector<QVector<double>> matrix(rows, QVector<double>(cols));
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          matrix[i][j] = matrix1LineEdit[i][j]->text().toDouble();
        }
      }

      qDebug() << "Rows: " << rows << "Cols: " << cols;

      bool ok;
      double multiplier = QInputDialog::getDouble(
          this, tr("Введите число"), tr("Число для умножения:"), 1.0,
          -std::numeric_limits<double>::max(),
          std::numeric_limits<double>::max(), 2, &ok);

      if (!ok) {
        return; // Пользователь нажал "Отмена" или закрыл окно
      }

      // Подготовка пошагового решения
      QString stepByStepMarkdown =
          "Пошаговое решение умножения матрицы на число " +
          QString::number(multiplier) + ":\n\n";
      stepByStepMarkdown += "1. Создали новую матрицу, в которую будем "
                            "записывать результат умножения.\n";
      stepByStepMarkdown += "2. Прошлись по каждому элементу исходной матрицы "
                            "и умножили его на число " +
                            QString::number(multiplier) + ".\n";
      stepByStepMarkdown += "3. Записали результат в новую матрицу.\n\n";

      // Умножение матрицы на число
      QVector<QVector<double>> resultMatrix(rows, QVector<double>(cols));
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          double originalValue = matrix[i][j];
          double resultValue = originalValue * multiplier;
          resultMatrix[i][j] = resultValue;

          // Добавляем шаг в пошаговое решение
          stepByStepMarkdown +=
              QString("   - Умножаем элемент [%1][%2]: %3 * %4 = %5\n")
                  .arg(i + 1)
                  .arg(j + 1)
                  .arg(originalValue)
                  .arg(multiplier)
                  .arg(resultValue);
        }
      }

      // Вывод результата в окно Answer
      QString resultString = "### Результат умножения матрицы на число\n\n";
      resultString += "\n**Исходная матрица:**\n\n";
      // ... код для вывода исходной матрицы
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          resultString += QString::number(matrix[i][j]) + "  \t";
        }
        resultString += "\n";
      }

      resultString +=
          "\n**Число для умножения:** " + QString::number(multiplier) + "\n\n";
      resultString += "\n**Результирующая матрица:**\n\n";
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          resultString += QString::number(resultMatrix[i][j]) + "  \t";
        }
        resultString += "\n";
      }

      // Отображение пошагового решения в окне Answer
      Answer answer(resultString, stepByStepMarkdown);
      answer.exec();
    } else if (operationIndex == 6) {
      // Получаем значения из matrixLineEdit и записываем их в матрицу
      int rows = matrix1LineEdit.size();
      int cols = matrix1LineEdit[0].size();

      qDebug() << "Rows: " << rows << "Cols: " << cols;

      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          qDebug() << "Value at [" << i << "][" << j
                   << "]: " << matrix1LineEdit[i][j]->text();
        }
      }

      // Получаем значения из matrixLineEdit и записываем их в матрицу
      QVector<QVector<double>> matrix(rows, QVector<double>(cols));
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          matrix[i][j] = matrix1LineEdit[i][j]->text().toDouble();
        }
      }

      qDebug() << "Rows: " << rows << "Cols: " << cols;

      if (!isSquareMatrix(matrix)) {
        QMessageBox::warning(this, tr("Ошибка"),
                             tr("Матрица должна быть квадратной."));
        return;
      }

      QString stepByStepMarkdown = "### Пошаговое решение нахождения определителя матрицы:\n";

      stepByStepMarkdown += "1. Начнем с исходной матрицы размером " + QString::number(rows1) + "x" + QString::number(cols1) + ".\n";
                                stepByStepMarkdown += "2. Применим метод Гаусса для приведения матрицы к верхнетреугольному виду.\n";
      // ... продолжайте добавлять пояснения для каждого шага

      // Вычисление определителя
      double determinant = determinantGauss(matrix);

                                stepByStepMarkdown += QString("Последний шаг. Получили верхнетреугольную матрицу размером %1x%2.\n")
                                                          .arg(rows1).arg(cols1);
                                stepByStepMarkdown += "Определитель матрицы равен произведению элементов главной диагонали:\n";
                                stepByStepMarkdown += "Определитель = ";
                                for (int i = 0; i < rows1; ++i) {
        stepByStepMarkdown += QString::number(matrix[i][i]);
        if (i < rows1 - 1) {
          stepByStepMarkdown += " * ";
        }
                                }
                                stepByStepMarkdown += " = " + QString::number(determinant) + "\n";

      // Вывод результата в окно Answer
      QString resultString =
          "### Результат нахождения определителя матрицы\n\n";
      resultString += "\n**Исходная матрица:**\n\n";
      // ... код для вывода исходной матрицы
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          resultString += QString::number(matrix[i][j]) + "  \t";
        }
        resultString += "\n";
      }

      resultString += "\n**Определитель матрицы:** " +
                      QString::number(determinant) + "\n\n";

      // Добавляем результат в окно Answer
      Answer answer(resultString, stepByStepMarkdown);
      answer.exec();
    }
  }
}

// Функция для обмена строк матрицы
void swapRows(QVector<QVector<double>> &matrix, int i, int j) {
  for (int k = 0; k < matrix[i].size(); ++k) {
    qSwap(matrix[i][k], matrix[j][k]);
  }
}

// Функция для вычисления определителя матрицы методом Гаусса
double MatrixInputDialog::determinantGauss(
    const QVector<QVector<double>> &matrix) const {
  int n = matrix.size();

  if (!isSquareMatrix(matrix)) {
    QMessageBox::warning(parentWidget(), "Ошибка",
                         "Матрица не является квадратной.");
    return 0.0; // Возвращаем 0 в случае ошибки
  }

  QVector<QVector<double>> tempMatrix =
      matrix; // Создаем временную копию матрицы

  double det = 1.0; // Инициализируем определитель

  for (int i = 0; i < n; ++i) {
    int maxRow = i;

    // Поиск максимального элемента в столбце для текущей строки
    for (int j = i + 1; j < n; ++j) {
      if (qAbs(tempMatrix[j][i]) > qAbs(tempMatrix[maxRow][i])) {
        maxRow = j;
      }
    }

    // Обмен текущей строки с строкой с максимальным элементом
    if (maxRow != i) {
      swapRows(tempMatrix, i, maxRow);
      det *= -1.0; // Меняем знак определителя при обмене строк
    }

    // Проверка на нулевой диагональный элемент
    if (qFuzzyCompare(tempMatrix[i][i], 0.0)) {
      return 0.0; // Определитель равен 0, если на диагонали есть 0
    }

    // Прямой ход
    for (int j = i + 1; j < n; ++j) {
      double factor = tempMatrix[j][i] / tempMatrix[i][i];
      for (int k = i; k < n; ++k) {
        tempMatrix[j][k] -= factor * tempMatrix[i][k];
      }
    }
  }

  // Вычисление определителя как произведение элементов главной диагонали
  for (int i = 0; i < n; ++i) {
    det *= tempMatrix[i][i];
  }

  return det;
}

bool MatrixInputDialog::isSquareMatrix(
    const QVector<QVector<double>> &matrix) const {
  int rows = matrix.size();

  if (rows == 0) {
    return false; // Матрица пуста
  }

  int cols = matrix[0].size();

  if (rows != cols) {
    return false; // Матрица не является квадратной
  }

  return true; // Матрица квадратная
}

bool MatrixInputDialog::isNonSingularMatrix(
    const QVector<QVector<double>> &matrix) const {
  if (!isSquareMatrix(matrix)) {
    return false; // Матрица не квадратная, значит, она не имеет определителя
  }

  double det = determinantGauss(matrix);
  double epsilon = 1e-6; // Порог для сравнения с нулем

  if (std::fabs(det) < epsilon) {
    return false; // Определитель близок к нулю, матрица вырождена
  }

  return true; // Матрица невырожденная
}

void MatrixInputDialog::swapRows(QVector<QVector<double>> &matrix, int row1,
                                 int row2) const {
  int numRows = matrix.size();
  if (row1 < 0 || row1 >= numRows || row2 < 0 || row2 >= numRows) {
    return; // Проверяем корректность индексов строк
  }

  for (int i = 0; i < matrix[row1].size(); ++i) {
    std::swap(matrix[row1][i], matrix[row2][i]);
  }
}

QVector<QVector<double>>
MatrixInputDialog::getMinor(const QVector<QVector<double>> &matrix, int row,
                            int col) {
  int n = matrix.size();
  if (n <= 1 || row < 0 || row >= n || col < 0 || col >= n) {
    return QVector<QVector<double>>(); // Возвращаем пустую матрицу в случае
                                       // некорректных параметров
  }

  QVector<QVector<double>> minor(n - 1, QVector<double>(n - 1, 0.0));

  int minorRow = 0;
  for (int i = 0; i < n; ++i) {
    if (i == row) {
      continue;
    }

    int minorCol = 0;
    for (int j = 0; j < n; ++j) {
      if (j == col) {
        continue;
      }

      minor[minorRow][minorCol] = matrix[i][j];
      ++minorCol;
    }

    ++minorRow;
  }

  return minor;
}

QVector<QVector<double>> MatrixInputDialog::getAlgebraicComplements(
    const QVector<QVector<double>> &matrix) {
  int n = matrix.size();
  if (n <= 0 || matrix[0].size() != n) {
    return QVector<QVector<double>>(); // Возвращаем пустую матрицу в случае
                                       // некорректных параметров
  }

  QVector<QVector<double>> algebraicComplements(n, QVector<double>(n, 0.0));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      QVector<QVector<double>> minor = getMinor(matrix, i, j);
      if (minor.isEmpty()) {
        return QVector<QVector<double>>(); // Возвращаем пустую матрицу в случае
                                           // некорректных параметров
      }
      double minorDeterminant = determinantGauss(minor);

      algebraicComplements[i][j] = std::pow(-1, i + j) * minorDeterminant;
    }
  }

  return algebraicComplements;
}

QVector<QVector<double>>
MatrixInputDialog::transposeMatrix(const QVector<QVector<double>> &matrix) {
  int rows = matrix.size();
  if (rows <= 0) {
    return QVector<QVector<double>>(); // Возвращаем пустую матрицу в случае
                                       // некорректных параметров
  }

  int cols = matrix[0].size();
  if (cols <= 0) {
    return QVector<QVector<double>>(); // Возвращаем пустую матрицу в случае
                                       // некорректных параметров
  }

  QVector<QVector<double>> transposedMatrix(cols, QVector<double>(rows, 0.0));

  for (int i = 0; i < rows; ++i) {
    if (matrix[i].size() != cols) {
      return QVector<QVector<double>>(); // Возвращаем пустую матрицу, если
                                         // входная матрица некорректна
    }

    for (int j = 0; j < cols; ++j) {
      transposedMatrix[j][i] = matrix[i][j];
    }
  }

  return transposedMatrix;
}

QVector<QVector<double>>
MatrixInputDialog::findInverseMatrix(const QVector<QVector<double>> &matrix) {
  int n = matrix.size();
  if (n <= 0 || !isSquareMatrix(matrix) || !isNonSingularMatrix(matrix)) {
    return QVector<QVector<double>>(); // Возвращаем пустую матрицу в случае
                                       // некорректных параметров
  }

  // Шаг 1: Вычисление определителя
  double det = determinantGauss(matrix);
  if (std::fabs(det) < 1e-6) {
    return QVector<QVector<double>>(); // Матрица вырождена, обратной матрицы
                                       // нет
  }

  // Шаг 2: Вычисление транспонированной матрицы алгебраических дополнений
  QVector<QVector<double>> algebraicComplements =
      getAlgebraicComplements(matrix);
  QVector<QVector<double>> transposedAlgebraicComplements =
      transposeMatrix(algebraicComplements);

  // Шаг 3: Вычисление обратной матрицы
  QVector<QVector<double>> inverseMatrix(n, QVector<double>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      inverseMatrix[i][j] = transposedAlgebraicComplements[i][j] / det;
    }
  }

  return inverseMatrix;
}

QVector<QVector<double>> MatrixInputDialog::calculateInverseMatrix(
    const QVector<QVector<double>> &matrix) {
  int n = matrix.size();
  if (n <= 0 || !isSquareMatrix(matrix)) {
    return QVector<QVector<double>>(); // Возвращаем пустую матрицу в случае
                                       // некорректных параметров
  }

  QVector<QVector<double>> augmentedMatrix(n, QVector<double>(2 * n, 0.0));

  // Создаем расширенную матрицу, добавляя к исходной единичную матрицу
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      augmentedMatrix[i][j] = matrix[i][j];
    }
    augmentedMatrix[i][n + i] = 1.0;
  }

  // Приводим augmentedMatrix к диагональному виду
  for (int i = 0; i < n; ++i) {
    double diagonalElement = augmentedMatrix[i][i];

    // Проверка на вырожденность
    if (qFuzzyCompare(diagonalElement, 0.0)) {
      return QVector<QVector<double>>(n, QVector<double>(n, 0.0));
    }

    // Делаем диагональный элемент 1
    for (int j = 0; j < 2 * n; ++j) {
      augmentedMatrix[i][j] /= diagonalElement;
    }

    // Обнуляем остальные элементы в столбце
    for (int k = 0; k < n; ++k) {
      if (k != i) {
        double factor = augmentedMatrix[k][i];
        for (int j = 0; j < 2 * n; ++j) {
          augmentedMatrix[k][j] -= factor * augmentedMatrix[i][j];
        }
      }
    }
  }

  // Извлекаем обратную матрицу из augmentedMatrix
  QVector<QVector<double>> inverseMatrix(n, QVector<double>(n, 0.0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      inverseMatrix[i][j] = augmentedMatrix[i][n + j];
    }
  }

  return inverseMatrix;
}
