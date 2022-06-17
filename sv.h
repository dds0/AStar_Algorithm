#ifndef SV_H
#define SV_H
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <QString>

class save_n_download
{
public:
    save_n_download();
    void save(QString fileName);

private:
    QString fileName;
};

#endif // SV_H
