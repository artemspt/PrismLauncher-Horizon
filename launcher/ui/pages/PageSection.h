// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include <QWidget>
#include "ui/pages/BasePage.h"

/// A heading that groups the pages under it in a page list.
class PageSection : public QWidget, public BasePage {
   public:
    PageSection(QString id, QString name, QWidget* parent = nullptr) : QWidget(parent), m_id(std::move(id)), m_name(std::move(name)) {}

    QString id() const override { return m_id; }
    QString displayName() const override { return m_name; }
    QIcon icon() const override { return {}; }
    bool isSection() const override { return true; }

   private:
    QString m_id;
    QString m_name;
};
