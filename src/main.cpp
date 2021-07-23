

#include <QApplication>
#include <QDialog>

#include "home/CHarts.h"

#include "home/MainWindowHome.h"
#include "home/MyTableWidget.h"

#include "login/loginDialog.h"
#include "setting/MainWindowSetting.h"
#include "setting/SettingDialog.h"
#include "setting/SystemSettingMainWindow.h"
#include "utility/CommonUtility.h"
#include "web/MyWeatherWidget.h"
#include "web/client.h"

#include "Test.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  app.setWindowIcon(QIcon(":/images/applogo.ico"));

  loginDialog login;
  CommonUtility::globalInit(&app);
  if (login.exec() ==
      QDialog::Accepted) //调用login.exec()，阻塞主控制流，直到完成返回
  {
#if 0
       SettingDialog setting;
       setting.show();

       MainWindowSetting setting;
       setting.show();

       SystemSettingMainWindow set;
       set.show();

#endif

    MainWindowHome home;
    home.show();
    //    Client c;
    //    c.show();

    MyWeatherWidget weather;
    weather.show();

    //    CHarts chart;
    //    chart.show();

    //    MyTableWidget table;
    //    table.show();

    //    Test t(nullptr);
    //    t.show();

    return app.exec();
  }

  return 0;
}
