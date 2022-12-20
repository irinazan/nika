#include "physicalConstantsManager.hpp"

#include "sc-agents-common/utils/CommonUtils.hpp"

#include "keynodes/Keynodes.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace physicalModule
{
physicalConstantsManager::physicalConstantsManager(ScMemoryContext * context)
  : context(context)
{
}

ScAddrVector physicalConstantsManager::manage(ScAddrVector const & processParameters) const
{
  ScAddr addr = processParameters.at(0);

  std::string name = getphysicalConstantName(addr);
  std::string value = getphysicalConstantValue(name);
  ScAddrVector answerElements;

  const auto & valueElements = addTempLinkWithRelation(addr, value, Keynodes::nrel_physical_constant_value);
  answerElements.insert(answerElements.cend(), valueElements.cbegin(), valueElements.cend());

  return answerElements;
}

std::string physicalConstantsManager::getphysicalConstantName(ScAddr addr) const
{
  const auto & physicalConstantNameIterator = context->Iterator5(
      addr,
      ScType::EdgeDCommonConst,
      ScType::LinkConst,
      ScType::EdgeAccessConstPosPerm,
      Keynodes::nrel_physical_constant_name);
  if (physicalConstantNameIterator->Next())
  {
    return utils::CommonUtils::getLinkContent(context, physicalConstantNameIterator->Get(2));
  }
  else
  {
    SC_THROW_EXCEPTION(
        utils::ExceptionItemNotFound,
        "physicalConstantsManager: The value not found for " + context->HelperGetSystemIdtf(addr));
  }
}

std::string physicalConstantsManager::getphysicalConstantValue(const std::string & physicalConstantName) const
{
  std::ifstream in(physical_CONSTANTS_RESOURCES);
  json data = json::parse(in);

  for (json::iterator it = data.begin(); it != data.end(); ++it)
  {
    if (it.key() == physicalConstantName)
    {
      return it.value().get<std::string>();
    }
  }

  SC_THROW_EXCEPTION(utils::ExceptionParseError, "physicalConstantsManager: The value not found for " + physicalConstantName);
}

ScAddrVector physicalConstantsManager::addTempLinkWithRelation(
    ScAddr addr,
    const std::string & linkContent,
    ScAddr relation) const
{
  const auto & link = context->CreateLink(ScType::LinkConst);
  context->SetLinkContent(link, ScStreamConverter::StreamFromString(linkContent));
  const auto & edgeDCommon = context->CreateEdge(ScType::EdgeDCommonConst, addr, link);
  const auto & tempArc = context->CreateArc(ScType::EdgeAccessConstPosTemp, relation, edgeDCommon);
  return {link, relation, edgeDCommon, tempArc};
}

}  // namespace physicalModule