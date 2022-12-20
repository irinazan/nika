#pragma once

#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include "sc-memory/kpm/sc_agent.hpp"

#include "physicalConstantsAgent.generated.hpp"
#include "manager/physicalConstantsManager.hpp"

namespace physicalModule
{

class physicalConstantsAgent : public ScAgent
{
  SC_CLASS(Agent, Event(scAgentsCommon::CoreKeynodes::question_initiated, ScEvent::Type::AddOutputEdge))

  SC_GENERATED_BODY();

private:
  std::unique_ptr<physicalConstantsManager> manager;

  bool checkActionClass(ScAddr const & actionAddr);

  void initFields();
};

}  // namespace physicalModule
