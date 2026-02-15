#include "UI.h"

#include <cstdlib>

MainWindow::MainWindow(int w, int h, const char* name) {
    window = new Fl_Window(w, h, name);
    window->color(FL_WHITE);

    int firstBorder = 60;
    int secondBorder = 430;
    int yCoord = 40;
    int step = 75;
    int longField = 300;
    int shortField = 150;
    int littleField = 80;
    int littleStep = 30 + littleField;
    int fieldHight =35;

    //------------------------1 line---------------------------------
    infInput = new Fl_Input(firstBorder, yCoord, longField, fieldHight, "Информационная последовательность");
    infInput->align(FL_ALIGN_TOP);

    btnInput = new Fl_Button(secondBorder, yCoord, shortField, fieldHight, "ВВОД");
    btnInput->callback(onInput, this);
    btnInput->color(FL_WHITE);

    yCoord += step;

    //------------------------2 line---------------------------------
    kOutput = new Fl_Output(firstBorder, yCoord, littleField, fieldHight, "k");
    kOutput->align(FL_ALIGN_TOP);
    mOutput = new Fl_Output(firstBorder + littleStep, yCoord, littleField, fieldHight, "m");
    mOutput->align(FL_ALIGN_TOP);
    nOutput = new Fl_Output(firstBorder + 2*littleStep, yCoord, littleField, fieldHight, "n");
    nOutput->align(FL_ALIGN_TOP);

    btnCode = new Fl_Button(secondBorder, yCoord, shortField, fieldHight, "КОДИРОВАТЬ");
    btnCode->color(FL_WHITE);
    btnCode->callback(onCode, this);

    yCoord += step;

    //------------------------3 line---------------------------------
    codeOutput = new Fl_Output(firstBorder, yCoord, longField, fieldHight, "Кодовая комбинация");
    codeOutput->align(FL_ALIGN_TOP);

    aChoice = new Fl_Choice(secondBorder, yCoord, shortField, fieldHight, "a");
    aChoice->align(FL_ALIGN_TOP);

    yCoord += step;

    //------------------------4 line---------------------------------
    codeInput = new Fl_Input(firstBorder, yCoord, longField, fieldHight, "Принятая кодовая комбинация");
    codeInput->align(FL_ALIGN_TOP);

    btnDeCode = new Fl_Button(secondBorder, yCoord, shortField, fieldHight, "ДЕКОДИРОВАТЬ");
    btnDeCode->color(FL_WHITE);
    btnDeCode->callback(onDeCode, this);

    yCoord += step;

    //------------------------5 line---------------------------------
    controlOutput = new Fl_Output(firstBorder, yCoord, littleField, fieldHight, "Контрольное число");
    controlOutput->align(FL_ALIGN_TOP);
    rOutput = new Fl_Output(firstBorder + littleStep, yCoord, littleField, fieldHight, "r");
    rOutput->align(FL_ALIGN_TOP);
    NOutput = new Fl_Output(firstBorder + 2*littleStep, yCoord, littleField, fieldHight, "N");
    NOutput->align(FL_ALIGN_TOP);

    eChoice = new Fl_Choice(secondBorder, yCoord, shortField, fieldHight, "E");
    eChoice->align(FL_ALIGN_TOP);

    yCoord += step;

    //------------------------6 line---------------------------------
    resultOutput = new Fl_Output(firstBorder, yCoord, longField, fieldHight, "Результат");
    resultOutput->align(FL_ALIGN_TOP);

    btnExit = new Fl_Button(secondBorder, yCoord, shortField, fieldHight, "ВЫХОД");
    btnExit->callback(onExit, this);
    btnExit->color(FL_WHITE);

    //---------------------------------------------------------

    window->end();
}

void MainWindow::show() {
    window->show();
}

void MainWindow::onInput(Fl_Widget*, void* userdata) {
    auto* ui = static_cast<MainWindow*>(userdata);

    if (!validateString(ui->infInput->value(), true)) {
        return;
    }

    infString = ui->infInput->value();

    Answer codingRes = obj.coding(ui->infInput->value());

    ui->kOutput->value(codingRes.k);
    ui->nOutput->value(codingRes.n);
    ui->mOutput->value(codingRes.m);
}

void MainWindow::onCode(Fl_Widget*, void* userdata) {
    auto* ui = static_cast<MainWindow*>(userdata);

    Answer codingRes = obj.coding(infString);
    
    ui->codeOutput->value(codingRes.combination.c_str());
    ui->codeInput->value(ui->codeOutput->value());

    ui->aChoice->clear();
    for (int i = 0; i < codingRes.A.size(); i++) {
        std::string value = "a" + std::to_string(i) + " = " + std::to_string(codingRes.A[i]);
        ui->aChoice->add(value.c_str());
    }
    ui->aChoice->redraw();
}

void MainWindow::onDeCode(Fl_Widget*, void* userdata) {
    auto* ui = static_cast<MainWindow*>(userdata);

    if (!validateString(ui->codeInput->value(), false)) {
        return;
    }

    Answer2 decodingRes = obj.checking(ui->codeInput->value());
    
    ui->controlOutput->value(decodingRes.s);
    ui->rOutput->value(decodingRes.r);
    ui->NOutput->value(decodingRes.n.c_str());

    ui->eChoice->clear();
    for (int i = 0; i < decodingRes.e.size(); i++) {
        std::string value = "E" + std::to_string(i) + " = " + std::to_string(decodingRes.e[i]);
        ui->eChoice->add(value.c_str());
    }
    ui->eChoice->redraw();

    ui->resultOutput->value(decodingRes.result.c_str()); 
}

void MainWindow::onExit(Fl_Widget*, void* userdata) {
    exit(0);
}

bool MainWindow::validateString(const std::string& s, bool isInf){
    if (s.size() > 20 && isInf) {
        return false;
    }

    for (char c : s) {
        if (c != '0' && c != '1') {
            return false;
        }
    }

    return true;
}