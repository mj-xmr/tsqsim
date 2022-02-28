#include "pch_qt.h"

#include "UtilBare.h"
#include <Util/StrColour.hpp>

UtilBare::UtilBare()
{
    //ctor
}

UtilBare::~UtilBare()
{
    //dtor
}


void UtilBare::HandleException(std::exception & ex)
{
    qDebug() << EnjoLib::StrColour::GenErr("\n\nEXCEPTION!\n").c_str();
    qDebug() << EnjoLib::StrColour::GenErr(ex.what()).c_str();
    QMessageBox msgBox;
    msgBox.setWindowTitle("EXCEPTION!");
    msgBox.setText(ex.what());
    msgBox.exec();
    throw EnjoLib::ExceptRuntimeError(ex.what());
}
