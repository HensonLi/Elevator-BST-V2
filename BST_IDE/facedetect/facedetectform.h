#ifndef FACEDETECTFORM_H
#define FACEDETECTFORM_H

#include "tabpage.h"
#ifdef SURRPORT_OPENCV
#include "highgui.h"
#include "cv.h"
#endif

namespace Ui {
class FaceDetectForm;
}

class FaceDetectForm : public TabPage
{
    Q_OBJECT
public:
    explicit FaceDetectForm(QWidget *parent = 0);
    ~FaceDetectForm();

    void openCamara();
    void closeCamara();
    void takingPictures();
    bool addPictureItem(QImage pImage, QString pName);
#ifdef SURRPORT_OPENCV
    void detect_and_draw(IplImage *img);
    void DetectOnePixmap(QString pFile);
#endif
    
private slots:
    void readFarme();
    void on_PictureQueneList_itemDoubleClicked(QListWidgetItem *item);
    void on_BtnOpenCamera_clicked();
    void on_BtnTakePicture_clicked();

private:
    Ui::FaceDetectForm *ui;
#ifdef SURRPORT_OPENCV
    CvHaarClassifierCascade* cascade;
    CvMemStorage* storage;
#endif
    QString   cascade_name; //�������Ҫ�õ��ķ�����

    quint32   m_PicTakenCount;

    QTimer    *timer;
#ifdef SURRPORT_OPENCV
    CvCapture *cam;// ��Ƶ��ȡ�ṹ�� ������Ϊ��Ƶ��ȡ������һ������
    IplImage  *frame;//����IplImage����ָ�룬���������ڴ�ռ������ÿһ֡ͼ��
#endif
};

#endif // FACEDETECTFORM_H