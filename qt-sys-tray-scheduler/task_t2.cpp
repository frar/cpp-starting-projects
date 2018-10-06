#include "task_t2.h"

// Qt headers
#include <QFileInfo>

Task_T2::Task_T2() : TaskStrategy()
{
    mTaskName = "2";
}

bool Task_T2::fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

void Task_T2::execute()
{
    // Check existence of file "C:/ESEMPIO.txt" and if found print a message
    if(!fileExists("C:/ESEMPIO.txt"))
    {
        task_print("File 'C:/ESEMPIO.txt' not found");
    }
}
