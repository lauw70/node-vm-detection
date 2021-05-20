#include <node_api.h>
#include <napi-macros.h>

#include "pafish/cpu.h"

NAPI_METHOD(getNumber)
{
  NAPI_RETURN_INT32(10);
}

NAPI_METHOD(getHypervisorVendor)
{
  char hypervisor[13];
  cpu_write_hv_vendor(hypervisor);
  NAPI_RETURN_STRING(hypervisor);
}

NAPI_INIT()
{
  NAPI_EXPORT_FUNCTION(getNumber);
  NAPI_EXPORT_FUNCTION(getHypervisorVendor);
}