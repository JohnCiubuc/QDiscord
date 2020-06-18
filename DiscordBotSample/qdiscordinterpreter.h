#ifndef QDISCORDINTERPRETER_H
#define QDISCORDINTERPRETER_H

#define db qDebug() << this <<

#include <QObject>
#include <QDiscord>


class QDiscordInterpreter: public QObject
{
    Q_OBJECT
public:
    explicit QDiscordInterpreter(QDiscord & discord,
                                 QString prefix = "self.",
                                 QObject * parent = 0);
signals:
    void discordMessage(QDiscordMessage);
    void request_restart();

private slots:
    void attemptingReconnect();
    void reconnectImpossible();
    void disconnected(QString reason, int reasonCode);
    void loginFailed();
    void loginSuccess();
    void error(QAbstractSocket::SocketError error);

    void guildEmojis(QByteArray emojiJson);
    void guildCreated(QSharedPointer<QDiscordGuild> guild);
    void pinnedMessages(QJsonArray messages);
    void reactions(QDiscordMessage message, QJsonArray usersWhoReacted);

private:
    void messageReceived(QDiscordMessage message);

    QDiscord & _discord;
    QMap<QString, QString> EmojiMaps;
};
#endif // QDISCORDINTERPRETER_H
