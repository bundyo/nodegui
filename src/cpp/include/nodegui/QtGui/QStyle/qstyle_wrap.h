#pragma once

#include <napi.h>

#include <QStyle>

#include "core/Component/component_macro.h"

class QStyleWrap : public Napi::ObjectWrap<QStyleWrap> {
 private:
  QStyle* instance;

 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QStyleWrap(const Napi::CallbackInfo& info);
  QStyle* getInternalInstance();
  // Wrapped methods
  Napi::Value pixelMetric(const Napi::CallbackInfo& info);

  COMPONENT_WRAPPED_METHODS_DECLARATION
};
