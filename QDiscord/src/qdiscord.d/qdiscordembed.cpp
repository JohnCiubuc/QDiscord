/*
 * QDiscord - An unofficial C++ and Qt wrapper for the Discord API.
 * Copyright (C) 2016-2017 inathero
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

#include "qdiscordembed.hpp"

QDiscordEmbed::QDiscordEmbed(const QJsonArray & array)
{
    QJsonObject object = array.first().toObject();
//  qDebug() << this << object;
    _title = object["title"].toString("");
    _type = object["type"].toString("");
    _description = object["description"].toString("");
    _url = object["url"].toString("");
    _color = object["color"].toInt(0);
    _footer = get_footer(object["footer"].toObject());
    _image = get_image(object["image"].toObject());
    _thumbnail = get_thumbnail(object["thumbnail"].toObject());
    _video = get_video(object["video"].toObject());
    _provider = get_provider(object["provider"].toObject());
    _author = get_author(object["author"].toObject());
    _fields = get_fields(object["fields"].toArray());
//    qDebug() << this << "Fields size: " << _fields.size();
    _hasEmbed = _fields.size() > 0;
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug()<<"QDiscordEmbed("<<this<<") constructed";
#endif
}

QDiscordEmbed::QDiscordEmbed()
{
}
QDiscordEmbed::QDiscordEmbed(const QDiscordEmbed & other)
{
//  _id = other.id();
//  _mentionEveryone = other.mentionEveryone();
//  _content = other.content();
//  _author = other.author();
//  _channel = other.channel();
//  _channelId = other.channelId();
//  _tts = other.tts();
//  _timestamp = other.timestamp();
//  QList<QSharedPointer<QDiscordUser>> otherMentions = other.mentions();
//  for (QSharedPointer<QDiscordUser> item : otherMentions)
//    _mentions.append(item);
//#ifdef QDISCORD_LIBRARY_DEBUG
//  qDebug()<<"QDiscordMessage("<<this<<") copy-constructed";
//#endif
}

QDiscordEmbed::~QDiscordEmbed()
{
}

DiscordEmbeds::footer QDiscordEmbed::get_footer(const QJsonObject object)
{
//  qDebug() << this << "Footer:" <<  object;
    DiscordEmbeds::footer embed;
    embed.text = object["text"].toString("");
    embed.icon_url = object["icon_url"].toString("");
    embed.proxy_icon_url = object["proxy_icon_url"].toString("");
    return embed;
}

DiscordEmbeds::image QDiscordEmbed::get_image(const QJsonObject object)
{
//  qDebug() << this << "Image:" <<  object;
    DiscordEmbeds::image embed;
    embed.url = object["url"].toString("");
    embed.proxy_url = object["proxy_url"].toString("");
    embed.height = object["height"].toInt();
    embed.width = object["width"].toInt();
    return embed;
}
DiscordEmbeds::thumbnail QDiscordEmbed::get_thumbnail(const QJsonObject object)
{
//  qDebug() << this << "Thumbnail:" <<  object;
    DiscordEmbeds::thumbnail embed;
    embed.url = object["url"].toString("");
    embed.proxy_url = object["proxy_url"].toString("");
    embed.height = object["height"].toInt();
    embed.width = object["width"].toInt();
    return embed;
}
DiscordEmbeds::video QDiscordEmbed::get_video(const QJsonObject object)
{
//  qDebug() << this << "Video:" <<  object;
    DiscordEmbeds::video embed;
    embed.url = object["url"].toString("");
    embed.height = object["height"].toInt();
    embed.width = object["width"].toInt();
    return embed;
}
DiscordEmbeds::provider QDiscordEmbed::get_provider(const QJsonObject object)
{
//  qDebug() << this << "Provider:" <<  object;
    DiscordEmbeds::provider embed;
    embed.url = object["url"].toString("");
    embed.name = object["name"].toString("");
    return embed;
}
DiscordEmbeds::author QDiscordEmbed::get_author(const QJsonObject object)
{
    qDebug() << this << "Author:" <<  object;
    DiscordEmbeds::author embed;
    embed.url = object["url"].toString("");
    embed.name = object["name"].toString("");
    embed.icon_url = object["icon_url"].toString("");
    embed.proxy_icon_url = object["proxy_icon_url"].toString("");
    return embed;
}

QList<DiscordEmbeds::field> QDiscordEmbed::get_fields(const QJsonArray array)
{
//  qDebug() << this << "Fields:" <<  array;
    QList<DiscordEmbeds::field> fn;

    for (QJsonValue item : array)
    {
        qDebug() << this << "Fields, Mini:" <<  item;
        QJsonObject o = item.toObject();
        DiscordEmbeds::field s;
        s.name = o["name"].toString("");
        s.value = o["value"].toString("");
        s.b_inline = bool(o["inline"].toInt());
        fn.append(s);
    }

    return fn;
}
