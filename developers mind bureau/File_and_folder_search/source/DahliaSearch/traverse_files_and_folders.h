#ifndef TRAVERSE_FILES_AND_FOLDERS_H
#define TRAVERSE_FILES_AND_FOLDERS_H

#include <QObject>

class traverse_files_and_folders : public QObject
{
    Q_OBJECT
public:
    explicit traverse_files_and_folders(QObject *parent = nullptr);
    void search(QString base_root_folder, QString search_text);

signals:

};

#endif // TRAVERSE_FILES_AND_FOLDERS_H
