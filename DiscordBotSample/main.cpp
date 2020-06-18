#include <QCoreApplication>
#include "discordbot.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DiscordBot * Bot = new DiscordBot();

    const QString botToken = "MzU3NzQ4NTcwNDQ0NzkxODEw.XcXoYA.Em8h1LAaTHbqHmYd2FccC1OGleY";

    Bot->login(botToken);

    return a.exec();
}
