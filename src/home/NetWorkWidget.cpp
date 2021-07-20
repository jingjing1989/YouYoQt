#include "NetWorkWidget.h"
#include "ui_NetWorkWidget.h"

NetWorkWidget::NetWorkWidget(QWidget *parent) :
                                                QWidget(parent),
                                                ui(new Ui::NetWorkWidget)
{
  ui->setupUi(this);
}

NetWorkWidget::~NetWorkWidget()
{
  delete ui;
}
