#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDir>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QFileInfo>

#include <podofo/podofo.h>
#include <cstdio>

using namespace std;
using namespace PoDoFo;


void splitDocument(QString inputFilePath, QPlainTextEdit *logBox) {

    auto fileInfo = new QFileInfo(inputFilePath);

    logBox->appendPlainText("Handling...");
    try {
        PdfMemDocument src;
        src.Load(inputFilePath.toStdString());

        const unsigned pages = src.GetPages().GetCount();
        for (unsigned i = 0; i < pages; ++i) {
            PdfMemDocument dst;
            dst.GetPages().AppendDocumentPages(src, i, 1);
            auto outputFilePath = QString::asprintf(
                    "%s/%s%03u.pdf",
                    fileInfo->absolutePath().toUtf8().constData(),
                    fileInfo->completeBaseName().toUtf8().constData(),
                    i + 1
            );

            dst.Save(outputFilePath.toStdString());

            logBox->appendPlainText("Output file: " + outputFilePath);
        }
    } catch (const std::exception& e) {
        logBox->appendPlainText("Error: " + QString(e.what()));
        return;
    }

    logBox->appendPlainText("Done!");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("PDF Splitter");

    auto *mainLayout = new QVBoxLayout(&window);

    auto *topLayout = new QHBoxLayout();

    auto *label = new QLabel("Choose a PDF to split into pages");
    topLayout->addWidget(label);

    auto *btn   = new QPushButton("Choose file");
    topLayout->addWidget(btn);


    auto *logBox = new QPlainTextEdit();
    logBox->setReadOnly(true);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(logBox);

    QString exeDir  = QDir::homePath();

    logBox->appendPlainText("Current directory: "  + exeDir);

    QObject::connect(btn, &QPushButton::clicked, [&](){
        const QString path = QFileDialog::getOpenFileName(
            &window,
            "Choose PDF file",
            exeDir,
            "PDF files (*.pdf)"
        );
        if (!path.isEmpty()) {
            logBox->appendPlainText("Chosen file: " + QDir::toNativeSeparators(path));
            splitDocument(path, logBox);
        }
    });

    window.resize(650, 250);
    window.show();
    return app.exec();
}