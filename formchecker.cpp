#include "formchecker.h"

FormChecker::FormChecker() {}

void FormChecker::showMessageAndFocus(QWidget *formName, QLineEdit *lineEdit, const QString &message)
{
    QMessageBox::information(formName, "Warning", message);
    lineEdit->setFocus();
}

void FormChecker::showMessageAndFocus(QWidget *formName, QComboBox *comboBox, const QString &message)
{
    QMessageBox::information(formName, "Warning", message);
    comboBox->setFocus();
}

bool FormChecker::isFieldEmpty(QWidget *formName, QLineEdit *lineEdit, const QString &message)
{

    if (lineEdit->text().isEmpty()) {
        showMessageAndFocus(formName, lineEdit, message);
        return true;
    }
    return false;
}

bool FormChecker::isFieldEmpty(QWidget *formName, QComboBox *comboBox, const QString &message)
{
    if (comboBox->currentText().isEmpty()) {
        showMessageAndFocus(formName, comboBox, message);
        return true;
    }
    return false;
}



