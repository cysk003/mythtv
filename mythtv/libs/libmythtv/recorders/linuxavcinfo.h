#ifndef LINUX_AVC_INFO_H
#define LINUX_AVC_INFO_H

#include "libmythbase/mythconfig.h"

#if CONFIG_FIREWIRE_LINUX

// Linux headers
#include <libraw1394/raw1394.h>
#include <libraw1394/csr.h>
#include <libiec61883/iec61883.h>
#include <libavc1394/avc1394.h>
#include <libavc1394/rom1394.h>

// C++ headers
#include <vector>

// Qt headers
#include <QMap>

// MythTV headers
#include "avcinfo.h"

class LinuxAVCInfo : public AVCInfo
{
  public:
    LinuxAVCInfo() = default;

    bool Update(uint64_t _guid, raw1394handle_t handle,
                uint _port, uint _node);

    bool OpenPort(void);
    bool ClosePort(void);

    bool SendAVCCommand(
        const std::vector<uint8_t> &cmd,
        std::vector<uint8_t>       &result,
        int                    retry_cnt)  override; // AVCInfo

    bool IsPortOpen(void) const { return m_fwHandle; }

    /// Returns remote node
    int GetNode(void) const { return m_node; }

  public:
    raw1394handle_t m_fwHandle {nullptr};
};
using avcinfo_list_t = QMap<uint64_t,LinuxAVCInfo*>;

#endif // CONFIG_FIREWIRE_LINUX

#endif // LINUX_AVC_INFO_H
