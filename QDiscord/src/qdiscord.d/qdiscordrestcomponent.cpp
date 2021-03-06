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

#include "qdiscordrestcomponent.hpp"
#include <QBuffer>

QDiscordRestComponent::QDiscordRestComponent(QObject * parent) : QObject(parent)
{
    _authentication = "";
    _self = QSharedPointer<QDiscordUser>();
    _loggedIn = false;
//#ifdef QDISCORD_LIBRARY_DEBUG
//    qDebug() << this << "constructed";
//#endif
}

QDiscordRestComponent::~QDiscordRestComponent()
{
//#ifdef QDISCORD_LIBRARY_DEBUG
//    qDebug() << this << "destroyed";
//#endif
}

void QDiscordRestComponent::login(const QString & email, const QString & password)
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << this << "acquiring token via email and password";
#endif
    qWarning() << "Logging in via email and password is deprecated";
    qWarning() << "Please use a token instead";
    qWarning() << "See the following link for more information:";
    qWarning() << "https://github.com/hammerandchisel/discord-api-docs/issues/69";

    if (!_authentication.isEmpty())
    {
#ifdef QDISCORD_LIBRARY_DEBUG
        qDebug() << this << "attempted to acquire a token while one is already stored";
#endif
        return;
    }

    QJsonObject object;
    object["email"] = email;
    object["password"] = password;
    post(object, QDiscordUtilities::endPoints.login,
         [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
        {
            _authentication = "";
            _loggedIn = false;
            emit loginFailed(reply->error());
        }
        else
        {
            _authentication =
                QJsonDocument::fromJson(
                    reply->readAll()
                ).object().value("token").toString();
            _loggedIn = true;
            emit tokenVerified(_authentication, QDiscordTokenType::None);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::login(const QString & token,
                                  QDiscordTokenType tokenType)
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << this << "verifying token";
#endif

    if (!_authentication.isEmpty())
    {
#ifdef QDISCORD_LIBRARY_DEBUG
        qDebug() << this << "attempted to verify a token while one is already stored";
#endif
        return;
    }

    _authentication = QDiscordUtilities::convertTokenToType(token, tokenType);
    get(QDiscordUtilities::endPoints.me,
        [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
        {
            qDebug() << "ERROR::" << reply->errorString();
            _authentication = "";
            _loggedIn = false;
            emit loginFailed(reply->error());
        }
        else
        {
            _loggedIn = true;
            emit tokenVerified(token, tokenType);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::sendMessage(const QString & content,
                                        QSharedPointer<QDiscordChannel> channel,
                                        bool tts)
{
    if (!_loggedIn)
        return;

    if (!channel)
        return;

    QString id = channel->id();
    QJsonObject object;
    object["content"] = content;

    if (tts)
        object["tts"] = true;

    post(object,
         QUrl(QString(
                  QDiscordUtilities::endPoints.channels + "/" +
                  id + "/messages"
              )),
         [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit messageSendFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordMessage message(object, channel);
            emit messageSent(message);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::sendMessage(const QString & content,
                                        const QString & channelId,
                                        bool tts)
{
    if (!_loggedIn)
        return;

    QJsonObject object;
    object["content"] = content;

    if (tts)
        object["tts"] = true;

    post(object,
         QUrl(QString(
                  QDiscordUtilities::endPoints.channels + "/" +
                  channelId + "/messages"
              )),
         [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit messageSendFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordMessage message(object, QSharedPointer<QDiscordChannel>());
            emit messageSent(message);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::sendEmbedAndMessage(const QString & message, const QJsonObject & embeds, const QString & channelId)
{
    if (!_loggedIn)
        return;

    QJsonObject object;
    object["content"] = message;
    object["embed"] = embeds;
    post(object,
         QUrl(QString(
                  QDiscordUtilities::endPoints.channels + "/" +
                  channelId + "/messages"
              )),
         [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit messageSendFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordMessage message(object, QSharedPointer<QDiscordChannel>());
            emit messageSent(message);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::sendEmbed(const QJsonObject & embeds, const QString & channelId)
{
    if (!_loggedIn)
        return;

    QJsonObject object;
    object["embed"] = embeds;
    post(object,
         QUrl(QString(
                  QDiscordUtilities::endPoints.channels + "/" +
                  channelId + "/messages"
              )),
         [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit messageSendFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordMessage message(object, QSharedPointer<QDiscordChannel>());
            emit messageSent(message);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::deleteMessage(QDiscordMessage message)
{
    deleteMessage(message.channelId(), message.id());
}

void QDiscordRestComponent::deleteMessage(const QString & channelId,
        const QString & messageId)
{
    if (!_loggedIn)
        return;

    deleteResource(QUrl(QString(
                            QDiscordUtilities::endPoints.channels + "/" +
                            channelId + "/messages/" + messageId
                        )),
                   [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit messageDeleteFailed(reply->error());
        else
            emit messageDeleted(messageId);

        reply->deleteLater();
    });
}

void QDiscordRestComponent::editMessage(const QString & newContent, QDiscordMessage message)
{
    editMessage(newContent, message.channelId(), message.id());
}

void QDiscordRestComponent::editMessage(const QString & newContent,
                                        const QString & channelId,
                                        const QString & messageId)
{
    if (!_loggedIn)
        return;

    QJsonObject object;
    object["content"] = newContent;
    patch(object,
          QUrl(
              QDiscordUtilities::endPoints.channels +
              "/" + channelId + "/messages/" + messageId
          ),
          [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            qDebug() << this << "messageEditFiles: " << reply->error();
//      emit messageEditFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordMessage newMessage(object,
                                       QSharedPointer<QDiscordChannel>());
            qDebug() << this << "MessageEditSucesf: " << object;
            emit messageEdited(newMessage);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::logout()
{
    if (_authentication.isEmpty())
        return;

    if (!_loggedIn)
        return;

    _self.reset();
    QJsonObject object;
    object["token"] = _authentication;
    _authentication = "";
    _loggedIn = false;
    post(object, QDiscordUtilities::endPoints.logout,
         [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        emit loggedOut();
        reply->deleteLater();
    });
}

void QDiscordRestComponent::getEndpoint()
{
    if (!_loggedIn)
        return;

    get(QDiscordUtilities::endPoints.gateway,
        [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit endpointAcquireFailed(reply->error());
        else
        {
            emit endpointAcquired(
                QJsonDocument::fromJson(
                    reply->readAll()
                ).object().value("url").toString()
            );
        }

        reply->deleteLater();
    });
}

void
QDiscordRestComponent::setChannelName(const QString & name,
                                      QSharedPointer<QDiscordChannel> channel)
{
    if (!_loggedIn)
        return;

    if (!channel)
        return;

    QJsonObject object;
    object["name"] = name;
    patch(object, QUrl(QString(
                           QDiscordUtilities::endPoints.channels + "/" + channel->id()
                       )),
          [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit channelUpdateFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordChannel updatedChannel(object);
            emit channelUpdated(updatedChannel);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::setChannelName(const QString & name,
        const QString & channelId)
{
    if (!_loggedIn)
        return;

    QJsonObject object;
    object["name"] = name;
    patch(object, QUrl(QString(
                           QDiscordUtilities::endPoints.channels + "/" + channelId
                       )),
          [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit channelUpdateFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordChannel updatedChannel(object);
            emit channelUpdated(updatedChannel);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::setChannelPosition(
    int position,
    QSharedPointer<QDiscordChannel> channel
)
{
    if (!_loggedIn)
        return;

    if (!channel)
        return;

    QJsonObject object;
    object["position"] = position;
    patch(object, QUrl(QString(
                           QDiscordUtilities::endPoints.channels + "/" + channel->id()
                       )),
          [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit channelUpdateFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordChannel updatedChannel(object);
            emit channelUpdated(updatedChannel);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::setChannelPosition(int position,
        const QString & channelId)
{
    if (!_loggedIn)
        return;

    QJsonObject object;
    object["position"] = position;
    patch(object, QUrl(QString(
                           QDiscordUtilities::endPoints.channels + "/" + channelId
                       )),
          [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit channelUpdateFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordChannel updatedChannel(object);
            emit channelUpdated(updatedChannel);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::setChannelTopic(
    const QString & topic,
    QSharedPointer<QDiscordChannel> channel
)
{
    if (!_loggedIn)
        return;

    if (!channel)
        return;

    if (channel->type() != QDiscordChannel::ChannelType::Text)
        return;

    QJsonObject object;
    object["topic"] = topic;
    patch(object, QUrl(QString(
                           QDiscordUtilities::endPoints.channels + "/" + channel->id()
                       )),
          [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit channelUpdateFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordChannel updatedChannel(object);
            emit channelUpdated(updatedChannel);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::setChannelTopic(const QString & topic,
        const QString & channelId)
{
    if (!_loggedIn)
        return;

    QJsonObject object;
    object["topic"] = topic;
    patch(object, QUrl(QString(
                           QDiscordUtilities::endPoints.channels + "/" + channelId
                       )),
          [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit channelUpdateFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordChannel updatedChannel(object);
            emit channelUpdated(updatedChannel);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::setChannelBitrate(
    int bitrate,
    QSharedPointer<QDiscordChannel> channel
)
{
    if (!_loggedIn)
        return;

    if (!channel)
        return;

    if (channel->type() != QDiscordChannel::ChannelType::Voice)
        return;

    QJsonObject object;
    object["bitrate"] = bitrate;
    patch(object, QUrl(QString(
                           QDiscordUtilities::endPoints.channels + "/" + channel->id()
                       )),
          [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit channelUpdateFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordChannel updatedChannel(object);
            emit channelUpdated(updatedChannel);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::setChannelBitrate(int bitrate,
        const QString & channelId)
{
    if (!_loggedIn)
        return;

    QJsonObject object;
    object["bitrate"] = bitrate;
    patch(object, QUrl(QString(
                           QDiscordUtilities::endPoints.channels + "/" + channelId
                       )),
          [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit channelUpdateFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordChannel updatedChannel(object);
            emit channelUpdated(updatedChannel);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::setChannelUserLimit(
    int limit,
    QSharedPointer<QDiscordChannel> channel
)
{
    if (!_loggedIn)
        return;

    if (!channel)
        return;

    if (channel->type() != QDiscordChannel::ChannelType::Voice)
        return;

    QJsonObject object;
    object["user_limit"] = limit;
    patch(object, QUrl(QString(
                           QDiscordUtilities::endPoints.channels + "/" + channel->id()
                       )),
          [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit channelUpdateFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordChannel updatedChannel(object);
            emit channelUpdated(updatedChannel);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::setChannelUserLimit(int limit,
        const QString & channelId)
{
    if (!_loggedIn)
        return;

    QJsonObject object;
    object["user_limit"] = limit;
    patch(object, QUrl(QString(
                           QDiscordUtilities::endPoints.channels + "/" + channelId
                       )),
          [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit channelUpdateFailed(reply->error());
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = document.object();
            QDiscordChannel updatedChannel(object);
            emit channelUpdated(updatedChannel);
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::setSelf(QSharedPointer<QDiscordUser> self)
{
    _self = self;
}

void QDiscordRestComponent::getGuildMember(const QString & guildID, const QString & memberID)
{
    if (!_loggedIn)
        return;

    qDebug() << this << QDiscordUtilities::endPoints.servers + QString("/" + guildID + "/members/" + memberID);
    get(QDiscordUtilities::endPoints.servers + QString("/" + guildID + "/members/" + memberID),
        [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            emit getGuildMemberFailed(reply->error());
        else
        {
            emit getGuildMemberAcquired(
                //QJsonDocument::fromJson(
                reply->readAll()
//        ).object().value("url").toString()
            );
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::getGuild(const QString & guildID)
{
    if (!_loggedIn)
        return;

    get(QDiscordUtilities::endPoints.gateway + QString("/guilds/" + guildID),
        [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());
        qDebug() << this << "Received Reply for Get Guild";

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
        {
            qDebug() << "ERROR RAILE";
        }
        else
        {
            emit getGuildAcquired(
                //QJsonDocument::fromJson(
                reply->readAll()
//        ).object().value("url").toString()
            );
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::getGuildEmojis(const QString &guildID)
{
    if (!_loggedIn)
        return;

    get(QDiscordUtilities::endPoints.apiBase + QString("/guilds/" + guildID + "/emojis"),
        [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());
        qDebug() << this << "Received Reply for getGuildEmojis";

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
        {
            qDebug() << "ERROR RAILE";
        }
        else
        {
            emit guildEmojis(reply->readAll() );
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::triggerTypingIndicator(QString channel_id)
{
    if (!_loggedIn)
        return;

    QJsonObject object;
    object["content"] = "typing";
    post(object, QDiscordUtilities::endPoints.apiBase + QString("/channels/" + channel_id + "/typing"),
         [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        qDebug() << "typing respnose: " << reply->readAll();

        reply->deleteLater();
    });
}
void QDiscordRestComponent::patchGuildMember(const QString & guildID, const QString & memberID, const QJsonObject & object)
{
    if (!_loggedIn)
        return;

    patch(object, QUrl(QString(
                           QDiscordUtilities::endPoints.servers + QString("/" + guildID + "/members/" + memberID)
                       )),
          [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            qDebug() << this << "patchGuildMemberRoles Failed: " << reply->error();
        else
        {
            qDebug() << this << "patchGuildMemberRoles Succeeded";
            emit patchGuildMemberSuccess();
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::patchGuildMember(const QString & guildID, const QString & memberID, const QJsonArray & array)
{
    if (!_loggedIn)
        return;

    qDebug() << this << array;
    patch(array, QUrl(QString(
                          QDiscordUtilities::endPoints.gateway + QString("/guilds/" + guildID + "/members/" + memberID)
                      )),
          [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            qDebug() << this << "patchGuildMemberRoles Failed: " << reply->error();
//            emit channelUpdateFailed(reply->error());
        else
        {
//            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
//            QJsonObject object = document.object();
//            QDiscordChannel updatedChannel(object);
//            emit channelUpdated(updatedChannel);
            qDebug() << this << "patchGuildMemberRoles Succeeded";
            emit patchGuildMemberSuccess();
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::getPinnedMessages(const QString channel_id)
{
    if (!_loggedIn)
        return;

    get(QDiscordUtilities::endPoints.apiBase + QString("/channels/" + channel_id + "/pins"),
        [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());
#ifdef QDISCORD_LIBRARY_DEBUG
        qDebug() << this << "Recieved pinned Messages" << url;
#endif

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            qDebug() << this << "Error on recieve pinned messages";
        else
        {
            emit pinnedMessages(QJsonDocument::fromJson(reply->readAll()).array());
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::addPinnedMessage(const QDiscordMessage message)
{
    if (!_loggedIn)
        return;

    put(QJsonArray(), QUrl(QString(
                               QDiscordUtilities::endPoints.apiBase + QString("/channels/" + message.channelId()+ "/pins/" + message.id())
                           )),
        [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;

        qDebug() << "add pinned:" << reply->readAll();

        reply->deleteLater();
    });
}

void QDiscordRestComponent::createReaction(const QDiscordMessage message, const QUrl emoji)
{
    if (!_loggedIn)
        return;

    put(QJsonArray(), QUrl(QString(
                               QDiscordUtilities::endPoints.apiBase + QString("/channels/" + message.channelId()+ "/messages/" + message.id() +"/reactions/"+ emoji.toEncoded() + "/@me")
                           )),
        [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;
        reply->deleteLater();
    });
}

void QDiscordRestComponent::deleteReaction(const QDiscordMessage message, const QUrl emoji)
{
    if (!_loggedIn)
        return;

    deleteResource(QUrl(QString(
                            QDiscordUtilities::endPoints.apiBase + QString("/channels/" + message.channelId()+ "/messages/" + message.id() +"/reactions/"+ emoji.toEncoded() + "/@me")
                        )),
                   [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;
        reply->deleteLater();
    });
}

void QDiscordRestComponent::deleteUserReaction(const QDiscordMessage message, const QString userId, const QUrl emoji)
{
    if (!_loggedIn)
        return;

    deleteResource(QUrl(QString(
                            QDiscordUtilities::endPoints.apiBase + QString("/channels/" + message.channelId()+ "/messages/" + message.id() +"/reactions/"+ emoji.toEncoded() + "/" + userId)
                        )),
                   [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;
        reply->deleteLater();
    });
}

void QDiscordRestComponent::getReactions(const QDiscordMessage message, const QUrl emoji)
{
    if (!_loggedIn)
        return;

    get(QDiscordUtilities::endPoints.apiBase + QString("/channels/" + message.channelId() + "/messages/"+message.id()+"/reactions/"+emoji.toEncoded()),
        [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());
#ifdef QDISCORD_LIBRARY_DEBUG
        qDebug() << this << "Recieved pinned Messages" << url;
#endif

        if (!reply)
            return;

        if (reply->error() != QNetworkReply::NoError)
            qDebug() << this << "Error on recieve reaction messages";
        else
        {
            emit reactions(message, QJsonDocument::fromJson(reply->readAll()).array());
        }

        reply->deleteLater();
    });
}

void QDiscordRestComponent::deleteAllReactions(const QDiscordMessage message)
{
    if (!_loggedIn)
        return;
    qDebug() << "Deleter:" <<QString(QDiscordUtilities::endPoints.apiBase + QString("/channels/" + message.channelId()+ "/messages/" + message.id() +"/reactions"));
    deleteResource(QUrl(QString(
                            QDiscordUtilities::endPoints.apiBase + QString("/channels/" + message.channelId()+ "/messages/" + message.id() +"/reactions")
                        )),
                   [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;
        reply->deleteLater();
    });
}

void QDiscordRestComponent::deleteAllReactionsForEmoji(const QDiscordMessage message, const QUrl emoji)
{
    if (!_loggedIn)
        return;

    deleteResource(QUrl(QString(
                            QDiscordUtilities::endPoints.apiBase + QString("/channels/" + message.channelId()+ "/messages/" + message.id() +"/reactions/"+ emoji.toEncoded() )
                        )),
                   [ = ]()
    {
        QNetworkReply * reply = static_cast<QNetworkReply *>(sender());

        if (!reply)
            return;
        reply->deleteLater();
    });
}
template<class Functor>
void QDiscordRestComponent::deleteResource(const QUrl & url,
        Functor function)
{
    QNetworkRequest request(url);

    if (_authentication != "")
        request.setRawHeader("Authorization", _authentication.toUtf8());

    request.setRawHeader("User-Agent", QDiscordUtilities::userAgent().toUtf8());
    connect(_manager.deleteResource(request), &QNetworkReply::finished,
            this, function);
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << this << "DELETE to" << url;
#endif
}

template<class Functor>
void QDiscordRestComponent::patch(const QJsonObject & object, const QUrl & url, Functor function)
{
    QJsonDocument document;
    document.setObject(object);
    QNetworkRequest request(url);

    if (_authentication != "")
        request.setRawHeader("Authorization", _authentication.toUtf8());

    request.setRawHeader("User-Agent", QDiscordUtilities::userAgent().toUtf8());
    request.setRawHeader("content-type", "application/json");
    QBuffer * buffer = new QBuffer();
    buffer->open(QBuffer::ReadWrite);
    buffer->write(document.toJson(QJsonDocument::Compact));
    buffer->seek(0);
    QNetworkReply * reply =
        _manager.sendCustomRequest(request, "PATCH", buffer);
    connect(reply, &QNetworkReply::finished, buffer, &QBuffer::deleteLater);
    connect(reply, &QNetworkReply::finished, this, function);
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << this << "patch:" << object << "to" << url;
#endif
}

template<class Functor>
void QDiscordRestComponent::patch(const QJsonArray & array, const QUrl & url, Functor function)
{
    QJsonDocument document;
    document.setArray(array);
    QNetworkRequest request(url);

    if (_authentication != "")
        request.setRawHeader("Authorization", _authentication.toUtf8());

    request.setRawHeader("User-Agent", QDiscordUtilities::userAgent().toUtf8());
    request.setRawHeader("content-type", "application/json");
    QBuffer * buffer = new QBuffer();
    buffer->open(QBuffer::ReadWrite);
    buffer->write(document.toJson(QJsonDocument::Compact));
    buffer->seek(0);
    QNetworkReply * reply =
        _manager.sendCustomRequest(request, "PATCH", buffer);
    connect(reply, &QNetworkReply::finished, buffer, &QBuffer::deleteLater);
    connect(reply, &QNetworkReply::finished, this, function);
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << this << "patch:" << array << "to" << url;
#endif
}

template<class Functor>
void QDiscordRestComponent::post(const QJsonObject & object,
                                 const QUrl & url,
                                 Functor function)
{
    QJsonDocument document;
    document.setObject(object);
    QNetworkRequest request(url);

    if (_authentication != "")
        request.setRawHeader("Authorization", _authentication.toUtf8());

    request.setRawHeader("User-Agent", QDiscordUtilities::userAgent().toUtf8());
    request.setRawHeader("content-type", "application/json");
    QNetworkReply * reply =
        _manager.post(request, document.toJson(QJsonDocument::Compact));
    connect(reply, &QNetworkReply::finished, this, function);
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << this << "posted:" << object << "to" << url;
#endif
}

template<class Functor>
void QDiscordRestComponent::post(const QJsonArray & array,
                                 const QUrl & url,
                                 Functor function)
{
    QJsonDocument document;
    document.setArray(array);
    QNetworkRequest request(url);

    if (_authentication != "")
        request.setRawHeader("Authorization", _authentication.toUtf8());

    request.setRawHeader("User-Agent", QDiscordUtilities::userAgent().toUtf8());
    request.setRawHeader("content-type", "application/json");
    QNetworkReply * reply =
        _manager.post(request, document.toJson(QJsonDocument::Compact));
    connect(reply, &QNetworkReply::finished, this, function);
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << this << "posted:" << array << "to" << url;
#endif
}

template<class Functor>
void QDiscordRestComponent::get(const QUrl & url,
                                Functor function)
{
    QNetworkRequest request(url);

    if (_authentication != "")
        request.setRawHeader("Authorization", _authentication.toUtf8());

    request.setRawHeader("User-Agent", QDiscordUtilities::userAgent().toUtf8());
    QNetworkReply * reply = _manager.get(request);
    qDebug() << this << "Sent Get Request: " << request.url();
    connect(reply, &QNetworkReply::finished, this, function);
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << this << "GET to" << url;
#endif
}
template<class Functor>
void QDiscordRestComponent::put(const QJsonArray & array,
                                const QUrl & url,
                                Functor function)
{
    QJsonDocument document;
    document.setArray(array);
    QNetworkRequest request(url);

    if (_authentication != "")
        request.setRawHeader("Authorization", _authentication.toUtf8());

    request.setRawHeader("User-Agent", QDiscordUtilities::userAgent().toUtf8());
    request.setRawHeader("content-type", "application/json");
    QNetworkReply * reply =
        _manager.put(request, document.toJson(QJsonDocument::Compact));
    connect(reply, &QNetworkReply::finished, this, function);
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << this << "posted:" << array << "to" << url;
#endif
}
