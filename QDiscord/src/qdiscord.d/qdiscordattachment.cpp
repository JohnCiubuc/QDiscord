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

#include "qdiscordattachment.hpp"

QDiscordAttachment::QDiscordAttachment(const QJsonArray & array)
{
    QJsonObject object = array.first().toObject();
//    qDebug () << "QDiscordAttachment:\n\n\n";
//    qDebug() << this << object;
    _id = object["id"].toString("");
    _filename = object["filename"].toString("");
    _size= object["size"].toInt(0);
    _url = object["url"].toString("");
    _proxy_url = object["proxy_url"].toString("");
    _height = object["height"].toInt(0);
    _width = object["width"].toInt(0);

//    qDebug() << _id;
//    qDebug() << _filename;
//    qDebug() << _size;
//    qDebug() << _url;
//    qDebug() << _proxy_url;
//    qDebug() << _height;

}

QDiscordAttachment::QDiscordAttachment()
{
}
QDiscordAttachment::QDiscordAttachment(const QDiscordAttachment & other)
{
    _id = other.id();
    _filename = other.filename();
    _size= other.size();
    _url = other.url();
    _proxy_url = other.proxy_url();
    _height = other.height();
    _width = other.width();
}

QDiscordAttachment::~QDiscordAttachment()
{
}
