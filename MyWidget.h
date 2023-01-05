#include <QWidget>
#include <QLabel>
#include <QLayout>

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        label = new QLabel(this);
        layout = new QVBoxLayout(this);
        layout->addWidget(label);
        setLayout(layout);
    }

    void updateFrame(QImage image)
    {
        label->setPixmap(QPixmap::fromImage(image));
    }

private:
    QLabel *label;
    QVBoxLayout *layout;
};

