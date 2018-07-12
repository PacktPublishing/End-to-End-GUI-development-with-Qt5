#include "mainwindow.h"
#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QListView>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QPrinter>
#include <QTextEdit>
#include "ui_mainwindow.h"

#include "../cutecomics/entities/characters.h"

#include "scripthighlighter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    auto charactersListView = w.ui->charactersListView;
    auto addCharacterButton = w.ui->addCharacterButton;
    auto addCharacterInput = w.ui->addCharacterInput;
    auto scriptEditor =  w.ui->scriptEditor;
    auto actionSaveAs =  w.ui->actionSaveAs;
    auto actionExportPdf =  w.ui->actionExportPdf;

    addCharacterInput->setStyleSheet("background-color: #333; color: #eee;");

    auto characters = new entities::Characters(&a);

    if (scriptEditor) {
        new ScriptHighlighter(scriptEditor->document());
    }

    if (charactersListView) {
        charactersListView->setModel(characters);
    }

    if (charactersListView && scriptEditor) {
        QObject::connect(charactersListView, &QListView::doubleClicked, [characters, scriptEditor](QModelIndex index) {
            scriptEditor->append(QString("> %1: ").arg(characters->data(index).toString()));
        });
    }

    if (addCharacterButton && addCharacterInput) {
        QObject::connect(addCharacterButton, &QPushButton::clicked, [characters, addCharacterInput]() {
            if (! addCharacterInput->text().isEmpty()) {
                characters->add(addCharacterInput->text());
                addCharacterInput->clear();
            }
        });
    }

    if (actionSaveAs && scriptEditor) {
        QObject::connect(actionSaveAs, &QAction::triggered, [&w, scriptEditor]() {
            QString fileName = QFileDialog::getSaveFileName();
            if (!fileName.isEmpty()) {
                QFile file(fileName);

                if (!file.open(QIODevice::WriteOnly)) {
                    QMessageBox::information(0, "Unable to open file", file.errorString());
                    return;
                }
                QDataStream out(&file);
                out << scriptEditor->toPlainText();
            }
        });
    }

    if (actionExportPdf && scriptEditor) {
        QObject::connect(actionExportPdf, &QAction::triggered, [scriptEditor]() {
            QString fileName = QFileDialog::getSaveFileName();
            if (!fileName.isEmpty()) {
                if (QFileInfo(fileName).suffix().isEmpty())
                    fileName.append(".pdf");

                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOutputFileName(fileName);
                printer.setFontEmbeddingEnabled(true);

                auto doc = scriptEditor->document();
                doc->print(&printer);
            }
        });
    }

    w.show();

    return a.exec();
}
