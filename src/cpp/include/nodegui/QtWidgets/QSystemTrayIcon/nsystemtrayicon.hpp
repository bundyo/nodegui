#pragma once

#include <QSystemTrayIcon>

#include "core/NodeWidget/nodewidget.h"
#include "napi.h"

class NSystemTrayIcon : public QSystemTrayIcon, public EventWidget {
  Q_OBJECT
  EVENTWIDGET_IMPLEMENTATIONS(QSystemTrayIcon)
 public:
  // inherit all constructors of QSystemTrayIcon
  using QSystemTrayIcon::QSystemTrayIcon;
  void connectWidgetSignalsToEventEmitter() {
    QObject::connect(this, &QSystemTrayIcon::activated, [=](int reason) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
          Napi::String::New(env, "activated"),
          Napi::Value::From(env, reason),
      });
    });

    QObject::connect(this, &QSystemTrayIcon::messageClicked, [=]() {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
          Napi::String::New(env, "messageClicked"),
      });
    });
  }
};
