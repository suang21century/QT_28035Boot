//针对28035的串口烧写上位机程序，读取hex文件，分行加帧头帧尾处理，1ms发送握手指令，50ms定时读取dsp反馈状态并发送一帧即一行数据
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QTimer>
#include "math.h"

quint16 readcnt=0;//read计数
quint16 sendinitflag=1;  //状态机标志 1：使能握手发送，接收 2：等待接收擦除成功帧 3：等待发送hex文件按键 4：发送过程中
quint16 readinitflag=0;  //读取文件标志 0：未读取hex文件  1：读取hex文件
quint16 writestatus=0;   //dsp写入状态
quint16 tmp_i=0;
quint16 tmp_leng=0;//hex行数
QStringList tmp;   //暂存整个hex文件数据，打包成list

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())//查找com口设备
    {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();   //打印设备信息

        // Example use QSerialPort
        QSerialPort serial;                                    //定义串口对象
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            ui->comboBox->addItem(info.portName());
            serial.close();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::senddata(quint16 n)
{
  if((n<=tmp_leng-1)&&(sendinitflag==4))
  {
    QByteArray TxData;
    TxData.resize(1);//发送
    TxData[0]=0xAA;

    my_serialport->write(TxData);
    QByteArray tmp_str = QByteArray::fromHex (tmp[n].toLatin1().data());//按十六进制编码接入文本
    my_serialport->write(tmp_str);
    TxData[0]=0x0A;
    my_serialport->write(TxData);
  }

}

void MainWindow::update()
{

  if(sendinitflag==1)//状态为握手等待
  {
    QByteArray TxData;
    TxData.resize(4);//发送握手指令11 22 33 44
    TxData[0]=0xAA;
    TxData[1]=0x50;
    TxData[2]=0x00;
    TxData[3]=0x50;
    my_serialport->write(TxData);

    quint8 readdata_tmp;      //暂存
    int i=0;
    int byteLeng = my_serialport->bytesAvailable(); //返回串口缓冲区字节数
    //qDebug()<<byteLeng;
    requestData = my_serialport->readAll();        //读取buffer内全部数据
    if(byteLeng>0)                                 //buffer非空时
    {
        for(i=0;i<byteLeng;i++)                    //遍历数组,i为此次缓存buffer的字节数计数
        {
          readdata_tmp=(quint8)requestData[i];        //强制转换为asc值

          switch(readcnt)
          {
            case 0:
              if(readdata_tmp==0xAA) readcnt=1; //0x12  ID
            break;
            case 1:
              if(readdata_tmp==0x50) readcnt=2;
              else  readcnt=0;
            break;
            case 2:
              if(readdata_tmp==0x01) readcnt=3;
              else  readcnt=0;
            break;
            case 3:
              if(readdata_tmp==0x51)
              {
                sendinitflag=2;     //状态读取擦除成功状态帧
                ui->textEdit->append(" 握手 ok");      //显示框显示
              }
              readcnt=0;
            break;
          }
        }
        requestData.clear();
    }
  }
  if(sendinitflag==2)    //等待读取状态擦除状态帧
  {
      quint8 readdata_tmp;      //暂存
      int i=0;
      int byteLeng = my_serialport->bytesAvailable(); //返回串口缓冲区字节数
      //qDebug()<<byteLeng;
      requestData = my_serialport->readAll();        //读取buffer内全部数据
      if(byteLeng>0)                                 //buffer非空时
      {
          for(i=0;i<byteLeng;i++)                    //遍历数组,i为此次缓存buffer的字节数计数
          {
            readdata_tmp=(quint8)requestData[i];        //强制转换为asc值

            switch(readcnt)
            {
              case 0:
                if(readdata_tmp==0xAA) readcnt=1; //
              break;
              case 1:
                if(readdata_tmp==0x51) readcnt=2;
                else  readcnt=0;
              break;
              case 2:
                if(readdata_tmp==0x01) readcnt=3;
                else  readcnt=0;
              break;
              case 3:
                if(readdata_tmp==0x52)
                {
                  sendinitflag=3;     //状态切换至等待读取hex
                  ui->textEdit->append(" 擦除 ok");      //显示框显示
                  timer->start(50);
                }
                readcnt=0;
              break;
            }
          }
          requestData.clear();
      }
  }
  if(sendinitflag==4)     //接收写入状态帧并发送下一帧
  {
      quint8 readdata_tmp;      //暂存
      int i=0;
      int byteLeng = my_serialport->bytesAvailable(); //返回串口缓冲区字节数

      requestData = my_serialport->readAll();        //读取buffer内全部数据
      if(byteLeng>0) qDebug()<<requestData;
      if(byteLeng>0)                                 //buffer非空时
      {
          for(i=0;i<byteLeng;i++)                    //遍历数组,i为此次缓存buffer的字节数计数
          {
            readdata_tmp=(quint8)requestData[i];        //强制转换为asc值

            switch(readcnt)
            {
              case 0:
                if(readdata_tmp==0xAA) readcnt=1; //0x12  ID
              break;
              case 1:
                if((readdata_tmp==0x52) || (readdata_tmp==0x53)) readcnt=2;
                else  readcnt=0;
              break;
              case 2:
                readcnt=3;
              break;
              case 3:
                if(readdata_tmp==0x53) //反馈帧正确
                {
                  tmp_i++;             //帧计数器累加
                }
                else if(readdata_tmp==0x52) //帧不正确，重复发送上一帧
                {
                  ui->textEdit->append(" 帧错误");      //显示框显示
                }
                else if(readdata_tmp==0x54)  //收到结束帧
                {
                  sendinitflag=5;    //发送结束
                  ui->textEdit->append(" 发送完毕");      //显示框显示
                }
                //usleep(200);
                senddata(tmp_i-1);  // 根据反馈状态判断发送情况
                readcnt=0;
                qDebug()<<tmp_i-1;
              break;
            }
          }
          requestData.clear();
      }

  }
}

void MainWindow::on_pushButton_cmopen_clicked() //open按钮槽函数，点击响应
{
    if(ui->pushButton_cmopen->text()==tr("打开串口"))
    {
    my_serialport= new QSerialPort();                             //串口设置
    qDebug()<<ui->comboBox->currentText();                        //打印使用的设备号
    my_serialport->setPortName(ui->comboBox->currentText());
    my_serialport->open(QIODevice::ReadWrite);                    //波特率手动输入
    qDebug()<<ui->lineEdit->text().toInt();                       //打印使用的波特率
    my_serialport->setBaudRate(ui->lineEdit->text().toInt());
    my_serialport->setDataBits(QSerialPort::Data8);
    my_serialport->setParity(QSerialPort::NoParity);
    my_serialport->setStopBits(QSerialPort::OneStop);
    my_serialport->setFlowControl(QSerialPort::NoFlowControl);
    ui->pushButton_cmopen->setText(tr("关闭串口"));                //按钮显示
    ui->textEdit->append(" send 握手");      //显示框显示
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));   //定时器调用刷新函数
    timer->start(1);                                          //定时5ms
     //startTimer(50);//单位为毫秒

    }
    else
    {
      my_serialport->clear(); //关闭串口
      my_serialport->close();
      //my_serialport->deleteLater();
      sendinitflag=1;  //握手标志，重新初始化
      readinitflag=0;  //读取文件标志
      ui->textEdit->clear();
      ui->pushButton_cmopen->setText(tr("打开串口"));
    }
}

