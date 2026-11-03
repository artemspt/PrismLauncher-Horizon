// SPDX-License-Identifier: GPL-3.0-only
#include "HorizonVersion.h"
#include <QCoreApplication>
#include <QVersionNumber>

HorizonVersion::HorizonVersion(const QString& tag,
                              const QString& publishedAt,
                              const QString& downloadUrl,
                              bool prerelease)
    : m_tag(tag)
    , m_publishedAt(publishedAt)
    , m_downloadUrl(downloadUrl)
    , m_prerelease(prerelease)
{}

QString HorizonVersion::name() const
{
    if (m_tag == HammerSourceTag)
        return QCoreApplication::translate("HorizonVersion", "Build from source (newest commit)");
    return m_tag;
}

bool HorizonVersion::operator<(BaseVersion& other) const
{
    auto* otherHorizon = dynamic_cast<HorizonVersion*>(&other);
    if (!otherHorizon) {
        return BaseVersion::operator<(other);
    }

    QString thisTag = m_tag;
    if (thisTag.startsWith('v') || thisTag.startsWith('V'))
        thisTag.remove(0, 1);

    QString otherTag = otherHorizon->m_tag;
    if (otherTag.startsWith('v') || otherTag.startsWith('V'))
        otherTag.remove(0, 1);

    QVersionNumber thisVersion = QVersionNumber::fromString(thisTag);
    QVersionNumber otherVersion = QVersionNumber::fromString(otherTag);
    if (thisVersion != otherVersion) {
        return thisVersion < otherVersion;
    }
    return m_publishedAt < otherHorizon->m_publishedAt;
}
