

#include <QApplication>
#include <QDialog>

#include "home/CHarts.h"
#include "home/MainWindowHome.h"
#include "home/MyTableWidget.h"
#include "login/loginDialog.h"
#include "setting/MainWindowSetting.h"
#include "setting/SettingDialog.h"
#include "setting/SystemSettingMainWindow.h"

#include "Test.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  // Widget w;
  //    w.show();
  //    return a.exec();

  loginDialog login;
  if (login.exec() == QDialog::Accepted) //调用login.exec()，阻塞主控制流，直到完成返回
  {
    // w.show();
#if 0
        SettingDialog setting;
        setting.show();


        MainWindowSetting setting;
        setting.show();

       SystemSettingMainWindow set;
       set.show();
       MyTableWidget home;
       home.show();


    MainWindowHome home;
    home.show();
#endif

    CHarts s;
    s.show();

    //    Test t;
    //    t.show();

    return app.exec();
  } else
    return 0;
}
