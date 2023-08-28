#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QThread>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <lcd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_pressed();

    void lcdPrint();

    void on_pushButton_released();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
