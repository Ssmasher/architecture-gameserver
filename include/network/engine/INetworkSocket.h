#pragma once

namespace network {

template <typename ContextType>
class INetworkSocket {
 public:
  INetworkSocket() = default;
  virtual ~INetworkSocket() = default;
  virtual bool create(ContextType& ioContext) = 0;
};

}  // namespace network