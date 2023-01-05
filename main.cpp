
#include <QThreadPool>
#include <QApplication>
#include <opencv.hpp>
#include "MyWidget.h"
#include "VideoStream.h"
#include "FrameProcessor.h"





int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    VideoStream videoStream;
    MyWidget widget;
    QObject::connect(&videoStream, &VideoStream::newFrame, &widget, &MyWidget::updateFrame);
    videoStream.startStream();
    widget.show();
    return app.exec();
}
