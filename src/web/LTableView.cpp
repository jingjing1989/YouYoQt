#include "LTableView.h"

LTableView::LTableView(QWidget *parent) : QTableView(parent) {}

void LTableView::paintEvent(QPaintEvent *e) {

  qDebug() << __FUNCTION__;
  int colCount = horizontalHeader()->count();
  qDebug() << "colCount:" << colCount;
  qDebug() << "width:" << width();
  qDebug() << "height:" << height();
  //  for (int i = 0; i < colCount - 1; i++) {
  //    resizeColumnToContents(i);
  //  }
  int rowCount = verticalHeader()->count();
  for (int i = 0; i < rowCount - 1; i++) {
    resizeRowToContents(i);
  }
  return QTableView::paintEvent(e);
}

int LTableView::sizeHintForColumn(int column) const {
  //  if (m_colsWidthPercent.size() == horizontalHeader()->count()) {
  //    if (m_colsWidthPercent.value(column) == 0) {
  //      return this->columnWidth(column);
  //    } else {
  //      return m_colsWidthPercent.value(column) *
  //             (this->width() - m_colsFixedWidth) / 100;
  //    }
  //  } else {
  qDebug() << __FUNCTION__;
  Q_UNUSED(column);
  int colCount = horizontalHeader()->count();
  return this->width() / colCount;
  //}
}

int LTableView::sizeHintForRow(int row) const {
  qDebug() << __FUNCTION__;
  if (row == 1) {
    return height() * 0.50;
  } else {
    return height() * 0.1;
  }
}
