#include <node_api.h>
#include <napi-macros.h>

NAPI_METHOD(getNumber)
{
    NAPI_RETURN_INT32(10)
}

NAPI_INIT() {
  NAPI_EXPORT_FUNCTION(getNumber)
}