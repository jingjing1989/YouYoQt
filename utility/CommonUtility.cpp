

#include "CommonUtility.h"

#include <QDebug>
#include <QFile>
#include <QFontDatabase>

CommonUtility::CommonUtility() {}

//设置样式表
void CommonUtility::setStyleSheet(const QString &strFile, QWidget *pwidget) {
  qDebug() << __FUNCTION__;
  //只有对qApp才可以直接用"file:///:/qss/files/application.css"设置
  if (pwidget == nullptr)
    return;
  QFile styleSheet(strFile);

  if (!styleSheet.open(QIODevice::ReadOnly)) {
    QString strWarning = "Unable to open file" + strFile;
    qWarning(strWarning.toUtf8().data());
    return;
  }
  pwidget->setStyleSheet(styleSheet.readAll());
}

/**一个简单的初始化步骤
 * @brief CommonUtility::globalInit
 */
void CommonUtility::globalInit(QApplication *app) {
  qDebug() << __FUNCTION__;
  if (app == nullptr)
    return;

  //----字体初始化----
  addIconFont();
  addDefaultFont();
  // QApplication::setFont(QFont("Microsoft Yahei", 9));
  // 先默认黑体
  QApplication::setFont(QFont("SimHei", 9));
}

void CommonUtility::addIconFont() {
  int fontId = QFontDatabase::addApplicationFont(":/iconfont/res/iconFont/fontawesome-webfont.ttf");
  if (fontId < 0)
    qWarning() << "FontAwesome cannot be loaded !";
  return;
}

void CommonUtility::addDefaultFont() {
  int fontId = QFontDatabase::addApplicationFont(":/iconfont/res/iconFont/NotoSansCJKsc.otf");
  if (fontId < 0)
    qWarning() << "NotoSansCJKsc cannot be loaded !";
  return;
}
