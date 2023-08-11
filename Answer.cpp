#include "Answer.hpp"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

Answer::Answer(const QString &resultString, const QString &stepByStepMarkdown, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Результат");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QString res = resultString + stepByStepMarkdown;

    textEdit = new QTextEdit(this);
    textEdit->setMarkdown(res); // Устанавливаем текст в формате Markdown
    textEdit->setReadOnly(true); // Запрещаем редактирование


    layout->addWidget(textEdit);

    QPushButton *closeButton = new QPushButton("Закрыть", this);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept); // Закрываем окно при нажатии кнопки

    layout->addWidget(closeButton);

    setLayout(layout);
}
