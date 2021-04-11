#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcustomplot.h"
#include <qt5/QtWidgets/QDialog>
#include <qt5/QtWidgets/QGridLayout>
#include <qt5/QtWidgets/QLayout>
#include <qt5/QtWidgets/QLineEdit>
#include <qt5/QtWidgets/QPushButton>
#include <qt5/QtWidgets/QWidget>


class MainWindow : public QWidget
{
// Warning to use meta-object compiler
Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = 0);
    void m_construct_pop_error_value(
        const char* error_message, size_t quantity_index
    );
signals:
    void popErrorValue();
public slots:
    void slotGetVoltage(void);
    void slotGetFrequency(void);
    void slotGetCrossSection(void);
    void slotGetLength(void);
    void slotGetMean(void);
private:
    // Standart sizes
    size_t WINDOW_HEIGHT = 600, WINDOW_WIDTH = 800;
    size_t BUTTON_HEIGHT = 20, BUTTON_WIDTH = 60;
    size_t TEXT_FIELD_HEIGHT = 20, TEXT_FIELD_WIDTH = 120;
    size_t INPUT_BLOCK_HEIGHT = 180, INPUT_BLOCK_WIDTH = 200;
    size_t PLOT_BLOCK_HEIGHT = 400, PLOT_BLOCK_WIDTH = 580;
    size_t POP_ERROR_HEIGHT = 150, POP_ERROR_WIDTH = 300;
    size_t PLOT_OPTIONS_HEIGHT = 200, PLOT_OPTIONS_WIDTH = 580;
    size_t SOME_MARGIN = 15;
    // physical quantities
    double m_voltage, m_frequency, m_cross_section;
    double m_length, m_mean;
    // pop condition
    bool pop_condition;
    // main window set up
    QCustomPlot *m_plot;
    QGridLayout *m_input_block;
    QLineEdit *m_lines[5];
    QPushButton *m_push_buttons[5];
    // Error Value pop up
    QDialog *m_error_message;
    QPushButton* m_pop_error_button;
    QLabel* m_pop_error_message;
    // Plot Options
    QWidget *m_widget_options_plot;
    QGridLayout *m_grid_options;
    QPushButton *m_normal_plot;

};


#endif