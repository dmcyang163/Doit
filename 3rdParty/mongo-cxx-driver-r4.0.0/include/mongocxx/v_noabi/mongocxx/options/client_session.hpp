// Copyright 2009-present MongoDB, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <mongocxx/client_session-fwd.hpp>
#include <mongocxx/options/client_session-fwd.hpp>

#include <bsoncxx/stdx/optional.hpp>

#include <mongocxx/options/transaction.hpp>

#include <mongocxx/config/prelude.hpp>

namespace mongocxx {
namespace v_noabi {
namespace options {

///
/// Class representing the optional arguments to mongocxx::v_noabi::client::start_session.
///
class client_session {
   public:
    ///
    /// Sets the causal_consistency option.
    ///
    /// If true (the default), each operation in the session will be causally ordered after the
    /// previous read or write operation. Set to false to disable causal consistency.
    ///
    /// Unacknowledged writes are not causally consistent. If you execute a write operation with an
    /// unacknowledged write concern (a mongocxx::v_noabi::write_concern with
    /// mongocxx::v_noabi::write_concern::acknowledge_level of @c k_unacknowledged), the write does
    /// not participate in causal consistency.
    ///
    /// @return
    ///   A reference to the object on which this member function is being called.  This facilitates
    ///   method chaining.
    ///
    /// @see
    /// - https://www.mongodb.com/docs/manual/core/read-isolation-consistency-recency/#causal-consistency
    ///
    MONGOCXX_ABI_EXPORT_CDECL(client_session&) causal_consistency(bool causal_consistency) noexcept;

    ///
    /// Gets the value of the causal_consistency option.
    ///
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bool) causal_consistency() const noexcept;

    ///
    /// Sets the read concern "snapshot" (not enabled by default).
    ///
    /// @return
    ///   A reference to the object on which this member function is being called.  This facilitates
    ///   method chaining.
    ///
    /// @see
    /// - https://www.mongodb.com/docs/manual/reference/read-concern-snapshot/
    ///
    /// @note Snapshot reads and causal consistency are mutually exclusive: only one or the
    /// other may be active at a time. Attempting to do so will result in an error being thrown
    /// by mongocxx::v_noabi::client::start_session.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(client_session&) snapshot(bool enable_snapshot_reads) noexcept;

    ///
    /// Gets the value of the snapshot_reads option.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bool) snapshot() const noexcept;

    ///
    /// Sets the default transaction options.
    ///
    /// @param default_transaction_opts
    ///   The default transaction options.
    ///
    /// @return
    ///   A reference to the object on which this member function is being called.  This facilitates
    ///   method chaining.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(client_session&)
    default_transaction_opts(transaction default_transaction_opts);

    ///
    /// Gets the current default transaction options.
    ///
    /// @return The default transaction options.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(const bsoncxx::v_noabi::stdx::optional<transaction>&)
    default_transaction_opts() const;

   private:
    friend ::mongocxx::v_noabi::client_session;

    bsoncxx::v_noabi::stdx::optional<bool> _causal_consistency;
    bsoncxx::v_noabi::stdx::optional<bool> _enable_snapshot_reads;

    bsoncxx::v_noabi::stdx::optional<transaction> _default_transaction_opts;
};

}  // namespace options
}  // namespace v_noabi
}  // namespace mongocxx

#include <mongocxx/config/postlude.hpp>

///
/// @file
/// Provides @ref mongocxx::v_noabi::options::client_session.
///
