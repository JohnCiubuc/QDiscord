#include "qdiscordinterpreter.h"

QDiscordInterpreter::QDiscordInterpreter(QDiscord & discord, QString prefix, QObject * parent)
    : QObject(parent), _discord(discord)
{
    connect(_discord.state(), &QDiscordStateComponent::messageCreated, this, &QDiscordInterpreter::messageReceived);
    connect(_discord.state(), &QDiscordStateComponent::guildCreated, this, &QDiscordInterpreter::guildCreated);

    connect(_discord.rest(), &QDiscordRestComponent::guildEmojis, this, &QDiscordInterpreter::guildEmojis);
    connect(_discord.rest(), &QDiscordRestComponent::pinnedMessages, this, &QDiscordInterpreter::pinnedMessages);
    connect(_discord.rest(), &QDiscordRestComponent::reactions, this, &QDiscordInterpreter::reactions);

    connect(_discord.ws(), &QDiscordWsComponent::attemptingReconnect, this, &QDiscordInterpreter::attemptingReconnect);
    connect(_discord.ws(), &QDiscordWsComponent::reconnectImpossible, this, &QDiscordInterpreter::reconnectImpossible);
    connect(_discord.ws(), &QDiscordWsComponent::disconnected, this, &QDiscordInterpreter::disconnected);
    connect(_discord.ws(), &QDiscordWsComponent::loginFailed, this, &QDiscordInterpreter::loginFailed);
    connect(_discord.ws(), &QDiscordWsComponent::loginSuccess, this, &QDiscordInterpreter::loginSuccess);
    connect(_discord.ws(), &QDiscordWsComponent::error, this, &QDiscordInterpreter::error);
}


void QDiscordInterpreter::attemptingReconnect()
{
    db "Attempting Reconnect";
}

void QDiscordInterpreter::reconnectImpossible()
{
    db "Unable to reconnect";
}

void QDiscordInterpreter::disconnected(QString reason, int reasonCode)
{
    db "Disconnected. Reason:" << reason <<", Error Code: "<<reasonCode;

    // General server dc
    if (reasonCode == 1000 || reasonCode == 1002)
        emit request_restart();
}

void QDiscordInterpreter::loginFailed()
{
    db "Login Failed!";
}

void QDiscordInterpreter::loginSuccess()
{
    db "Login Success!";
}

void QDiscordInterpreter::error(QAbstractSocket::SocketError error)
{
    db "Error: " << error;
}

void QDiscordInterpreter::guildEmojis(QByteArray emojiJson)
{
    QJsonDocument d = QJsonDocument::fromJson(emojiJson);
    QJsonArray sett2 = d.array();

    for(QJsonArray::iterator i = sett2.begin(); i != sett2.end(); ++i)
    {
        QJsonObject o = (*i).toObject();
        EmojiMaps.insert(o["name"].toString(), o["id"].toString());
    }
}

void QDiscordInterpreter::guildCreated(QSharedPointer<QDiscordGuild> guild)
{
    db "Guild Created - " << guild->name();
    _discord.rest()->getGuildEmojis(guild->id());
}

void QDiscordInterpreter::pinnedMessages(QJsonArray messages)
{
    foreach(QJsonValue val, messages)
    {
        qDebug() << "Pinned Message:" << val.toObject();
    }
}

void QDiscordInterpreter::reactions(QDiscordMessage message, QJsonArray usersWhoReacted)
{
    foreach(QJsonValue val, usersWhoReacted)
    {

        _discord.rest()->sendMessage(QJsonDocument(val.toObject()).toJson(), message.channelId());
        qDebug() << "Users who reacted:" << val.toObject();
    }
}

void QDiscordInterpreter::messageReceived(QDiscordMessage message)
{
    emit discordMessage(message);

    return;
}
