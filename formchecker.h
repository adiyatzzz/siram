#ifndef FORMCHECKER_H
#define FORMCHECKER_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QDebug>

class FormChecker
{
public:
    FormChecker();
    void showMessageAndFocus(QWidget *formName, QLineEdit *lineEdit, const QString &message);
    void showMessageAndFocus(QWidget *formName, QComboBox *comboBox, const QString &message);
    bool isFieldEmpty(QWidget *formName, QLineEdit *lineEdit, const QString &message);
    bool isFieldEmpty(QWidget *formName, QComboBox *comboBox, const QString &message);

};

#endif // FORMCHECKER_H
