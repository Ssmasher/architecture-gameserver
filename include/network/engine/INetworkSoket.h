#pragma once

namespace network {

template <typename ContextType>
class INetworkSoket {
 public:
  INetworkSoket() = default;
  virtual ~INetworkSoket() = default;
  virtual bool create(ContextType& ioContext) = 0;
};

}  // namespace network