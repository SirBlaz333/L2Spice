#include "preferencestabs.h"
#include "ui_preferencestabs.h"

PreferencesTabs::PreferencesTabs(QWidget *parent)
    : QTabWidget(parent)
    , ui(new Ui::PreferencesTabs)
{
    ui->setupUi(this);
}

PreferencesTabs::~PreferencesTabs()
{
    delete ui;
}
