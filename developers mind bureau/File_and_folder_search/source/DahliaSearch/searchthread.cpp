#include "searchthread.h"

SearchThread::SearchThread()
{

}

void SearchThread::do_work()
{
    int output = -1;//1 = file text matches search; 2 = filename matches search; 3 = directory matches

    QFileInfo file_info(next_file_folder_path);
    if (file_info.exists() == true && file_info.isFile() == true)
    {
        //is file
            //open file
            QMimeType mime = mime_db.mimeTypeForFile(next_file_folder_path);
            if(mime.inherits("text/plain") == true)
            {
                QFile file(next_file_folder_path);
                file.open(QFile::ReadOnly);
                QTextStream in(&file);
                QString file_data = in.readAll();
                if(file_data.contains(search_text, Qt::CaseInsensitive) == true)
                {
                    output = 1;
                    qDebug() << next_file_folder_path;
                }
            }
    }else if(file_info.exists() == true && file_info.isDir() == true)
    {
        //is dir

    }

    emit result(output);
}

void SearchThread::set_search_text_and_file_folder_path(QString set_search_text, QString set_next_file_folder_path)
{
    search_text.clear();
    search_text.append(set_search_text);
    next_file_folder_path.clear();
    next_file_folder_path.append(set_next_file_folder_path);

}