void MainWindow::on_pushButton_readhex_clicked()
{
    QString file_name;
    file_name = QFileDialog::getOpenFileName(this, "load hex file", "", "");  //读取文件目录对话框
    QFile f(file_name);
    f.open(QIODevice::ReadOnly);
    //f.write(import_data_tmp_.toLocal8Bit());
    import_data_tmp = f.readAll();
    f.close();
    import_data_tmp.remove(':');

    readinitflag=1;     //状态切换至等待读取hex
    ui->textEdit->append(" 读入hex ok");      //显示框显示
}

void MainWindow::on_pushButton_sendhex_clicked()
{
    if((readinitflag==1)&&(sendinitflag==3))
    {
      tmp = import_data_tmp.split("\r\n");//剔除行结束符，存入字符串序列
      //qDebug()<<tmp.count();//返回序列长度，0~N-1
      tmp_leng=tmp.count();
      qDebug()<<tmp_leng;
      ui->textEdit->append(" 发送..");      //显示框显示
      //str2.clear();

      QByteArray TxData;
      TxData.resize(1);//发送
      TxData[0]=0xAA;

      my_serialport->write(TxData);
      QByteArray tmp_str = QByteArray::fromHex (tmp[0].toLatin1().data());//按十六进制编码接入文本
      my_serialport->write(tmp_str);
      TxData[0]=0x0A;
      my_serialport->write(TxData);

      sendinitflag=4;//只发送第一帧，跳出
      tmp_i=1;//初始化第一帧
    }
    else
    {
      ui->textEdit->append(" init 失败");      //显示框显示
    }
}
