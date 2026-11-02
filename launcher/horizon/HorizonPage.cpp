// SPDX-License-Identifier: GPL-3.0-only
#include "HorizonPage.h"

#include "Application.h"
#include "Filter.h"
#include "HorizonCreationTask.h"
#include "ui/dialogs/NewInstanceDialog.h"

#include <QCheckBox>
#include <QCoreApplication>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
#include <QRegularExpression>
#include <QVBoxLayout>

// Builds of the game with the Horizon Hammer mod core, released by the core's repository
static const QString HammerRepo = "artemspt/horizon-hammer-core";
static const QString HammerTagPrefix = "hammer-";

// Strings the Minecraft page has: its translations serve this page too
static QString minecraftPageText(const char* text)
{
    return QCoreApplication::translate("CustomPage", text);
}

HorizonPage::HorizonPage(NewInstanceDialog* dialog, QWidget* parent) : QWidget(parent), m_dialog(dialog)
{
    // Laid out as the Minecraft page: versions on top, the mod core under them
    auto layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_versionSelect = new VersionSelectWidget(this);
    layout->addWidget(m_versionSelect, 0, 0);

    auto filters = new QVBoxLayout;
    auto filtersTitle = new QLabel(minecraftPageText("Filter"), this);
    filtersTitle->setAlignment(Qt::AlignHCenter);
    filters->addWidget(filtersTitle);
    m_releases = new QCheckBox(minecraftPageText("Releases"), this);
    m_releases->setChecked(true);
    m_nightlies = new QCheckBox(minecraftPageText("Snapshots"), this);
    filters->addWidget(m_releases);
    filters->addWidget(m_nightlies);
    filters->addStretch();
    layout->addLayout(filters, 0, 1);

    auto line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line, 1, 0, 1, 2);

    m_coreSelect = new VersionSelectWidget(this);
    layout->addWidget(m_coreSelect, 2, 0);

    auto cores = new QVBoxLayout;
    auto coresTitle = new QLabel(minecraftPageText("Mod Loader"), this);
    coresTitle->setAlignment(Qt::AlignHCenter);
    cores->addWidget(coresTitle);
    m_noCore = new QRadioButton(minecraftPageText("None"), this);
    m_noCore->setChecked(true);
    m_hammer = new QRadioButton("Horizon Hammer", this);
    cores->addWidget(m_noCore);
    cores->addWidget(m_hammer);
    cores->addStretch();
    layout->addLayout(cores, 2, 1);

    layout->setRowStretch(0, 1);
    layout->setRowStretch(2, 1);

    connect(m_versionSelect, &VersionSelectWidget::selectedVersionChanged, this, &HorizonPage::setSelectedVersion);
    connect(m_coreSelect, &VersionSelectWidget::selectedVersionChanged, this, &HorizonPage::setSelectedCore);
    connect(m_releases, &QCheckBox::toggled, this, &HorizonPage::filterChanged);
    connect(m_nightlies, &QCheckBox::toggled, this, &HorizonPage::filterChanged);
    connect(m_noCore, &QRadioButton::toggled, this, &HorizonPage::coreChanged);
}

HorizonPage::~HorizonPage() {}

void HorizonPage::openedImpl()
{
    if (m_initialized) {
        suggestCurrent();
        return;
    }
    m_vlist = new HorizonVersionList("horizon-rust/horizon", {}, this);
    m_versionSelect->initialize(m_vlist);
    m_coreList = new HorizonVersionList(HammerRepo, HammerTagPrefix, this);
    m_coreSelect->initialize(m_coreList);
    m_initialized = true;
    filterChanged();
    coreChanged();
}

void HorizonPage::filterChanged()
{
    QStringList types;
    if (m_releases->isChecked())
        types << "(release)";
    if (m_nightlies->isChecked())
        types << "(snapshot)";
    m_versionSelect->setFilter(BaseVersionList::TypeRole, Filters::regexp(QRegularExpression(types.join('|'))));
}

void HorizonPage::coreChanged()
{
    if (m_noCore->isChecked()) {
        m_coreSelect->setExactFilter(BaseVersionList::VersionIdRole, "");  // every build has a tag: nothing left
        m_coreSelect->setEmptyString(minecraftPageText("No mod loader is selected."));
    } else {
        m_coreSelect->setFuzzyFilter(BaseVersionList::VersionIdRole, "");
        m_coreSelect->setEmptyString(tr("No Horizon Hammer builds have been released yet."));
    }
    m_coreSelect->setEmptyMode(VersionListView::String);
    suggestCurrent();
}

void HorizonPage::setSelectedVersion(BaseVersion::Ptr version)
{
    m_selectedVersion = version;
    suggestCurrent();
}

void HorizonPage::setSelectedCore(BaseVersion::Ptr version)
{
    m_selectedCore = version;
    suggestCurrent();
}

void HorizonPage::suggestCurrent()
{
    // Lists finishing their load while another page is open must not change its suggestion
    if (!m_dialog || !isOpened)
        return;
    // A Hammer build is a whole game of its own: it replaces the Horizon version above
    auto version = m_hammer->isChecked() ? m_selectedCore : m_selectedVersion;
    if (!version) {
        m_dialog->setSuggestedPack();
        return;
    }
    auto name = m_hammer->isChecked() ? "Horizon Hammer " + version->descriptor() : version->descriptor();
    m_dialog->setSuggestedPack(name, new HorizonCreationTask(version));
    m_dialog->setSuggestedIcon("default");
}
