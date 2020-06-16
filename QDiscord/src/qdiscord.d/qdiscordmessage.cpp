/*
 * QDiscord - An unofficial C++ and Qt wrapper for the Discord API.
 * Copyright (C) 2016-2017 george99g
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qdiscordmessage.hpp"

QDiscordMessage::QDiscordMessage(const QJsonObject & object,
                                 QSharedPointer<QDiscordChannel> channel)
{
    _id = object["id"].toString("");
    _mentionEveryone = object["mention_everyone"].toBool(false);
    _content = object["content"].toString("");
    _channel = channel;
    _channelId = object["channel_id"].toString("");
    _author = object.contains("author") ?
              QSharedPointer<QDiscordUser>(
                  new QDiscordUser(object["author"].toObject())
              ) : QSharedPointer<QDiscordUser>();
    _tts = object["tts"].toBool(false);
    _timestamp = QDateTime::fromString(object["timestamp"].toString(""),
                                       Qt::ISODate);
//    qDebug() << this << "Message Create:";
//    qDebug() << this << object;
//    qDebug() << this << object["embeds"].toObject();
    _embed = QSharedPointer<QDiscordEmbed>( new QDiscordEmbed(object["embeds"].toArray()));
    _attachment = QSharedPointer<QDiscordAttachment>( new QDiscordAttachment(object["attachments"].toArray()));
    for (QJsonValue item : object["mentions"].toArray())
    {
        if (guild())
        {
            QSharedPointer<QDiscordMember> member =
                guild()->member(item.toObject()["id"].toString(""));

            if (member && member->user())
            {
                _mentions.removeAll(member->user());
                _mentions.append(member->user());
            }
            else
            {
                _mentions.append(QSharedPointer<QDiscordUser>(
                                     new QDiscordUser(item.toObject())
                                 ));
            }
        }
        else
        {
            _mentions.append(QSharedPointer<QDiscordUser>(
                                 new QDiscordUser(item.toObject())
                             ));
        }
    }

//#ifdef QDISCORD_LIBRARY_DEBUG
//  qDebug()<<"QDiscordMessage("<<this<<") constructed";
//#endif
}

QDiscordMessage::QDiscordMessage()
{
    _id = "";
    _mentionEveryone = false;
    _content = "";
    _author = QSharedPointer<QDiscordUser>();
    _channel = QSharedPointer<QDiscordChannel>();
    _channelId = "";
    _tts = false;
    _timestamp = QDateTime();
//#ifdef QDISCORD_LIBRARY_DEBUG
//  qDebug()<<"QDiscordMessage("<<this<<") constructed";
//#endif
}

QDiscordMessage::QDiscordMessage(const QDiscordMessage & other)
{
    _id = other.id();
    _mentionEveryone = other.mentionEveryone();
    _content = other.content();
    _author = other.author();
    _channel = other.channel();
    _channelId = other.channelId();
    _tts = other.tts();
    _timestamp = other.timestamp();
    _embed = other.embed();
    _attachment = other.attachment();
    QList<QSharedPointer<QDiscordUser>> otherMentions = other.mentions();

    for (QSharedPointer<QDiscordUser> item : otherMentions)
        _mentions.append(item);

//#ifdef QDISCORD_LIBRARY_DEBUG
//  qDebug()<<"QDiscordMessage("<<this<<") copy-constructed";
//#endif
}

QDiscordMessage::~QDiscordMessage()
{
//#ifdef QDISCORD_LIBRARY_DEBUG
//  qDebug()<<"QDiscordMessage("<<this<<") destroyed";
//#endif
}

QSharedPointer<QDiscordGuild> QDiscordMessage::guild() const
{
    return _channel ? _channel->guild() : QSharedPointer<QDiscordGuild>();
}

void QDiscordMessage::set_channelID(QString id)
{
    _channelId = id;
}
