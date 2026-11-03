// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "tasks/Task.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QProcess>
#include "minecraft/MinecraftInstance.h"

class HorizonInstallTask : public Task {
    Q_OBJECT
   public:
    explicit HorizonInstallTask(MinecraftInstance* instance);
    ~HorizonInstallTask() override = default;

    bool abort() override;

   protected:
    void executeTask() override;

   private slots:
    void downloadFinished();

   private:
    void installExtracted();
    void extractAndFinish();
    void buildFromSource();
    void runNextStep();
    void installBuilt();

   private:
    MinecraftInstance* m_instance = nullptr;
    QNetworkAccessManager* m_nam = nullptr;
    QNetworkReply* m_reply = nullptr;
    QString m_archivePath;
    QString m_targetDir;
    QString m_executablePath;
    // Building from source: where the core is checked out and built, the commands left, and the one running
    QString m_sourceDir;
    QList<QStringList> m_steps;
    QProcess* m_process = nullptr;
    QStringList m_output;
};
