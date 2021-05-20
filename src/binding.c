#include <node_api.h>
#include <napi-macros.h>
#include <stdio.h>

#include <windows.h>

#include "pafish/cpu.h"
#include "pafish/vmware.h"
#include "pafish/vbox.h"
#include "pafish/qemu.h"
#include "pafish/wine.h"
#include "pafish/sandboxie.h"

#define NAPI_EXPORT_BOOL(name)                                                    \
  {                                                                               \
    napi_value name##_bool;                                                       \
    NAPI_STATUS_THROWS(napi_get_boolean(env, name, &name##_bool))                 \
    NAPI_STATUS_THROWS(napi_set_named_property(env, exports, #name, name##_bool)) \
  }

NAPI_METHOD(cpuRdtsc)
{
  NAPI_ARGV(3)

  bool force_vm_exit;
  napi_get_value_bool(env, argv[0], &force_vm_exit);

  NAPI_ARGV_INT32(n_samples, 1);
  NAPI_ARGV_INT32(interval, 2);

  // allocate array to receive the samples
  uint64_t *samples = malloc(n_samples * sizeof(uint64_t));
  if (samples == NULL)
  {
    napi_throw_error(env, NULL, "failed to allocate samples");
  }

  // run
  CpuRdtscResult result = cpu_rdtsc(force_vm_exit, n_samples, samples, interval);

  // build output
  napi_value exports;
  NAPI_STATUS_THROWS(napi_create_object(env, &exports));

  napi_value average, isVM;
  NAPI_STATUS_THROWS(napi_create_uint32(env, result.average, &average));
  NAPI_STATUS_THROWS(napi_get_boolean(env, result.is_vm, &isVM));
  NAPI_STATUS_THROWS(napi_set_named_property(env, exports, "average", average));
  NAPI_STATUS_THROWS(napi_set_named_property(env, exports, "isVM", isVM));

  napi_value samplesArray;
  NAPI_STATUS_THROWS(napi_create_array_with_length(env, n_samples, &samplesArray));
  for (int i = 0; i < n_samples; i++)
  {
    napi_value sample;
    NAPI_STATUS_THROWS(napi_create_uint32(env, samples[i], &sample));
    NAPI_STATUS_THROWS(napi_set_element(env, samplesArray, i, sample));
  }
  NAPI_STATUS_THROWS(napi_set_named_property(env, exports, "samples", samplesArray));

  free(samples);

  return exports;
}

NAPI_METHOD(cpuInfo)
{
  napi_value exports;
  NAPI_STATUS_THROWS_VOID(napi_create_object(env, &exports));

  // get vendor
  char vendor[13];
  cpu_write_vendor(vendor);
  NAPI_EXPORT_STRING(vendor);

  // hypervisor vendor
  char hypervisorVendor[13];
  cpu_write_hv_vendor(hypervisorVendor);
  if (strlen(hypervisorVendor) > 10)
  {
    NAPI_EXPORT_STRING(hypervisorVendor);
  }
  else
  {
    napi_value nullVal;
    NAPI_STATUS_THROWS_VOID(napi_get_null(env, &nullVal));
    NAPI_STATUS_THROWS_VOID(napi_set_named_property(env, exports, "hypervisorVendor", nullVal));
  }

  // hypervisor bit
  int hv_bit = cpu_hv();
  NAPI_EXPORT_BOOL(hv_bit);

  // cpu brand
  char brand[49];
  cpu_write_brand(brand);
  NAPI_EXPORT_STRING(brand);

  // known cpu vendor
  int knownVMVendor = cpu_known_vm_vendors();
  NAPI_EXPORT_BOOL(knownVMVendor);

  return exports;
}

NAPI_METHOD(vmware)
{
  int scsi = vmware_reg_key1();
  int registry = vmware_reg_key2();
  int mouseDriver = vmware_sysfile1();
  int graphicsDriver = vmware_sysfile2();
  int macAddress = vmware_mac();
  int adapterName = vmware_adapter_name();
  int devices = vmware_devices();
  int wmiSerial = vmware_wmi_serial();

  napi_value exports;
  NAPI_STATUS_THROWS(napi_create_object(env, &exports));

  NAPI_EXPORT_BOOL(scsi);
  NAPI_EXPORT_BOOL(registry);
  NAPI_EXPORT_BOOL(mouseDriver);
  NAPI_EXPORT_BOOL(graphicsDriver);
  NAPI_EXPORT_BOOL(macAddress);
  NAPI_EXPORT_BOOL(adapterName);
  NAPI_EXPORT_BOOL(devices);
  NAPI_EXPORT_BOOL(wmiSerial);

  return exports;
}

NAPI_METHOD(virtualBox)
{
  int scsi = vbox_reg_key1();
  int biosVersion = vbox_reg_key2();
  int guestAdditions = vbox_reg_key3();
  int videoBiosVersion = vbox_reg_key4();
  int acpi = vbox_reg_key5();
  int fadtAcpi = vbox_reg_key7();
  int rsdtAcpi = vbox_reg_key8();
  int service = vbox_reg_key9();
  int systemBiosDate = vbox_reg_key10();
  int deviceDrivers = vbox_sysfile1();
  int systemFiles = vbox_sysfile2();
  int nicMacAddress = vbox_mac();
  int devices = vbox_devices();
  int trayWindow = vbox_traywindow();
  int sharedNetwork = vbox_network_share();
  int processes = vbox_processes();
  int wmi = vbox_wmi_devices();

  napi_value exports;
  NAPI_STATUS_THROWS(napi_create_object(env, &exports));

  NAPI_EXPORT_BOOL(scsi);
  NAPI_EXPORT_BOOL(biosVersion);
  NAPI_EXPORT_BOOL(guestAdditions);
  NAPI_EXPORT_BOOL(videoBiosVersion);
  NAPI_EXPORT_BOOL(acpi);
  NAPI_EXPORT_BOOL(fadtAcpi);
  NAPI_EXPORT_BOOL(rsdtAcpi);
  NAPI_EXPORT_BOOL(service);
  NAPI_EXPORT_BOOL(systemBiosDate);
  NAPI_EXPORT_BOOL(deviceDrivers);
  NAPI_EXPORT_BOOL(systemFiles);
  NAPI_EXPORT_BOOL(nicMacAddress);
  NAPI_EXPORT_BOOL(deviceDrivers);
  NAPI_EXPORT_BOOL(trayWindow);
  NAPI_EXPORT_BOOL(sharedNetwork);
  NAPI_EXPORT_BOOL(processes);
  NAPI_EXPORT_BOOL(wmi);

  return exports;
}

NAPI_METHOD(qemu)
{
  int scsi = qemu_reg_key1();
  int systemBios = qemu_reg_key2();
  int cpuBrand = qemu_cpu_name();

  napi_value exports;
  NAPI_STATUS_THROWS(napi_create_object(env, &exports));

  NAPI_EXPORT_BOOL(scsi);
  NAPI_EXPORT_BOOL(systemBios);
  NAPI_EXPORT_BOOL(cpuBrand);

  return exports;
}

NAPI_METHOD(wine)
{
  int unixFileName = wine_detect_get_unix_file_name();
  int registry = wine_reg_key1();

  napi_value exports;
  NAPI_STATUS_THROWS(napi_create_object(env, &exports));

  NAPI_EXPORT_BOOL(unixFileName);
  NAPI_EXPORT_BOOL(registry);

  return exports;
}

NAPI_METHOD(sandboxie)
{
  int dll = sboxie_detect_sbiedll();

  napi_value exports;
  NAPI_STATUS_THROWS(napi_create_object(env, &exports));

  NAPI_EXPORT_BOOL(dll);

  return exports;
}

NAPI_INIT()
{
  #if _WIN32
  NAPI_EXPORT_FUNCTION(cpuRdtsc);
  NAPI_EXPORT_FUNCTION(cpuInfo);

  NAPI_EXPORT_FUNCTION(vmware);
  NAPI_EXPORT_FUNCTION(virtualBox);
  NAPI_EXPORT_FUNCTION(qemu);
  NAPI_EXPORT_FUNCTION(wine);
  NAPI_EXPORT_FUNCTION(sandboxie);
  #endif
}