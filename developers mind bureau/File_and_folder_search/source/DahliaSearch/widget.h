#ifndef WIDGET_H
#define WIDGET_H

#include "head.h"

#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QDebug>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void initalize();
    void set_head(head * set_ptr_to_head);

    head * ptr_to_head_of_body;

    QBoxLayout * layout;
        QWidget * container_widget_for_search_root_location;
        QBoxLayout * container_layout_for_search_root_location;
            QLineEdit * search_root_location_lineedit;

        QWidget * container_widget_for_search_options;
        QBoxLayout * container_layout_for_search_options;
            QLineEdit * search_by_text_bar_lineedit;

        QWidget * container_widget_for_searchresults_tableview;
        QBoxLayout * container_layout_for_searchresults_tableview;
            QTableView * searchresults_tableview;
            QStandardItemModel * myModel;

        QPushButton * button_begin_search;

private slots:
    void search_activated();
    void result(int);

};
#endif // WIDGET_H
