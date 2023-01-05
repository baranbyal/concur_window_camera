#include <QApplication>
#include <opencv.hpp>
#include <QThreadPool>
#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QTimer>
#include "FrameProcessor.h"

class VideoStream : public QObject
{
    Q_OBJECT

public:
    VideoStream() : running(false) {}

    void startStream()
    {
        running = true;
        capture.open(0); // open the default camera
        timer.start(0);
    }

    void stopStream()
    {
        running = false;
        timer.stop();
        capture.release();
    }

signals:
    void newFrame(QImage image);

private slots:
    void processFrame()
    {
        if (running)
        {
            cv::Mat frame;
            capture >> frame; // get a new frame from camera
            FrameProcessor *frameProcessor = new FrameProcessor(frame);
            connect(frameProcessor, &FrameProcessor::finished, this, &VideoStream::frameProcessed);
            QThreadPool::globalInstance()->start(frameProcessor);
        }
    }

    void frameProcessed()
    {
        FrameProcessor *frameProcessor = qobject_cast<FrameProcessor*>(sender());
        QImage image = frameProcessor->getQImage();
        emit newFrame(image);
        frameProcessor->deleteLater();
    }

private:
    bool running;
    cv::VideoCapture capture;
    QTimer timer;
};
