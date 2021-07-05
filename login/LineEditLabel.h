#ifndef LINEEDITLABEL_H
#define LINEEDITLABEL_H

#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QWidget>
class LineEditLabel : public QLineEdit

{
  Q_OBJECT
public:
  explicit LineEditLabel(QWidget *parent = nullptr);

  QPushButton *pb_passwordvisible;
};

#endif // LINEEDITLABEL_H
