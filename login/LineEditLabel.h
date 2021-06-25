#ifndef LINEEDITLABEL_H
#define LINEEDITLABEL_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
class LineEditLabel : public QLineEdit

{
  Q_OBJECT
public:
  explicit LineEditLabel(QWidget *parent = nullptr);

  QPushButton *pb_passwordvisible;
};

#endif // LINEEDITLABEL_H
