#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "algorithm/split_rgb.h"
#include "algorithm/butterworth.h"
#include "process/process.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initial();
}

MainWindow::~MainWindow()
{
    if(ui->Start->isEnabled())
        closeCamara();
    destroy_recode();
    delete ui;
}

void MainWindow::initial()
{
    ui->Start->setEnabled(false);
    cam = nullptr;
    timer = new QTimer(this);
    /*信号和槽*/
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息

    AI = D1.get_adj_value();
}

void MainWindow::destroy_recode()
{
    size_t vector_sizr = mode_record_img.size();
    for (size_t i = 0; i < vector_sizr; i++)
    {
        delete mode_record_img[i];
        mode_record_img[i] = nullptr;
    }
}

bool MainWindow::openCamara(int idex)
{
    cam = new VideoCapture;//打开摄像头，从摄像头中获取视频
    bool flage = cam->open(idex);
    if(flage)
    timer->start(TIMER);              // 开始计时，超时则发出timeout()信号
    return flage;
}

bool MainWindow::closeCamara()
{
    if(came_open)
    {
        timer->stop();         // 停止读取数据。
        cam->release();
        return cam->isOpened();
    }

}

void MainWindow::takingPictures()
{
    taking_frame = frame;
}

bool MainWindow::iden_proc(Mat img,int &whitch)
{
    static eigenvalue Iden_Img(img);
    double Ide_R;
    whitch;

    for (int i = 0;i<mode_record_img.size();i++) {
        Ide_R = calculate_19_value_R(Iden_Img.get_eigenvalue(),
                                     mode_record_img[i]->get_eigenvalue());
        if(judgment(Ide_R,ui->Ide_threshold->value()))
        {
            whitch = i+1;
            return true;
        }else {
            whitch = 0;
        }
    }
    return false;
}

QImage MainWindow::matToQImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
        if(mat.type() == CV_8UC1)
        {
            QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
            // Set the color table (used to translate colour indexes to qRgb values)
            image.setColorCount(256);
            for(int i = 0; i < 256; i++)
            {
                image.setColor(i, qRgb(i, i, i));
            }
            // Copy input Mat
            uchar *pSrc = mat.data;
            for(int row = 0; row < mat.rows; row ++)
            {
                uchar *pDest = image.scanLine(row);
                memcpy(pDest, pSrc, mat.cols);
                pSrc += mat.step;
            }
            return image;
        }
        // 8-bits unsigned, NO. OF CHANNELS = 3
        else if(mat.type() == CV_8UC3)
        {
            // Copy input Mat
            const uchar *pSrc = (const uchar*)mat.data;
            // Create QImage with same dimensions as input Mat
            QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
            return image.rgbSwapped();
        }
        else if(mat.type() == CV_8UC4)
        {
            // Copy input Mat
            const uchar *pSrc = (const uchar*)mat.data;
            // Create QImage with same dimensions as input Mat
            QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
            return image.copy();
        }
        else
        {
            return QImage();
        }
}

void MainWindow::on_Camera_Switch_clicked()
{
    static bool flage = true;
    if(flage)
    {
        came_open = openCamara(ui->Camera_index->currentIndex());
        if(came_open)
        {
            ui->Start->setEnabled(true);
            ui->Camera_Switch->setText(QString::fromLocal8Bit("关闭相机"));
            ui->Camera_index->setEnabled(false);
            ui->Adjust_Settings->setEnabled(false);
            flage = false;
        }
        else{
            QMessageBox message(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("未找到设备"),QMessageBox::Yes,nullptr);
            message.exec();
        }
    }else {
        came_open = closeCamara();
        ui->Camera_Switch->setText(QString::fromLocal8Bit("打开相机"));
        ui->Start->setEnabled(false);
        ui->Camera_index->setEnabled(true);
        ui->Adjust_Settings->setEnabled(true);
        flage = true;
    }
}

void MainWindow::readFarme()
{
    cam->read(frame);

    Mat channel[3],Mer;
    Split_RGB(frame,channel[2],channel[1],channel[0],false);

    if(AI.auto_adj)
    {
        for (int i=0;i<3;i++) {
            Equalizehist(channel[i],channel[i]);
        }
    }else {
        for (int i=0;i<3;i++) {
            Adj_Img(channel[i],channel[i],AI);
        }
    }

    if(ui->filter->isChecked())
    {
        for (int i=0;i<3;i++) {
            channel[i] = Butterworth_Low_Paass_Filter(channel[i],
                                                      ui->order_n->value(),
                                                      ui->D0_R->value(),false);
        }
    }

    Merge_RGB(channel[2],channel[1],channel[0],Mer);
    frame = Mer;
    ui->Camera_View->displayImage(frame);
} 

