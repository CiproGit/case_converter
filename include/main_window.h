#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Main_window; }
QT_END_NAMESPACE

class Main_window : public QMainWindow {
	Q_OBJECT

private:
	Ui::Main_window *ui;
	QString input_string;
	QString output_string;

	void convert();

private slots:
	void on_textChanged();
	void on_stateChanged();

public:
	Main_window(QWidget *parent = nullptr);
	~Main_window();
};
#endif // MAIN_WINDOW_H
