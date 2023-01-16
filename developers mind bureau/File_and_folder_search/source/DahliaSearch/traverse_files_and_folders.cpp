#include "traverse_files_and_folders.h"

traverse_files_and_folders::traverse_files_and_folders(QObject *parent)
    : QObject{parent}
{

}

void traverse_files_and_folders::search(QString base_root_folder, QString search_text)
{
    search_thread = new SearchThread();
    search_thread->moveToThread(&q_thread);
    QObject::connect(this, SIGNAL(start_search_thread()), search_thread, SLOT(do_work()));
    QObject::connect(search_thread, SIGNAL(result(int)), this, SLOT(result(int)));
    q_thread.start();
    emit start_search_thread();
}

void traverse_files_and_folders::result(int number)
{
    emit sig_result(number);
}
