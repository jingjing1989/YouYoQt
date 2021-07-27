#ifndef ROWDELEGATE_H
#define ROWDELEGATE_H

#include <QItemDelegate>
#include <QObject>
#include <QPainter>
#include <QRect>
#include <QStyleOptionViewItem>

class RowDelegate : public QItemDelegate {
public:
  RowDelegate(QObject *parent = 0);

  void drawFocus(QPainter *painter, const QStyleOptionViewItem &option,
                 const QRect &rect) const override;

  void drawCheck(QPainter *painter, const QStyleOptionViewItem &option,
                 const QRect &rect, Qt::CheckState state) const override;
};

#endif // ROWDELEGATE_H
