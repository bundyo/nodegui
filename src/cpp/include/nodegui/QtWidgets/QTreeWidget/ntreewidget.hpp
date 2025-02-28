#pragma once

#include <QTreeWidget>

#include "core/NodeWidget/nodewidget.h"
#include "napi.h"

class NTreeWidget : public QTreeWidget, public NodeWidget {
  Q_OBJECT
  NODEWIDGET_IMPLEMENTATIONS(QTreeWidget)

 public:
  using QTreeWidget::QTreeWidget;  // inherit all constructors of QTreeWidget

  void connectWidgetSignalsToEventEmitter() {
    QObject::connect(this, &QTreeWidget::itemSelectionChanged, [=]() {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "itemSelectionChanged")});
    });
  }
};
