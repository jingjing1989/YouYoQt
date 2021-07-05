#ifndef TOOLBUTTONICONTEXT_H
#define TOOLBUTTONICONTEXT_H

#include <QToolButton>
#include <QWidget>

class ToolButtonIconText : public QToolButton {
  Q_OBJECT

public:
  explicit ToolButtonIconText(QWidget *parent = nullptr);

signals:
};

#endif // TOOLBUTTONICONTEXT_H
