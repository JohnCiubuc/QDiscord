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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QDISCORDATTACHMENT_HPP
#define QDISCORDATTACHMENT_HPP

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>


class QDiscordAttachment
{
public:
    /*!
     * \brief Creates an instance from the provided parameters.
     * \param object A JSON object of a Discord attachment.
     */
    QDiscordAttachment(
        const QJsonArray & array);
    QDiscordAttachment();
    QDiscordAttachment(const QDiscordAttachment & other);
    ~QDiscordAttachment();

    QString id() const
    {
        return _id;
    }
    QString filename() const
    {
        return _filename;
    }
    int size() const
    {
        return _size;
    }
    QString url() const
    {
        return _url;
    }
    QString proxy_url() const
    {
        return _proxy_url;
    }
    int height() const
    {
        return _height;
    }
    int width() const
    {
        return _width;
    }
private:
    // functions
    // variables
    QString _id;
    QString _filename;
    int _size;
    QString _url;
    QString _proxy_url;
    int _height;
    int _width;
};

Q_DECLARE_METATYPE(QDiscordAttachment)

#endif // QDiscordAttachment_HPP
