#ifndef DISCORDBOT_H
#define DISCORDBOT_H

#include <QObject>
#include <QTimer>
#include "qdiscordinterpreter.h"


class DiscordBot: public QObject
{
    Q_OBJECT
public:
    DiscordBot(QObject * parent = nullptr);
public slots:
    void login(QString token);

private slots:
    void reload();
    void discordMessage(QDiscordMessage message);
    void loginSuccess();
    void loginFailed();
private:
    QDiscord _discord;
    QDiscordInterpreter _interpreter;
    QString token;
};

#endif // DISCORDBOT_H
