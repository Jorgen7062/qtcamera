#pragma once

#ifndef QTGUIAPPLICATION1_H
#define QTGUIAPPLICATION1_H

#include <QtWidgets/QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QGraphicsScene>  
#include <QGraphicsView>                //graphicsview��
#include <qfiledialog.h>                //getopenfilename ������
#include <qlabel.h>                     //label��
#include <qtimer.h>
#include <qimage.h>

#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>  //opencv����

#include "ui_QtGuiApplication1.h"

using namespace cv;

class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);
	~QtGuiApplication1();

private slots:                        
	void on_open_clicked();           //��ͼƬ
	void on_process_clicked();        //����ͼƬ
	void on_OpenCameraBtn_clicked();    //������ͷ
	void getFrame();
	void on_TakePicBtn_clicked();
	void on_CloseCameraBtn_clicked();   //�ر�����ͷ

private:
	Ui::QtGuiApplication1Class ui;

	void open();
	QAction *openAction;

	Mat image;

	QTimer *timer;//��ʱ�����ڶ�ʱȡ֡������˵�ĸ�һ��ʱ���ȥȡ���������ʵ��
	QImage *img;
	Mat showimage;//����ͷÿ��ץȡ��ͼ��Ϊһ֡��ʹ�ø�ָ��ָ��һ֡ͼ����ڴ�ռ�
	VideoCapture capture1;

	QLabel *label;
	QLabel *label_2;
	QLabel *label_3;
	QLabel *label_4;

	QImage Mat2QImage(Mat cvImg);

};

#endif //QTGUIAPPLICATION1_H