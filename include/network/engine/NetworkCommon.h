#pragma once

namespace network {

using port_t = short;

enum class NetworkProtocol { TCP_V4, TCP_V6, UDP_V4, UDP_V6 };

}  // namespace network