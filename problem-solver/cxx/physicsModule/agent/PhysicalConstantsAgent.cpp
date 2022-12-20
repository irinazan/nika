#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/GenerationUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"

#include "keynodes/Keynodes.hpp"
#include "utils/ActionUtils.hpp"

#include "physicalConstantsAgent.hpp"

namespace physicalModule
{
SC_AGENT_IMPLEMENTATION(physicalConstantsAgent)
{
  ScAddr actionAddr = otherAddr;
  if (!checkActionClass(actionAddr))
  {
    return SC_RESULT_OK;
  }

  SC_LOG_INFO("physicalConstantsAgent started");

  initFields();
  ScAddrVector answerElements;

  ScAddr const & messageAddr = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionAddr, scAgentsCommon::CoreKeynodes::rrel_1);
  if (!messageAddr.IsValid())
  {
    SC_LOG_ERROR("The message isn’t valid");
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, false);
    return SC_RESULT_ERROR;
  }

  if (!m_memoryCtx.HelperCheckEdge(
          Keynodes::concept_message_about_physical_constant, messageAddr, ScType::EdgeAccessConstPosPerm))
  {
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, ScAddrVector(), true);
    return SC_RESULT_OK;
  }

  ScAddr const & physicalConstantAddr = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, messageAddr, Keynodes::rrel_entity);
  if (!physicalConstantAddr.IsValid())
  {
    SC_LOG_ERROR("The physical constant isn’t valid");
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, false);
    return SC_RESULT_ERROR;
  }

  try
  {
    answerElements = manager->manage({physicalConstantAddr});
  }
  catch (utils::ScException & exception)
  {
    SC_LOG_ERROR(exception.Description());
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, answerElements, false);
    SC_LOG_DEBUG("physicalConstantsAgent finished");
    return SC_RESULT_ERROR;
  }

  utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, answerElements, true);
  SC_LOG_DEBUG("physicalConstantsAgent finished");
  return SC_RESULT_OK;
}

bool physicalConstantsAgent::checkActionClass(ScAddr const & actionAddr)
{
  return m_memoryCtx.HelperCheckEdge(
      Keynodes::action_get_physical_constant_value, actionAddr, ScType::EdgeAccessConstPosPerm);
}

void physicalConstantsAgent::initFields()
{
  this->manager = std::make_unique<physicalConstantsManager>(&m_memoryCtx);
}
}
