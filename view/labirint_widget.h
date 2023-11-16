#ifndef LABIRINT_WIDGET_H
#define LABIRINT_WIDGET_H

#include "maze.h"
#include "pathfinder.h"
#include <QWidget>
#include <QPainter>


namespace Ui {
class LabirintWidget;
}

class LabirintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LabirintWidget(QWidget *parent = nullptr);
    ~LabirintWidget();

private:
    Ui::LabirintWidget *ui;
    Maze* maze_;
    Pathfinder* pf_;
    void paintEvent(QPaintEvent *) override;

private slots:
    void SlotGenerateBtn();
    void SlotPathBtn();
    void SlotSaveBtn();
    void SlotLoadBtn();
};

#endif // LABIRINT_WIDGET_H
