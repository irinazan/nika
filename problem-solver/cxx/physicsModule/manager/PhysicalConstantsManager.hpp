#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_memory.hpp"

namespace physicalModule
{

class physicalConstantsManager
{
public:
  explicit physicalConstantsManager(ScMemoryContext * context);

  ScAddrVector manage(ScAddrVector const & processParameters) const;

protected:
  ScMemoryContext * context;

  std::string getphysicalConstantName(ScAddr physicalConstantAddr) const;

  std::string getphysicalConstantValue(const std::string & physicalConstantName) const;

  ScAddrVector addTempLinkWithRelation(ScAddr addr, const std::string & linkContent, ScAddr relation) const;
};

}  // namespace physicalModule
