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

    // Simple Response
    if(message.content() == "beep")
        _discord.rest()->sendMessage("boop", message.channelId());


    // Delayed response showing typing indicator
    else if(message.content() == "beep indicator")
    {
        _discord.rest()->triggerTypingIndicator(message.channelId());
        QTimer::singleShot(2000, this, [=]()
        {
            _discord.rest()->sendMessage("bot is typing... boop!", message.channelId());
        });
    }

    // Returns pinned messages
    else if(message.content() == "get pins")
        _discord.rest()->getPinnedMessages(message.channelId());

    // Pins user message
    else if(message.content() == "pin this")
        _discord.rest()->addPinnedMessage(message);

    // Reacts to user message with normal emoji
    else if(message.content() == "react this")
        _discord.rest()->createReaction(message, QUrl("💖"));
     // For custom emojis. You can escape an emoji (ex custom emoji :kek:, type \:kek: in message
    // Then remove the <: and > from the emoji. Now you can react with it.
    else if(message.content() == "custom react this")
    {
        testMessage = message;
        _discord.rest()->createReaction(message, QUrl("kek:722192865899577378"));
    }
     // Sending custom emojis in message requires the whole thing though
    else if(message.content() == "kek")
        _discord.rest()->sendMessage("<:kek:722192865899577378>", message.channelId());
     // Deletes all reacts for emoji for message
    else if (message.content() == "delete react")
    {
        _discord.rest()->deleteReaction(testMessage, QUrl("kek:722192865899577378"));
    }
      // Deletes user's emoji reaction
    else if (message.content() == "delete user react in 5s")
    {
        _discord.rest()->triggerTypingIndicator(message.channelId());
        QTimer::singleShot(5000, this, [=]()
        {
            _discord.rest()->deleteUserReaction(message, message.author()->id(), QUrl("kek:722192865899577378"));
        });
   }
     // Gets all users who reacted with emoji
    else if (message.content() == "get reactions")
    {
        _discord.rest()->triggerTypingIndicator(message.channelId());
        QTimer::singleShot(5000, this, [=]()
        {
            _discord.rest()->getReactions(message, QUrl("kek:722192865899577378"));
        });
    }
     // Deletes all reactions on message
    else if (message.content() == "delete all reactions")
    {
        _discord.rest()->triggerTypingIndicator(message.channelId());
        QTimer::singleShot(5000, this, [=]()
        {
            _discord.rest()->deleteAllReactions(message);
        });
    }
     // Deletes all reactions with emoji

   else if (message.content() == "delete all reactions to emoji")
    {
        _discord.rest()->triggerTypingIndicator(message.channelId());
        QTimer::singleShot(5000, this, [=]()
        {
            _discord.rest()->deleteAllReactionsForEmoji(message, QUrl("💖"));
        });
    }
}

