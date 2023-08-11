#ifndef ANSWER_HPP
#define ANSWER_HPP

#include <QDialog>

class QTextEdit;

class Answer : public QDialog {
    Q_OBJECT
public:
    explicit Answer(const QString &resultMarkdown, const QString &stepByStepMarkdown, QWidget *parent = nullptr);

private:
    QTextEdit *textEdit;
};

#endif // ANSWER_HPP
