#ifndef LTABLEVIEW_H
#define LTABLEVIEW_H

#include <QDebug>
#include <QHeaderView>
#include <QObject>
#include <QTableView>
#include <QWidget>

class LTableView : public QTableView

{
  Q_OBJECT
public:
  explicit LTableView(QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *e) override;

  int sizeHintForColumn(int column) const;
  int sizeHintForRow(int row) const;
};

#endif // LTABLEWIVEW_H
