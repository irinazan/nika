#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "Keynodes.generated.hpp"

namespace physicalModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:
  SC_PROPERTY(Keynode("nrel_physical_constant_name"), ForceCreate)
  static ScAddr nrel_physical_constant_name;

  SC_PROPERTY(Keynode("nrel_physical_constant_value"), ForceCreate)
  static ScAddr nrel_physical_constant_value;

  SC_PROPERTY(Keynode("rrel_entity"), ForceCreate)
  static ScAddr rrel_entity;

  SC_PROPERTY(Keynode("action_get_physical_constant_value"), ForceCreate)
  static ScAddr action_get_physical_constant_value;

  SC_PROPERTY(Keynode("concept_message_about_physical_constant"), ForceCreate)
  static ScAddr concept_message_about_physical_constant;
};

}