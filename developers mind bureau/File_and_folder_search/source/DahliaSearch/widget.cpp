#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

void Widget::initalize()
{
    layout = new QBoxLayout(QBoxLayout::TopToBottom, nullptr);
    this->setLayout(layout);
        container_widget_for_search_root_location = new QWidget();
        container_layout_for_search_root_location = new QBoxLayout(QBoxLayout::LeftToRight);
        container_widget_for_search_root_location->setLayout(container_layout_for_search_root_location);
        layout->addWidget(container_widget_for_search_root_location);
            search_root_location_lineedit = new QLineEdit(QString("Root Folder Path"), nullptr);
            container_layout_for_search_root_location->addWidget(search_root_location_lineedit);

        container_widget_for_search_options = new QWidget();
        container_layout_for_search_options = new QBoxLayout(QBoxLayout::LeftToRight);
        container_widget_for_search_options->setLayout(container_layout_for_search_options);
        layout->addWidget(container_widget_for_search_options);

            search_by_text_bar_lineedit = new QLineEdit(QString("Search"), nullptr);
            container_layout_for_search_options->addWidget(search_by_text_bar_lineedit);

        container_widget_for_searchresults_tableview = new QWidget();
        container_layout_for_searchresults_tableview = new QBoxLayout(QBoxLayout::TopToBottom);
        container_widget_for_searchresults_tableview->setLayout(container_layout_for_searchresults_tableview);
        layout->addWidget(container_widget_for_searchresults_tableview);

            searchresults_tableview = new QTableView(nullptr);
            container_layout_for_searchresults_tableview->addWidget(searchresults_tableview);
            myModel = new QStandardItemModel();
            QStandardItem *item1 = new QStandardItem("Test");

           // set the item to the model
           myModel->setItem(0,0,item1);
            searchresults_tableview->setModel(myModel);

        button_begin_search = new QPushButton(QString("Begin Search"), nullptr);
        layout->addWidget(button_begin_search);

    QObject::connect(button_begin_search, SIGNAL(pressed()), this, SLOT(search_activated()));

}

void Widget::set_head(head * set_ptr_to_head)
{
    ptr_to_head_of_body = set_ptr_to_head;
    QObject::connect(ptr_to_head_of_body, SIGNAL(sig_result(int)), this, SLOT(result(int)));
}

void Widget::search_activated()
{
    button_begin_search->setDisabled(true);
    search_root_location_lineedit->setDisabled(true);
    search_by_text_bar_lineedit->setDisabled(true);
    ptr_to_head_of_body->queue_search(search_root_location_lineedit->text(), search_by_text_bar_lineedit->text());
}

void Widget::result(int number)
{
    qDebug() << number;
}