void MainWindow::on_Adjust_Settings_triggered()
{
    if(D1.exec()==adjust_Dialog::Accepted)
    AI = D1.get_adj_value();
}

void MainWindow::on_Start_clicked()
{
    ui->Start->setEnabled(false);
    if(came_open)
    {
        timer->stop();

        takingPictures();
    }

    int witch;
    bool flag = iden_proc(taking_frame,witch);
    QString QS_witch;
    if(flag)
    {
        QS_witch = QString::fromLocal8Bit("与模板")+ QString::number(witch) + QString::fromLocal8Bit("属于一类");
    }else {
        QS_witch = QString::fromLocal8Bit("不属于任何一类模板");
    }
    QMessageBox message(QMessageBox::Information,QString::fromLocal8Bit("结果"),
                        QS_witch,QMessageBox::Yes,nullptr);
    message.exec();

    if(came_open)
    timer->start(TIMER);

    ui->Start->setEnabled(true);
}

void MainWindow::on_add_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                       this,
                       QString::fromLocal8Bit("文件对话框！"),
                       "C:",
                       QString::fromLocal8Bit("图片文件(*png *jpg *tif *bmp);"));

    Mat img;
    QImage data;
    QPixmap p_data;
    QIcon icon;

    eigenvalue *Eprt;
    QByteArray Qb = fileName.toLocal8Bit();
    if(!Qb.isEmpty())
    {
        img = imread(Qb.toStdString());
        Eprt = new eigenvalue(img);
        mode_record_img.push_back(Eprt);
        //imshow("打开图片",Eprt->get_img());

        cv::resize(img,img,cv::Size (36,36));
        data = matToQImage(img);
        p_data = QPixmap::fromImage(data);
        icon = p_data;
        int rows=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rows);           //插入一行

        double L,a,b,*temp;
        temp = Eprt->get_eigenvalue();
        L = temp[0];
        a = temp[1];
        b = temp[2];

        ui->tableWidget->setItem(rows,0,new QTableWidgetItem(icon,""));
        ui->tableWidget->setItem(rows,1,new QTableWidgetItem(QString::number(L)));
        ui->tableWidget->setItem(rows,2,new QTableWidgetItem(QString::number(a)));
        ui->tableWidget->setItem(rows,3,new QTableWidgetItem(QString::number(b)));
        ui->tableWidget->selectRow(rows);
        //std::cout<<"mode_record_img size="<<mode_record_img.size()<<std::endl;
    }


}

void MainWindow::on_remove_clicked()
{
    QTableWidgetItem * item = ui->tableWidget->currentItem();
    if(item==Q_NULLPTR)return;

    int row = item->row();
    eigenvalue *I = mode_record_img[row];

    std::vector<eigenvalue*>::iterator iter;
    iter = std::find(mode_record_img.begin(), mode_record_img.end(),I);
    if (iter != mode_record_img.end())
    {
        double *temp,L;
        temp = I->get_eigenvalue();
        L = temp[0];
        //std::cout<<"L="<<L<<std::endl;
        //释放指针
        delete *iter;
        mode_record_img.erase(iter);

        ui->tableWidget->removeRow(row);
        //std::cout<<"mode_record_img size="<<mode_record_img.size()<<std::endl;
    }
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    eigenvalue *I = mode_record_img[row];
    Mat img = I->get_img();

    imshow(std::to_string(row+1),img);
}

void MainWindow::on_Load_Img_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                       this,
                       QString::fromLocal8Bit("文件对话框！"),
                       "C:",
                       QString::fromLocal8Bit("图片文件(*png *jpg *tif *bmp);"));
    QByteArray Qb = fileName.toLocal8Bit();
    if(!Qb.isEmpty())
    {
        taking_frame = imread(Qb.toStdString());
        ui->Camera_View->displayImage(taking_frame);
        ui->Start->setEnabled(true);
    }
}

void MainWindow::on_save_as_mode_triggered()
{
    if(came_open)
    timer->stop();

    QString fileName = QFileDialog::getSaveFileName(
                this,
                QString::fromLocal8Bit("保存对话框！"),
                "C:",
                QString::fromLocal8Bit("图片文件(*.png"));
    QByteArray Qb = fileName.toLocal8Bit();
    if(!Qb.isEmpty())
    {
        std::cout<<"fileName="<<Qb.toStdString()<<std::endl;
        imwrite(Qb.toStdString(),frame);
    }

    if(came_open)
    timer->start(TIMER);
}
