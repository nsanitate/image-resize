/**
 *<author>Nicola Sanitate</author>
 *<email>n.sanitate@apuliasoft.com</email>
 *<date>2012-02-02</date>
 *<summary>Resize all images of a choosen directory and save them in "Ridimensionate" subdirectory.</summary>
 *
 *<copyright file="main.cpp" company="ApuliaSoft">
 *Copyright (c) 2012. All Right Reserved, http://apuliasoft.com
 *
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with this program. If not, see <http://www.gnu.org/licenses/>.
 *</copyright>
 */

#include <QApplication>
#include <QFileDialog>
#include <QProgressDialog>
#include <QStringBuilder>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFileDialog dialog(0,"Scegli la cartella...",QDir::home().absolutePath());
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setViewMode(QFileDialog::Detail);

    if (dialog.exec())
    {
        QDir directory(dialog.directory());

        qDebug() << "Scelta la directory: " << directory.absolutePath();
        qDebug() << "Trovati numero files: " << directory.count();

        QProgressDialog progress("Ridimensionamento immagini...", "Cancella", 0, directory.count());
        progress.setWindowModality(Qt::WindowModal);

        QStringList files = directory.entryList();
        QString resized_path = directory.absolutePath() % QDir::separator() % "Ridimensionate";
        QDir resized_dir(resized_path);

        if (!resized_dir.exists())
           resized_dir.mkpath(resized_path);

        for (int i = 0; i < files.count(); ++i)
        {
            progress.setValue(i);

            if (progress.wasCanceled())
                break;

            QString file(files.at(i));

            if(file.endsWith(".jpg",Qt::CaseInsensitive) || file.endsWith(".jpeg",Qt::CaseInsensitive))
            {
                qDebug() << "Trovata questa immagine: " << file;

                QPixmap file_image(directory.absoluteFilePath(file));
                QSize size(1280,960);
                QPixmap resized_image(file_image.scaled(size));
                resized_image.save(resized_dir.absoluteFilePath(file));

                qDebug() << "Immagine ridimensionata: " << file;
            }
        }

        progress.setValue(directory.count());
    }
    return EXIT_SUCCESS;
}
