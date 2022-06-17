#include "sv.h"

void save_n_download::save(QString str)
{
    str = QFileDialog::getSaveFileName(this,"Save file","test","Bin files (*.bin);");

    std::ofstream file(str.toStdString(), std::ios::binary | std::ios::trunc | std::ios::in);

    if (file.is_open())
    {
        //file.write(reinterpret_cast<char*>(&rs), sizeof(rs));
        char download_rs[sizeof(rs)];
        std::memcpy(download_rs,(char*)&rs,sizeof(rs));
        file.write(download_rs,sizeof(rs));

        qDebug() << "File " <<str<<" save with size"<<sizeof(rs);
        file.close();
    }
    else
        qDebug() << "File " <<str<<" cannot save with size"<<sizeof(rs);
}
