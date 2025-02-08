/*
 * Copyright 2006 Milan Digital Audio LLC
 * Copyright 2009-2025 GrandOrgue contributors (see AUTHORS)
 * License GPL-2.0 or later
 * (https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
 */

#include "GOMidiObjectWithShortcut.h"

GOMidiObjectWithShortcut::GOMidiObjectWithShortcut(
  GOOrganModel &organModel,
  const wxString &midiTypeCode,
  const wxString &midiTypeName,
  GOMidiSenderType senderType,
  GOMidiReceiverType receiverType,
  GOMidiShortcutReceiver::ReceiverType shortcutType)
  : GOMidiReceivingSendingObject(
    organModel, midiTypeCode, midiTypeName, senderType, receiverType),
    m_ShortcutReceiver(shortcutType) {
  SetMidiShortcutReceiver(&m_ShortcutReceiver);
}

GOMidiObjectWithShortcut::~GOMidiObjectWithShortcut() {
  SetMidiShortcutReceiver(nullptr);
}

void GOMidiObjectWithShortcut::LoadMidiObject(
  GOConfigReader &cfg, const wxString &group, GOMidiMap &midiMap) {
  GOMidiReceivingSendingObject::LoadMidiObject(cfg, group, midiMap);
  if (!IsReadOnly()) {
    m_ShortcutReceiver.Load(cfg, group);
  }
}

void GOMidiObjectWithShortcut::SaveMidiObject(
  GOConfigWriter &cfg, const wxString &group, GOMidiMap &midiMap) {
  GOMidiReceivingSendingObject::SaveMidiObject(cfg, group, midiMap);
  if (!IsReadOnly()) {
    m_ShortcutReceiver.Save(cfg, group);
  }
}

void GOMidiObjectWithShortcut::HandleKey(int key) {
  if (!IsReadOnly()) {
    auto matchType = m_ShortcutReceiver.Match(key);

    if (matchType != GOMidiShortcutReceiver::KEY_MATCH_NONE)
      OnShortcutKeyReceived(matchType, key);
  }
}
