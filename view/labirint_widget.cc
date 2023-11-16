#include "labirint_widget.h"
#include "ui_labirint_widget.h"
#include <QIntValidator>
#include <QFileDialog>
LabirintWidget::LabirintWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabirintWidget)
{
    ui->setupUi(this);
    setFixedSize(700, 550);
    maze_ = new Maze();
    pf_ = new Pathfinder();
    connect(ui->gen_btn, SIGNAL(clicked()), this, SLOT(SlotGenerateBtn()));
    connect(ui->path_btn, SIGNAL(clicked()), this, SLOT(SlotPathBtn()));
    connect(ui->save_btn, SIGNAL(clicked()), this, SLOT(SlotSaveBtn()));
    connect(ui->load_btn, SIGNAL(clicked()), this, SLOT(SlotLoadBtn()));
    ui->path_btn->setEnabled(false);
    QIntValidator* int_val = new QIntValidator(0,50, this);
    ui->cols_le->setValidator(int_val);
    ui->rows_le->setValidator(int_val);
    ui->from_x_le->setValidator(int_val);
    ui->from_y_le->setValidator(int_val);
    ui->to_x_le->setValidator(int_val);
    ui->to_y_le->setValidator(int_val);
}

LabirintWidget::~LabirintWidget()
{
    delete ui;
}

void LabirintWidget::SlotGenerateBtn() {
    int cols = ui->cols_le->text().toInt();
    int rows = ui->rows_le->text().toInt();
    if (rows < 2) {
        rows = 2;
        ui->rows_le->setText("2");
    }
    if (cols < 2) {
        cols = 2;
        ui->cols_le->setText("2");
    }
    if (rows > 50) {
        rows = 50;
        ui->rows_le->setText("50");
    }
    if (cols > 50) {
        cols = 50;
        ui->cols_le->setText("50");
    }
    ui->from_x_le->setText("0");
    ui->from_y_le->setText("0");
    ui->to_x_le->setText(QString::number(cols - 1));
     ui->to_y_le->setText(QString::number(rows - 1));
    maze_->Generate(rows, cols);
    repaint();
    ui->path_btn->setEnabled(true);
}

void LabirintWidget::SlotPathBtn() {
    std::pair<size_t, size_t> start;
    std::pair<size_t, size_t> finish;
    start.first =  ui->from_x_le->text().toUInt();
    start.second =  ui->from_y_le->text().toUInt();
    finish.first =  ui->to_x_le->text().toUInt();
    finish.second =  ui->to_y_le->text().toUInt();
    if (start.first > maze_->cols_- 1) {
        start.first = 0;
        ui->from_x_le->setText("0");
    }
    if (start.second > maze_->rows_ - 1) {
        start.second = 0;
        ui->from_y_le->setText("0");
    }
    if (finish.first > maze_->cols_- 1) {
        finish.first = maze_->cols_- 1;
        ui->to_x_le->setText(QString::number(maze_->cols_ - 1));
    }
    if (finish.second > maze_->rows_- 1) {
        finish.second = maze_->rows_- 1;
        ui->to_y_le->setText(QString::number(maze_->rows_ - 1));
    }
    if (start == finish) {
        start.first = 0;
        ui->from_x_le->setText("0");
        start.second = 0;
        ui->from_y_le->setText("0");
        finish.first = maze_->cols_- 1;
        ui->to_x_le->setText(QString::number(maze_->cols_ - 1));
        finish.second = maze_->rows_- 1;
        ui->to_y_le->setText(QString::number(maze_->rows_ - 1));
    }
    pf_->Init(maze_, start, finish);
    pf_->Solve();
    repaint();
}

void LabirintWidget::SlotSaveBtn() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "/",
                               tr(" (*.txt)"));
    maze_->SaveMaze(fileName.toStdString());
}

void LabirintWidget::SlotLoadBtn() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/",
                                                     tr(" (*.txt)"));
    maze_->LoadMaze(fileName.toStdString());
    repaint();
}

void LabirintWidget::paintEvent(QPaintEvent *) {
    if (maze_->side_border_.size() == 0 || maze_->bottom_border_.size() == 0)
        return;
    QPainter p(this);
    p.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    int x = 2;
    int y = 2;
    for (int i = 0; i < maze_->rows_; ++i) {
        for (int j = 0; j < maze_->cols_; ++j) {
            if (i == 0)
                p.drawLine(x, y, x + maze_->hor_length_, y);
            if (j == 0)
                p.drawLine(x, y, x, y + maze_->vert_length_);
            if (maze_->side_border_[i][j])
                p.drawLine(x + maze_->hor_length_, y, x + maze_->hor_length_, y + maze_->vert_length_);
            if (maze_->bottom_border_[i][j])
                p.drawLine(x, y + maze_->vert_length_, x + maze_->hor_length_, y + maze_->vert_length_);
            j == maze_->cols_ - 1 ? x = 2 : x += (maze_->hor_length_);

        }
        y += (maze_->vert_length_);
    }
    if (pf_->result_.size() > 1) {
        p.setPen(QPen(Qt::red, 2, Qt::SolidLine));
        for (int i = 0; i < pf_->result_.size() - 1; ++i) {
            p.drawLine(pf_->result_[i].first * maze_->hor_length_ + maze_->hor_length_/2 + 2,
                       pf_->result_[i].second * maze_->vert_length_ + maze_->vert_length_/2 + 2,
                       pf_->result_[i + 1].first * maze_->hor_length_ + maze_->hor_length_/2 + 2,
                       pf_->result_[i + 1].second * maze_->vert_length_ + maze_->vert_length_/2 + 2);
        }
        pf_->result_.clear();
    }
}
