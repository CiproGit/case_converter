#include "main_window.h"
#include "ui_main_window.h"

Main_window::Main_window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Main_window) {
	ui->setupUi(this);

	this->setWindowTitle(APPLICATION_NAME);

	connect(ui->input_textEdit, SIGNAL(textChanged()), this, SLOT(on_textChanged()));
	connect(ui->upper_checkBox, SIGNAL(clicked()), this, SLOT(on_stateChanged()));
	connect(ui->snake_checkBox, SIGNAL(clicked()), this, SLOT(on_stateChanged()));

	connect(ui->about_action, SIGNAL(triggered()), this, SLOT(show_about()));
}

Main_window::~Main_window() {
	delete ui;
}

void Main_window::convert() {
	if (ui->upper_checkBox->isChecked()) this->output_string = this->input_string.toUpper();
	else this->output_string = this->input_string.toLower();

	if (ui->snake_checkBox->isChecked()) this->output_string.replace(" ", "_");
	else this->output_string.replace("_", " ");

	ui->output_textBrowser->setText(this->output_string);
}

void Main_window::on_textChanged() {
	this->input_string = ui->input_textEdit->toPlainText();
	this->output_string = this->input_string;

	convert();
}

void Main_window::on_stateChanged() {
	convert();
}

void Main_window::show_about() {
	this->about.show();
}
