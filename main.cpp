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

#include <cstdio>

using namespace std;
using namespace PoDoFo;

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
        }
    });

    window.resize(650, 250);
    window.show();
    return app.exec();
}