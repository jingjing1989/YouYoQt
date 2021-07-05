#include "Test.h"
#include "ui_Test.h"

Test::Test(QWidget *parent) : QWidget(parent), ui(new Ui::Test) { ui->setupUi(this); }

Test::~Test() { delete ui; }
