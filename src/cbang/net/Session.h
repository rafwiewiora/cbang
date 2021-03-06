/******************************************************************************\

          This file is part of the C! library.  A.K.A the cbang library.

              Copyright (c) 2003-2017, Cauldron Development LLC
                 Copyright (c) 2003-2017, Stanford University
                             All rights reserved.

        The C! library is free software: you can redistribute it and/or
        modify it under the terms of the GNU Lesser General Public License
        as published by the Free Software Foundation, either version 2.1 of
        the License, or (at your option) any later version.

        The C! library is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
        Lesser General Public License for more details.

        You should have received a copy of the GNU Lesser General Public
        License along with the C! library.  If not, see
        <http://www.gnu.org/licenses/>.

        In addition, BSD licensing may be granted on a case by case basis
        by written permission from at least one of the copyright holders.
        You may request written permission by emailing the authors.

                For information regarding this software email:
                               Joseph Coffland
                        joseph@cauldrondevelopment.com

\******************************************************************************/

#pragma once

#include <cbang/StdTypes.h>
#include <cbang/net/IPAddress.h>
#include <cbang/json/Serializable.h>
#include <cbang/json/Dict.h>
#include <cbang/time/Time.h>

#include <string>
#include <set>


namespace cb {
  class Session : public JSON::Dict {
    typedef std::set<std::string> groups_t;
    groups_t groups;

  public:
    Session(const JSON::Value &value) {read(value);}
    Session(const std::string &id, const IPAddress &ip);

    const std::string &getID() const {return getString("id");}
    void setID(const std::string &id) {insert("id", id);}

    uint64_t getCreationTime() const;
    void setCreationTime(uint64_t creationTime);

    void touch() {setLastUsed(Time::now());}
    uint64_t getLastUsed() const;
    void setLastUsed(uint64_t lastUsed);

    void setUser(const std::string &user) {insert("user", user);}
    const std::string &getUser() const {return getString("user");}

    IPAddress getIP() const {return getString("ip");}
    void setIP(const IPAddress &ip) {insert("ip", ip.toString());}
    void matchIP(const IPAddress &ip) const;

    typedef groups_t::const_iterator group_iterator;
    group_iterator groupsBegin() const {return groups.begin();}
    group_iterator groupsEnd() const {return groups.end();}
    bool hasGroup(const std::string &group) const;
    void addGroup(const std::string &group);

    void read(const JSON::Value &value);
    void write(JSON::Sink &sink) const {JSON::Dict::write(sink);}
  };
}
