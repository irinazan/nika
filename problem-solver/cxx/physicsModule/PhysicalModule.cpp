#include "physicalModule.hpp"

#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

#include "keynodes/Keynodes.hpp"
#include "agent/physicalConstantsAgent.hpp"
#include "utils/ActionUtils.hpp"

namespace physicalModule
{

SC_IMPLEMENT_MODULE(physicalModule)

sc_result physicalModule::InitializeImpl()
{

  if (!Keynodes::InitGlobal())
    return SC_RESULT_ERROR;

  SC_AGENT_REGISTER(physicalConstantsAgent);
  return SC_RESULT_OK;
}

sc_result physicalModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(physicalConstantsAgent);
  return SC_RESULT_OK;
}

}
