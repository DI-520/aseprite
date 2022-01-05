// Aseprite
// Copyright (C) 2021  Igara Studio S.A.
//
// This program is distributed under the terms of
// the End-User License Agreement for Aseprite.

#ifndef APP_UI_ASEPRITE_UPDATE_H_INCLUDED
#define APP_UI_ASEPRITE_UPDATE_H_INCLUDED
#pragma once

#include "drm/download_thread.h"
#include "drm/installation_thread.h"
#include "aseprite_update.xml.h"
#include "ui/timer.h"

namespace app {

class AsepriteUpdate : public app::gen::AsepriteUpdate {
public:
  AsepriteUpdate(std::string version);

protected:

  void onBeforeClose(ui::CloseEvent& ev) override;
  void onDataReceived(long total, long now);
  void onDownloadFailed(drm::LicenseManager::DownloadException& e);
  void onDownloadFinished(drm::Package& package);
  void onInstallationPhaseChanged(drm::InstallationPhase oldPhase, drm::InstallationPhase phase);
  void onInstallationFailed(drm::LicenseManager::InstallationException& e);
  void onTimerTick();

private:
  drm::DownloadThread m_download;
  std::unique_ptr<drm::InstallationThread> m_installation;
  ui::Timer m_timer;
  bool m_closing = false;

  void log(std::string text);
};

}

#endif
