// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "ui/pages/BasePage.h"
#include "HorizonVersionList.h"
#include "minecraft/auth/MinecraftAccount.h"
#include "ui/widgets/VersionSelectWidget.h"

class QCheckBox;
class QRadioButton;
class NewInstanceDialog;

/// Minecraft rewritten in Rust: a Horizon release, plain or with the Horizon Hammer mod core.
class HorizonPage : public QWidget, public BasePage {
    Q_OBJECT
   public:
    explicit HorizonPage(NewInstanceDialog* dialog, QWidget* parent = nullptr);
    ~HorizonPage();

    QString id() const override { return "horizon"; }
    QString displayName() const override { return tr("Minecraft (Rust)"); }
    QIcon icon() const override { return QIcon::fromTheme("minecraft"); }
    bool shouldDisplay() const override { return true; }

    void openedImpl() override;

   private slots:
    void setSelectedVersion(BaseVersion::Ptr version);
    void setSelectedCore(BaseVersion::Ptr version);
    void filterChanged();
    void coreChanged();

   private:
    void suggestCurrent();

   private:
    NewInstanceDialog* m_dialog = nullptr;
    HorizonVersionList* m_vlist = nullptr;
    HorizonVersionList* m_coreList = nullptr;
    VersionSelectWidget* m_versionSelect = nullptr;
    VersionSelectWidget* m_coreSelect = nullptr;
    QCheckBox* m_releases = nullptr;
    QCheckBox* m_nightlies = nullptr;
    QRadioButton* m_noCore = nullptr;
    QRadioButton* m_hammer = nullptr;
    BaseVersion::Ptr m_selectedVersion;
    BaseVersion::Ptr m_selectedCore;
    bool m_initialized = false;
};
