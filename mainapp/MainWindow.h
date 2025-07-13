#include <QMainWindow>
#include <QByteArray>
#include <QString>
#include <QLocalSocket>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr)
        : QMainWindow(parent), socket(new QLocalSocket(this)),
        btn(new QPushButton("Send Request", this)),
        label(new QLabel("Result will be here", this)),
        currentValue(42)
    {
        auto layout = new QVBoxLayout;
        layout->addWidget(btn);
        layout->addWidget(label);

        auto central = new QWidget(this);
        central->setLayout(layout);
        setCentralWidget(central);

        connect(btn, &QPushButton::clicked, this, &MainWindow::sendRequest);

        socket->connectToServer("MyPluginSocket");
    }

private slots:
    void sendRequest() {
        if (socket->state() != QLocalSocket::ConnectedState) {
            socket->connectToServer("MyPluginSocket");
            if (!socket->waitForConnected(1000)) {
                label->setText("Failed to connect to server");
                return;
            }
        }

        QByteArray req = createRequest(currentValue);
        socket->write(req);
        socket->flush();

        if (!socket->waitForReadyRead(1000)) {
            label->setText("No response from server");
            return;
        }

        QByteArray resp = socket->readAll();
        label->setText("Result: " + QString(resp));
    }

private:
    QByteArray createRequest(int value) {
        return QByteArray::number(value);
    }

    QLocalSocket* socket;
    QPushButton* btn;
    QLabel* label;
    int currentValue;
};
