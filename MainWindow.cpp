#include "MainWindow.h"
#include <iostream>
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
    input_block->move(0,400);

    // Create a block for the plot canvas
    QWidget *plot_block = new QWidget(this);
    plot_block->setFixedSize(PLOT_BLOCK_WIDTH, PLOT_BLOCK_HEIGHT);
    plot_block->move(200,5);

    // Create a grid layout for organize labels
    // entry fields and buttons
    m_input_block = new QGridLayout(input_block);

    // Create a canvas for plot the charts
    m_plot = new QCustomPlot(plot_block);
    m_plot->setFixedSize(PLOT_BLOCK_WIDTH, PLOT_BLOCK_HEIGHT);
    
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