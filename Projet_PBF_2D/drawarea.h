#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include "context.h"


class DrawArea : public QWidget
{
    Q_OBJECT

public:

    Context context;

    explicit DrawArea(QWidget *parent = nullptr);
    ~DrawArea() override {};

    void resizeEvent(QResizeEvent *event) override;

signals:

void particleCountChanged(int newCount);

public slots:

    void paintEvent(QPaintEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void animate();
    void resetSimulation();
    void paint(bool clicked);

};

#endif // DRAWAREA_H
