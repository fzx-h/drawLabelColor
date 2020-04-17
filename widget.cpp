#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QSvgRenderer>
#include <QDomDocument>

void UkuiMediaButton::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    p.setBrush(QBrush(QColor(0x13,0x13,0x14,0x00)));
    p.setPen(Qt::NoPen);
    QPainterPath path;
    opt.rect.adjust(0,0,0,0);
    path.addRoundedRect(opt.rect,6,6);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect,6,6);
    setProperty("blurRegion",QRegion(path.toFillPolygon().toPolygon()));
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QRect UkuiMediaButton::IconGeometry()
{
    QRect res = QRect(QPoint(0,0),QSize(24,24));
    res.moveCenter(QRect(0,0,width(),height()).center());
    return res;
}

void UkuiMediaButton::draw(QPaintEvent* /*event*/)
{
//    QImage()/
    QImage image("/usr/share/ukui-media/img/microphone-low.svg");
    QPainter painter(this);
    QRect iconRect = IconGeometry();
    if (image.size() != iconRect.size())
    {
        image = image.scaled(iconRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QRect r = image.rect();
        r.moveCenter(iconRect.center());
        iconRect = r;
    }

//    isPixmapPureColor(image);
//    this->setProperty("useIconHighlightEffect", true);
//    this->setProperty("iconHighlightEffectMode", true);
//    qApp->setProperty("symbolicColor", QColor(0,255,0));
    this->setProperty("fillIconSymbolicColor", true);
    QColor green(0,0,0,0);
    filledSymbolicColoredPixmap(image,green);
    painter.drawImage(iconRect, image);

}


bool UkuiMediaButton::event(QEvent *event)
{

        switch (event->type())
        {
        case QEvent::Paint:
            draw(static_cast<QPaintEvent*>(event));
            break;

        case QEvent::Move:
        case QEvent::Resize:
        {
            QRect rect = IconGeometry();
//            xfitMan().moveWindow(mWindowId, rect.left(), rect.top());
        }
            break;

        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
            event->accept();
            break;

        default:
            break;
        }


    return QPushButton::event(event);
}


UkuiMediaButton::UkuiMediaButton(QWidget *parent)
{
    Q_UNUSED(parent);
    this->setFixedSize(36,36);
}
UkuiMediaButton::~UkuiMediaButton()
{

}

QPixmap UkuiMediaButton::filledSymbolicColoredPixmap(QImage &img, QColor &baseColor)
{
//    QImage img = source.toImage();

    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            auto color = img.pixelColor(x, y);
            if (color.alpha() > 0) {
                int hue = color.hue();
                if (!qAbs(hue - symbolic_color.hue()) < 10) {
                    qDebug() << "***********************";
                    color.setRed(baseColor.red());
                    color.setGreen(baseColor.green());
                    color.setBlue(baseColor.blue());
                    img.setPixelColor(x, y, color);
                }
            }
        }
    }

    return QPixmap::fromImage(img);
}



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    btn = new UkuiMediaButton(this);
    btn->show();
    btn->move(200,200);
}

Widget::~Widget()
{
    delete ui;
}

