#include "QtGuiApplication1.h"

using namespace cv;
using namespace std;

QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowTitle(tr("Main Window"));
	openAction = new QAction(QIcon(":/images/doc-open"), tr("&Open..."), this);
	openAction->setShortcuts(QKeySequence::Open);
	openAction->setStatusTip(tr("Open an existing file"));

	connect(openAction, &QAction::triggered, this, &QtGuiApplication1::open);

	QMenu *file = menuBar()->addMenu(tr("&File"));
	file->addAction(openAction);

	QToolBar *toolBar = addToolBar(tr("&File"));
	toolBar->addAction(openAction);

	statusBar();

	timer = new QTimer(this);
	img = new QImage();
	connect(timer, SIGNAL(timeout()), this, SLOT(getFrame()));//��ʱ�Ͷ�ȡ��ǰ����ͷ��Ϣ
}

QtGuiApplication1::~QtGuiApplication1()                        //��������
{
	
}

void QtGuiApplication1::open()
{
	QMessageBox::information(this, tr("Information"), tr("Open"));
}

void QtGuiApplication1::on_open_clicked()
{
	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		tr("ѡ��ͼ��"),
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	if (filename.isEmpty())
	{
		return;
	}
	else
	{
		QImage* imgtest = new QImage;
		if (!(imgtest->load(filename)))                        //����ͼ��
		{
			QMessageBox::information(this,
				tr("��ͼ��ʧ��"),
				tr("��ͼ��ʧ��!"));
			delete imgtest;
			return;
		}

		string str = filename.toStdString();                  // ��filenameת��Ϊstring���ͣ�
		image = imread(str);
		cvtColor(image, image, CV_BGR2RGB);
		cv::resize(image, image, Size(300, 200));
		QImage img = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);

		label = new QLabel();
		label->setPixmap(QPixmap::fromImage(img));
		label->resize(QSize(img.width(), img.height()));
		ui.scrollArea->setWidget(label);

	}

}

void QtGuiApplication1::on_process_clicked()
{
	flip(image, image, 4);                                    //��ת���� 0 ���·�ת��������ˮƽ��ת��������ˮƽ��ֱ����ת
	QImage img1 = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);
	label_2 = new QLabel();
	label_2->setPixmap(QPixmap::fromImage(img1));
	label_2->resize(QSize(img1.width(), img1.height()));
	ui.scrollArea_2->setWidget(label_2);

}

//������ͷ
void QtGuiApplication1::on_OpenCameraBtn_clicked()
{
	capture1.open(0);                                            //������ͷ��������ͷ�л�ȡ��Ƶ
	timer->start(20);                                            //��ʼ��ʱ����ʱ�򷢳�timeout()�ź�,1000Ϊ1�룬50����ȡһ֡
}

//����ȡͼ
void QtGuiApplication1::getFrame()
{
	
	capture1 >> showimage;                         //������ͷ��ץȡ������ÿһ֡����ץȡ����֡����Mat��ʽת��ΪQImage��ʽ,rgbSwapped��Ϊ����ʾЧ��ɫ�ʺ�һЩ��QImage::Format_RGB888��ͬ������ͷ�ò�ͬ�ĸ�ʽ��
	QImage img = Mat2QImage(showimage);

	//1...����label��
	ui.label_3->setScaledContents(true);
	ui.label_3->setPixmap(QPixmap::fromImage(img));              //��ʾͼƬ

	//2...����scrollArea��
	//label = new QLabel();
	//label->setPixmap(QPixmap::fromImage(img));
	//label->resize(QSize(img.width(), img.height()));
	//ui.scrollArea->setWidget(label);
	
}

//����
void QtGuiApplication1::on_TakePicBtn_clicked()
{
	capture1.open(0);                                            //������ͷ������ʱ��һ���������㣬������ӣ�û�������ͷ�����
	capture1 >> showimage;		 
	QImage img = Mat2QImage(showimage);

	ui.label_4->setScaledContents(true);
	ui.label_4->setPixmap(QPixmap::fromImage(img));             //����ȡ��ͼƬ��ʾ��label4��
}

//�ر�����ͷ
void QtGuiApplication1::on_CloseCameraBtn_clicked()
{
	timer->stop(); //ֹͣȡ֡
	ui.label_3->clear();
	capture1.release();

}

QImage QtGuiApplication1::Mat2QImage(Mat cvImg)
{
	Mat cvRgbImg;
	cvtColor(cvImg, cvRgbImg, CV_BGR2RGB);
	//cvtColor(cvImg, cvRgbImg, CV_BGR2GRAY);                   
	cv::resize(showimage, showimage, Size(300, 200));
	QImage dstImage((const uchar *)cvRgbImg.data, cvRgbImg.cols, cvRgbImg.rows, cvRgbImg.step, QImage::Format_RGB888);
	dstImage.bits();
	return dstImage;
}


