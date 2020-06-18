#include "discordbot.h"
#include "discordbot.h"

DiscordBot::DiscordBot(QObject* parent) : QObject(parent), _discord(), _interpreter(_discord)
{
    connect(&_discord, &QDiscord::loginSuccess, this, &DiscordBot::loginSuccess);
    connect(&_discord, &QDiscord::loginFailed, this, &DiscordBot::loginFailed);
    connect(&_interpreter, &QDiscordInterpreter::request_restart, this, &DiscordBot::reload);
    connect(&_interpreter, &QDiscordInterpreter::discordMessage, this, &DiscordBot::discordMessage);
}

void DiscordBot::login(QString botToken)
{
    db "Login with Token: " << token;
    token = botToken;
    _discord.login(token, QDiscordTokenType::Bot);
}

void DiscordBot::loginSuccess()
{
    db "Login successful.";
}

void DiscordBot::loginFailed()
{
    db "Login failed.";
}

void DiscordBot::reload()
{
    db "Reloading Bot";
    _discord.logout();
    _discord.login(token, QDiscordTokenType::Bot);
}

void DiscordBot::discordMessage(QDiscordMessage message)
{

    // Prevent bot responding to itself
    if (message.author()->id() == _discord.state()->self()->id())
        return;

    QString messageString;
    messageString.append("Message received. Author: ").append(message.author() ? message.author()->username() : "nullptr")
    .append(" ").append(message.author()->id()).append(" - ")
    .append(" Content: ").append(message.content())
    .append(" Channel: ").append(message.channel() ? message.channel()->name() : message.channelId())
    .append(" Channel ID: ").append(message.channel()->id());

    db messageString;

    if(message.content() == "beep")
        _discord.rest()->sendMessage("boop", message.channelId());
    else if(message.content() == "beep indicator")
    {
        _discord.rest()->triggerTypingIndicator(message.channelId());
        QTimer::singleShot(2000, this, [=]()
        {
            _discord.rest()->sendMessage("bot is typing... boop!", message.channelId());
        });
    }
    else if(message.content() == "get pins")
        _discord.rest()->getPinnedMessages(message.channelId());
    else if(message.content() == "pin this")
        _discord.rest()->addPinnedMessage(message);

}
