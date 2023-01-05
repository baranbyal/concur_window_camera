#include <QApplication>
#include <opencv.hpp>
#include <QThreadPool>
#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QLayout>
#include "VideoStream.h"


class FrameProcessor : public QObject, public QRunnable
{
    Q_OBJECT

public:
    FrameProcessor(cv::Mat frame) : frame(frame) {}

    void run()
    {
        // process the frame
        // ...
        MatToQImage matToQImage;
        qImage = matToQImage.getQImage(frame);
        emit finished();
    }

    QImage getQImage() { return qImage; }

signals:
    void finished();

private:
    cv::Mat frame;
    QImage qImage;
};
