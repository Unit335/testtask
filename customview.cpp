#include "customview.h"

customView::customView(QWidget *parent) : QGraphicsView(parent)
{

}

//provides scaling of QGraphicsView by mouse wheel
void customView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor = 1.15;

    if (event->delta() > 0)
    {
        scale(scaleFactor, scaleFactor);
    }
    else
    {
        scale(1/scaleFactor, 1/scaleFactor);
    }
}
