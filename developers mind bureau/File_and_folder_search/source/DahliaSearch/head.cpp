#include "head.h"

head::head(QObject *parent)
    : QObject{parent}
{
    traverse = new traverse_files_and_folders();
}

void head::queue_search(QString root_location, QString search_option)
{
    base_root_folder.clear();
    base_root_folder.append(root_location);

    search_text.clear();
    search_text.append(search_option);

    QObject::connect(traverse, SIGNAL(sig_result(int)), this, SLOT(result(int)));
    traverse->search(base_root_folder, search_text);
}

void head::result(int number)
{
    emit sig_result(number);
}
