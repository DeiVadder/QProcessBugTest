#include <QApplication>

#include <QProcess>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>

class MyClass : public QObject
{
    Q_OBJECT

    QProcess *m_process1{nullptr};
    QProcess *m_process2{nullptr};

    QWidget *m_widget{nullptr};
public:
    MyClass (QObject *parent = nullptr) : QObject(parent)
    {
        auto btn1 = new QPushButton("Parentless");
        connect(btn1, &QPushButton::clicked, this, &MyClass::launchNotePad2);

        auto btn2 = new QPushButton("With Parent");
        connect(btn2, &QPushButton::clicked, this, &MyClass::launchNotePad1);

        m_widget = new QWidget();
        auto layout = new QHBoxLayout(m_widget);
        layout->addWidget(btn1);
        layout->addWidget(btn2);
        m_widget->show();
    }

    ~MyClass() {
        if(m_widget)
            m_widget->deleteLater();
        if(m_process1)
            m_process1->deleteLater();
        if(m_process2)
            m_process2->deleteLater();
        //Calling delete directly, forces same behaviour as with parent
        //delete m_process2;
    }

public slots:
    void launchNotePad1(){
        m_process1 = new QProcess(this);
        connect(m_process1, &QProcess::started, qApp, &QCoreApplication::quit);
        m_process1->start("notepad.exe");
    }

    void launchNotePad2(){
        m_process2 = new QProcess();
        connect(m_process2, &QProcess::started, qApp, &QCoreApplication::quit);
        m_process2->start("notepad.exe");
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MyClass m;


    return a.exec();
}

#include "main.moc"
