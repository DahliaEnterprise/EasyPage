#include "traverse_files_and_folders.h"

traverse_files_and_folders::traverse_files_and_folders()
{

}

void traverse_files_and_folders::search(QString set_base_root_folder, QString set_search_text)
{
    base_root_folder.clear();
    base_root_folder.append(set_base_root_folder);

    search_text.clear();
    search_text.append(set_search_text);

    directory_iterator = new QDirIterator(QDir(base_root_folder), QDirIterator::Subdirectories);

    QString next_file_folder_path = directory_iterator->next();
    search_thread = new SearchThread();
    search_thread->set_search_text_and_file_folder_path(set_search_text, next_file_folder_path);
    search_thread->moveToThread(&q_thread);
    QObject::connect(this, SIGNAL(start_search_thread()), search_thread, SLOT(do_work()));
    QObject::connect(search_thread, SIGNAL(result(int)), this, SLOT(result(int)));
    q_thread.start();
    emit start_search_thread();
}

void traverse_files_and_folders::result(int number)
{

    emit sig_result(number);
    if(directory_iterator->hasNext() == true)
    {
        QString next_file_folder_path = directory_iterator->next();
        search_thread->set_search_text_and_file_folder_path(search_text, next_file_folder_path);
         emit start_search_thread();
    }else{
        emit finished_work();
    }

}
