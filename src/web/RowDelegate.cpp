#include "RowDelegate.h"
RowDelegate::RowDelegate(QObject *parent) : QItemDelegate(parent) {}

void RowDelegate::drawFocus(QPainter *painter,
                            const QStyleOptionViewItem &option,
                            const QRect &rect) const {}

void RowDelegate::drawCheck(QPainter *painter,
                            const QStyleOptionViewItem &option,
                            const QRect &rect, Qt::CheckState state) const {}
