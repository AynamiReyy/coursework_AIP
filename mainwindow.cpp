#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->cmb_controller->addItems({"double", "float", "uint8_t", "int", "int64_t", "size_t", "Rational"});
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key) {
        ui->tb_extra->setText(QString::fromStdString(*key));
        ui->tb_extra->setVisible(true);
    } else {
        ui->tb_extra->setVisible(false);
    }
}

void MainWindow::SetDigitKeyCallback(std::function<void(int)> cb) {
    digit_cb_ = cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation)> cb) {
    operation_cb_ = cb;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey)> cb) {
    control_cb_ = cb;
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType)> cb) {
    controller_cb_ = cb;
}

void MainWindow::on_tb_one_clicked() {
    if (digit_cb_) {
        digit_cb_(1);
    }
}

void MainWindow::on_tb_two_clicked() {
    if (digit_cb_) {
        digit_cb_(2);
    }
}

void MainWindow::on_tb_three_clicked() {
    if (digit_cb_) {
        digit_cb_(3);
    }
}

void MainWindow::on_tb_four_clicked() {
    if (digit_cb_) {
        digit_cb_(4);
    }
}
void MainWindow::on_tb_five_clicked() {
    if (digit_cb_) {
        digit_cb_(5);
    }
}

void MainWindow::on_tb_six_clicked() {
    if (digit_cb_) {
        digit_cb_(6);
    }
}

void MainWindow::on_tb_seven_clicked() {
    if (digit_cb_) {
        digit_cb_(7);
    }
}

void MainWindow::on_tb_eight_clicked() {
    if (digit_cb_) {
        digit_cb_(8);
    }
}

void MainWindow::on_tb_nine_clicked() {
    if (digit_cb_) {
        digit_cb_(9);
    }
}

void MainWindow::on_tb_zero_clicked() {
    if (digit_cb_) {
        digit_cb_(0);
    }
}

void MainWindow::on_tb_extra_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::EXTRA_KEY);
    }
}

void MainWindow::on_tb_negate_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::PLUS_MINUS);
    }
}
void MainWindow::on_tb_backspace_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::BACKSPACE);
    }
}
void MainWindow::on_tb_equal_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::EQUALS);
    }
}
void MainWindow::on_tb_reset_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::CLEAR);
    }
}

void MainWindow::on_tb_ms_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::MEM_SAVE);
    }
}
void MainWindow::on_tb_mc_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::MEM_CLEAR);
    }
}
void MainWindow::on_tb_mr_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::MEM_LOAD);
    }
}

void MainWindow::on_tb_add_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::ADDITION);
    }
}

void MainWindow::on_tb_substract_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::SUBTRACTION);
    }
}

void MainWindow::on_tb_multiplicate_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::MULTIPLICATION);
    }
}

void MainWindow::on_tb_divide_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::DIVISION);
    }
}

void MainWindow::on_tb_power_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::POWER);
    }
}

void MainWindow::on_cmb_controller_currentIndexChanged(int) {
    if (!controller_cb_) {
        return;
    }

    static const QHash<QString, ControllerType> types = {
        {"double",   ControllerType::DOUBLE},
        {"float",    ControllerType::FLOAT},
        {"uint8_t",  ControllerType::UINT8_T},
        {"int",      ControllerType::INT},
        {"int64_t",  ControllerType::INT64_T},
        {"size_t",   ControllerType::SIZE_T},
        {"Rational", ControllerType::RATIONAL}
    };

    QString current = ui->cmb_controller->currentText();
    if(types.contains(current)) {
        controller_cb_(types.value(current));
    }
}