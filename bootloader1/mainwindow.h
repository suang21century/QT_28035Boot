#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QFile>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_cmopen_clicked();
    void update();
    void on_pushButton_readhex_clicked();
    void senddata(quint16 n);
    void on_pushButton_sendhex_clicked();
private:
    Ui::MainWindow *ui;
    QSerialPort *my_serialport;
    QByteArray requestData;
    QTimer *timer;

    QString import_data_tmp;
};

#endif // MAINWINDOW_H
