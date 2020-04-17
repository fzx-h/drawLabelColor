#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QDomElement>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
static QColor symbolic_color = Qt::gray;
class UkuiMediaButton:public QPushButton
{
    Q_OBJECT
public:
    UkuiMediaButton(QWidget *parent = nullptr);
    ~UkuiMediaButton();
    QPixmap filledSymbolicColoredPixmap(QImage &source, QColor &baseColor);
    QRect IconGeometry();
protected:
    void paintEvent(QPaintEvent *event);
    bool event(QEvent *e);
    void draw(QPaintEvent *e);
};
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    UkuiMediaButton *btn;
    Ui::Widget *ui;
};
#endif // WIDGET_H
