/*
   Copyright 2020 The Silkworm Authors

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef SILKWORM_ETH_INTRA_BLOCK_STATE_H_
#define SILKWORM_ETH_INTRA_BLOCK_STATE_H_

#include <evmc/evmc.hpp>
#include <intx/intx.hpp>
#include <string_view>

namespace silkworm::eth {

class IntraBlockState {
 public:
  IntraBlockState(const IntraBlockState&) = delete;
  IntraBlockState& operator=(const IntraBlockState&) = delete;

  IntraBlockState() = default;

  bool Exists(const evmc::address& address) const;
  void Create(const evmc::address& address, bool contract);

  intx::uint256 GetBalance(const evmc::address& address) const;
  void AddBalance(const evmc::address& address, const intx::uint256& addend);
  void SubBalance(const evmc::address& address, const intx::uint256& subtrahend);

  uint64_t GetNonce(const evmc::address& address) const;
  void SetNonce(const evmc::address& address, uint64_t nonce);

  std::string_view GetCode(const evmc::address& address) const;
  evmc::bytes32 GetCodeHash(const evmc::address& address) const;

  uint64_t GetRefund() const;
  void AddRefund(uint64_t addend);
  void SubRefund(uint64_t subtrahend);

  evmc::bytes32 GetStorage(const evmc::address& address, const evmc::bytes32& key) const;
  void SetStorage(const evmc::address& address, const evmc::bytes32& key,
                  const evmc::bytes32& value);
};

}  // namespace silkworm::eth

#endif  // SILKWORM_ETH_INTRA_BLOCK_STATE_H_