#include "MainWindow.h"
#include <iostream>
#include <cmath>
MainWindow::MainWindow(QWidget* parent) : QWidget(parent){
    // Class to define the look of the main window for the
    // measure device

    // name of the labels
    const char* names_label[] = {
        "Voltage(V)", "Frequency(kHz)", "Cross Section(m^2)", "Length(m)", "Mean(Integer)"
        };

    // Set the size of the window
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // Create a block for inputs
    QWidget *input_block = new QWidget(this);
    input_block->setFixedSize(INPUT_BLOCK_WIDTH, INPUT_BLOCK_HEIGHT);
    input_block->move(0,415);

    // Create a block for the plot canvas - in this case the histerese chart (BxH)
    QWidget *plot_block = new QWidget(this);
    plot_block->setFixedSize(PLOT_BLOCK_WIDTH, PLOT_BLOCK_HEIGHT);
    plot_block->move(200,5);

    // Create a block for place some buttons for testing
    m_plot_options_place = new QWidget(this);
    m_plot_options_place->setFixedSize(50,50);
    m_plot_options_place->move(0,0);
    m_testing = new QGridLayout(m_plot_options_place);
    m_push_test = new QPushButton("Ok");
    m_testing->addWidget(m_push_test, 0, 0);

    
    // Create a block to receive options for the plot like
    // plot, real-time plot, usb address, connection status
    // and other things
    m_secundary_plot_block = new QWidget(this);
    m_secundary_plot_block->setFixedSize(PLOT_BLOCK_WIDTH, INPUT_BLOCK_HEIGHT);
    m_secundary_plot_block->move(201, 430);

    /*
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    m_widget_options_plot->setAutoFillBackground(true);
    m_widget_options_plot->setPalette(pal);*/

    // Create a grid layout for organize labels
    // entry fields and buttons
    m_input_block = new QGridLayout(input_block);

    // Create a canvas for plot the charts
    m_plot = new QCustomPlot(plot_block);
    m_plot->setFixedSize(PLOT_BLOCK_WIDTH, PLOT_BLOCK_HEIGHT);    
    
    /* 
        Create the buttons that will define the options for the plots.
        For example, it will be possible in these fields change the 
        plot mode from a static one for a dinamic one (real-time).
    */
    m_sec_plot = new QCustomPlot(m_secundary_plot_block);
    m_sec_plot->setFixedSize(SEC_PLOT_WIDTH, SEC_PLOT_HEIGHT);
    m_sec_plot->xAxis->setLabel("Time (s)");
    m_sec_plot->yAxis->setLabel("Voltage (V)");

    // Set the entry fields and buttons
    for (size_t i = 0; i < 5; i++)
    {
        // Entry Field
        m_lines[i] = new QLineEdit();
        QString aux(names_label[i]);
        m_lines[i]->setPlaceholderText(aux);
        m_lines[i]->setMaxLength(40);
        m_lines[i]->setFixedSize(TEXT_FIELD_WIDTH, TEXT_FIELD_HEIGHT);

        // Buttons
        m_push_buttons[i] = new QPushButton("Ok");
        m_push_buttons[i]->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    }

    // Set Labels in the m_input_block
    for (size_t i = 0; i < 5; i++)
    {
        m_input_block->addWidget(m_lines[i], i, 1);
        m_input_block->addWidget(m_push_buttons[i], i, 2);
    }
    
    // Implement connect method: SIGNAL and SLOT -> new syntax
    connect(
        m_push_buttons[0], &QPushButton::clicked,
        this, &MainWindow::slotGetVoltage
    );   
    connect(
        m_push_buttons[1], &QPushButton::clicked,
        this, &MainWindow::slotGetFrequency
    );
    connect(
        m_push_buttons[2], &QPushButton::clicked,
        this, &MainWindow::slotGetCrossSection
    );
    connect(
        m_push_buttons[3], &QPushButton::clicked,
        this, &MainWindow::slotGetLength
    );
    connect(
        m_push_buttons[4], &QPushButton::clicked,
        this, &MainWindow::slotGetMean
    );

    // Test for see if the voltage plot is working
    connect(
        m_push_test, &QPushButton::clicked,
        m_sec_plot, [this](){
            m_sec_plot->addGraph();
            QVector<double> x(251), y(251); // 2 arrays with 251 points
            for (size_t i = 0; i < 251; i++)
            {
                x[i] = (2*M_PI*i)/251;
                y[i] = sin(x[i]);
            }
            m_sec_plot->xAxis->setLabel("Time (s)");
            m_sec_plot->yAxis->setLabel("Voltage (V)");
            m_sec_plot->graph(0)->addData(x, y);
            m_sec_plot->graph(0)->rescaleAxes();
            m_sec_plot->replot();                 
        }
    );

    // test for the primary plot canvas
    connect(
        m_push_test, &QPushButton::clicked,
        m_plot, [this](){
            m_plot->addGraph();
            QVector<double> x(251), y(251);
            for (size_t i = 0; i < 251; i++)
            {
                x[i] = i;
                y[i] = i;
            }
            m_plot->xAxis->setLabel("H(A/m)");
            m_plot->yAxis->setLabel("B(T)");
            m_plot->graph(0)->addData(x, y);
            m_plot->graph(0)->rescaleAxes();
            m_plot->replot();
        }
    );
}

