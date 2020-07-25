#ifndef DIALOGCOMPILELOGWINDOW_H
#define DIALOGCOMPILELOGWINDOW_H

#include <QDialog>

namespace Ui {
class DialogCompileLogWindow;
}

class DialogCompileLogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCompileLogWindow(QWidget *parent = nullptr);
    ~DialogCompileLogWindow();

private:
    Ui::DialogCompileLogWindow *ui;
};

#endif // DIALOGCOMPILELOGWINDOW_H
