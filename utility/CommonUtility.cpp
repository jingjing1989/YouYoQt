

#include "CommonUtility.h"

#include <QFile>
#include <QDebug>

CommonUtility::CommonUtility()
{

}

//设置样式表
void CommonUtility::setStyleSheet(const QString &strFile,QWidget *pwidget)
{
  qDebug()<<__FUNCTION__;
  //只有对qApp才可以直接用"file:///:/qss/files/application.css"设置
  if(pwidget==nullptr)
    return;
  QFile styleSheet(strFile);

  if (!styleSheet.open(QIODevice::ReadOnly)) {
      QString strWarning = "Unable to open file"+strFile;
      qWarning(strWarning.toUtf8().data());
      return;
  }
  qDebug()<<strFile;
   pwidget->setStyleSheet(styleSheet.readAll());
}