void MainWindow::slotGetVoltage(void)
{   
    
    const char* voltage_error_message = {
        "VALUE ERROR!\n"
        "The value for the voltage should be\n"
        "of the type double and not zero!"
    };
    QString *aux_string = new QString();
    *aux_string = m_lines[0]->text();
    m_lines[0]->selectAll();
    m_lines[0]->del();
    
    m_voltage = aux_string[0].toDouble();
    
    if (m_voltage == 0) // When the toDouble get a invalid value, return a zero.
    {
        MainWindow::m_construct_pop_error_value(
            voltage_error_message,
            0
            );
    }  
    connect(
        m_pop_error_button, &QPushButton::clicked,
        this, [this](){
            m_push_buttons[0]->setEnabled(true);
            m_lines[0]->setEnabled(true);
        }
    );
    connect(
        m_pop_error_button, &QPushButton::clicked,
        m_error_message, &QDialog::close
    );

}

void MainWindow::slotGetFrequency(void)
{
    const char* frequency_error_message = {
        "VALUE ERROR!\n"
        "The value for the frequency should be\n"
        "of the type double and not zero!"
    };
    QString *aux_string = new QString();
    *aux_string = m_lines[1]->text();
    m_lines[1]->selectAll();
    m_lines[1]->del();
    
    m_frequency = aux_string[0].toDouble();
    
    if (m_frequency == 0) // When the toDouble get a invalid value, return a zero.
    {
        MainWindow::m_construct_pop_error_value(
            frequency_error_message,
            1
            );
    }  
    connect(
        m_pop_error_button, &QPushButton::clicked,
        this, [this](){
            m_push_buttons[1]->setEnabled(true);
            m_lines[1]->setEnabled(true);
        }
    );
    connect(
        m_pop_error_button, &QPushButton::clicked,
        m_error_message, &QDialog::close
    );
}

void MainWindow::slotGetCrossSection(void)
{
    const char* cross_error_message = {
        "VALUE ERROR!\n"
        "The value for the cross section\nshould be "
        "of the type double\nand not zero!"
    };
    QString *aux_string = new QString();
    *aux_string = m_lines[2]->text();
    m_lines[2]->selectAll();
    m_lines[2]->del();
    
    m_cross_section = aux_string[0].toDouble();
    
    if (m_cross_section == 0) // When the toDouble get a invalid value, return a zero.
    {
        MainWindow::m_construct_pop_error_value(
            cross_error_message,
            2
            );
    }  
    connect(
        m_pop_error_button, &QPushButton::clicked,
        this, [this](){
            m_push_buttons[2]->setEnabled(true);
            m_lines[2]->setEnabled(true);
        }
    );
    connect(
        m_pop_error_button, &QPushButton::clicked,
        m_error_message, &QDialog::close
    );
}

void MainWindow::slotGetLength(void)
{
    const char* length_error_message = {
        "VALUE ERROR!\n"
        "The value for the length should be\n"
        "of the type double and not zero!"
    };
    QString *aux_string = new QString();
    *aux_string = m_lines[3]->text();
    m_lines[3]->selectAll();
    m_lines[3]->del();
    
    m_length = aux_string[0].toDouble();
    
    if (m_length == 0) // When the toDouble get a invalid value, return a zero.
    {
        MainWindow::m_construct_pop_error_value(
            length_error_message,
            3
            );
    }  
    connect(
        m_pop_error_button, &QPushButton::clicked,
        this, [this](){
            m_push_buttons[3]->setEnabled(true);
            m_lines[3]->setEnabled(true);
        }
    );
    connect(
        m_pop_error_button, &QPushButton::clicked,
        m_error_message, &QDialog::close
    );
}

void MainWindow::slotGetMean(void)
{
    const char* mean_error_message = {
        "VALUE ERROR!\n"
        "The value for the mean should be\n"
        "of the type integer and not zero!"
    };
    QString *aux_string = new QString();
    *aux_string = m_lines[4]->text();
    m_lines[4]->selectAll();
    m_lines[4]->del();
    
    m_mean = aux_string[0].toDouble();
    
    if (m_mean == 0) // When the toDouble get a invalid value, return a zero.
    {
        MainWindow::m_construct_pop_error_value(
            mean_error_message,
            4
            );
    }  
    connect(
        m_pop_error_button, &QPushButton::clicked,
        this, [this](){
            m_push_buttons[4]->setEnabled(true);
            m_lines[4]->setEnabled(true);
        }
    );
    connect(
        m_pop_error_button, &QPushButton::clicked,
        m_error_message, &QDialog::close
    );
}


void MainWindow::m_construct_pop_error_value(const char* error_message, size_t quantity_index){
    // Disable button and entry until close the popup
        m_push_buttons[quantity_index]->setEnabled(false);
        m_lines[quantity_index]->setEnabled(false);
        // Error pop up
        m_error_message = new QDialog();
        m_error_message->setFixedSize(POP_ERROR_WIDTH, POP_ERROR_HEIGHT);
        m_error_message->setWindowTitle("Value Error!");
        m_pop_error_button = new QPushButton("Ok", m_error_message);
        m_pop_error_button->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
        m_pop_error_button->move(
            POP_ERROR_WIDTH/2 - BUTTON_WIDTH/2,
            3*POP_ERROR_HEIGHT/4 - BUTTON_HEIGHT/4
        );

        m_pop_error_message = new QLabel(m_error_message);
        
        m_pop_error_message->setText(error_message);
        m_pop_error_message->setWordWrap(true);
        m_pop_error_message->move(SOME_MARGIN+20, SOME_MARGIN);
        // Raise a pop up with the error.
        m_error_message->show();
        m_error_message->raise();
        m_error_message->activateWindow();
}